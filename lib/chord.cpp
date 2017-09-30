#include "chord.h"

#include <iostream>

Chord::Chord(std::vector<Note> _notes) {
    Note root = _notes[0];
    for (size_t i = 0; i < _notes.size(); ++i) {
        Interval interval = root.getIntervals(_notes[i]);
        notes.push_back(std::make_pair(_notes[i], interval));
    }

    size_t nb = notes.size();

    type = NONE;

    std::map<Type, std::vector<Interval>> mappings = {
        { MAJOR, { UNISON, MAJOR_THIRD, PERFECT_FIFTH } },
        { MINOR, { UNISON, MINOR_THIRD, PERFECT_FIFTH } },
        { DIM, { UNISON, MINOR_THIRD, DIMINISHED_FIFTH } },
        { MAJOR7, { UNISON, MAJOR_THIRD, PERFECT_FIFTH, MAJOR_SEVENTH } },
        { MINOR7, { UNISON, MINOR_THIRD, PERFECT_FIFTH, MINOR_SEVENTH } },
        { DIM7, { UNISON, MINOR_THIRD, DIMINISHED_FIFTH, MINOR_SEVENTH } },
        { DOM7, { UNISON, MAJOR_THIRD, PERFECT_FIFTH, MINOR_SEVENTH } },
    };

    for (auto mapping : mappings) {
        auto intervals = mapping.second;
        if (nb == intervals.size()) {
            bool ok = true;
            for (size_t i = 0; i < intervals.size(); ++i) {
                ok = ok && notes[i].second == intervals[i];
            }

            if (ok) {
                type = mapping.first;
                break;
            }
        }
    }
}

QString Chord::getName() const {
    std::map<Type, QString> mapping = {
        { NONE, "NONE" },
        { MAJOR, "maj" },
        { MINOR, "min" },
        { MAJOR7, "maj7" },
        { MINOR7, "min7" },
        { DIM, "dim" },
        { DIM7, "dim7" },
        { DOM7, "dom7" },
        { SUS2, "sus2" },
        { SUS4, "sus4" },
    };

    QString name = notes[0].first.toString() + mapping[type];
    return name;
}

std::vector<ScaleNote> Chord::getNotes() const {
    return notes;
}

void Chord::print() {
    std::cout << getName().toStdString() << ": ";
    for (auto note : notes) {
         std::cout << note.first.toString().toStdString() << ", ";
    }
    std::cout << std::endl;
}
