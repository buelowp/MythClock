/*
    This file is part of MythClock.

    MythClock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MythClock is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MythClock.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef MYTHCLOCK_H_
#define MYTHCLOCK_H_

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDateTime>
#include <QtGui>

class MythClock : public QWidget {
	Q_OBJECT
public:
	MythClock(QWidget *parent = 0);
	virtual ~MythClock();
	void start();
	void stop();

protected slots:
	void myUpdate();

protected:
	void paintEvent(QPaintEvent *event);

private:
	QTimer *pTimer;
};

#endif /* MYTHCLOCK_H_ */
