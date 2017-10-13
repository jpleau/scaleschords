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

    // C C# D D# E F F# G G# A A# B C
    // B C C# D D# E F F# G G# A A# B C
    std::map<Type, std::vector<Interval>> mappings = {
        { MAJOR, { UNISON, MAJOR_THIRD, PERFECT_FIFTH } },
        { MINOR, { UNISON, MINOR_THIRD, PERFECT_FIFTH } },
        { DIM, { UNISON, MINOR_THIRD, DIMINISHED_FIFTH, } },

        // Seventh chords
        { MAJOR7, { UNISON, MAJOR_THIRD, PERFECT_FIFTH, MAJOR_SEVENTH } },
        { MINOR7, { UNISON, MINOR_THIRD, PERFECT_FIFTH, MINOR_SEVENTH } },

        { DOM7, { UNISON, MAJOR_THIRD, PERFECT_FIFTH, MINOR_SEVENTH } },

        { DIM7, { UNISON, MINOR_THIRD, DIMINISHED_FIFTH, MAJOR_SIXTH } },

        { HALF_DIM7, { UNISON, MINOR_THIRD, DIMINISHED_FIFTH, MINOR_SEVENTH } },

        { MIN_MAJ_7, { UNISON, MINOR_THIRD, PERFECT_FIFTH, MAJOR_SEVENTH } },
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

QString Chord::getName(bool real_name) const {
    std::map<Type, QString> mapping = {
        { NONE, "NONE" },
        { MAJOR, "" },
        { MINOR, "m" },

        { DOM7, "7" },
        { MAJOR7, "maj7" },
        { MINOR7, "min7" },
        { DIM7, "dim7" },
        { DIM, "dim" },
        { HALF_DIM7, "m7b5" },
        { MIN_MAJ_7, "m/M7" },

        { SUS2, "sus2" },
        { SUS4, "sus4" },
    };

	QString note_letter = "";
	if (real_name) {
		note_letter = notes[0].first.getLetter();
	}
    QString name = notes[0].first.toString(note_letter) + mapping[type];
    return name;
}

std::vector<ScaleNote> Chord::getNotes() const {
	return notes;
}

Note Chord::getRoot() const {
	return notes[0].first;
}

QString Chord::print(bool real_note) {
    QString out;
    for (auto &note : notes) {
		QString  note_letter = "";
		if (real_note) {
			note_letter = note.first.getLetter();
		}
		out += note.first.toString(note_letter);
		if (&note != &notes.back()) {
			out += ", ";
		}
    }
    return out;
}

bool Chord::isInScale(QString scale) const {
    auto find = std::find(scales.begin(), scales.end(), scale);
	return find != scales.end();
}

bool Chord::isSeventh() const {

	return std::find(seventh_types.begin(), seventh_types.end(), type) != seventh_types.end();
}
