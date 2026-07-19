#include<iostream>
#include<vector>
#include<string>
using namespace std;


class playListIterator{
public:
    virtual ~playListIterator() = default;
    virtual bool hasNext() const = 0;
    virtual Video next() = 0;
};

class YoutubeplayListIterator : public playListIterator{
public:
    YoutubeplayListIterator(const vector<Video>& videos): videos(videos), index(0) {}

    bool hasNext() const override {
        return index < videos.size();
    }

    Video next() override {
        if (hasNext()) {
            return videos[index++];
        }
        throw out_of_range("No more videos in the playlist.");
    }
};

class Video{
public:
    Video(string name):name(name){}
    string getName() const { return name; }
};


class YoutTubePlaylist{
public:
    void addVideo(const Video& video){
        videos.push_back(video);
    }


    playListIterator createIterator() const {
        return new YoutubeplayListIterator(videos);
    }

    private:
    vector<Video> videos;
};

int main(){
    YoutTubePlaylist playlist;
    playlist.addVideo(Video("C++ Design Patterns"));
    playlist.addVideo(Video("Iterator Pattern in C++"));
    return 0;
}   





