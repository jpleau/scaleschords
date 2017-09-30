#include "scale.h"

#include <QDebug>
#include <iostream>

Scale::Scale(Note::Sound key, Type type) {
    this->type = type;
    auto notes = Note::getNotes(key);

    std::vector<QString> letters = {
        "A", "B", "C", "D", "E", "F", "G",
    };

    auto find = std::find(letters.begin(), letters.end(), notes[0].getLetter());

    std::rotate(letters.begin(), find, letters.end());

    std::vector<Interval> intervals;

    notes.push_back(notes[0]);

    bool fix_letters = true;
    switch (type) {
         case MAJOR:
            intervals = {
                UNISON,
                MAJOR_SECOND,
                MAJOR_THIRD,
                PERFECT_FOURTH,
                PERFECT_FIFTH,
                MAJOR_SIXTH,
                MAJOR_SEVENTH,
                OCTAVE,
             };
            break;

        case MINOR:
            intervals = {
                UNISON,
                MAJOR_SECOND,
                MINOR_THIRD,
                PERFECT_FOURTH,
                PERFECT_FIFTH,
                MINOR_SIXTH,
                MINOR_SEVENTH,
                OCTAVE,
             };
            break;

        case MAJOR_PENTATONIC:
            fix_letters = false;
            intervals = {
                UNISON,
                MAJOR_SECOND,
                MAJOR_THIRD,
                PERFECT_FIFTH,
                MAJOR_SIXTH,
                OCTAVE,
            };
            break;

        case MINOR_PENTATONIC:
            fix_letters = false;
            intervals = {
                UNISON,
                MINOR_THIRD,
                PERFECT_FOURTH,
                PERFECT_FIFTH,
                MINOR_SEVENTH,
                OCTAVE,
            };
            break;
    }

    scale.push_back(notes[0]);

    for (size_t i = 1; i < intervals.size() - 1; ++i) {
        auto interval = intervals[i];
        Note note = notes[interval];
        if (fix_letters) {
            note.setLetter(letters[i]);
        }

        scale.push_back(note);
        //std::cout << "i = " << i << ", letter = " << letter.toStdString() << std::endl;
    }
    scale.push_back(notes[0]);
}

QString Scale::printScale() const {
    QString out;
    for (auto it = scale.begin(); it != scale.end(); ++it) {
        auto note = *it;
        out += note.toString();

        if (it + 1 < scale.end()) {
            out += ", ";
        }
    }

    return out;
}

std::vector<Chord> Scale::getChords() {
    std::vector<Chord> ret;
    std::vector<ChordPosition> chords;
    std::map<Scale::Type, std::vector<QString>> mappings = {
        { MAJOR, { "maj", "min", "min", "maj", "maj", "min", "dim" } },
        { MINOR, { "min", "dim", "maj", "min", "min", "maj", "maj" } },
    };
    switch (type) {
        case MAJOR:
        case MINOR:
            for (size_t i = 0; i < 7; ++i) {
                chords.push_back(ChordPosition(mappings[type][i], { i, i + 2, i + 4}));
                //chords.push_back(ChordPosition(mappings[type][i] + "7", { i, i + 2, i + 4, i + 6}));
            }
            break;
    }
    ret = buildChords(chords);
    return ret;
}

std::vector<Chord> Scale::buildChords(std::vector<ChordPosition> chord_positions) {
    std::vector<Chord> ret;

    auto _scale = scale;
    _scale.pop_back();
    _scale.insert(_scale.end(), scale.begin(), scale.end());
    for (auto chord_position : chord_positions) {

        auto _notes = chord_position.note_positions;
        QString root = _scale[_notes[0]].toString();
        QString name = root + chord_position.name;

        std::vector<Note> chordNotes;
        for (auto i : _notes) {
            chordNotes.push_back(_scale[i]);
        }

        Chord chord(name, chordNotes);
        ret.push_back(chord);
    }

    return ret;

}





