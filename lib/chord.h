#ifndef CHORD_H
#define CHORD_H

#include "note.h"
#include "intervals.h"

#include <QString>
#include <vector>

using ScaleNote = std::pair<Note, Interval>;

class Chord {

public:
    enum Type {
        NONE,
        MAJOR,
        MINOR,
        MAJOR7,
        MINOR7,
        DIM,
        DIM7,
        DOM7,
        SUS2,
        SUS4,
    };

    Chord(std::vector<Note> notes);

    QString getName() const;

    std::vector<ScaleNote> getNotes() const;

    void print();

private:
    Type type;
    std::vector<ScaleNote> notes;
};

#endif // CHORD_H
