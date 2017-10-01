#ifndef NOTE_H
#define NOTE_H

#include "intervals.h"

#include <QString>
#include <map>
#include <utility>
#include <vector>

class Note {
public:
    enum Sound : int {
        A, Asharp,
        B,
        C, Csharp,
        D, Dsharp,
        E,
        F, Fsharp,
        G, Gsharp,
    };

    static std::map<Sound, QString> notes;

    static std::map<Sound, std::map<QString, QString>> notations;
	
	static std::vector<Sound> sounds;

    Note(Sound sound);

    QString toString(QString letter = "") const;

    static std::vector<Note> getNotes(Sound first = Sound::A);

    Sound getSound() const {
        return sound;
    }

    QString getLetter() const;

    bool operator==(const Note &other) const {
        return sound == other.getSound();
    }

    void setLetter(QString l) {
        this->letter = l;
    }

    Interval getIntervals(const Note &other) const;

private:
    Sound sound;
    QString letter;
};

#endif // NOTE_H
