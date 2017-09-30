#include "note.h"

std::map<Note::Sound, QString> Note::notes = {
    { Sound::A, "A" },
    { Sound::Asharp, "A" },
    { Sound::B, "B", },
    { Sound::C, "C", },
    { Sound::Csharp, "C" },
    { Sound::D, "D" },
    { Sound::Dsharp, "D" },
    { Sound::E, "E" },
    { Sound::F, "F" },
    { Sound::Fsharp, "F" },
    { Sound::G, "G" },
    { Sound::Gsharp, "G" }
};

std::map<Note::Sound, std::map<QString, QString>> Note::notations = {
    { Sound::A, { { "A", "A"} , { "G", "G##" } } },
    { Sound::Asharp, { { "A", "A#" }, { "B", "Bb" } } },
    { Sound::B, { { "B", "B" }, { "C", "Cb" } } },
    { Sound::C, { { "C", "C" }, { "B", "B#" } } },
    { Sound::Csharp, { { "C", "C#" }, { "D", "Db" } } },
    { Sound::D, { { "D", "D", }, { "C", "C##" } } },
    { Sound::Dsharp, { { "D", "D#" }, { "E", "Eb" } } },
    { Sound::E, { { "E", "E" }, { "F", "Fb" } } },
    { Sound::F, { { "F", "F" }, { "E", "E#" } } },
    { Sound::Fsharp, { { "F", "F#" }, { "G", "Gb" } } },
    { Sound::G, { { "G", "G" }, { "F", "F##" } } },
    { Sound::Gsharp, { { "G", "G#" }, { "A", "Ab" } } },
};

Note::Note(Sound sound) : sound(sound) {
    letter = notes[sound];
}

QString Note::toString(QString letter) const {
    if (letter == "") {
        return notations[sound][this->letter];
    }

    return notations[sound][letter];
}

std::vector<Note> Note::getNotes(Sound first) {
    Note _first(first);

    std::vector<Note> ret = {
        Note(A), Note(Asharp), Note(B), Note(C), Note(Csharp), Note(D), Note(Dsharp), Note(E), Note(F), Note(Fsharp), Note(G), Note(Gsharp)
    };

    auto f = std::find(ret.begin(), ret.end(), first);

    std::rotate(ret.begin(), f, ret.end());

    return ret;
}

QString Note::getLetter() const {
    return notes[sound];
}

Interval Note::getIntervals(const Note &other) const {
    std::vector<Sound> sounds = {
        Sound::A,
        Sound::Asharp,
        Sound::B,
        Sound::C,
        Sound::Csharp,
        Sound::D,
        Sound::Dsharp,
        Sound::E,
        Sound::F,
        Sound::Fsharp,
        Sound::G,
        Sound::Gsharp,
    };

    auto find = std::find(sounds.begin(), sounds.end(), sound);

    std::rotate(sounds.begin(), find, sounds.end());

    for (size_t i = 0; i < sounds.size(); ++i) {
        if (sounds[i] == other.getSound()) {
            return static_cast<Interval>(i);
        }
    }
}
