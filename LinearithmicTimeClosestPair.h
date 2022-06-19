//
// Created by FNU Shariful on 2/7/22.
//

#ifndef INC_5930__COMPUTATIONAL_GEOMETRY_HW1_LINEARITHMICTIMECLOSESTPAIR_H
#define INC_5930__COMPUTATIONAL_GEOMETRY_HW1_LINEARITHMICTIMECLOSESTPAIR_H

#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/Timer.h>

#include "CGALComponents.h"


typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point;

//void plot() {
//    freopen("a.txt", "w", stdout);
//}

Point currentX, currentY;
double clDist = INFINITY;

bool compareXCord(Point p, Point q) {
    //if (p.x() == q.x()) return p.y() <= q.y();
    return p.x() < q.x();
}

bool compareYCord(Point p, Point q) {
    //if (p.y() == q.y()) return p.x() <= p.y();
    return p.y() < q.y();
}


double baseCaseHandle(const std::vector<Point> &XSorted, Point &closestX, Point &closestY) {
    for (unsigned i = 0; i < XSorted.size() - 1; i++) {
        for (unsigned j = i + 1; j < XSorted.size(); j++) {
            double d = std::sqrt(CGAL::squared_distance(XSorted[i], XSorted[j]));
            if (clDist > d) {
                clDist = d;
                currentX = XSorted[i];
                currentY = XSorted[j];
            }
        }
    }
    return clDist;
}

double searchInsideStrip(const std::vector<Point> &strip, Point &closestX, Point &closestY) {
    double currentMin = clDist;
    unsigned stripSize = strip.size();
    for (unsigned i = 0; i < stripSize; i++) {
        unsigned stripInternalLen = std::min(stripSize, 7 + i + 1);
        for (unsigned j = i + 1; j < stripInternalLen; j++) {
            if (fabs(strip[i].y() - strip[j].y()) < currentMin) {
                double stripInternalMin = std::sqrt(CGAL::squared_distance(strip[i], strip[j]));
                if (stripInternalMin < currentMin) {
                    currentMin = stripInternalMin;
                    currentX = strip[i];
                    currentY = strip[j];
                    clDist = currentMin;
                }
            }
        }
    }
    return currentMin;
}


double
computeClosetPair(const std::vector<Point> &XSorted,
                  const std::vector<Point> &YSorted,
                  unsigned n, Point &closestX,
                  Point &closestY) {

    if (n <= 3) return baseCaseHandle(XSorted, closestX, closestY);

    unsigned sz = YSorted.size();
    n = sz;
    unsigned mid = n / 2;


    Point midPoint = XSorted.at(mid);
    std::vector<Point> yL;
    std::vector<Point> yR;

    std::vector<Point> xL;
    std::vector<Point> xR;

    for (unsigned i = 0; i < n; i++) {
        if (YSorted.at(i).x() <= midPoint.x()) {
            yL.emplace_back(YSorted[i]);
        } else {
            yR.emplace_back(YSorted[i]);
        }
    }
    for (unsigned i = 0; i < mid; i++)
        xL.emplace_back(XSorted.at(i));
    unsigned xs = XSorted.size();
    for (unsigned i = mid; i < xs; i++) {
        xR.emplace_back(XSorted.at(i));
    }


    double dL = computeClosetPair(xL, yL, mid, closestX, closestY);
    double dR = computeClosetPair(xR, yR, n - mid, closestX, closestY);
    double d = std::min(dL, dR);

    std::vector<Point> strip;
    for (unsigned i = 0; i < n; i++) {
        if (fabs(YSorted.at(i).x() - midPoint.x()) <= d) {
            strip.emplace_back(YSorted.at(i));
        }
    }
    double dM = searchInsideStrip(strip, closestX, closestY);

    return std::min(d, dM);
}

std::pair<unsigned, unsigned> findClosestPairLinearithmic(const std::vector<Point> &P) {
    std::vector<Point> XSorted;
    std::vector<Point> YSorted;

    for (auto x: P) {
        XSorted.emplace_back(x);
        YSorted.emplace_back(x);
    }

    sort(XSorted.begin(), XSorted.end(), compareXCord);
    sort(YSorted.begin(), YSorted.end(), compareYCord);
    Point closestX, closestY;
    clDist = INFINITY;
    computeClosetPair(XSorted, YSorted, P.size(), closestX, closestY);
    auto pointsToIdsMap = createMapOfPoints(P);
    return std::make_pair(pointsToIdsMap[currentX], pointsToIdsMap[currentY]);
}

#endif //INC_5930__COMPUTATIONAL_GEOMETRY_HW1_LINEARITHMICTIMECLOSESTPAIR_H
