#include <iostream>
#include <string>

using namespace std;

// Service class responsible for handling payments
class PaymentService {
public:
    void makePayment(const string& accountId, double amount) {
        cout << "Payment of \u20B9" << amount << " successful for account " << accountId << "\n";
    }
};

// Service class responsible for reserving seats
class SeatReservationService {
public:
    void reserveSeat(const string& movieId, const string& seatNumber) {
        cout << "Seat " << seatNumber << " reserved for movie " << movieId << "\n";
    }
};

// Service class responsible for sending notifications
class NotificationService {
public:
    void sendBookingConfirmation(const string& userEmail) {
        cout << "Booking confirmation sent to " << userEmail << "\n";
    }
};

// Service class for managing loyalty/reward points
class LoyaltyPointsService {
public:
    void addPoints(const string& accountId, int points) {
        cout << points << " loyalty points added to account " << accountId << "\n";
    }
};

// Service class for generating movie tickets
class TicketService {
public:
    void generateTicket(const string& movieId, const string& seatNumber) {
        cout << "Ticket generated for movie " << movieId << ", Seat: " << seatNumber << "\n";
    }
};

// ========== The MovieBookingFacade class ==============
class MovieBookingFacade {
private:
    // The facade owns the workflow and coordinates all subsystems
    PaymentService paymentService;
    SeatReservationService seatReservationService;
    NotificationService notificationService;
    LoyaltyPointsService loyaltyPointsService;
    TicketService ticketService;

public:
    // Constructor exists, but services are already safely initialized by default
    MovieBookingFacade() = default;

    // Method providing a simplified interface for booking a movie ticket
    void bookMovieTicket(
        const string& accountId,
        const string& movieId,
        const string& seatNumber,
        const string& userEmail,
        double amount
    ) {
        // Step 1: Make payment
        paymentService.makePayment(accountId, amount);

        // Step 2: Reserve seat
        seatReservationService.reserveSeat(movieId, seatNumber);

        // Step 3: Generate ticket
        ticketService.generateTicket(movieId, seatNumber);

        // Step 4: Add loyalty points
        loyaltyPointsService.addPoints(accountId, 50);

        // Step 5: Send confirmation
        notificationService.sendBookingConfirmation(userEmail);

        // Indicate successful completion of the entire booking process
        cout << "Movie ticket booking completed successfully!" << "\n";
    }
};

int main() {
    // Booking a movie ticket using the facade
    MovieBookingFacade movieBookingFacade;

    // Client calls a single high-level API instead of coordinating multiple services
    movieBookingFacade.bookMovieTicket("user123", "movie456", "A10", "user@example.com", 500);

    return 0;
}