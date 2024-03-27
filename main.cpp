#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <random>
#include <limits>
#include <sstream>


using namespace std;


class Array
{
private:
    int* array; //Pointer to actual array
    int capacity; //Memory use
    int size = 0; //Number of elements;
public:
    int get_capacity(){return capacity;};
    int get_size(){return size;};
    bool is_empty(){return ((size == 0) ? true : false);};
    int get_value_by_index(int index){return array[index];};
    int get_index_by_value(int value){
        for(int i = 0; i < size; i++)
            if(array[i] == value)
                return i;
        return 0;
    } 
    void add(int object, int index) //Dodawanie na określone miejsce
    {
        if(capacity == size){
            double_capacity();
        }
        this->move_right(index);
        array[index] = object;
        size++;
        return;
    }
    void add(int object) //Dodawanie na końcu(domyślne)
    {
        if(capacity == size){
            this->double_capacity();
        }
        array[size] = object;
        size++;
        return;
    }
    void remove_by_index(int index)
    {
        this->move_left(index);
        size--;
    }
    void remove_by_value(int value)
    {
        this->remove_by_index(this->get_index_by_value(value));
    }
    void show_all()
    {
        for(int i = 0; i < size; i++)
        {
            cout<<"["<<i<<"] = "<<array[i]<<endl;
        }
    }

    Array(int typed_capacity = 4): capacity{typed_capacity}{
        array = (int*) malloc(typed_capacity * sizeof(int));
    }
    ~Array(){
        if(!is_empty())
            delete array;
    }
private:
    void double_capacity()
    {
        array = (int*)realloc(array, capacity*2*sizeof(int));
        capacity *= 2;
    }
    void move_right(int index)
    {
        for(int i = size; i > index; i--)
        {
            array[i] = array[i - 1];
        }
    }
    void move_left(int index)
    {
        for(int i = index; i < size; i++)
        {
            array[i] = array[i + 1]; 
        }
    }
};


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
    ~List(){};
    int get_size(){return size;}
    int get_value_by_index(int index) //Zwroc wartosć na danym indexie 
    {
        Node* tmp = get_node(index);
        return tmp->value;
    }
    void add(int elem) //Dodanie na początku
    {
        Node* new_node = new Node;
        new_node->value = elem;
        new_node->next = head;
        head = new_node;
        size++;
    }
    void add(int elem, int index) //Dodanie na dowolną pozycję
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
    void remove(int index) //Usuwanie z dowolnej pozycji
    {
        Node* old = get_node(index-1);
        Node* tmp = old->next;
        old->next = old->next->next;
        delete tmp;
        size--;
    }
    void remove() //Domyslne usuwanie na początku
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }
   
    void show_all()
    {
        Node* tmp = head;
        for(int i = 0; i < size; i++)
        {
            std::cout<<"["<<i<<"]="<<tmp->value<<std::endl;
            tmp = tmp->next;
        }
    }
private:
    Node* get_node(int index) //Zwroc node nr index
    {
        Node* tmp = head;
        for(int i = 0; i < index; i++)
            tmp = tmp->next;
        return tmp;
    }
};

List::List(int elem)
{
    head = nullptr;
    size = 0;
}
// int Array_test(Array arr)
// {
//     //time.start
    
// }
int generuj_x_liczb_do_pliku(int x, std::ofstream &outputFile)
{
    // Pobierz minimalną i maksymalną wartość dla typu int
    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();
    // Inicjalizuj generator liczb pseudolosowych
    std::random_device rd;
    std::mt19937 gen(rd());
    // Utwórz rozkład równomierny na przedziale [min_int, max_int]
    std::uniform_int_distribution<int> distribution(min_int, max_int);
    // Wygeneruj 100 losowych liczb i zapisz je do pliku CSV
    for (int i = 0; i < x; ++i) {
        // Wylosuj liczbę z przedziału [min_int, max_int]
        int random_number = distribution(gen);
        
        // Zapisz wylosowaną liczbę do pliku CSV
        outputFile << random_number;
        
        // Dodaj przecinek, z wyjątkiem ostatniej liczby w wierszu
        if (i < x - 1)
            outputFile << ",";
    }
    return 0;
}
int wczytaj_liczby_z_pliku_do_tablicy(Array& tab, std::ifstream &inputFile)
{
std::string line;
    while (std::getline(inputFile, line)) {
        // Utwórz strumień łańcuchowy ze wiersza
        std::istringstream iss(line);
        std::string token;

        // Parsuj każdą liczbę w wierszu i dodaj ją do wektora
        while (std::getline(iss, token, ',')) {
            // Konwertuj łańcuch na liczbę i dodaj do wektora
            tab.add(std::stoi(token));
            //Sprawdzenie postępow
            if( tab.get_size()%10000 == 0)
                cout<<"Wczytano "<<tab.get_size()<<" elementow"<<endl;
        }
    }
    return 0;
}
int wczytaj_liczby_z_pliku_do_listy(List& l, std::ifstream &inputFile)
{
std::string line;
    while (std::getline(inputFile, line)) {
        // Utwórz strumień łańcuchowy ze wiersza
        std::istringstream iss(line);
        std::string token;
    while (std::getline(iss, token, ',')) {
        l.add(std::stoi(token), l.get_size());
        // //Sprawdzenie postępow
        // if( l.get_size()%10000 == 0)
        //     cout<<"Wczytano "<<l.get_size()<<" elementow"<<endl;
    }
    }
    return 0;
}
int main(void)
{
    // Otwórz plik do zapisu
    std::ofstream outputFile("random_numbers.csv");

    // Sprawdź, czy plik został poprawnie otwarty
    if (!outputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu.";
        return 1;
    }
    generuj_x_liczb_do_pliku(200000, outputFile);

    // Zamknij plik
    outputFile.close();
    // /*LISTA*/
    // std::ifstream inputFile("random_numbers.csv");
    // if (!inputFile.is_open()) {
    //     std::cerr << "Nie można otworzyć pliku do odczytu.";
    //     return 1;
    // }
    // List L{};
    // wczytaj_liczby_z_pliku_do_listy(L, inputFile);
    // inputFile.close();

    // return 0;


    /*TABLICA*/
    std::ifstream inputFile("random_numbers.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu.";
        return 1;
    }
    Array tab{};
    wczytaj_liczby_z_pliku_do_tablicy(tab, inputFile);
    inputFile.close();

    return 0;



    // Array tab[100000];

    //  for (size_t i = 0; i < 100000; i++)
    // {
    //     for(int j = 0; i < 100;i++)
    //         tab[i].add(j);
    // }
    // auto begin = std::chrono::high_resolution_clock::now();
    // for(int i = 0;i<100000;i++)
    // {
    //     tab[i].add(10);
    // }
    // auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    // printf("Time measured: %.5f seconds.\n", elapsed.count() * 1e-9);
    // std::cout<<elapsed.count()<<endl;
    // tab.add(90,0);
    // tab.add(100,1);
    // tab.add(20,2);
    // tab.add(200);
    // tab.show_all();
    // for(int i = 0; i < 130; i++){
    //     tab.add(88+i);
    // }
    // tab.show_all();
    // std::cout<<"Index: "<<tab.get_index_by_value(88)<<std::endl;
    // std::cout<<"Value: "<<tab.get_value_by_index(9)<<std::endl;
    // // tab.remove_by_value(89);
    // // tab.remove_by_value(200);
    // // tab.remove_by_index(0);
    // tab.show_all();

    // time tic
    // for(int i = 0; i < 10000; i++)
    //     tab.add();
    // time toc
    // List l{};
    // for(int i = 0; i < 10; i++)
    //     l.add(i);
    // l.add(100, 1);
}