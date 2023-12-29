#include <iostream>
#include <fstream>
#include "ArrayList.hpp"
#include <string> 
#include <cmath>
#ifndef DIMENSIONS
#define DIMENSIONS 5 // default value
#endif

#ifndef NUMBEROFPOINTS
#define NUMBEROFPOINTS 10 // default value
#endif

double euclideanMetric(ArrayList<double, DIMENSIONS> point1, ArrayList<double, DIMENSIONS> point2)
{
    double sum = 0;
    for (int i = 0; i < DIMENSIONS; i++)
    {
        sum += pow(point1[i] - point2[i], 2);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    std::cout<<"\n Nearest neighbour - brute force"<<std::endl;
    std::string filename = argv[1];
    std::string filename2 = argv[2];

    const int dimensions = DIMENSIONS;
    const int numberOfPoints = NUMBEROFPOINTS;
    ArrayList<ArrayList<double, dimensions>, numberOfPoints> startingPoints;
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
        startingPoints.push_back(point);
    }
    ArrayList<double, dimensions> searchPoint;
    for(int i=0;i<dimensions;i++)
    {
        file >> value;
        searchPoint.push_back(value);
    } 
    file.close();

    double minDistance=euclideanMetric(startingPoints[0], searchPoint);
    ArrayList<double, dimensions> nearestPoint=startingPoints[0];
    for(int i=1;i<numberOfPoints;i++)
    {   
        if(euclideanMetric(startingPoints[i], searchPoint)<minDistance)
        {
            minDistance=euclideanMetric(startingPoints[i], searchPoint);
            nearestPoint=startingPoints[i];
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

    //po dodaniu punktow
    std::cout<<"After adding points"<<std::endl;
    std::ifstream file2(filename2);
    int numberOfAddedPoints;
    file2>>numberOfAddedPoints;
    for(int i=0;i<numberOfAddedPoints+1;i++)
    {
        file2.ignore(1000,'\n');
    }
    searchPoint.clear();
    for(int i=0;i<dimensions;i++)
    {
        file2 >> value;
        searchPoint.push_back(value);
    }
    file2.seekg(0, std::ios::beg); //wracamy na poczatek pliku
    file2.ignore(1000,'\n');
    minDistance=euclideanMetric(startingPoints[0], searchPoint);
    nearestPoint=startingPoints[0];
    for(int i=0;i<numberOfAddedPoints;i++)
    {    
        ArrayList<double, dimensions> point;
        for(int i=0;i<dimensions;i++)
        {
            file2 >> value;
            point.push_back(value);
        }
        if(euclideanMetric(point, searchPoint)<minDistance)
        {
            minDistance=euclideanMetric(point, searchPoint);
            nearestPoint=point;
        }
    }
    for(int i=1;i<numberOfPoints;i++)
    {   
        if(euclideanMetric(startingPoints[i], searchPoint)<minDistance)
        {
            minDistance=euclideanMetric(startingPoints[i], searchPoint);
            nearestPoint=startingPoints[i];
        }
    }
    file2.close();
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
}