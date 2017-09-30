#ifndef SCALE_H
#define SCALE_H

#include "note.h"
#include "intervals.h"
#include "chord.h"

class Scale {
public:
    enum Type {
        MAJOR,
        MINOR,
        MINOR_PENTATONIC,
        MAJOR_PENTATONIC,
    };

    using ScaleNote = std::pair<Note, Interval>;

    Scale(Note::Sound key, Type type);
    QString printScale() const;

    std::vector<Chord> getChords();
    //std::vector<Chord> buildChords(std::vector<ChordPosition>);

private:
    Note::Sound key;
    std::vector<ScaleNote> scale;
    Type type;
};

#endif // SCALE_H
