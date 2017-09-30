#ifndef SCALE_H
#define SCALE_H

#include "note.h"
#include "chord.h"

struct ChordPosition {
    QString name;
    std::vector<size_t> note_positions;

    ChordPosition(QString name, std::vector<size_t> note_positions) : name(name), note_positions(note_positions) {
    }

};

class Scale {
public:
    enum Type {
        MAJOR,
        MINOR,
        MINOR_PENTATONIC,
        MAJOR_PENTATONIC,
    };

    enum Interval : size_t {
        UNISON= 0,
        MINOR_SECOND,
        MAJOR_SECOND,
        MINOR_THIRD,
        MAJOR_THIRD,
        PERFECT_FOURTH,
        DIMINISHED_FIFTH,
        AUGMENTED_FOURTH = DIMINISHED_FIFTH,
        PERFECT_FIFTH,
        MINOR_SIXTH,
        MAJOR_SIXTH,
        MINOR_SEVENTH,
        MAJOR_SEVENTH,
        OCTAVE,
        NONE = 99,
    };

    Scale(Note::Sound key, Type type);
    QString printScale() const;

    std::vector<Chord> getChords();
    std::vector<Chord> buildChords(std::vector<ChordPosition>);
private:

    Note::Sound key;
    std::vector<Note> scale;
    Type type;
};

#endif // SCALE_H
