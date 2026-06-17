#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <clocale>
#include <list> 

using namespace std;

class Device{
    public: 
    string name;
    string creator;
    int year;
    Device(string n, string c, int y) : name(n), creator(c), year(y) {}

    void showInfo(const Device& device) {
    cout << "Name: " << device.name << endl;
    cout << "Creator: " << device.creator << endl;
    cout << "Year: " << device.year << endl;
}
};

class MediaPlayer{
    public:
    list<string> SongFormat;
    MediaPlayer(string sf) { SongFormat.push_back(sf); }
    void showInfo(const MediaPlayer& player) {
    cout << "Song Format: ";
    for (const auto& format : player.SongFormat) {
        cout << format << " ";
    }
    cout << endl;
    }

};

class SmartTV : public Device, public MediaPlayer {
    public:
    int screenSize;
    string resolution;
    SmartTV(string n, string c, int y, string sf, int ss, string res) : Device(n, c, y), MediaPlayer(sf), screenSize(ss), resolution(res) {}
    void showInfo() {
        Device::showInfo(*this);
        MediaPlayer::showInfo(*this);
    }
    friend void Display(const SmartTV& tv){
        if (tv.screenSize <32) {
            cout << "Screen size is too small for a Smart TV." << endl;
        } else {
            cout << "Screen size is suitable for a Smart TV." << endl;
        }
    }
};

int main()
{
SmartTV myTV("Samsung Smart TV", "Samsung", 2020, "MP3", 40, "4K");
myTV.showInfo();
Display(myTV);
return 0;
}