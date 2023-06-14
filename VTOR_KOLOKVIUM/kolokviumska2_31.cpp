#include <iostream>
#include <cstring>

using namespace std;

enum format {
    mp3, wav, ogg, flac
};

enum compression {
    x264, Theora, AV1
};

class MediaSegment {
protected:
    char name[100];
    char author[100];
    int duration;
    int sizeInMB;
public:
    MediaSegment(const char *name = "", const char *author = "", int duration = 0, int sizeInMb = 0) : duration(
            duration),
                                                                                                       sizeInMB(
                                                                                                               sizeInMb) {
        strcpy(this->name, name);
        strcpy(this->author, author);
    }

    virtual double price() = 0;
};

class AudioRecording : virtual public MediaSegment {
protected:
    format f;
    int short channels;
public:
    AudioRecording(const char *name = "", const char *author = "", int duration = 0, int sizeInMb = 0, int f = 0,
                   short channels = 0) : MediaSegment(name,
                                                      author,
                                                      duration,
                                                      sizeInMb) {
        this->f = (format) f;
        this->channels = channels;
    }

    virtual double price() {
        double sum = duration * channels;
        if (f == 3) {
            sum += sum * 0.5;
        }
        return sum;
    }

    friend ostream &operator<<(ostream &os, AudioRecording &recording) {
        os << recording.name << " - " << recording.author << " - " << recording.duration << " - " << recording.sizeInMB
           << " - " << recording.price() << endl;
        return os;
    }

};

class VideoRecording : virtual public MediaSegment {
protected:
    int width;
    compression c;
public:
    VideoRecording(const char *name = "", const char *author = "", int duration = 0, int sizeInMb = 0, int width = 0,
                   int c = 0) : MediaSegment(name, author,
                                             duration,
                                             sizeInMb) {
        this->width = width;
        this->c - (compression) c;
    }

    virtual double price() {
        double sum = 0;
        if (width <= 1920) {
            sum = duration * 100;
        } else {
            sum = duration * 170;
        }
        if (c == 0) {
            sum *= 1.5;
        } else if (c == 1) {
            sum *= 0.9;
        }
        return sum;
    }

    friend ostream &operator<<(ostream &os, VideoRecording &recording) {
        os << recording.name << " - " << recording.author << " - " << recording.duration << " - " << recording.sizeInMB
           << " - " << recording.width << " - " << recording.price() << endl;
        return os;
    }
};

class MusicVideo : public AudioRecording, public VideoRecording {
private:
    char date[9];
public:
    MusicVideo(const char *name = "", const char *author = "", int duration = 0, int sizeInMb = 0, int f = 0,
               short channels = 0, int width = 0, int c = 0,
               const char *date = "") : MediaSegment(name, author, duration, sizeInMb),
                                        AudioRecording(name, author, duration,
                                                       sizeInMb, f, channels),
                                        VideoRecording(name, author, duration,
                                                       sizeInMb, width, c) {

        strcpy(this->date, date);
    }

    double price() {
        double sum = AudioRecording::price() + VideoRecording::price();
        if (strcmp(&date[4], "2010") > 0) {
            sum *= 1.3;
        }
        return sum;
    }

    friend ostream &operator<<(ostream &os, MusicVideo &recording) {
        os << recording.name << " - " << recording.author << " - " << recording.date << " - " << recording.duration
           << " - " << recording.price() << endl;
        return os;
    }

};

double total_price(MediaSegment **ms, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += ms[i]->price();
    }
    return sum;
}

MusicVideo *cheapeset_music_video(MediaSegment **ms, int n) {
    int flag = 1;
    MusicVideo *min;
    for (int i = 0; i < n; ++i) {
        MusicVideo *casted = dynamic_cast<MusicVideo *>(ms[i]);
        if (casted) {
            if (flag) {
                min = casted;
                flag = 0;
            } else {
                if (casted->price() < min->price()) {
                    min = casted;
                }
            }
        }
    }
    return min;
}

int main() {
    AudioRecording m1("Rap", "Eminem", 362, 3, 2, 5);
    AudioRecording m2("Rock", "GnR", 522, 7, 3, 8);
    VideoRecording v1("Gags", "Mike", 321, 12, 1919, 1);
    VideoRecording v2("Gameplay", "GG", 524, 52, 2240, 0);
    MusicVideo mv1("YAY", "ABC", 524, 52, 2, 5, 1650, 1, "12042012");
    MusicVideo mv2("BU", "BCA", 1203, 52, 2, 5, 3240, 1, "06042003");

    MediaSegment **ms = new MediaSegment *[6];
    ms[0] = &m1;
    ms[1] = &m2;
    ms[2] = &v1;
    ms[3] = &v2;
    ms[4] = &mv1;
    ms[5] = &mv2;
    cout << total_price(ms, 6) << endl;
    cout << *cheapeset_music_video(ms, 6) << endl;
    return 0;
}