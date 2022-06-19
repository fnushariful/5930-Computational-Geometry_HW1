//
// Created by Ghosh, Anirban on 2/5/22.
//

#ifndef CODE_GRADECLOSESTPAIR_H
#define CODE_GRADECLOSESTPAIR_H

#include "QuadraticTimeClosestPair.h"
#include "LinearithmicTimeClosestPair.h"
#include "CGALComponents.h"
#include "LinearithmicTimeClosestPair.h"
#include "QuadraticTimeClosestPair.h"


void evaluate() {
    double runtimes[20][2];
    for (auto &runtime: runtimes)
        runtime[0] = runtime[1] = 0.0;

    CGAL::Timer clock;

    unsigned failedTests = 0;

    for (unsigned n = 1; n <= 20; ++n) {
        std::cout << "n: " << n << std::endl;
        for (unsigned i = 0; i < 5; ++i) {
            std::cout << "Run: " << i + 1 << " ";
            std::vector<Point> P;
            generatePointsInsideASquare(n * 1000, 500, P);

            std::vector<Point> copyOfP;
            std::copy(P.begin(), P.end(), back_inserter(copyOfP));

            clock.reset();
            clock.start();
            std::pair closestPairFast = findClosestPairLinearithmic(P);
            clock.stop();
            runtimes[n - 1][0] += clock.time();

            clock.reset();
            clock.start();
            std::pair closestPairSlow = findClosestPairQuadratic(copyOfP);
            clock.stop();
            runtimes[n - 1][1] += clock.time();

            bool isCorrect = (closestPairFast.first == closestPairSlow.first &&
                              closestPairFast.second == closestPairSlow.second) ||
                             (closestPairFast.first == closestPairSlow.second &&
                              closestPairFast.second == closestPairSlow.first);

            if (!isCorrect)
                failedTests++;

        }
        std::cout << std::endl;
    }

    std::cout << "Number of tests failed: " << failedTests << " out of 100 tests" << std::endl;

    // take average over 5 runs
    for (auto &runtime: runtimes) {
        runtime[0] /= 5;
        runtime[1] /= 5;
    }

    //std::ofstream out("a.txt");
    freopen("a.txt", "w", stdout);
    for (unsigned i = 0; i < 20; ++i)
        std::cout << (i + 1) * 1000 << " " << runtimes[i][0] << " " << runtimes[i][1] << std::endl;
    //out.close();

    system("gnuplot -p -e \"plot 'a.txt' using 1:2 with linespoints lw 3 pt 7, 'a.txt' using 1:3 with linespoints lw 3 pt 7\" ");
}

#endif //CODE_GRADECLOSESTPAIR_H
