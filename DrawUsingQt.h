//
// Created by FNU Shariful on 2/2/22.
//

#ifndef INC_5930__COMPUTATIONAL_GEOMETRY_HW1_DRAWUSINGQT_H
#define INC_5930__COMPUTATIONAL_GEOMETRY_HW1_DRAWUSINGQT_H

#include <QtWidgets>
#include <QApplication>
#include <QLabel>
#include <QString>

#include <QTranslator>

#include <cstdlib>
#include <ctime>
#include <vector>
#include "CGALComponents.h"

void draw(const std::vector<Point> &P, const std::vector<unsigned> &idsOfSpecialPoints,
          const bool turnOnLabels = true) {

    const double pointSize = 2.0; // adjust this value to change the size of the points
    const double adjustTextPosition = 3.0; // adjust this value to change the position of the labels
    /***************************************************/
    QPicture pi;
    QPainter canvas(&pi);
    canvas.setRenderHint(QPainter::Antialiasing);
    // DO NOT TOUCH THESE Qt STATEMENTS!!!
    /***************************************************/
    // Plot the points in P
    for (unsigned i = 0; i < P.size(); ++i) {
        canvas.drawEllipse(QPointF(P[i].x(), P[i].y()), pointSize, pointSize);
        if (turnOnLabels) {
            QPointF textPos(P[i].x() + adjustTextPosition, P[i].y() + adjustTextPosition);
            canvas.drawText(textPos, QString(std::to_string(i).c_str()));
        }
    }

    canvas.setBrush(Qt::red);

    // Plot the special points in red
    for (auto id: idsOfSpecialPoints)
        canvas.drawEllipse(QPointF(P[id].x(), P[id].y()), pointSize, pointSize);

    canvas.end();

    auto l = new QLabel;
    l->setStyleSheet("QLabel { background-color : white; color : black; }");
    l->setPicture(pi);
    l->setWindowTitle("QT-output");
    l->show();

    QApplication::exec();
}

#endif //INC_5930__COMPUTATIONAL_GEOMETRY_HW1_DRAWUSINGQT_H
