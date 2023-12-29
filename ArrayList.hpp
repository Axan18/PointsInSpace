#ifndef ARRAY_LIST
#define ARRAY_LIST
#include <stdexcept>
template<typename T, int capacity>
class ArrayList
{
    private:
        T array[capacity];
        int sizeOfList;
    public:
        ArrayList()
        {
            sizeOfList=0;
        }
        void push_front(T x)
        {
            if(sizeOfList==capacity) throw std::out_of_range("Lista pelna");
            for(int i =sizeOfList+1; i>0;i--)
            {
                array[i]=array[i-1];
            }
            sizeOfList++;
            array[0]=x;
        }
        T pop_front()
        {
            if(empty()) throw std::out_of_range("Lista pusta");
            T value=array[0];
            for(int i=0; i<sizeOfList-1;i++)
            {
                array[i]=array[i+1];
            }
            sizeOfList--;
            return value;
        }
        void push_back(T x)
        {
            if(sizeOfList==capacity) throw std::out_of_range("Lista pelna");
            array[sizeOfList++]=x;
        }
        T pop_back()
        {
            if(empty()) throw std::out_of_range("Lista pusta");
            return array[--sizeOfList];
        }
        bool empty()
        {
            return sizeOfList==0;
        }
        int size()
        {
            return sizeOfList;
        }
        void clear()
        {
            sizeOfList=0;

        }
        int find(T x)
        {
            for(int i=0;i<sizeOfList;i++)
            {
                if(array[i]==x) return i;
            }
            return -1;
        }
        int remove(T x)
        {
            int counter = 0;
            for (int i = 0; i < sizeOfList; i++)
            {
                if (array[i] == x) counter++;
                else if (counter > 0)
                {
                    array[i - counter] = array[i]; //jak coś usunęliśmy to indeksy są przesuwane o odpowiednią liczbę w następnej iteracji
                }
            }
            return counter;
        }
        void insert(int i, T x)
        {
            if(sizeOfList==capacity) throw std::out_of_range("Lista pelna");
            for(int j =sizeOfList+1; j>i;j--)
            {
                array[j]=array[j-1]; //wszystkie elementy po wstawionym przesuwamy o 1
            }
            array[i]=x;
            sizeOfList++;
        }
        T erase(int i)
        {
            if(empty()) throw std::out_of_range("Lista pusta");
            T value=array[i];
            for(i; i<sizeOfList-1;i++)
            {
                array[i]=array[i+1]; //przedostatni się staje ostatnim i tak dalej przesuwamy
            }
            sizeOfList--;
            return value;
        }
        bool replace(T x, T y)
        {
            int index = find(x);
            if (index==-1) return false;
            array[index]=y;
            return true;
        }
        T& operator[](int index) {
        return array[index];
    }

};
#endif