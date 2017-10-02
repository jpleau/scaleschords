#ifndef CHORD_H
#define CHORD_H

#include "note.h"
#include "intervals.h"

#include <QString>
#include <vector>
#include <set>


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
        m7B5,
        DOM7,
        SUS2,
        SUS4,
    };

	Chord() {}
    Chord(std::vector<Note> notes);

    QString getName() const;

    std::vector<ScaleNote> getNotes() const;
	
	Note getRoot() const;

    QString print();
	
	void addScale(QString name) {
		auto contains = std::find(scales.begin(), scales.end(), name);
		
		if (contains == scales.end()) {
			scales.push_back(name);	
		}
		
	}
	
	const std::vector<QString> & getScales() {
		return scales;
	}

    bool isInScale(QString scale) const;


    Type getType() const {
        return type;
    }
private:
    Type type;
    std::vector<ScaleNote> notes;
	std::vector<QString> scales;
};

#endif // CHORD_H
