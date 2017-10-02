#ifndef GUITAR_H
#define GUITAR_H

#include <vector>

class Guitar {
public:
    Guitar();
    void print();

private:
    std::vector<std::vector<QString>> fretboard;
    void buildFretboard();
};

#endif // GUITAR_H
