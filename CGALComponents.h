//
// Created by FNU Shariful on 2/2/22.
//

#ifndef INC_5930__COMPUTATIONAL_GEOMETRY_HW1_CGALCOMPONENTS_H
#define INC_5930__COMPUTATIONAL_GEOMETRY_HW1_CGALCOMPONENTS_H

#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/Timer.h>
#include <unordered_set>

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point;

//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void generatePointsInsideASquare(const unsigned n, const double sizeOfSquare, std::vector<Point> &P) {
    typedef CGAL::Random_points_in_square_2<K::Point_2, CGAL::Creator_uniform_2<double, K::Point_2> > Point_generator;
    Point_generator g(sizeOfSquare / 2);
    std::copy_n(g, n, back_inserter(P));
}

std::unordered_map<Point, unsigned> createMapOfPoints(const std::vector<Point> &P) {
    std::unordered_map<Point, unsigned> M;
    for (unsigned i = 0; i < P.size(); ++i)
        M[P[i]] = i;
    return M;
}


#endif //INC_5930__COMPUTATIONAL_GEOMETRY_HW1_CGALCOMPONENTS_H
