#ifndef SCALE_H
#define SCALE_H

#include "note.h"
#include "intervals.h"
#include "chord.h"

#include <set>

class Scale {
public:
    enum Type {
        MAJOR,
        MINOR,
        MINOR_PENTATONIC,
        MAJOR_PENTATONIC,
    };

    using ScaleNote = std::pair<Note, Interval>;

	Scale() {}
    Scale(Note::Sound key, Type type);
    QString printScale(bool real_notes = false) const;
	
	static std::map<Type, QString> getScaleTypes();

    std::vector<Chord> getChords();
	
	QString getName() const;
	
	std::set<Note::Sound> getNotes();
	
	Note getRoot() const;
	
	Type getType() const;

    //std::vector<Chord> buildChords(std::vector<ChordPosition>);

private:
	void buildChords();
	
    Note::Sound key;
    std::vector<ScaleNote> scale;
	std::set<Note::Sound> notes;
    Type type;	
	std::vector<Chord> chords;
};

#endif // SCALE_H
