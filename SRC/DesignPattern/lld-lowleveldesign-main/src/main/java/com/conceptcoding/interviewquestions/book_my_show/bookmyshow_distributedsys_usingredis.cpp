// BookMyShowRedis.cpp
// Build with: g++ -std=c++20 BookMyShowRedis.cpp -o BookMyShowRedis -lcpp_redis -ltacopie -pthread

#include <cpp_redis/cpp_redis>
#include <tacopie/tacopie>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ------------------------------------------------------------
// Simple UUID / token helper (not RFC4122, but fine for locking)
// ------------------------------------------------------------
static string makeRandomToken() {
    static thread_local mt19937_64 gen{random_device{}()};
    uniform_int_distribution<uint64_t> dist;
    uint64_t v = dist(gen);
    stringstream ss;
    ss << hex << v;
    return ss.str();
}

// ------------------------------------------------------------
// Distributed lock helper (Redis)
// ------------------------------------------------------------
class RedisDistributedLock {
public:
    RedisDistributedLock(cpp_redis::client& redis,
                         string key,
                         chrono::milliseconds ttl)
        : _redis(redis), _key(move(key)), _ttl(ttl), _token(makeRandomToken()) {}

    // Try acquire lock (returns true if acquired)
    bool tryLock() {
        // SET key token NX PX <ttl>
        _redis.set(_key, _token,
                   cpp_redis::client::set_options::nx().px(_ttl.count()));
        _redis.sync_commit();

        auto reply = _redis.get_reply();
        if (!reply.is_string()) return false;
        return reply.as_string() == "OK";
    }

    // Release lock safely; returns true if released
    bool unlock() {
        // Lua: if redis.call('GET', KEYS[1]) == ARGV[1] then return redis.call('DEL', KEYS[1]) else return 0 end
        static const string lua = R"(
            if redis.call('GET', KEYS[1]) == ARGV[1] then
                return redis.call('DEL', KEYS[1])
            else
                return 0
            end
        )";

        _redis.eval(lua, {_key}, {_token});
        _redis.sync_commit();

        auto reply = _redis.get_reply();
        return reply.is_integer() && reply.as_integer() == 1;
    }

private:
    cpp_redis::client& _redis;
    string _key;
    string _token;
    chrono::milliseconds _ttl;
};

// ------------------------------------------------------------
// Domain / Entities
// ------------------------------------------------------------
enum class City { BANGALORE, DELHI };
enum class SeatCategory { SILVER, GOLD, PLATINUM };
enum class SeatStatus { AVAILABLE, LOCKED, BOOKED };
enum class PaymentStatus { SUCCESS, FAILED };

class Seat {
public:
    Seat(int id, SeatCategory cat) : seatId(id), category(cat) {}
    int getSeatId() const { return seatId; }
    SeatCategory getCategory() const { return category; }

private:
    int seatId;
    SeatCategory category;
};

class Movie {
public:
    Movie(string name) : name_(move(name)) {}
    const string& getName() const { return name_; }

private:
    string name_;
};

class Show {
public:
    Show(string showId,
         shared_ptr<Movie> movie,
         const vector<shared_ptr<Seat>>& seats,
         cpp_redis::client& redisClient,
         const string& redisPrefix = "seat_lock")
        : showId_(move(showId)),
          movie_(move(movie)),
          redisClient_(redisClient),
          redisPrefix_(redisPrefix) {
        for (auto& seat : seats) {
            seatStatusMap_[seat->getSeatId()] = SeatStatus::AVAILABLE;
        }
    }

    // Distributed locking across servers via Redis
    bool lockSeats(const vector<int>& seatIds) {
        if (seatIds.empty()) return true;

        vector<int> sorted = seatIds;
        sort(sorted.begin(), sorted.end());

        // Try to acquire all locks in sorted order
        vector<unique_ptr<RedisDistributedLock>> locks;
        locks.reserve(sorted.size());

        for (int seatId : sorted) {
            string key = makeRedisKey(showId_, seatId);
            locks.emplace_back(make_unique<RedisDistributedLock>(
                redisClient_, move(key), chrono::milliseconds(5000)));
        }

        const int maxAttempts = 5;
        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            bool ok = true;
            for (auto& lock : locks) {
                if (!lock->tryLock()) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                // Mark local state as LOCKED
                for (int seatId : sorted) {
                    seatStatusMap_[seatId] = SeatStatus::LOCKED;
                }
                // Keep locks alive until we release() or confirm()
                activeLocks_.swap(locks);
                return true;
            }

            // Release partial locks and retry with backoff
            for (auto& lock : locks) {
                if (lock) lock->unlock();
            }
            this_thread::sleep_for(chrono::milliseconds(50 + attempt * 30));
        }

        return false;
    }

    void confirmSeats(const vector<int>& seatIds) {
        for (int seatId : seatIds) {
            seatStatusMap_[seatId] = SeatStatus::BOOKED;
        }
        releaseLocks();
    }

    void releaseSeats(const vector<int>& seatIds) {
        for (int seatId : seatIds) {
            seatStatusMap_[seatId] = SeatStatus::AVAILABLE;
        }
        releaseLocks();
    }

    SeatStatus getSeatStatus(int seatId) const {
        auto it = seatStatusMap_.find(seatId);
        if (it == seatStatusMap_.end()) return SeatStatus::AVAILABLE;
        return it->second;
    }

private:
    string makeRedisKey(const string& showId, int seatId) const {
        return redisPrefix_ + ":" + showId + ":" + to_string(seatId);
    }

    void releaseLocks() {
        for (auto& lock : activeLocks_) {
            if (lock) lock->unlock();
        }
        activeLocks_.clear();
    }

    string showId_;
    shared_ptr<Movie> movie_;
    map<int, SeatStatus> seatStatusMap_;
    cpp_redis::client& redisClient_;
    string redisPrefix_;
    vector<unique_ptr<RedisDistributedLock>> activeLocks_;
};

class Booking {
public:
    Booking(string id, shared_ptr<Show> show, vector<int> seats)
        : bookingId_(move(id)), show_(move(show)), seats_(move(seats)) {}
    const string& getId() const { return bookingId_; }
    const vector<int>& getSeats() const { return seats_; }

private:
    string bookingId_;
    shared_ptr<Show> show_;
    vector<int> seats_;
};

class BookingService {
public:
    shared_ptr<Booking> book(shared_ptr<Show> show, const vector<int>& seats) {
        if (!show->lockSeats(seats)) {
            throw runtime_error("Failed to acquire locks for seats");
        }

        // Simulate payment
        bool paymentOK = true;
        if (!paymentOK) {
            show->releaseSeats(seats);
            throw runtime_error("Payment failed");
        }

        show->confirmSeats(seats);
        auto booking = make_shared<Booking>(makeRandomToken(), show, seats);
        bookings_[booking->getId()] = booking;
        return booking;
    }

private:
    map<string, shared_ptr<Booking>> bookings_;
};

// ------------------------------------------------------------
// Example usage
// ------------------------------------------------------------
int main() {
    // Connect to Redis on the remote server
    cpp_redis::client redis;
    redis.connect("192.12.1.1", 6379,
                  [](auto& host, auto port, auto state) {
                      if (state == cpp_redis::connect_state::ok) {
                          cerr << "Connected to Redis " << host << ":" << port << "\n";
                      } else {
                          cerr << "Redis connect failed\n";
                      }
                  });

    // Setup domain
    auto movie = make_shared<Movie>("Avengers");
    vector<shared_ptr<Seat>> seats;
    for (int i = 1; i <= 10; ++i) {
        seats.push_back(make_shared<Seat>(i, SeatCategory::SILVER));
    }

    auto show = make_shared<Show>("show-1", movie, seats, redis);

    BookingService bookingService;
    try {
        auto booking = bookingService.book(show, vector<int>{1, 2, 3});
        cout << "Booking success: " << booking->getId() << "\n";
    } catch (const exception& ex) {
        cout << "Booking failed: " << ex.what() << "\n";
    }

    return 0;
}