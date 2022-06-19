//
// Created by FNU Shariful on 2/7/22.
//

#ifndef INC_5930__COMPUTATIONAL_GEOMETRY_HW1_LINEARITHMICTIMECLOSESTPAIR_DRAFT_H
#define INC_5930__COMPUTATIONAL_GEOMETRY_HW1_LINEARITHMICTIMECLOSESTPAIR_DRAFT_H


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

void plot() {
    freopen("a.txt", "w", stdout);
}

bool compareXCord(Point p, Point q) {
    //if (p.x() == q.x()) return p.y() <= q.y();
    return p.x() < q.x();
}

bool compareYCord(Point p, Point q) {
    //if (p.y() == q.y()) return p.x() <= p.y();
    return p.y() < q.y();
}


double baseCaseHandle(const std::vector<Point> &XSorted, Point &closestX, Point &closestY) {
    double minDist = INFINITY;
    for (unsigned i = 0; i < XSorted.size() - 1; i++) {
        for (unsigned j = i + 1; j < XSorted.size(); j++) {
            double d = std::sqrt(CGAL::squared_distance(XSorted[i], XSorted[j]));
            if (minDist > d) {
                minDist = d;
                closestX = XSorted[i];
                closestY = XSorted[j];
                //std::cout << minDist << std::endl;
            }
        }
    }
    //XSorted.clear();
    return minDist;
}

double searchInsideStrip(const std::vector<Point> &strip, double d, Point &closestX, Point &closestY) {
    double currentMin = d;
    unsigned stripSize = strip.size();
    for (unsigned i = 0; i < stripSize; i++) {
        unsigned stripInternalLen = std::min(stripSize, 7 + i);
        for (unsigned j = i + 1; j < stripInternalLen; j++) {
            if (fabs(strip[i].y() - strip[j].y()) < currentMin) {
                double stripInternalMin = std::sqrt(CGAL::squared_distance(strip[i], strip[j]));
                if (stripInternalMin < currentMin) {
                    currentMin = stripInternalMin;
                    //std::cout << currentMin << std::endl;
                    closestX = strip[i];
                    closestY = strip[j];
                }
            }
        }
    }
    //strip.clear();
    return currentMin;
}


double
computeClosetPair(const std::vector<Point> &XSorted, const std::vector<Point> &YSorted, unsigned n, Point &closestX,
                  Point &closestY) {
    //std::cout << "n " << n << std::endl;
    if (n <= 3) return baseCaseHandle(XSorted, closestX, closestY);

    unsigned mid = n / 2;

    Point midPoint = XSorted.at(mid);
    //std::cout << mid << " " << midPoint << std::endl;
//    std::vector<Point> yL;
//    std::vector<Point> yR;

    std::vector<Point> xL;
    std::vector<Point> xR;

    unsigned sz = XSorted.size();
    for (unsigned i = 0; i < mid; i++) {
        //if (XSorted.at(i).x() <= midPoint.x()) {
        xL.emplace_back(XSorted.at(i));
    }
    for (unsigned i = mid; i < sz; i++) {
        xR.emplace_back(XSorted.at(i));
    }

    double dL = computeClosetPair(xL, YSorted, mid, closestX, closestY);
    double dR = computeClosetPair(xR, YSorted, n - mid, closestX, closestY);
    double d = std::min(dL, dR);

    //std::cout << d << std::endl;
    std::vector<Point> strip;

    sz = YSorted.size();
    for (unsigned i = 0; i < n; i++)
        if (fabs(YSorted.at(i).x() - midPoint.x()) <= d) {
            strip.emplace_back(YSorted.at(i));
        }
    double dM = searchInsideStrip(strip, d, closestX, closestY);
    //XSorted.clear();
    //YSorted.clear();
    //xL.clear();
    //xR.clear();
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
    //std::cout << (computeClosetPair(XSorted, YSorted, P.size(), closestX, closestY)) << std::endl;
    computeClosetPair(XSorted, YSorted, P.size(), closestX, closestY);
    auto pointsToIdsMap = createMapOfPoints(P);
    //std::cout << "Closest Points " << closestX << " " << closestY << std::endl;
    std::cout << pointsToIdsMap[closestY] << " " << pointsToIdsMap[closestX] << std::endl;

    //std::cout << "NlogN 1 " << std::sqrt(CGAL::squared_distance(closestX, closestY))
    //        << std::endl;
    return std::make_pair(pointsToIdsMap[closestX], pointsToIdsMap[closestY]);
}


#endif //INC_5930__COMPUTATIONAL_GEOMETRY_HW1_LINEARITHMICTIMECLOSESTPAIR_DRAFT_H
