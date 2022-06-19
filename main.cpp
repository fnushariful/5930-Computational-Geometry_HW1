#include <iostream>

#include "LinearithmicTimeClosestPair.h"
#include "CGALComponents.h"
#include "QuadraticTimeClosestPair.h"
#include "DrawUsingQt.h"
#include "GradeClosestPair.h"

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_2 Point;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie();

    //freopen("a.txt", "w", stdout);
    //plot();

    evaluate();

    for (unsigned i = 1; i <= 1; i++) {
        size_t numOfPoints = i * 1000;
        double timeCountNlonN = 0.0;
        double timeCountQuadraticAlgo = 0.0;
        for (unsigned j = 1; j <= 1; j++) {
            std::vector<Point> points;

//            points.emplace_back(Point{1, 3});
//            points.emplace_back(Point{12, 30});
//            points.emplace_back(Point{40, 50});
//            points.emplace_back(Point{5, 1});
//            points.emplace_back(Point{12, 10});
//            points.emplace_back(Point{3, 4});
//            points.emplace_back(Point{1, 1});
//            points.emplace_back(Point{10, 2});
//            points.emplace_back(Point{4, 16});

            CGAL::Timer clock;
            generatePointsInsideASquare(numOfPoints, 500, points);

//            for (auto x: points) {
//                std::cout << x.x() << " " << x.y() << std::endl;
//            }
            //std::cout << "Points generation end" << std::endl;
            auto pointsToIdsMap = createMapOfPoints(points);
            clock.reset();
            clock.start();
            std::pair closestNlogN = findClosestPairLinearithmic(points);
            //std::cout << "NlogN " << std::sqrt(CGAL::squared_distance(closetPair.first, closetPair.second))
            //        << std::endl;
            //std::cout << "NlogN " << closestNlogN.first << " " << closestNlogN.second << std::endl;
            clock.stop();
            timeCountNlonN += clock.time();
            //std::cout << "NlogN " << std::sqrt(CGAL::squared_distance(closetPair.first, closetPair.second))
            //        << std::endl;
            clock.reset();

            clock.start();
            std::pair closetPair = findClosestPairQuadratic(points);
            clock.stop();

            timeCountQuadraticAlgo += clock.time();
            std::vector<unsigned> idsOfSpecialPoints;
            //idsOfSpecialPoints.emplace_back(closetPair.first);
            //idsOfSpecialPoints.push_back(closetPair.second);
            //std::cout << "n^2 " << closetPair.first << " " << closetPair.second << std::endl;
            //draw(points, idsOfSpecialPoints, false);
            points.clear();
        }
        std::cout << numOfPoints << " " << (double) timeCountQuadraticAlgo << " " << (double) timeCountNlonN
                  << std::endl;
    }
}

