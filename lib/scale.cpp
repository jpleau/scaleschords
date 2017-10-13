#include "scale.h"

#include <QDebug>
#include <iostream>

Scale::Scale(Note::Sound key, Type type) {
    this->type = type;
    auto all_notes = Note::getNotes(key);

    std::vector<QString> letters = {
        "A", "B", "C", "D", "E", "F", "G",
    };

    auto find = std::find(letters.begin(), letters.end(), all_notes[0].getLetter());

    std::rotate(letters.begin(), find, letters.end());

    std::vector<Interval> intervals;

    all_notes.push_back(all_notes[0]);

    bool fix_letters = true;
	bool add_octave = true;
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
                //OCTAVE,
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
                //OCTAVE,
             };
            break;

        case MAJOR_PENTATONIC:
            fix_letters = false;
			add_octave = false;
            intervals = {
                UNISON,
                MAJOR_SECOND,
                MAJOR_THIRD,
                PERFECT_FIFTH,
                MAJOR_SIXTH,
				//OCTAVE,
            };
            break;

        case MINOR_PENTATONIC:
            fix_letters = false;
			add_octave = false;
            intervals = {
                UNISON,
                MINOR_THIRD,
                PERFECT_FOURTH,
                PERFECT_FIFTH,
                MINOR_SEVENTH,
				//OCTAVE
			};
            break;
    }

    scale.push_back({all_notes[0], UNISON});
	notes.insert(all_notes[0].getSound());
    for (size_t i = 1; i < intervals.size(); ++i) {
        auto interval = intervals[i];
        Note note = all_notes[interval];
        if (fix_letters) {
            note.setLetter(letters[i]);
        }
		notes.insert(note.getSound());
        scale.push_back({note, interval});
        //std::cout << "i = " << i << ", letter = " << letter.toStdString() << std::endl;
    }
	
	if (add_octave) {
		//scale.push_back({all_notes[0], OCTAVE});	
	}
    
	
	buildChords();
}

QString Scale::printScale(bool real_notes) const {
    QString out;
    for (auto it = scale.begin(); it != scale.end(); ++it) {
        auto note = *it;
		
		QString note_letter = "";
		
		if (real_notes) {
			note_letter = note.first.getLetter();
		}

        out += note.first.toString(note_letter);

        if (it + 1 < scale.end()) {
            out += ", ";
        }
    }

	return out;
}

std::map<Scale::Type, QString> Scale::getScaleTypes() {
	return {
		{ MAJOR, "Major" },
		{ MINOR, "minor" },
		{ MINOR_PENTATONIC, "minor pentatonic" },
		{ MAJOR_PENTATONIC, "Major pentatonic" },
	};
}

std::vector<Chord> Scale::getChords() {
	return chords;
}

void Scale::buildChords() {
    auto _scale = scale;
    _scale.insert(_scale.end(), scale.begin(), scale.end());

	std::vector<Chord> seventh_chords;
	
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
                seventh_chords.push_back(Chord(chord_notes));
            }
            break;
    }
	
	chords.insert(chords.end(), seventh_chords.begin(), seventh_chords.end());
}

QString Scale::getName() const {
	auto types = getScaleTypes();
	if (types.find(type) == types.end()) {
		return "";
	}
	
	
	return scale[0].first.toString() + " " + types[type];
}

std::set<Note::Sound> Scale::getNotes() {
	return notes;
}

Note Scale::getRoot() const {
	return scale[0].first;
}

Scale::Type Scale::getType() const {
	return type;
}
