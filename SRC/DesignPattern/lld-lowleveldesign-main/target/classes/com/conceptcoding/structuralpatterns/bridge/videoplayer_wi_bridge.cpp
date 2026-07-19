#include <iostream>
#include <memory>
#include <string>

using namespace std;

// ======== Implementor Interface =========
class VideoQuality {
public:
    // Virtual destructor for safe polymorphic delete
    virtual ~VideoQuality() = default;

    // Loads a title in a specific quality
    virtual void load(const string& title) = 0;
};

// ============ Concrete Implementors ==============
class SDQuality : public VideoQuality {
public:
    void load(const string& title) override {
        cout << "Streaming " << title << " in SD Quality\n";
    }
};

class HDQuality : public VideoQuality {
public:
    void load(const string& title) override {
        cout << "Streaming " << title << " in HD Quality\n";
    }
};

class UltraHDQuality : public VideoQuality {
public:
    void load(const string& title) override {
        cout << "Streaming " << title << " in 4K Ultra HD Quality\n";
    }
};

// ========== Abstraction ==========
class VideoPlayer {
protected:
    // Composition: the abstraction holds a reference to the implementor
    shared_ptr<VideoQuality> quality;

public:
    // Store the quality implementation
    explicit VideoPlayer(shared_ptr<VideoQuality> q) : quality(std::move(q)) {}

    // Virtual destructor
    virtual ~VideoPlayer() = default;

    // Platform decides how to play
    virtual void play(const string& title) = 0;
};

// =========== Refined Abstractions ==============
class WebPlayer : public VideoPlayer {
public:
    explicit WebPlayer(shared_ptr<VideoQuality> q) : VideoPlayer(std::move(q)) {}

    void play(const string& title) override {
        cout << "Web Platform:\n";
        quality->load(title);
    }
};

class MobilePlayer : public VideoPlayer {
public:
    explicit MobilePlayer(shared_ptr<VideoQuality> q) : VideoPlayer(std::move(q)) {}

    void play(const string& title) override {
        cout << "Mobile Platform:\n";
        quality->load(title);
    }
};

int main() {
    // Playing on Web with HD Quality
    WebPlayer player1(make_shared<HDQuality>());
    player1.play("Interstellar");

    cout << "\n";

    // Playing on Mobile with Ultra HD Quality
    MobilePlayer player2(make_shared<UltraHDQuality>());
    player2.play("Inception");

    cout << "\n";

    // Runtime flexibility: swap quality without changing platform class
    WebPlayer player3(make_shared<SDQuality>());
    player3.play("The Dark Knight");

    return 0;
}