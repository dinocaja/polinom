#ifndef POLINOM_H_INCLUDED
#define POLINOM_H_INCLUDED
#include<vector>
#include<iostream>
using namespace std;

struct Monom{
        double koeficijent;
        int stepen;
        Monom* sljedeci;
        Monom* prethodni;
        Monom(double koeficijent,int stepen,Monom* prethodni = nullptr,Monom* sljedeci = nullptr):koeficijent(koeficijent),stepen(stepen),prethodni(prethodni),sljedeci(sljedeci){}
    };

class Polinom{

    Monom* glava;
    Monom* rep;
    int broj_elemenata;
    void init();

public:
    void Dodaj(double k,int s);
    void Ukloni();

    Polinom(){init();}
    Polinom(double n,int m); //Konstruktor koji pravi polinom koji se sastoji od monoma koji ima koef n i stepen m
    Polinom(const vector<double> &k,const vector<int> &s); //Konstruktor koji pravi polinom na osnovu elemenata vektora k (koeficijenti) i dodjeljuje im elemente vektora s(stepeni)
    Polinom(const Polinom &p); //Konstruktor kopije
    Polinom& operator =(Polinom &p); //Operator dodjele
    ~Polinom(); //Destruktor

    int velicina(){return broj_elemenata; }
    void sortiraj();
    void preuredi();
    bool prazno() {return !broj_elemenata; }
    Monom* pocetak() {return glava->sljedeci; }

    Polinom& operator += (Polinom &p);
    Polinom& operator -= (Polinom &p);
    Polinom& operator *= (Polinom &p);
    Polinom& operator ~ (); //izvod
    Polinom& operator & (); //integral

    friend ostream& operator << (ostream& cout, Polinom &p);
    friend istream& operator >> (istream& cin, Polinom &p);

};


#endif // POLINOM_H_INCLUDED
