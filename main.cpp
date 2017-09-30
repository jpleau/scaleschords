#include "mainwindow.h"
#include <QApplication>

#include "note.h"
#include "scale.h"

#include <QDebug>
#include <iostream>
#include <functional>
#include <sstream>

std::ostream &operator << (std::ostream& stream, const QString &str) {
    stream << str.toStdString();
    return stream;
}

using SCALE_LIST = std::map<QString, std::pair<QString, Note::Sound>>;


void printScale(QString prefix, Scale::Type type, SCALE_LIST& scales) {

    std::stringstream ss;
    bool all_ok = true;
    for (auto scale : scales) {

        QString name = scale.first;
        QString real_val = scale.second.first;



        Scale _scale(scale.second.second, type);
        QString test = _scale.printScale();

        bool ok = test == real_val;
        QString ok_msg = ok ? "OK" : "FAIL";

        if (!ok) {
            ss << scale.first << " (" << ok_msg << ")";
            ss << ": " << test << " vs " << real_val << "\n";
        }
        all_ok = all_ok && ok;
    }

    if (all_ok) {
        std::cout << "[OK] " << prefix << std::endl;
    } else {
        std::cout << "[FAIL] " << prefix << std::endl;
        std::cout << ss.str();
    }



}

int main(int argc, char *argv[]) {
    Scale c_major(Note::D, Scale::MAJOR);
    std::vector<Chord> chords = c_major.getChords();

    for (auto chord : chords) {
        chord.print();
    }

    return 0;
    SCALE_LIST scales = {};

    scales = {
        {" A Minor Pentatonic", { "A, C, D, E, G, A", Note::A } },
        {" B Minor Pentatonic", { "B, D, E, F#, A, B", Note::B } },
        {" C Minor Pentatonic", { "C, D#, F, G, A#, C", Note::C } },
        {" D Minor Pentatonic", { "D, F, G, A, C, D", Note::D } },
        {" E Minor Pentatonic", { "E, G, A, B, D, E", Note::E } },
        {" F Minor Pentatonic", { "F, G#, A#, C, D#, F", Note::F } },
        {" G Minor Pentatonic", { "G, A#, C, D, F, G", Note::G } },
    };

    printScale("Minor Pentatonic Scales", Scale::MINOR_PENTATONIC, scales);

    scales = {
        {" A# Minor Pentatonic", { "A#, C#, D#, F, G#, A#", Note::Asharp } },
        {" C# Minor Pentatonic", { "C#, E, F#, G#, B, C#", Note::Csharp } },
        {" D# Minor Pentatonic", { "D#, F#, G#, A#, C#, D#", Note::Dsharp } },
        {" F# Minor Pentatonic", { "F#, A, B, C#, E, F#", Note::Fsharp } },
        {" G# Minor Pentatonic", { "G#, B, C#, D#, F#, G#", Note::Gsharp } },
    };

    printScale("Minor Sharp Pentatonic Scales", Scale::MINOR_PENTATONIC, scales);


    scales = {
        {" A Major Pentatonic", { "A, B, C#, E, F#, A", Note::A } },
        {" B Major Pentatonic", { "B, C#, D#, F#, G#, B", Note::B } },
        {" C Major Pentatonic", { "C, D, E, G, A, C", Note::C } },
        {" D Major Pentatonic", { "D, E, F#, A, B, D", Note::D } },
        {" E Major Pentatonic", { "E, F#, G#, B, C#, E", Note::E } },
        {" F Major Pentatonic", { "F, G, A, C, D, F", Note::F } },
        {" G Major Pentatonic", { "G, A, B, D, E, G", Note::G } },
    };

    printScale("Major Pentatonic Scales", Scale::MAJOR_PENTATONIC, scales);

    scales = {
        {" A# Major Pentatonic", { "A#, C, D, F, G, A#", Note::Asharp } },
        {" C# Major Pentatonic", { "C#, D#, F, G#, A#, C#", Note::Csharp } },
        {" D# Major Pentatonic", { "D#, F, G, A#, C, D#", Note::Dsharp } },
        {" F# Major Pentatonic", { "F#, G#, A#, C#, D#, F#", Note::Fsharp } },
        {" G# Major Pentatonic", { "G#, A#, C, D#, F, G#", Note::Gsharp } },
    };

    printScale("Major Sharp Pentatonic Scales", Scale::MAJOR_PENTATONIC, scales);


    scales = {
        { "A Major", { "A, B, C#, D, E, F#, G#, A", Note::A, } },
        { "B Major", { "B, C#, D#, E, F#, G#, A#, B", Note::B } },
        { "C Major", { "C, D, E, F, G, A, B, C", Note::C } },
        { "D Major", { "D, E, F#, G, A, B, C#, D", Note::D } },
        { "E Major", { "E, F#, G#, A, B, C#, D#, E", Note::E } },
        { "F Major", { "F, G, A, Bb, C, D, E, F", Note::F } },
        { "G Major", { "G, A, B, C, D, E, F#, G", Note::G } },
    };

    printScale("Major Scales", Scale::MAJOR, scales);

    scales = {

        { "A# Major", { "A#, B#, C##, D#, E#, F##, G##, A#", Note::Asharp } },
        { "C# Major", { "C#, D#, E#, F#, G#, A#, B#, C#", Note::Csharp } },
        { "D# Major", { "D#, E#, F##, G#, A#, B#, C##, D#", Note::Dsharp } },
        { "F# Major", { "F#, G#, A#, B, C#, D#, E#, F#", Note::Fsharp } },
        { "G# Major", { "G#, A#, B#, C#, D#, E#, F##, G#", Note::Gsharp } },

    };
    printScale("Major Sharp Scales", Scale::MAJOR, scales);


    scales = {

        { "A Minor", { "A, B, C, D, E, F, G, A", Note::A } },
        { "B Minor", { "B, C#, D, E, F#, G, A, B", Note::B } },
        { "C Minor", { "C, D, Eb, F, G, Ab, Bb, C", Note::C } },
        { "D Minor", { "D, E, F, G, A, Bb, C, D", Note::D } },
        { "E Minor", { "E, F#, G, A, B, C, D, E", Note::E } },
        { "F Minor", { "F, G, Ab, Bb, C, Db, Eb, F", Note::F } },
        { "G Minor", { "G, A, Bb, C, D, Eb, F, G", Note::G } },
    };


    printScale("Minor Scales", Scale::MINOR, scales);


    scales = {

        { "A# Minor", { "A#, B#, C#, D#, E#, F#, G#, A#", Note::Asharp } },
        { "C# Minor", { "C#, D#, E, F#, G#, A, B, C#", Note::Csharp } },
        { "D# Minor", { "D#, E#, F#, G#, A#, B, C#, D#", Note::Dsharp } },
        { "F# Minor", { "F#, G#, A, B, C#, D, E, F#", Note::Fsharp } },
        { "G# Minor", { "G#, A#, B, C#, D#, E, F#, G#", Note::Gsharp } },
    };


    printScale("Minor Sharp Scales", Scale::MINOR, scales);

    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
