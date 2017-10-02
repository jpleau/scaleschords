#include "guitar.h"

Guitar::Guitar() {
    buildFretboard();
}

void Guitar::printChord() {

}

void Guitar::buildFretboard() {
    fretboard.clear();

    fretboard = {
        { "E", "F", "F#", "G", "G#" },
        { "B", "C", "C#", "D", "D#" },
        { "G", "G#", "A", "A#", "B" },
        { "D", "D#", "E", "F", "F#" },
        { "A", "B", "C", "C#", "D" },
        { "E", "F", "F#", "G", "G#" },
    }
}
