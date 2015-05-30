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

#include "MythClock.h"

MythClock::MythClock(QWidget *parent) : QWidget(parent) {
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);

	pTimer = new QTimer(this);
	connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
}

MythClock::~MythClock() {
}

void MythClock::start()
{
	pTimer->setInterval(250);
	pTimer->start();
}

void MythClock::stop()
{
	pTimer->stop();
}

void MythClock::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHandFront[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -((height() / 4) - 2))
    };
    static const QPoint minuteHandFront[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -((height() / 3) - 2))
    };
    static const QPoint hourHandBack[3] = {
        QPoint(8, 9),
        QPoint(-8, 9),
        QPoint(0, -((height() / 4) + 1))
    };
    static const QPoint minuteHandBack[3] = {
        QPoint(8, 9),
        QPoint(-8, 9),
        QPoint(0, -((height() / 3) + 1))
    };

    QColor hourColorFront(Qt::white);
    QColor minuteColorFront(Qt::white);
    QColor hourColorBack(Qt::gray);
    QColor minuteColorBack(Qt::gray);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::darkGray);
    painter.setBrush(Qt::gray);
    static const QPointF radialPoints[4] = {
		QPointF(86, -2),
		QPointF(96, -2),
		QPointF(96, 2),
		QPointF(86, 2)
    };

    for (int i = 0; i < 12; ++i) {
    	painter.drawPolygon(radialPoints, 4);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColorBack);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    QRectF minback(-6, 6, 7.0, -(height() / 5.5));
    painter.drawRoundedRect(minback, 20, 2);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColorFront);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    QRectF minfront(-5, 5, 5.0, -(height() / 5.5 - 2));
    painter.drawRoundedRect(minfront, 20, 2);
    painter.restore();

    painter.setPen(minuteColorFront);

    for (int j = 0; j < 60; ++j) {
    	if ((j % 5) != 0)
    		painter.drawLine(92, 0, 95, 0);

    	painter.rotate(6.0);
    }

    static const QPointF hourPointsBack[4] = {
    		QPointF(19, -5),
			QPointF(51, -5),
			QPointF(51, 5),
			QPointF(19, 5)
    };
    static const QPointF hourPointsFront[4] = {
    		QPointF(20, -4),
			QPointF(50, -4),
			QPointF(50, 4),
			QPointF(20, 4)
    };

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColorBack);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawPolygon(hourPointsBack, 4);
    painter.drawLine(1, 0, 19, 0);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColorFront);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawPolygon(hourPointsFront, 4);
    painter.restore();
/*
    QRect button(QPoint(-15, -15), QSize(30, 30));
    painter.setPen(Qt::black);
    painter.setBrush(QColor(Qt::black));
    painter.save();
    painter.drawEllipse(button);
    painter.restore();
    */
}
