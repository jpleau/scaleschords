#include "chord.h"

#include <iostream>

Chord::Chord(QString name, std::vector<Note> notes) : name(name), notes(notes) {

}

QString Chord::getName() const {
    return name;
}

std::vector<Note> Chord::getNotes() const {
    return notes;
}

void Chord::print() {
    std::cout << name.toStdString() << ": ";
    for (auto note : notes) {
         std::cout << note.toString().toStdString() << ", ";
    }
    std::cout << std::endl;
}
