#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <random>
#include <sstream>
#include <iomanip>
#include <thread>
#include <shared_mutex>
#include <atomic>
#include <functional>

using namespace std;

// ============================================================
// ENUMS
// ============================================================

enum class City {
    BANGALORE,
    DELHI
};

enum class SeatCategory {
    SILVER,
    GOLD,
    PLATINUM
};

enum class SeatStatus {
    AVAILABLE,
    LOCKED,
    BOOKED
};

enum class PaymentStatus {
    SUCCESS,
    FAILED
};

// ============================================================
// UTILITY CLASSES
// ============================================================

class UUID {
private:
    string id;

    static string generateRandomUUID() {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<int> dis(0, 15);

        stringstream ss;
        ss << hex;

        // Generate 8-4-4-4-12 format UUID
        for (int i = 0; i < 8; ++i) ss << dis(gen);
        ss << "-";
        for (int i = 0; i < 4; ++i) ss << dis(gen);
        ss << "-";
        for (int i = 0; i < 4; ++i) ss << dis(gen);
        ss << "-";
        for (int i = 0; i < 4; ++i) ss << dis(gen);
        ss << "-";
        for (int i = 0; i < 12; ++i) ss << dis(gen);

        return ss.str();
    }

public:
    UUID() : id(generateRandomUUID()) {}

    UUID(const string& id_str) : id(id_str) {}

    string toString() const {
        return id;
    }

    bool operator==(const UUID& other) const {
        return id == other.id;
    }

    bool operator<(const UUID& other) const {
        return id < other.id;
    }
};

class LocalDate {
private:
    int year, month, day;

public:
    LocalDate(int y, int m, int d) : year(y), month(m), day(d) {}

    static LocalDate now() {
        auto t = chrono::system_clock::now();
        auto tt = chrono::system_clock::to_time_t(t);
        auto tm = *localtime(&tt);
        return LocalDate(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    }

    LocalDate plusDays(int days) const {
        // Simple implementation - add days
        LocalDate result = *this;
        result.day += days;
        if (result.day > 28) {
            result.month += 1;
            result.day -= 28;
        }
        if (result.month > 12) {
            result.year += 1;
            result.month -= 12;
        }
        return result;
    }

    string toString() const {
        return to_string(year) + "-" + to_string(month) + "-" + to_string(day);
    }

    bool operator==(const LocalDate& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    bool operator<(const LocalDate& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

class LocalTime {
private:
    int hour, minute;

public:
    LocalTime(int h, int m) : hour(h), minute(m) {}

    static LocalTime of(int h, int m) {
        return LocalTime(h, m);
    }

    string toString() const {
        return (hour < 10 ? "0" : "") + to_string(hour) + ":" +
               (minute < 10 ? "0" : "") + to_string(minute);
    }
};

// ============================================================
// ENTITY CLASSES
// ============================================================

class Movie {
private:
    string name;

public:
    Movie(const string& n) : name(n) {}

    string getName() const {
        return name;
    }

    bool operator==(const Movie& other) const {
        return name == other.name;
    }

    bool operator<(const Movie& other) const {
        return name < other.name;
    }
};

class Seat {
private:
    int seatId;
    SeatCategory category;

public:
    Seat(int id, SeatCategory cat) : seatId(id), category(cat) {}

    int getSeatId() const {
        return seatId;
    }

    SeatCategory getCategory() const {
        return category;
    }
};

class Show;

class Screen {
private:
    int screenId;
    vector<shared_ptr<Seat>> seats;
    map<LocalDate, vector<shared_ptr<Show>>> showsByDate;

public:
    Screen(int id, vector<shared_ptr<Seat>> s) : screenId(id), seats(s) {}

    int getScreenId() const {
        return screenId;
    }

    vector<shared_ptr<Seat>> getSeats() const {
        return seats;
    }

    void addShow(shared_ptr<Show> show);

    vector<shared_ptr<Show>> getShows(const LocalDate& date) const {
        auto it = showsByDate.find(date);
        if (it != showsByDate.end()) {
            return it->second;
        }
        return vector<shared_ptr<Show>>();
    }
};

class Show {
    private:
    shared_ptr<Movie> movie;
    LocalDate showDate;
    LocalTime startTime;
    map<int, SeatStatus> seatStatusMap;
    map<int, mutex> seatLocks;  // Per-seat locks for fine-grained concurrency
    map<int, chrono::steady_clock::time_point> lockExpiryMap;
    mutable shared_mutex showMutex;  // For read/write access to the show

    function<void(const vector<int>&)> onAutoReleaseCallback;
    atomic<bool> stopExpiryThread{false};
    thread expiryThread;

    void expiryLoop(int intervalSeconds) {
        while (!stopExpiryThread.load()) {
            this_thread::sleep_for(chrono::seconds(intervalSeconds));
            expireOldLocks();
        }
    }

public:
    Show(shared_ptr<Movie> m, shared_ptr<Screen> screen, const LocalDate& date, const LocalTime& time)
        : movie(m), showDate(date), startTime(time) {
        // Pre-initialize all seat statuses and locks to avoid race conditions
        for (auto& seat : screen->getSeats()) {
            int id = seat->getSeatId();
            seatStatusMap[id] = SeatStatus::AVAILABLE;
            seatLocks[id];  // Default construct mutex
        }
        expiryThread = thread(&Show::expiryLoop, this, 2);
    }

    ~Show() {
        stopExpiryThread.store(true);
        if (expiryThread.joinable()) {
            expiryThread.join();
        }
    }

    void setAutoReleaseCallback(function<void(const vector<int>&)> callback) {
        unique_lock<shared_mutex> lock(showMutex);
        onAutoReleaseCallback = move(callback);
    }

    shared_ptr<Movie> getMovie() const {
        shared_lock<shared_mutex> lock(showMutex);
        return movie;
    }

    LocalDate getShowDate() const {
        shared_lock<shared_mutex> lock(showMutex);
        return showDate;
    }

    LocalTime getStartTime() const {
        shared_lock<shared_mutex> lock(showMutex);
        return startTime;
    }

    // Thread-safe seat locking with deadlock prevention
    bool lockSeats(const vector<int>& seatIds, int ttlSeconds = 120) {
        if (seatIds.empty()) return true;

        vector<int> sorted = seatIds;
        sort(sorted.begin(), sorted.end());  // Consistent lock order

        vector<unique_lock<mutex>> locks;
        locks.reserve(sorted.size());

        // Acquire all per-seat locks in sorted order
        for (int seatId : sorted) {
            auto it = seatLocks.find(seatId);
            if (it == seatLocks.end()) {
                return false;
            }
            locks.emplace_back(it->second);
        }

        unique_lock<shared_mutex> writeLock(showMutex);

        // Validate all seats are available
        for (int seatId : sorted) {
            if (seatStatusMap[seatId] != SeatStatus::AVAILABLE) {
                return false;
            }
        }

        auto expiryTime = chrono::steady_clock::now() + chrono::seconds(ttlSeconds);
        for (int seatId : sorted) {
            seatStatusMap[seatId] = SeatStatus::LOCKED;
            lockExpiryMap[seatId] = expiryTime;
        }

        return true;
    }

    // Confirm booking - assumes seats are already locked
    void confirmSeats(const vector<int>& seatIds) {
        vector<int> sorted = seatIds;
        sort(sorted.begin(), sorted.end());

        vector<unique_lock<mutex>> locks;
        locks.reserve(sorted.size());
        for (int seatId : sorted) {
            locks.emplace_back(seatLocks[seatId]);
        }

        unique_lock<shared_mutex> writeLock(showMutex);
        for (int seatId : sorted) {
            seatStatusMap[seatId] = SeatStatus::BOOKED;
            lockExpiryMap.erase(seatId);
        }
    }

    // Release seats back to available
    void releaseSeats(const vector<int>& seatIds) {
        vector<int> sorted = seatIds;
        sort(sorted.begin(), sorted.end());

        vector<unique_lock<mutex>> locks;
        locks.reserve(sorted.size());
        for (int seatId : sorted) {
            locks.emplace_back(seatLocks[seatId]);
        }

        unique_lock<shared_mutex> writeLock(showMutex);
        for (int seatId : sorted) {
            seatStatusMap[seatId] = SeatStatus::AVAILABLE;
            lockExpiryMap.erase(seatId);
        }
    }

    void expireOldLocks() {
        vector<int> released;
        auto now = chrono::steady_clock::now();

        {
            unique_lock<shared_mutex> lock(showMutex);
            for (auto& [seatId, status] : seatStatusMap) {
                if (status == SeatStatus::LOCKED) {
                    auto it = lockExpiryMap.find(seatId);
                    if (it != lockExpiryMap.end() && it->second <= now) {
                        status = SeatStatus::AVAILABLE;
                        released.push_back(seatId);
                        lockExpiryMap.erase(it);
                    }
                }
            }
        }

        if (!released.empty() && onAutoReleaseCallback) {
            onAutoReleaseCallback(released);
        }
    }

    // Get current seat status (read-only)
    SeatStatus getSeatStatus(int seatId) const {
        shared_lock<shared_mutex> lock(showMutex);
        auto it = seatStatusMap.find(seatId);
        return (it != seatStatusMap.end()) ? it->second : SeatStatus::AVAILABLE;
    }
};

void Screen::addShow(shared_ptr<Show> show) {
    showsByDate[show->getShowDate()].push_back(show);
}

class User {
private:
    string userId;
    string name;

public:
    User(const string& id, const string& n) : userId(id), name(n) {}

    string getUserId() const {
        return userId;
    }

    string getName() const {
        return name;
    }

    bool operator==(const User& other) const {
        return userId == other.userId;
    }
};

class Payment {
private:
    UUID paymentId;
    PaymentStatus status;

public:
    Payment(PaymentStatus s) : status(s) {}

    UUID getPaymentId() const {
        return paymentId;
    }

    PaymentStatus getStatus() const {
        return status;
    }
};

class Booking {
private:
    UUID bookingId;
    shared_ptr<User> user;
    shared_ptr<Show> show;
    vector<int> seats;
    shared_ptr<Payment> payment;

public:
    Booking(shared_ptr<User> u, shared_ptr<Show> s, const vector<int>& st, shared_ptr<Payment> p)
        : user(u), show(s), seats(st), payment(p) {}

    UUID getBookingId() const {
        return bookingId;
    }

    shared_ptr<User> getUser() const {
        return user;
    }

    shared_ptr<Show> getShow() const {
        return show;
    }

    vector<int> getSeats() const {
        return seats;
    }

    shared_ptr<Payment> getPayment() const {
        return payment;
    }
};

class Theatre {
private:
    string name;
    City city;
    vector<shared_ptr<Screen>> screens;

public:
    Theatre(const string& n, City c, vector<shared_ptr<Screen>> s)
        : name(n), city(c), screens(s) {}

    string getName() const {
        return name;
    }

    City getCity() const {
        return city;
    }

    vector<shared_ptr<Screen>> getScreens() const {
        return screens;
    }

    bool operator==(const Theatre& other) const {
        return name == other.name && city == other.city;
    }
};

// ============================================================
// SERVICE CLASSES
// ============================================================

class TheatreService {
private:
    map<City, vector<shared_ptr<Theatre>>> cityTheatres;
    mutable shared_mutex serviceMutex;

public:
    void addTheatre(shared_ptr<Theatre> theatre) {
        unique_lock<shared_mutex> lock(serviceMutex);
        cityTheatres[theatre->getCity()].push_back(theatre);
    }

    set<shared_ptr<Movie>> getMovies(City city, const LocalDate& date) {
        shared_lock<shared_mutex> lock(serviceMutex);
        set<shared_ptr<Movie>> movies;
        auto it = cityTheatres.find(city);

        if (it == cityTheatres.end()) return movies;

        for (auto& theatre : it->second) {
            for (auto& screen : theatre->getScreens()) {
                for (auto& show : screen->getShows(date)) {
                    movies.insert(show->getMovie());
                }
            }
        }
        return movies;
    }

    vector<shared_ptr<Theatre>> getTheatres(City city, shared_ptr<Movie> movie, const LocalDate& date) {
        shared_lock<shared_mutex> lock(serviceMutex);
        vector<shared_ptr<Theatre>> result;
        auto it = cityTheatres.find(city);

        if (it == cityTheatres.end()) return result;

        for (auto& theatre : it->second) {
            bool hasShow = false;
            for (auto& screen : theatre->getScreens()) {
                for (auto& show : screen->getShows(date)) {
                    if (*show->getMovie() == *movie) {
                        hasShow = true;
                        break;
                    }
                }
                if (hasShow) break;
            }
            if (hasShow) {
                result.push_back(theatre);
            }
        }
        return result;
    }

    vector<shared_ptr<Show>> getShows(shared_ptr<Movie> movie, const LocalDate& date, shared_ptr<Theatre> theatre) {
        shared_lock<shared_mutex> lock(serviceMutex);
        vector<shared_ptr<Show>> result;

        for (auto& screen : theatre->getScreens()) {
            for (auto& show : screen->getShows(date)) {
                if (*show->getMovie() == *movie) {
                    result.push_back(show);
                }
            }
        }
        return result;
    }
};

class BookingService {
private:
    map<UUID, shared_ptr<Booking>> bookings;
    mutable shared_mutex bookingMutex;

public:
    shared_ptr<Booking> book(shared_ptr<User> user, shared_ptr<Show> show, const vector<int>& seats) {
        // Expire stale locked seats before trying to lock requested seats
        show->expireOldLocks();

        // Attempt to lock seats with TTL (in seconds)
        if (!show->lockSeats(seats, 30)) {
            throw runtime_error("Seats unavailable or invalid");
        }

        try {
            // Simulate payment processing
            auto payment = make_shared<Payment>(PaymentStatus::SUCCESS);

            if (payment->getStatus() == PaymentStatus::SUCCESS) {
                show->confirmSeats(seats);
                auto booking = make_shared<Booking>(user, show, seats, payment);
                {
                    unique_lock<shared_mutex> lock(bookingMutex);
                    bookings[booking->getBookingId()] = booking;
                }
                return booking;
            } else {
                show->releaseSeats(seats);
                throw runtime_error("Payment failed");
            }
        } catch (const exception& e) {
            // Release seats on any failure
            show->releaseSeats(seats);
            throw;
        }
    }

    shared_ptr<Booking> getBooking(const UUID& bookingId) {
        shared_lock<shared_mutex> lock(bookingMutex);
        auto it = bookings.find(bookingId);
        if (it != bookings.end()) {
            return it->second;
        }
        return nullptr;
    }
};

// ============================================================
// MAIN FUNCTION (Example Usage)
// ============================================================

int main() {
    // Create sample data
    auto movie = make_shared<Movie>("Avengers");
    auto user = make_shared<User>("user1", "John Doe");

    // Create seats
    vector<shared_ptr<Seat>> seats = {
        make_shared<Seat>(1, SeatCategory::SILVER),
        make_shared<Seat>(2, SeatCategory::GOLD),
        make_shared<Seat>(3, SeatCategory::PLATINUM)
    };

    // Create screen and show
    auto screen = make_shared<Screen>(1, seats);
    auto show = make_shared<Show>(movie, screen, LocalDate::now(), LocalTime::of(18, 0));
    show->setAutoReleaseCallback([](const vector<int>& releasedSeats){
        cout << "Auto-released seats: ";
        for (int id : releasedSeats) cout << id << " ";
        cout << "\n";
    });
    screen->addShow(show);

    // Create theatre and services
    vector<shared_ptr<Screen>> screens = {screen};
    auto theatre = make_shared<Theatre>("PVR", City::BANGALORE, screens);

    TheatreService theatreService;
    theatreService.addTheatre(theatre);

    BookingService bookingService;

    try {
        // Attempt booking
        vector<int> requestedSeats = {1, 2};
        auto booking = bookingService.book(user, show, requestedSeats);
        cout << "Booking successful: " << booking->getBookingId().toString() << endl;
    } catch (const exception& e) {
        cout << "Booking failed: " << e.what() << endl;
    }

    return 0;
}
