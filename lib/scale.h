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
		/*
        MINOR_PENTATONIC,
        MAJOR_PENTATONIC,
		*/
    };

    using ScaleNote = std::pair<Note, Interval>;

	Scale() {}
    Scale(Note::Sound key, Type type);
    QString printScale() const;
	
	static std::vector<Type> getScaleTypes();

    std::vector<Chord> getChords();
	
	QString getName() const;

    //std::vector<Chord> buildChords(std::vector<ChordPosition>);

private:
	void buildChords();
	
    Note::Sound key;
    std::vector<ScaleNote> scale;
    Type type;	
	std::vector<Chord> chords;
};

#endif // SCALE_H
