#include "scale.h"

#include <QDebug>

Scale::Scale(Note::Sound key, Type type) {
    this->type = type;
    auto notes = Note::getNotes(key);

    std::vector<QString> letters = {
        "A", "B", "C", "D", "E", "F", "G",
    };

    auto find = std::find(letters.begin(), letters.end(), notes[0].getLetter());

    std::rotate(letters.begin(), find, letters.end());

    letters.push_back(notes[0].getLetter());

    switch (type) {
         case MAJOR:
            scale = {
                notes[0],
                notes[2],
                notes[4],
                notes[5],
                notes[7],
                notes[9],
                notes[11],
                notes[0],
            };

            for (size_t i = 0; i < scale.size(); ++i) {
                scale[i].setLetter(letters[i]);
            }
        break;

        case MINOR:
            scale = {
                notes[0],
                notes[2],
                notes[3],
                notes[5],
                notes[7],
                notes[8],
                notes[10],
                notes[0],
            };

            for (size_t i = 0; i < scale.size(); ++i) {
                scale[i].setLetter(letters[i]);
            }
        break;
    }
}

QString Scale::printScale() const {
    QString out;
    for (auto note : scale) {
        out += note.toString() += ", ";
    }

    return out;
}

