#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <random>
#include <limits>
#include <sstream>
#include "array.hpp"


using namespace std;


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
int generuj_x_liczb_do_pliku(int x, std::string nazwa_pliku)
{
    // Otwórz plik do zapisu
    std::ofstream outputFile(nazwa_pliku);

    // Sprawdź, czy plik został poprawnie otwarty
    if (!outputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu.";
        return 1;
    }
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
    outputFile.close();
    return 0;
}
int wczytaj_liczby_z_pliku_do_tablicy(Array& tab, std::string nazwa_pliku)
{
    std::ifstream inputFile(nazwa_pliku);
    if (!inputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu.";
        return 1;
    }
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
            //if( tab.get_size()%10000 == 0)
                //cout<<"Wczytano "<<tab.get_size()<<" elementow"<<endl;
        }
    }
    inputFile.close();
    return 0;
}
int wczytaj_liczby_z_pliku_do_listy(List& l, std::string nazwa_pliku)
{
    std::ifstream inputFile("random_numbers.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu.";
        return 1;
    }
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
    inputFile.close();
    return 0;
}
int test_dodawania_do_tablicy(Array& arr, int n)
{
    //Zapełnij tablice losowymi numerami
    generuj_x_liczb_do_pliku(n, "random_numbers.csv");
    int ileTablic = 100;
    Array* Tablice = new Array[ileTablic];
    for(int i = 0; i < ileTablic;i++){
        wczytaj_liczby_z_pliku_do_tablicy(Tablice[i], "random_numbers.csv");
    }
   //Dodawaj do kazdej tablicy element na ostatnią pozycję
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < ileTablic;i++)
    {
        Tablice[i].add(5,0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::ofstream outputFile("wyniki.txt", std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu.";
        return 1;
    }
    outputFile<< n << "         " << elapsed.count() * 1e-6 << " ms." << std::endl;
    printf("Time measured: %.6f ms.\n", elapsed.count() * 1e-6);


    delete[] Tablice;
    return 0;
}
int main(void)
{
    Array B{};
    test_dodawania_do_tablicy(B, 10);
    test_dodawania_do_tablicy(B, 100);
    test_dodawania_do_tablicy(B, 1002);
    test_dodawania_do_tablicy(B, 2002);
    test_dodawania_do_tablicy(B, 4002);
    test_dodawania_do_tablicy(B, 8001);
    test_dodawania_do_tablicy(B, 16002);
    test_dodawania_do_tablicy(B, 32002);
    test_dodawania_do_tablicy(B, 64000);
    test_dodawania_do_tablicy(B, 128002);


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