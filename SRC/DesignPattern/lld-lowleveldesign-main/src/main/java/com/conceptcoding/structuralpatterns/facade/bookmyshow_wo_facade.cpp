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

int main() {
    // Booking a movie ticket manually (without a facade)

    // Step 1: Make payment
    PaymentService paymentService;
    paymentService.makePayment("user123", 500);

    // Step 2: Reserve seat
    SeatReservationService seatReservationService;
    seatReservationService.reserveSeat("movie456", "A10");

    // Step 3: Send booking confirmation via email
    NotificationService notificationService;
    notificationService.sendBookingConfirmation("user@example.com");

    // Step 4: Add loyalty points to user's account
    LoyaltyPointsService loyaltyPointsService;
    loyaltyPointsService.addPoints("user123", 50);

    // Step 5: Generate the ticket
    TicketService ticketService;
    ticketService.generateTicket("movie456", "A10");

    return 0;
}