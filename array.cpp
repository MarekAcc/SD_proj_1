#include "array.hpp"

    int Array::get_capacity(){return capacity;};
    int Array::get_size(){return size;};
    bool Array::is_empty(){return ((size == 0) ? true : false);};
    int Array::get_value_by_index(int index){return array[index];};
    int Array::get_index_by_value(int value){
        for(int i = 0; i < size; i++)
            if(array[i] == value)
                return i;
        return 0;
    }
    void Array::change_value(int index, int value)
    {
        array[index] = value;
    } 
    void Array::swap(int index1, int index2)
    {
        int tmp;
        tmp = get_value_by_index(index1);
        array[index1] = array[index2];
        array[index2] = tmp;
    }
    void Array::add(int object, int index) //Dodawanie na określone miejsce
    {
        if(capacity == size){
            double_capacity();
        }
        this->move_right(index);
        array[index] = object;
        size++;
        return;
    }
    void Array::add(int object) //Dodawanie na końcu(domyślne)
    {
        if(capacity == size){
            this->double_capacity();
        }
        array[size] = object;
        size++;
        return;
    }
    void Array::remove_by_index(int index)
    {
        move_left(index);
        size--;
        if(2*size == capacity){
            array = (int*)realloc(array, capacity*0.5*sizeof(int));
            capacity = capacity/2;
        }
    }
    void Array::remove_by_value(int value)
    {
        this->remove_by_index(this->get_index_by_value(value));
    }
    void Array::show_all()
    {
        for(int i = 0; i < size; i++)
        {
            std::cout<<"["<<i<<"]="<<array[i]<<"  ";
        }
    }

    Array::Array(int typed_capacity): capacity{typed_capacity}{
        array = (int*) malloc(typed_capacity * sizeof(int));
        size = 0;
    }
    Array::~Array(){
        //std::cout<<"Zwalnianie "<<capacity<<" int pamięci!"<<std::endl;
        if(!is_empty())
            delete array;
    }
    int& Array::operator[](int index)
    {
        return array[index];
    }
    void Array::double_capacity()
    {
        array = (int*)realloc(array, capacity*2*sizeof(int));
        capacity *= 2;
    }
    void Array::move_right(int index)
    {
        for(int i = size; i > index; i--)
        {
            array[i] = array[i - 1];
        }
    }
    void Array::move_left(int index)
    {
        for(int i = index; i < size; i++)
        {
            array[i] = array[i + 1]; 
        }
    }
//     class Array
// {
// private:
//     int* array; //Pointer to actual array
//     int capacity; //Memory use
//     int size = 0; //Number of elements;
// public:
//     int get_capacity(){return capacity;};
//     int get_size(){return size;};
//     bool is_empty(){return ((size == 0) ? true : false);};
//     int get_value_by_index(int index){return array[index];};
//     int get_index_by_value(int value){
//         for(int i = 0; i < size; i++)
//             if(array[i] == value)
//                 return i;
//         return 0;
//     } 
//     void add(int object, int index) //Dodawanie na określone miejsce
//     {
//         if(capacity == size){
//             double_capacity();
//         }
//         this->move_right(index);
//         array[index] = object;
//         size++;
//         return;
//     }
//     void add(int object) //Dodawanie na końcu(domyślne)
//     {
//         if(capacity == size){
//             this->double_capacity();
//         }
//         array[size] = object;
//         size++;
//         return;
//     }
//     void remove_by_index(int index)
//     {
//         this->move_left(index);
//         size--;
//     }
//     void remove_by_value(int value)
//     {
//         this->remove_by_index(this->get_index_by_value(value));
//     }
//     void show_all()
//     {
//         for(int i = 0; i < size; i++)
//         {
//             cout<<"["<<i<<"] = "<<array[i]<<endl;
//         }
//     }

//     Array(int typed_capacity = 4): capacity{typed_capacity}{
//         array = (int*) malloc(typed_capacity * sizeof(int));
//     }
//     ~Array(){
//         //std::cout<<"Zwalnianie "<<capacity<<" int pamięci!"<<std::endl;
//         if(!is_empty())
//             delete array;
//     }
// private:
//     void double_capacity()
//     {
//         array = (int*)realloc(array, capacity*2*sizeof(int));
//         capacity *= 2;
//     }
//     void move_right(int index)
//     {
//         for(int i = size; i > index; i--)
//         {
//             array[i] = array[i - 1];
//         }
//     }
//     void move_left(int index)
//     {
//         for(int i = index; i < size; i++)
//         {
//             array[i] = array[i + 1]; 
//         }
//     }
// };