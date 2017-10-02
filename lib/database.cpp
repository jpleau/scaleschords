#include "database.h"

#include <iostream>

Database::Database() {
	auto scales_types = Scale::getScaleTypes();

	std::vector<Note::Sound> sounds = {
		Note::Sound::A,
		Note::Sound::Asharp,
		Note::Sound::B,
		Note::Sound::C,
		Note::Sound::Csharp,
		Note::Sound::D,
		Note::Sound::Dsharp,
		Note::Sound::E,
		Note::Sound::F,
		Note::Sound::Fsharp,
		Note::Sound::G,
		Note::Sound::Gsharp,
	};
	
	for (auto sound : sounds) {
		for (auto scale_type : scales_types) {
			Scale scale(sound, scale_type);
			
			QString scale_name = scale.getName();

			std::vector<Chord> scale_chords = scale.getChords();
			
			scales[scale.getName()] = scale;
			
			for (auto chord : scale_chords) {
				QString chord_name = chord.getName();
				
				if (!chords.count(chord_name)) {
					chords[chord.getName()] = chord;	
				}
				
				Chord &ref = chords[chord.getName()];
				ref.addScale(scale_name);

                auto &v1 = scales_by_chord[chord_name];
                auto &v2 = chords_by_scale[scale_name];
                if (std::find(v1.begin(), v1.end(), scale_name) == v1.end()) {
                    v1.push_back(scale_name);
                }

                if (std::find(v2.begin(), v2.end(), chord_name) == v2.end()) {
                    v2.push_back(chord_name);
                }
			}
		}
	}
}

Scale & Database::getScale(QString name)  {
	return scales[name];
}

std::map<QString, Scale> & Database::getScales() {
	return scales;
}

Chord & Database::getChord(QString name)  {
	return chords[name];
}

std::map<QString, Chord> & Database::getChords() {
    return chords;
}

std::vector<QString> Database::findScaleByChords(std::vector<QString> _chords) {
    if (_chords.size() == 0) {
        return {};
    }

    if (_chords.size() == 1) {
        return scales_by_chord[_chords[0]];
    }

    std::vector<QString> current = scales_by_chord[_chords[0]];

    for (size_t i = 1; i < _chords.size(); ++i) {
        std::vector<QString> test = scales_by_chord[_chords[i]];
        std::vector<QString> tmp;
        std::set_intersection(current.begin(), current.end(), test.begin(), test.end(), std::back_inserter(tmp));
        current.clear();
        current = tmp;
    }

    return current;

}


std::vector<QString> Database::getChordsByRoot(QString root) {
    std::vector<QString> ret;

    for (auto chord : chords) {
        if (chord.second.getRoot().toString() == root) {
            ret.push_back(chord.first);
        }
    }

    return ret;
}
