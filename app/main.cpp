#include "mainwindow.h"

#include <QApplication>

#include "database.h"

#include <QDebug>
int main(int argc, char *argv[]) {
	/*
	Database db;
	auto scales =  db.findScaleByNotes({Note::C, Note::D, Note::E, Note::F, Note::G, Note::A, Note::B});
    
	for (auto s : scales) {
		qDebug() << s;
	}
	*/
	
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	return a.exec();
}
