#include <iostream>
#include <fstream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);

    int num_points = 100;
    std::ofstream file("points.txt");

    for (int n = 0; n < num_points; ++n) {
        for (int i = 0; i < 10; ++i) {
            file << dis(gen) << " ";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Generated " << num_points << " points in 10D space.\n";

    return 0;
}