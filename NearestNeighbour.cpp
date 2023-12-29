#include <iostream>
#include <fstream>
#include "ArrayList.hpp"
#include "KD-tree.hpp"
#include <string> 
#include <cmath>
constexpr int dimensions = 10;
constexpr int numberOfPoints = 100;
int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    ArrayList<ArrayList<double, dimensions>, numberOfPoints> points;
    double value;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }
    for(int i=0;i<numberOfPoints;i++)
    {
        ArrayList<double, dimensions> point;
        for (int i = 0; i < dimensions; i++) {
            file >> value;
            point.push_back(value);
        }
        points.push_back(point);
    }
    KDTree<double,dimensions, numberOfPoints> tree(points);
    ArrayList<double, dimensions> searchPoint;
    for(int i=0;i<dimensions;i++)
    {
        searchPoint.push_back(0);
    }
    ArrayList<double, dimensions> nearestPoint = tree.searchNearestNeighbourTo(searchPoint);

    std::cout << "The nearest point to ";
    for(int i=0;i<dimensions;i++)
    {
        std::cout<<searchPoint[i]<<",";
    }
    std::cout<< " is: (" ;   
    for(int i=0;i<dimensions;i++)
    {
        std::cout<<nearestPoint[i]<<",";
    }
    std::cout<< ") with distance: " << sqrt(tree.euclideanMetric(nearestPoint, searchPoint))<< std::endl;

    ArrayList<double, dimensions> point2;
    for(int i=0;i<dimensions;i++)
    {
        point2.push_back(1);
    }
    tree.insert(point2);
    nearestPoint = tree.searchNearestNeighbourTo(searchPoint);

    std::cout << "The nearest point to ";
    for(int i=0;i<dimensions;i++)
    {
        std::cout<<searchPoint[i]<<",";
    }
    std::cout<< " is: (" ;   
    for(int i=0;i<dimensions;i++)
    {
        std::cout<<nearestPoint[i]<<",";
    }
    std::cout<< ") with distance: " << sqrt(tree.euclideanMetric(nearestPoint, searchPoint))<< std::endl;
    return 0;
}