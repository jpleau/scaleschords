/*
 * notecheckbox.cpp
 * Copyright (C) 2017  Jason Pleau <jason@jpleau.ca>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "notecheckbox.h"

NoteCheckbox::NoteCheckbox(Note::Sound sound) : note(Note(sound)) {
	this->setText(note.toString());
	
}

Note NoteCheckbox::getNote() const {
	return note;
}

Note::Sound NoteCheckbox::getSound() const {
	return note.getSound();
}
