//
// Created by FNU Shariful on 2/2/22.
//

#ifndef INC_5930__COMPUTATIONAL_GEOMETRY_HW1_QUADRATICTIMECLOSESTPAIR_H
#define INC_5930__COMPUTATIONAL_GEOMETRY_HW1_QUADRATICTIMECLOSESTPAIR_H


#include <utility>
#include "CGALComponents.h"

std::pair<double, double>
findClosestPairQuadratic(const std::vector<Point> &P) {
//double findClosestPairQuadratic(const std::vector<Point> &P) {
    double minDistanceSoFar = INFINITY;
    unsigned p, q;

    //for (auto x: P) std::cout << "Point " << x << std::endl;

    auto pointsToIdsMap = createMapOfPoints(P);

    for (unsigned i = 0; i < P.size() - 1; ++i)
        for (unsigned j = i + 1; j < P.size(); ++j) {
            double d = std::sqrt(CGAL::squared_distance(P[i], P[j])); // returns squared distance
            //std::cout << P[i] << " " << P[j] << " " << std::endl;
            if (d < minDistanceSoFar) {
                p = pointsToIdsMap[P[i]];
                q = pointsToIdsMap[P[j]];
                minDistanceSoFar = d;
            }
        }
    //std::cout << "N^2 " << minDistanceSoFar << std::endl;
    return std::make_pair(p, q);
    //return minDistanceSoFar;
}

#endif //INC_5930__COMPUTATIONAL_GEOMETRY_HW1_QUADRATICTIMECLOSESTPAIR_H
