#ifndef CHORD_H
#define CHORD_H

#include "note.h"

#include <QString>

#include <vector>

class Chord
{
public:
    Chord(QString name, std::vector<Note> notes);
    QString getName() const;

    std::vector<Note> getNotes() const;

    void print();

private:
    QString name;
    std::vector<Note> notes;
};

#endif // CHORD_H
