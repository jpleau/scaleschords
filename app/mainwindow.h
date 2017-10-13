#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"

#include <QMainWindow>
#include <QListWidgetItem>

class NoteCheckbox;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Database db;
	
	void update_scales();
	void scale_changed();
	
	void select_scale_note(QString);
	void select_scale_type(QString);
	
	void note_checked(bool);
	
	std::vector<NoteCheckbox *> note_checkboxes;
};

#endif // MAINWINDOW_H
