#include <bits/stdc++.h>
using namespace std;

// ========== Video class representing a single video ==========
class Video {
    string title;

public:
    Video(const string& t) : title(t) {}

    string getTitle() const {
        return title;
    }
};

// ================ Playlist interface ================
// (acts as a contract for collections that are iterable) 
class PlaylistIterator;

class Playlist {
public:
    virtual PlaylistIterator* createIterator() = 0;
    virtual ~Playlist() = default;
};

// ========== Iterator interface (defines traversal contract) ==========
class PlaylistIterator {
public:
    virtual bool hasNext() = 0;        // Checks if more elements are left
    virtual Video* next() = 0;         // Returns the next element
    virtual ~PlaylistIterator() = default;
};

// ========== Concrete Iterator class ==========
// Implements the actual logic for traversing the YouTubePlaylist
class YouTubePlaylistIterator : public PlaylistIterator {
    vector<Video>* videos;
    size_t position;

public:
    // Constructor takes the collection to iterate over
    YouTubePlaylistIterator(vector<Video>* vids) {
        videos = vids;
        position = 0;
    }

    // Check if more videos are left
    bool hasNext() override {
        return position < videos->size();
    }

    // Return the next video in the playlist
    Video* next() override {
        return hasNext() ? &(*videos)[position++] : nullptr;
    }
};

// ========== YouTubePlaylist class (Aggregate) ==========
// Implements Playlist to guarantee it provides an iterator
class YouTubePlaylist : public Playlist {
    vector<Video> videos;

public:
    // Method to add a video to the playlist
    void addVideo(const Video& video) {
        videos.push_back(video);
    }

    // Instead of exposing the list, return an iterator
    PlaylistIterator* createIterator() override {
        return new YouTubePlaylistIterator(&videos);
    }
};

// ========== Main method (Client code) ==========
int main() {
    // Create a playlist and add videos to it
    YouTubePlaylist playlist;
    playlist.addVideo(Video("LLD Tutorial"));
    playlist.addVideo(Video("System Design Basics"));

    // Client simply asks for an iterator — no access to internal data structure
    PlaylistIterator* iterator = playlist.createIterator();

    // Iterate through the playlist using the provided interface
    while (iterator->hasNext()) {
        cout << iterator->next()->getTitle() << endl;
    }

    delete iterator;
    return 0;
}
