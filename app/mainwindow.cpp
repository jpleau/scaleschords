#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (auto scale : database.getScales()) {
        ui->list->addItem(scale.first);
    }



    connect(ui->list, &QListWidget::currentTextChanged, [=](const QString &text) {
        auto scale = database.getScale(text);
        auto chords = scale.getChords();

        ui->list2->clear();
        for (auto chord : chords) {
            if (chord.getType() != Chord::MAJOR7 && chord.getType() != Chord::MINOR7
                    && chord.getType() != Chord::m7B5 && chord.getType() != Chord::DOM7) {
                ui->list2->addItem(chord.getName());
            }

        }

        ui->label->setText(scale.printScale());
    });

    connect(ui->list2, &QListWidget::currentTextChanged, [=](const QString &text) {
        auto chord = database.getChord(text);
        ui->label2->setText(chord.print());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
