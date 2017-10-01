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

		/*
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
		*/
    }

    scale.push_back({notes[0], UNISON});
    for (size_t i = 1; i < intervals.size() - 1; ++i) {
        auto interval = intervals[i];
        Note note = notes[interval];
        if (fix_letters) {
            note.setLetter(letters[i]);
        }
        scale.push_back({note, interval});
        //std::cout << "i = " << i << ", letter = " << letter.toStdString() << std::endl;
    }
    scale.push_back({notes[0], OCTAVE});
	
	buildChords();
}

QString Scale::printScale() const {
    QString out;
    for (auto it = scale.begin(); it != scale.end(); ++it) {
        auto note = *it;
        out += note.first.toString();

        if (it + 1 < scale.end()) {
            out += ", ";
        }
    }

	return out;
}

std::vector<Scale::Type> Scale::getScaleTypes() {
	return {MAJOR, MINOR};
}

std::vector<Chord> Scale::getChords() {
	return chords;
}

void Scale::buildChords() {
    auto _scale = scale;
    _scale.pop_back();
    _scale.insert(_scale.end(), scale.begin(), scale.end());

    switch (type) {
        case MAJOR:
        case MINOR:
            for (size_t i = 0; i < 7; ++i) {
                std::vector<Note> chord_notes = {
                    _scale[i].first,
                    _scale[i + 2].first,
                    _scale[i + 4].first,
                };
                chords.push_back(Chord(chord_notes));

				chord_notes.push_back(_scale[i + 6].first);

                chords.push_back(Chord(chord_notes));
            }
            break;
    }
}

QString Scale::getName() const {
	std::map<Type, QString> mapping = {
		{ MAJOR, "Major" },
		{ MINOR, "minor" },
	};
	
	QString name = scale[0].first.toString() + " " + mapping[type];
	return name;
}
