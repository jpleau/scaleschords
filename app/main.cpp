#include "database.h"

#include <iostream>

int main(int argc, char *argv[]) {
	
	Database database;
	
    auto scales = database.getChord("E").getScales();
	
	for (auto s : scales) {
        std::cout << s.toStdString() << std::endl;
	}
	
    std::cout << "==================" << std::endl;

	Scale bmajor = database.getScale("B Major");
	
	for (auto c : bmajor.getChords()) {
        //std::cout << c.getName().toStdString() << std::endl;
	}

    std::vector<QString> cmajor_scales = database.findScaleByChords({ "D", "G", "A", "Bm", "F",});
    for (auto x : cmajor_scales) {
        std::cout << x.toStdString() << std::endl;
    }
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
}
