#include <iostream>
#include <fstream>
#include "ArrayList.hpp"
#include <string> 
#include <cmath>

constexpr int dimensions = 10;
constexpr int numberOfPoints = 100;

double euclideanMetric(ArrayList<double, dimensions> point1, ArrayList<double, dimensions> point2)
{
    double sum = 0;
    for (int i = 0; i < dimensions; i++)
    {
        sum += pow(point1[i] - point2[i], 2);
    }
    return sum;
}

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
    ArrayList<double, dimensions> searchPoint;
    for(int i=0;i<dimensions;i++)
    {
        searchPoint.push_back(0);
    }
    double minDistance=euclideanMetric(points[0], searchPoint);
    ArrayList<double, dimensions> nearestPoint=points[0];
    for(int i=1;i<numberOfPoints;i++)
    {   
        if(euclideanMetric(points[i], searchPoint)<minDistance)
        {
            minDistance=euclideanMetric(points[i], searchPoint);
            nearestPoint=points[i];
        }
    }
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
    std::cout<< ") with distance: " << sqrt(minDistance)<< std::endl;
    return 0;
}