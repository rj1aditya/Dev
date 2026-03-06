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

class UUID 
{
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
        stringstream ss;
        ss << setfill('0') << setw(2) << hour << ":" << setw(2) << minute;
        return ss.str();
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
    map<int, mutex> seatLocks;

public:
    Show(shared_ptr<Movie> m, shared_ptr<Screen> screen, const LocalDate& date, const LocalTime& time)
        : movie(m), showDate(date), startTime(time) {
        for (auto seat : screen->getSeats()) {
            seatStatusMap[seat->getSeatId()] = SeatStatus::AVAILABLE;
        }
    }

    shared_ptr<Movie> getMovie() const {
        return movie;
    }

    LocalDate getShowDate() const {
        return showDate;
    }

    LocalTime getStartTime() const {
        return startTime;
    }

    bool lockSeats(const vector<int>& seatIds) {
        vector<int> sorted = seatIds;
        std::sort(sorted.begin(), sorted.end());

        vector<mutex*> acquiredLocks;

        try {
            // Phase 1: acquire all locks
            for (int seatId : sorted) {
                seatLocks[seatId].lock();
                acquiredLocks.push_back(&seatLocks[seatId]);
            }

            // Phase 2: validate availability
            for (int seatId : sorted) {
                if (seatStatusMap[seatId] != SeatStatus::AVAILABLE) {
                    for (auto lock : acquiredLocks) {
                        lock->unlock();
                    }
                    return false;
                }
            }

            // Phase 3: mark LOCKED
            for (int seatId : sorted) {
                seatStatusMap[seatId] = SeatStatus::LOCKED;
            }

            // Phase 4: release locks
            for (auto lock : acquiredLocks) {
                lock->unlock();
            }

            return true;
        } catch (...) {
            for (auto lock : acquiredLocks) {
                lock->unlock();
            }
            return false;
        }
    }

    void confirmSeats(const vector<int>& seatIds) {
        for (int seatId : seatIds) {
            seatStatusMap[seatId] = SeatStatus::BOOKED;
        }
    }

    void releaseSeats(const vector<int>& seatIds) {
        for (int seatId : seatIds) {
            seatStatusMap[seatId] = SeatStatus::AVAILABLE;
        }
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

public:
    void addTheatre(shared_ptr<Theatre> theatre) {
        cityTheatres[theatre->getCity()].push_back(theatre);
    }

    set<shared_ptr<Movie>> getMovies(City city, const LocalDate& date) {
        set<shared_ptr<Movie>> movies;
        auto it = cityTheatres.find(city);
        
        if (it == cityTheatres.end()) return movies;

        for (auto theatre : it->second) {
            for (auto screen : theatre->getScreens()) {
                for (auto show : screen->getShows(date)) {
                    movies.insert(show->getMovie());
                }
            }
        }
        return movies;
    }

    vector<shared_ptr<Theatre>> getTheatres(City city, shared_ptr<Movie> movie, const LocalDate& date) {
        vector<shared_ptr<Theatre>> result;
        auto it = cityTheatres.find(city);
        
        if (it == cityTheatres.end()) return result;

        for (auto theatre : it->second) {
            bool hasShow = false;
            for (auto screen : theatre->getScreens()) {
                for (auto show : screen->getShows(date)) {
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
        vector<shared_ptr<Show>> result;
r
        for (auto screen : theatre->getScreens()) {
            for (auto show : screen->getShows(date)) {
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

public:
    shared_ptr<Booking> book(shared_ptr<User> user, shared_ptr<Show> show, const vector<int>& seats) {
        if (!show->lockSeats(seats)) {
            throw runtime_error("Seat unavailable");
        }

        auto payment = make_shared<Payment>(PaymentStatus::SUCCESS);

        if (payment->getStatus() == PaymentStatus::SUCCESS) {
            show->confirmSeats(seats);
            auto booking = make_shared<Booking>(user, show, seats, payment);
            bookings[booking->getBookingId()] = booking;
            return booking;
        } else {
            show->releaseSeats(seats);
            throw runtime_error("Payment failed");
        }
    }

    shared_ptr<Booking> getBooking(const UUID& bookingId) {
        auto it = bookings.find(bookingId);
        if (it != bookings.end()) {
            return it->second;
        }
        return nullptr;
    }

    vector<shared_ptr<Booking>> getBookingsForUser(shared_ptr<User> user) {
        vector<shared_ptr<Booking>> result;
        for (auto& pair : bookings) {
            if (*pair.second->getUser() == *user) {
                result.push_back(pair.second);
            }
        }
        return result;
    }
};

// ============================================================
// CONTROLLER CLASSES
// ============================================================

class TheatreController {
private:
    shared_ptr<TheatreService> theatreService;

public:
    TheatreController() : theatreService(make_shared<TheatreService>()) {}

    void addTheatre(shared_ptr<Theatre> theatre) {
        theatreService->addTheatre(theatre);
    }

    set<shared_ptr<Movie>> getMovies(City city, const LocalDate& date) {
        return theatreService->getMovies(city, date);
    }

    vector<shared_ptr<Theatre>> getTheatres(City city, shared_ptr<Movie> movie, const LocalDate& date) {
        return theatreService->getTheatres(city, movie, date);
    }

    vector<shared_ptr<Show>> getShows(shared_ptr<Movie> movie, const LocalDate& date, shared_ptr<Theatre> theatre) {
        return theatreService->getShows(movie, date, theatre);
    }
};

class BookingController {
private:
    shared_ptr<BookingService> bookingService;

public:
    BookingController() : bookingService(make_shared<BookingService>()) {}

    shared_ptr<Booking> createBooking(shared_ptr<User> user, shared_ptr<Show> show, const vector<int>& seats) {
        return bookingService->book(user, show, seats);
    }

    shared_ptr<Booking> getBooking(const UUID& bookingId) {
        return bookingService->getBooking(bookingId);
    }

    vector<shared_ptr<Booking>> getBookingsForUser(shared_ptr<User> user) {
        return bookingService->getBookingsForUser(user);
    }
};

// ============================================================
// MAIN APPLICATION CLASS
// ============================================================

class BookMyShowApp {
private:
    shared_ptr<TheatreController> theatreController;
    shared_ptr<BookingController> bookingController;

public:
    BookMyShowApp() : theatreController(make_shared<TheatreController>()),
                      bookingController(make_shared<BookingController>()) {}

    void initialize() {
        /*
         * 1. Create Movies
         */
        auto baahubali = make_shared<Movie>("BAAHUBALI");
        auto avengers = make_shared<Movie>("AVENGERS");

        /*
         * 2. Create Theatre -> Screen -> Seats
         */
        auto inoxScreen1 = make_shared<Screen>(1, createSeats());
        auto inoxTheatreBangalore = make_shared<Theatre>(
            "INOX",
            City::BANGALORE,
            vector<shared_ptr<Screen>>{inoxScreen1}
        );

        auto pvrScreen1 = make_shared<Screen>(1, createSeats());
        auto pvrTheatreDelhi = make_shared<Theatre>(
            "PVR",
            City::DELHI,
            vector<shared_ptr<Screen>>{pvrScreen1}
        );

        theatreController->addTheatre(inoxTheatreBangalore);
        theatreController->addTheatre(pvrTheatreDelhi);

        /*
         * 3. Create Shows
         */
        auto inoxMorningShowToday = make_shared<Show>(
            baahubali,
            inoxScreen1,
            LocalDate::now(),
            LocalTime::of(8, 0)
        );

        auto inoxAfternoonShowToday = make_shared<Show>(
            baahubali,
            inoxScreen1,
            LocalDate::now(),
            LocalTime::of(15, 0)
        );

        auto inoxEveningShowToday = make_shared<Show>(
            avengers,
            inoxScreen1,
            LocalDate::now(),
            LocalTime::of(18, 0)
        );

        auto pvrMorningShowTomorrow = make_shared<Show>(
            baahubali,
            pvrScreen1,
            LocalDate::now().plusDays(1),
            LocalTime::of(9, 0)
        );

        // Attach shows to screens
        inoxScreen1->addShow(inoxMorningShowToday);
        inoxScreen1->addShow(inoxAfternoonShowToday);
        inoxScreen1->addShow(inoxEveningShowToday);
        pvrScreen1->addShow(pvrMorningShowTomorrow);
    }

    void userFlow() {
        // User enters system
        auto user = make_shared<User>("U1", "Shrayansh");

        cout << "User logged in: Shrayansh" << endl;

        // 1. User selects city
        City selectedCity = City::BANGALORE;
        cout << "Selected City: BANGALORE" << endl;

        // 2. For specific date, show movies running in city
        LocalDate selectedDate = LocalDate::now();
        cout << "Selected Date: " << selectedDate.toString() << endl;

        auto movies = theatreController->getMovies(selectedCity, selectedDate);
        cout << "Movies available:" << endl;
        for (auto movie : movies) {
            cout << " - " << movie->getName() << endl;
        }

        // 3. User selects movie
        if (movies.empty()) {
            cout << "No movies available" << endl;
            return;
        }

        auto selectedMovie = *movies.begin();
        cout << "Selected Movie: " << selectedMovie->getName() << endl;

        // 4. Show theatres and show times in city
        auto theatres = theatreController->getTheatres(selectedCity, selectedMovie, selectedDate);
        cout << "Theatres available:" << endl;
        for (auto theatre : theatres) {
            cout << " - " << theatre->getName() << endl;
        }

        if (theatres.empty()) {
            cout << "No theatres available" << endl;
            return;
        }

        // 6. User selects theatre
        auto selectedTheatre = theatres[0];
        cout << "Selected Theatre: " << selectedTheatre->getName() << endl;

        // 7. Show running shows for movie + date + theatre
        auto shows = theatreController->getShows(selectedMovie, selectedDate, selectedTheatre);

        cout << "Shows available:" << endl;
        for (auto show : shows) {
            cout << " - " << show->getStartTime().toString() << endl;
        }

        if (shows.empty()) {
            cout << "No shows available" << endl;
            return;
        }

        // 8. User selects show
        auto selectedShow = shows[0];
        cout << "Selected Show Time: " << selectedShow->getStartTime().toString() << endl;

        // 9. User selects seats
        vector<int> selectedSeats = {1, 2, 3};
        cout << "Selected Seats: ";
        for (int seat : selectedSeats) {
            cout << seat << " ";
        }
        cout << endl;

        // 10. Booking + Payment
        try {
            auto booking = bookingController->createBooking(user, selectedShow, selectedSeats);
            cout << "BOOKING SUCCESSFUL" << endl;
            cout << "Booking ID: " << booking->getBookingId().toString() << endl;
        } catch (const exception& e) {
            cout << "Booking failed: " << e.what() << endl;
        }
    }

    vector<shared_ptr<Seat>> createSeats() {
        vector<shared_ptr<Seat>> seats;
        for (int i = 1; i <= 20; i++) {
            seats.push_back(make_shared<Seat>(i, SeatCategory::SILVER));
        }
        return seats;
    }

    static void run() {
        BookMyShowApp app;
        app.initialize();
        app.userFlow();
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    try {
        BookMyShowApp::run();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
