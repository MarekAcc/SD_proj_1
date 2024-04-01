#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <random>
#include <limits>
#include <sstream>
#include "array.hpp"
#include "list.hpp"


using namespace std;

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
int test_tablicy_dodawanie_na_koncu(int n)
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
    for(int i = 0; i < ileTablic;i++){
        Tablice[i].add(5);
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
int test_tablicy_dodawanie_na_poczatku(int n)
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
    for(int i = 0; i < ileTablic;i++){
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
int test_listy_dodawanie(int n, int x)
{
    int pozycja;
    if(n == x)
        pozycja = n;
    else
        pozycja = 0;
    generuj_x_liczb_do_pliku(n, "random_numbers.csv");
    int ileList = 10;
    List* Listy = new List[ileList];
    for(int i = 0; i < ileList;i++){
        wczytaj_liczby_z_pliku_do_listy(Listy[i],"random_numbers.csv");
    }
    //Dodawaj do kazdej listy element na ostatnią pozycję
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < ileList;i++)
    {
        Listy[i].add(5, pozycja);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::ofstream outputFile("wyniki_list.txt", std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu.";
        return 1;
    }
    outputFile<< n << "         " << elapsed.count() * 1e-6 << " ms." << std::endl;
    printf("Time measured: %.6f ms.\n", elapsed.count() * 1e-6);


    delete[] Listy;
    return 0;
}
int test_tablicy_usuwanie_na_poczatku(int n)
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
    for(int i = 0; i < ileTablic;i++){
        Tablice[i].remove_by_index(0);
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
int test_tablicy_usuwanie_na_koncu(int n)
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
    for(int i = 0; i < ileTablic;i++){
        Tablice[i].remove_by_index(n-1);
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
int test_listy_usuwanie();
int main(void)
{

    // //Dodawanie ostatni element tablicy
    // test_tablicy_dodawanie_na_koncu(10);
    // test_tablicy_dodawanie_na_koncu(100);
    // test_tablicy_dodawanie_na_koncu(1002);
    // test_tablicy_dodawanie_na_koncu(2002);
    // test_tablicy_dodawanie_na_koncu(4002);
    // test_tablicy_dodawanie_na_koncu(8001);
    // test_tablicy_dodawanie_na_koncu(16002);
    // test_tablicy_dodawanie_na_koncu(32002);
    // test_tablicy_dodawanie_na_koncu(64000);
    // test_tablicy_dodawanie_na_koncu(128002);

    // //Dodawanie pierwszy element tablicy
    // test_tablicy_dodawanie_na_poczatku(10);
    // test_tablicy_dodawanie_na_poczatku(100);
    // test_tablicy_dodawanie_na_poczatku(1001);
    // test_tablicy_dodawanie_na_poczatku(2002);
    // test_tablicy_dodawanie_na_poczatku(4002);
    // test_tablicy_dodawanie_na_poczatku(8001);
    // test_tablicy_dodawanie_na_poczatku(16002);
    // test_tablicy_dodawanie_na_poczatku(32002);
    // test_tablicy_dodawanie_na_poczatku(64002);
    // test_tablicy_dodawanie_na_poczatku(128002);

    // //Dodawanie ostatni element listy
    // test_listy_dodawanie(10, 10);
    // test_listy_dodawanie(100, 100);
    // test_listy_dodawanie(1001, 1001);
    // test_listy_dodawanie(2002, 2002);
    // test_listy_dodawanie(4002, 4002);
    // test_listy_dodawanie(8001, 8001);
    // test_listy_dodawanie(16001, 16001);
    // test_listy_dodawanie(32002, 32002);
    // test_listy_dodawanie(64002, 64002);
    // test_listy_dodawanie(128002, 128002);

    // //Dodawanie pierwszy element listy
    // test_listy_dodawanie(10, 0);
    // test_listy_dodawanie(100, 0);
    // test_listy_dodawanie(1001, 0);
    // test_listy_dodawanie(2002, 0);
    // test_listy_dodawanie(4002, 0);
    // test_listy_dodawanie(8001, 0);
    // test_listy_dodawanie(16001, 0);
    // test_listy_dodawanie(32002, 0);
    // test_listy_dodawanie(64002, 0);
    // test_listy_dodawanie(128002, 0);

    // //Usuwanie pierwszy element tablicy
    // test_tablicy_usuwanie_na_poczatku(10);
    // test_tablicy_usuwanie_na_poczatku(100);
    // test_tablicy_usuwanie_na_poczatku(1001);
    // test_tablicy_usuwanie_na_poczatku(2002);
    // test_tablicy_usuwanie_na_poczatku(4002);
    // test_tablicy_usuwanie_na_poczatku(8001);
    // test_tablicy_usuwanie_na_poczatku(16001);
    // test_tablicy_usuwanie_na_poczatku(32002);
    // test_tablicy_usuwanie_na_poczatku(64002);
    // test_tablicy_usuwanie_na_poczatku(123002);

    //Usuwanie ostatni element tablicy
    test_tablicy_usuwanie_na_koncu(10);
    test_tablicy_usuwanie_na_koncu(100);
    test_tablicy_usuwanie_na_koncu(1001);
    test_tablicy_usuwanie_na_koncu(2002);
    test_tablicy_usuwanie_na_koncu(4002);
    test_tablicy_usuwanie_na_koncu(8001);
    test_tablicy_usuwanie_na_koncu(16001);
    test_tablicy_usuwanie_na_koncu(32002);
    test_tablicy_usuwanie_na_koncu(64002);
    test_tablicy_usuwanie_na_koncu(123002);
}