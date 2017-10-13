#include "mainwindow.h"
#include "notecheckbox.h"

#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	auto notes = db.getNotes();

	for (auto _note: notes) {
		Note note(_note.first);

		QListWidgetItem *item = new QListWidgetItem;
		item->setData(Qt::UserRole, note.getSound());
		item->setText(note.toString());
		
		ui->list_roots->addItem(item);
		
		if (note.toString() == "C") {
			ui->list_roots->setCurrentRow(ui->list_roots->count() - 1);
		}
	}
	
	for (auto type : db.getScalesTypes()) {
		QListWidgetItem *item = new QListWidgetItem;
		item->setData(Qt::UserRole, type.first);
		item->setText(type.second);
		
		ui->list_scales_types->addItem(item);
		
		if (type.second == "Major") {
			ui->list_scales_types->setCurrentRow(ui->list_scales_types->count() - 1);
		}
	}
	
	
	update_scales();

	connect(ui->list_roots, &QListWidget::itemSelectionChanged, this, &MainWindow::update_scales);
	connect(ui->list_scales_types, &QListWidget::itemSelectionChanged, this, &MainWindow::update_scales);
	connect(ui->list_scales, &QListWidget::currentItemChanged, this, [=](QListWidgetItem *cur, QListWidgetItem *) {
		if (cur == nullptr) {
			ui->tmp->document()->setHtml("");
			return;
		}
		
		this->scale_changed();
	});
	connect(ui->seventh_chords, &QCheckBox::toggled, this, &MainWindow::scale_changed);
	
	connect(ui->tmp, &QTextBrowser::anchorClicked, [=](const QUrl &) {
	});
	
	connect(ui->only_notes, &QCheckBox::toggled, this, &MainWindow::note_checked);
	
	const int NB_COLS = 7;
	int i = 0, j = 0;
	for (auto note: notes) {
		auto *cb = new NoteCheckbox(note.first);
				
		connect(cb, &QCheckBox::toggled, this, &MainWindow::note_checked);
		
		note_checkboxes.push_back(cb);
		ui->chk_notes->addWidget(cb, j, i);
		
		++i;
		
		if (i + 1 == NB_COLS) {
			++j;
			i = 0;
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::update_scales() {
	QString current_item = "";
	
	if (ui->list_scales->currentItem() != nullptr) {
		current_item = ui->list_scales->currentItem()->data(Qt::UserRole).toString();
	}

	int reselect = 0;
	ui->list_scales->clear();
	int i = 0;
	for (auto root : ui->list_roots->selectedItems()) {
		for (auto type : ui->list_scales_types->selectedItems()) {
			QString scale_name = root->text() + " " + type->text();
			Scale scale = db.getScale(scale_name);
			
			if (scale_name == current_item) {
				reselect = i;
			}
			QListWidgetItem *item = new QListWidgetItem;
			item->setData(Qt::UserRole, scale_name);
			item->setText(scale.getName() + " (" + scale.printScale(true) + ")");
			ui->list_scales->addItem(item);
			i += 1;
		}
	}
	
	if (i > 0) {
		ui->list_scales->setCurrentRow(reselect);
		scale_changed();
	}
}

void MainWindow::scale_changed() {
	auto item = ui->list_scales->currentItem();
	
	if (item == nullptr) {
		return;
	}


	Scale scale = db.getScale(item->data(Qt::UserRole).toString());
	auto chords = scale.getChords();
	qDebug() << chords.size();
	
	QString content = "";
	if (chords.empty()) {
		content = "No chords defined for this scale. Maybe a bug, or maybe not. Who knows.";
	} else {
		int i = 1;
		for (auto chord : chords) {
			if (chord.isSeventh() && !ui->seventh_chords->isChecked()) {
				continue;
			}
			
			if (!chord.isSeventh()) {
				content += QString::number(i) + ". ";
			}
			content += "<a href=\"" + chord.getName() + "\">" + chord.getName(true) + "</a>";
			content += " (" + chord.print(true) + ")";
			content += "<br/>";
			
			if (!chord.isSeventh()) {
				++i;
			}
		}	
	}


	
	ui->tmp->document()->setHtml(content);
}

void MainWindow::select_scale_note(QString note) {
	auto items = ui->list_roots->findItems(note, Qt::MatchExactly);
	
	
	for (auto item : items) {
		ui->list_roots->setItemSelected(item, true);
	}
}

void MainWindow::select_scale_type(QString type) {
	auto items = ui->list_scales->findItems(type, Qt::MatchExactly);
	
	
	for (auto item : items) {
		ui->list_scales->setItemSelected(item, true);
	}
}

void MainWindow::note_checked(bool) {
	std::vector<Note::Sound> _notes;
	for (auto cb : note_checkboxes) {
		if (cb->isChecked()) {
			Note n = cb->getNote();
			qDebug() << n.toString();
			_notes.push_back(cb->getSound());
		}
	}
	
	auto scales = db.findScaleByNotes(_notes, ui->only_notes->isChecked());

	QString content = "";
	for (auto _scale : scales) {
		Scale scale = db.getScale(_scale);
		content += scale.getName() + " (" + scale.printScale(true) + ")" + "<br/>";
	}
	ui->scales_from_notes->document()->setHtml(content);
}
