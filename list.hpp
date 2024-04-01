
#ifndef list_hpp
#define list_hpp
#include <iostream>
#include <string>
class Node
{
    public:
    int value;
    Node* next;
};
class List
{
private:
    int size;
    Node* head;
public:
    List(int elem = 1);
    ~List();
    int get_size();
    int get_value_by_index(int index); //Zwroc wartosć na danym indexie 
    void add(int elem); //Dodanie na początku
    void add(int elem, int index); //Dodanie na dowolną pozycję
    void remove(int index); //Usuwanie z dowolnej pozycji
    void remove(); //Domyslne usuwanie na początku
   
    void show_all();
private:
    Node* get_node(int index); //Zwroc node nr index
};
#endif