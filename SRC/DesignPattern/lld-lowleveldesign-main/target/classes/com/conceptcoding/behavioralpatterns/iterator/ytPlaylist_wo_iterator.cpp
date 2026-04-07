#include <vector>
#include<iostream>

using namespace std;

// A simple Video class
class Video {
    string title;

public:
    Video(string t) : title(t) {}

    string getTitle() const {
        return title;
    }
};

// YouTubePlaylist class
class YouTubePlaylist {
    vector<Video> videos;

public:
    void addVideo(const Video& video) {
        videos.push_back(video);
    }

    vector<Video>& getVideos() {
        return videos;
    }
};

// CLient Code
int main() {
    YouTubePlaylist playlist;
    playlist.addVideo(Video("LLD Tutorial"));
    playlist.addVideo(Video("System Design Basics"));

    // Iterate and print video titles
    for (const Video& v : playlist.getVideos()) {
        cout << v.getTitle() << endl;
    }

    return 0;
}
