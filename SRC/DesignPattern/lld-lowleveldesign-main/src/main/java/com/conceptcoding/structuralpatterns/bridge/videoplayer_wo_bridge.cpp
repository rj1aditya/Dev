#include <iostream>
#include <memory>
#include <string>

using namespace std;

// ======= Interface for play quality =======
class PlayQuality {
public:
    // Virtual destructor is important for safe polymorphic deletion
    virtual ~PlayQuality() = default;

    // Plays a given title
    virtual void play(const string& title) = 0;
};

// Each class here represents a combination of platform and quality

class WebHDPlayer : public PlayQuality {
public:
    void play(const string& title) override {
        // Web player plays in HD
        cout << "Web Player: Playing " << title << " in HD\n";
    }
};

class MobileHDPlayer : public PlayQuality {
public:
    void play(const string& title) override {
        // Mobile player plays in HD
        cout << "Mobile Player: Playing " << title << " in HD\n";
    }
};

class SmartTVUltraHDPlayer : public PlayQuality {
public:
    void play(const string& title) override {
        // Smart TV plays in Ultra HD
        cout << "Smart TV: Playing " << title << " in ultra HD\n";
    }
};

class Web4KPlayer : public PlayQuality {
public:
    void play(const string& title) override {
        // Web player plays in 4K
        cout << "Web Player: Playing " << title << " in 4K\n";
    }
};

int main() {
    // Client chooses one specific combined class
    unique_ptr<PlayQuality> player = make_unique<WebHDPlayer>();

    // Play a movie
    player->play("Interstellar");

    return 0;
}