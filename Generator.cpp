#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <chrono>

#ifndef DIMENSIONS
#define DIMENSIONS 5 // default value
#endif

#ifndef NUMBEROFPOINTS
#define NUMBEROFPOINTS 10 // default value
#endif
int main() {
    srand(time(0));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    int num_points = NUMBEROFPOINTS;
    int dimensions = DIMENSIONS;
    std::ofstream file("points.txt");

    for (int n = 0; n < num_points; ++n) {
        for (int i = 0; i < dimensions; ++i) {
            file << dis(gen) << " ";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Generated " << num_points << " points in "<<dimensions<<"D space.\n";

    return 0;
}