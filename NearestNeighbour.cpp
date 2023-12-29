#include <iostream>
#include <fstream>
#include "ArrayList.hpp"
#include "KD-tree.hpp"
#include <string> 
#include <cmath>

#ifndef DIMENSIONS
#define DIMENSIONS 5 // default value
#endif

#ifndef NUMBEROFPOINTS
#define NUMBEROFPOINTS 10 // default value
#endif

int main(int argc, char* argv[]) {
    const int dimensions = DIMENSIONS;
    const int numberOfPoints = NUMBEROFPOINTS;
    std::string filename = argv[1];
    std::string filename2 = argv[2];
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
    file.close();

    KDTree<double,dimensions, numberOfPoints> tree(points);
    ArrayList<double, dimensions> searchPoint;
        std::ofstream filePoint(filename, std::ios::app); //na koniec pliku z punktami dodajemy punkt, ktorego sąsiada chcemy znaleźć
    std::cout<<"Insert the point whose NN we will look for in the following format: x1 x2 x3 ..."<<std::endl;
    for(int i=0;i<dimensions;i++)
    {
        std::cin>>value;
        filePoint<<value<<" ";
        searchPoint.push_back(value);
    }
    filePoint<<"\n";
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
    int numberOfAddedPoints;
    std::cout<<"How many points do you want to insert?"<<std::endl;
    std::cin>>numberOfAddedPoints;
    std::ofstream file2(filename2);
    file2<<numberOfAddedPoints<<"\n";
    for(int i=0;i<numberOfAddedPoints;i++)
    {    
        std::cout<<"Insert the point in the following format: x1 x2 x3 ..."<<std::endl;
        ArrayList<double, dimensions> point;
        for(int i=0;i<dimensions;i++)
        {
            std::cin>>value;
            point.push_back(value);
            file2<<value<<" "; //dodajemy punkty do pliku z nowymi punktami
        }
        file2<<"\n";
        tree.insert(point);
    }   

    std::cout<<"Insert the point whose NN we will look for in the following format: x1 x2 x3 ..."<<std::endl;
    searchPoint.clear();
    for(int i=0;i<dimensions;i++)
    {
        std::cin>>value;
        searchPoint.push_back(value);
        file2<<value<<" "; //na koniec pliku z punktami dodajemy punkt, ktorego sąsiada chcemy znaleźć
    }
    file2<<"\n";
    file2.close();
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
    std::cout<< ") with distance: " << sqrt(tree.euclideanMetric(nearestPoint, searchPoint))<<"\n"<< std::endl;
    return 0;
}