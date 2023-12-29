#include "ArrayList.hpp"
#include <vector>
#include <iostream>
#include <cmath>

template<typename T, int dimensions, int numberOfPoints>
class KDTree
{
private:
    struct Node
    {
        ArrayList<T,dimensions> coordinates;
        Node *left;
        Node *right;
    };

    Node *root = nullptr;
    int depth=0;
    int sizeOfTree = 0;

    void sort(ArrayList<ArrayList<T, dimensions>, numberOfPoints> &v, int axis)
    {
        for (int i = 1; i < v.size(); i++)
        {
            ArrayList<T, dimensions> temp = v[i];
            int j = i - 1;

            // Porównaj elementy względem zadanego indeksu
            while (j >= 0 && v[j][axis] > temp[axis])
            {
                v[j + 1] = v[j];
                j--;
            }

            v[j + 1] = temp;
        }
    }

    Node* creation(ArrayList<ArrayList<T, dimensions>, numberOfPoints>& listOfPoints, int depth)
    {
        // Base case: if the list of points is empty, return nullptr
        if (listOfPoints.size() == 0) {
            return nullptr;
        }
        int axis = depth % dimensions;
        ArrayList<T, dimensions> median;
        int size = listOfPoints.size();
        sort(listOfPoints, axis);
        median = listOfPoints[size / 2];
        ArrayList<ArrayList<T, dimensions>, numberOfPoints> list1, list2;
        for (int i = 0; i < size / 2; i++)
        {
            list1.push_back(listOfPoints[i]);
        }
        for (int i = size / 2 + 1; i < size; i++)
        {
            list2.push_back(listOfPoints[i]);
        }

        Node *temp = new Node();
        for (int i = 0; i < dimensions; i++)
            temp->coordinates.push_back(median[i]);
        if(depth>this->depth) this->depth=depth;
        if (root == nullptr)
        {
            root = temp;
        }
        temp->left = creation(list1, depth + 1);
        temp->right = creation(list2, depth + 1);
        return temp;
    }
    Node* closestPoint(Node* next, Node* prev, ArrayList<T,dimensions> target)
    {
        if(next == nullptr) return prev;
        if(prev == nullptr) return next;

        if(euclideanMetric(next->coordinates, target) > euclideanMetric(prev->coordinates, target)) 
            return prev;
        else 
            return next; 
    }
    Node* search(Node* node, ArrayList<T,dimensions>& point, int height)
    {
        if(node == nullptr) return nullptr;
        
        int axis = height % dimensions;
        Node *next; // branch we're entering
        Node *other; // the other branch
        if(point[axis] < node->coordinates[axis]) // we go left
        {
            next = node->left;
            other = node->right;
        }
        else // we go right
        {
            next = node->right;
            other = node->left;
        }
        Node* temp = search(next, point, height+1); // we go deeper into the tree and descend in the right directions
        Node* best = closestPoint(temp, node, point); // we're at the bottom of the tree and we check the nearest distances of the point where we are

        if(best == nullptr) return nullptr; // if we're at the bottom of the tree and we don't have a point to compare, we return nullptr
        double distance = euclideanMetric(best->coordinates, point); // Changed type to double
        double distanceToBoundary = pow(node->coordinates[axis] - point[axis], 2); // Calculate square of distance along splitting axis
        
        if(distance >= distanceToBoundary) // if there's a chance that the nearest point is in another sector
        {
            temp = search(other, point, height+1); // we enter the second branch by going back;
            best = closestPoint(temp, best, point);
        }
        return best;
    }

public:
    KDTree(ArrayList<ArrayList<T, dimensions>, numberOfPoints>& listOfPoints)
    {
        creation(listOfPoints, 0);
    }

    void insert(ArrayList<T,dimensions> point)
    {
        Node *temp =root;
        int level =1;
        while(true)
        {
            level++;
            int axis = (level-2) % dimensions;
            if(point[axis]>=temp->coordinates[axis])
            {
                if(temp->right==nullptr)
                {
                    temp->right=new Node();
                    for(int i=0;i<dimensions;i++)
                    {
                        temp->right->coordinates.push_back(point[i]);
                    }
                    if(level>depth) {depth = level;
                    break;}
                }
                temp=temp->right;
            }
            else
            {
                if(temp->left==nullptr)
                {
                    temp->left=new Node();
                    for(int i=0;i<dimensions;i++)
                    {
                        temp->left->coordinates.push_back(point[i]);
                    }
                    if(level>depth) 
                    {depth = level;
                    break;}
                }
                temp=temp->left;
            }
        }
    }
    ArrayList<T,dimensions> searchNearestNeighbourTo(ArrayList<T,dimensions> point)
    {
        Node* temp = search(root, point, 0);
        if (temp == nullptr) return ArrayList<T,dimensions>();

        return temp->coordinates;
    }
    T euclideanMetric(ArrayList<T,dimensions> point,ArrayList<T,dimensions> target)
    {
        T distance = 0;
        for (int i = 0; i < dimensions; i++)
        {
            T temp = point[i]-target[i];
            distance += temp * temp;
        }
        return distance;
    }
};
