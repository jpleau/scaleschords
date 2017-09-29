#ifndef SCALE_H
#define SCALE_H

#include "note.h"

class Scale {
public:
    enum Type {
        MAJOR,
        MINOR,
    };
    Scale(Note::Sound key, Type type);
    QString printScale() const;
private:
    Note::Sound key;
    std::vector<Note> scale;
    Type type;
};

#endif // SCALE_H
