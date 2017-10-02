#ifndef DATABASE_H
#define DATABASE_H

#include "note.h"
#include "scale.h"

#include <map>
#include <vector>

class Database {
public:
	Database();
	
	Scale & getScale(QString name);
	std::map<QString, Scale> & getScales();
	
	Chord & getChord(QString name);
	std::map<QString, Chord> & getChords();

    std::vector<QString> findScaleByChords(std::vector<QString>);

    std::vector<QString> getChordsByRoot(QString root);
private:
	std::map<QString, Scale> scales;
	std::map<QString, Chord> chords;

    std::map<QString, std::vector<QString>> scales_by_chord;
    std::map<QString, std::vector<QString>> chords_by_scale;
};

#endif // DATABASE_H
