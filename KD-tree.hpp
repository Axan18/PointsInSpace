#include "ArrayList.hpp"
#include <vector>

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

    void sort(ArrayList<ArrayList<T, dimensions>, numberOfPoints> &v, int dim)
    {
        for (int i = 1; i < v.size(); i++)
        {
            ArrayList<T, dimensions> temp = v[i];
            int j = i - 1;

            // Porównaj elementy względem zadanego indeksu
            while (j >= 0 && v[j][dim] > temp[dim])
            {
                v[j + 1] = v[j];
                j--;
            }

            v[j + 1] = temp;
        }
    }

    Node* creation(ArrayList<ArrayList<T, dimensions>, numberOfPoints>& listOfPoints, int depth)
    {
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
        if (root == nullptr)
        {
            root = new Node();
            for (int i = 0; i < dimensions; i++)
            root->coordinates.push_back(median[i]);
            depth=1;
            root->left = creation(list1, depth + 1);
            root->right = creation(list2, depth + 1);
        }
        else
        {
            Node *temp = new Node();
            for (int i = 0; i < dimensions; i++)
            temp->coordinates.push_back(median[i]);
            if(depth>this->depth) this->depth=depth;
            temp->left = creation(list1, depth + 1);
            temp->right = creation(list2, depth + 1);
            return temp;
        }
        return root;
    }
    Node closestPoint(ArrayList<T,dimensions> next, ArrayList<T,dimensions> prev, ArrayList<T,dimensions> target)
    {
        if(euclideanMetric(next,target)>euclideanMetric(prev,target)) return prev;
        else return next; 
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
    Node searchNearestNeighbour(Node node,ArrayList<T,dimensions> point,int height)
    {
        if(node == null) return null;
        
        int axis = height % dimensions;
        Node *next; //gałąź w którą wchodzimy
        Node *other; //druga gałąź
        if(point[axis] < node.coordinates[axis]) //idziemy w lewo
        {
            next = node->left;
            other = node->right;
        }
        else //idziemy w prawo
        {
            next = node->right;
            other = node -> left;
        }
        Node temp = searchNearestNeighbour(next,point,height+1); //wchodzimy w głąb drzewa i schodzimy w odpowiednich kierunkach
        Node best = closestPoint(temp.coordinates,node.coordinates,point); //jesteśmy na dole drzewa i sprawdzamy najbliższe odległości punktu w którym jesteśmy i 

        int distance = euclideanMetric(best.coordinates,point);
        int distanceToOtherSection = node.coordinates[axis] - point[axis];

        if(distance>= distanceToOtherSection*distanceToOtherSection) //jeśli jest możliwość na to że w innym sektorze jest najbliższy punkt
        {
            temp = searchNearestNeighbour(other, point, depth+1); //wchodzimy w drugą gałąź cofając się;
            best = closestPoint(temp.coordinates,best.coordinates,point);
        }
        return best;
    }
};
