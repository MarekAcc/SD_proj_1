#include "list.hpp"
    List::~List(){};
    int List::get_size(){return size;}
    int List::get_value_by_index(int index) //Zwroc wartosć na danym indexie 
    {
        Node* tmp = get_node(index);
        return tmp->value;
    }
    void List::add(int elem) //Dodanie na początku
    {
        Node* new_node = new Node;
        new_node->value = elem;
        new_node->next = head;
        head = new_node;
        size++;
    }
    void List::add(int elem, int index) //Dodanie na dowolną pozycję
    {
        if(index > 0){
            Node* tmp = get_node(index-1);
            Node* new_node = new Node;
            new_node->value = elem;
            new_node->next = tmp->next;
            tmp->next = new_node;
            size++;
        }
        else //w przypadku gdy index <= 0 dodaj na początku
            add(elem);
    }
    void List::remove(int index) //Usuwanie z dowolnej pozycji
    {
        Node* old = get_node(index-1);
        Node* tmp = old->next;
        old->next = old->next->next;
        delete tmp;
        size--;
    }
    void List::remove() //Domyslne usuwanie na początku
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }
   
    void List::show_all()
    {
        Node* tmp = head;
        for(int i = 0; i < size; i++)
        {
            std::cout<<"["<<i<<"]="<<tmp->value<<std::endl;
            tmp = tmp->next;
        }
    }
    Node* List::get_node(int index) //Zwroc node nr index
    {
        Node* tmp = head;
        for(int i = 0; i < index; i++)
            tmp = tmp->next;
        return tmp;
    }

    List::List(int elem)
    {
        head = nullptr;
        size = 0;
    }