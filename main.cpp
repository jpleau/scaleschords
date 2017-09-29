#include "mainwindow.h"
#include <QApplication>

#include "note.h"
#include "scale.h"

#include <QDebug>
#include <iostream>
#include <functional>


std::ostream &operator << (std::ostream& stream, const QString &str) {
    stream << str.toStdString();
    return stream;
}

using SCALE_LIST = std::map<QString, std::pair<QString, Note::Sound>>;


void printScale(QString prefix, Scale::Type type, SCALE_LIST& scales) {
    std::cout << prefix << std::endl;
    for (auto scale : scales) {

        QString name = scale.first;
        QString real_val = scale.second.first;



        Scale _scale(scale.second.second, type);
        QString test = _scale.printScale();

        bool ok = test == real_val;
        QString ok_msg = ok ? "OK" : "FAIL";

        std::cout << scale.first << " (" << ok_msg << ")";

        if (!ok) {
            std::cout << ": " << real_val << " vs " << test;
         }

        std::cout << std::endl;
    }
}

int main(int argc, char *argv[]) {


    SCALE_LIST scales = {
        { "A Major", { "A, B, C#, D, E, F#, G#, A, ", Note::A, } },
        { "B Major", { "B, C#, D#, E, F#, G#, A#, B, ", Note::B } },
        { "C Major", { "C, D, E, F, G, A, B, C, ", Note::C } },
        { "D Major", { "D, E, F#, G, A, B, C#, D, ", Note::D } },
        { "E Major", { "E, F#, G#, A, B, C#, D#, E, ", Note::E } },
        { "F Major", { "F, G, A, Bb, C, D, E, F, ", Note::F } },
        { "G Major", { "G, A, B, C, D, E, F#, G, ", Note::G } },
    };

    printScale("Major Scales", Scale::MAJOR, scales);

    scales = {

        { "A# Major", { "A#, B#, C##, D#, E#, F##, G##, A#, ", Note::Asharp } },
        { "C# Major", { "C#, D#, E#, F#, G#, A#, B#, C#, ", Note::Csharp } },
        { "D# Major", { "D#, E#, F##, G#, A#, B#, C##, D#, ", Note::Dsharp } },
        { "F# Major", { "F#, G#, A#, B, C#, D#, E#, F#, ", Note::Fsharp } },
        { "G# Major", { "G#, A#, B#, C#, D#, E#, F##, G#, ", Note::Gsharp } },

    };
    printScale("Major Sharp Scales", Scale::MAJOR, scales);



    scales = {

        { "A Minor", { "A, B, C, D, E, F, G, A, ", Note::A } },
        { "C Minor", { "C, D, Eb, F, G, Ab, Bb, C, ", Note::C } },
    };


    printScale("Minor Scales", Scale::MINOR, scales);

    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */


}
