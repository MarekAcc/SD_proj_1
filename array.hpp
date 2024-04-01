#ifndef array_hpp
#define array_hpp
#include <iostream>
#include <string>

class Array
{
private:
    int* array; //Pointer to actual array
    int capacity; //Memory use
    int size; //Number of elements;
public:
    Array(int typed_capacity = 4);
    ~Array();
    int get_capacity();
    int get_size();
    int get_value_by_index(int index);
    int get_index_by_value(int value);
    int& operator[](int index);
    void change_value(int index, int value);
    void swap(int index1, int index2);
    void add(int object, int index);//Dodawanie na określone miejsce
    void add(int object); //Dodawanie na końcu(domyślne)
    void remove_by_index(int index);
    void remove_by_value(int value);
    void show_all();
    bool is_empty();
private:
    void double_capacity();
    void move_right(int index);
    void move_left(int index);
};
#endif