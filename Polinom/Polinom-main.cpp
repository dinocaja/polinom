#include<iostream>
#include"Polinom.h"


using namespace std;

int main(){
    /* //Kreirenje Polinoma te dodavanje elemenata rucno
    Polinom p;
    p.Dodaj(3,2);
    p.Dodaj(1,3);
    p.Dodaj(1,3);
    p.Dodaj(1,3);
    p.Ukloni();
    cout << p << endl;*/

    /* //Konstruktor kopije,konstruktor za 1 monom, konstruktor sa vektorima i operator =
    Polinom p2(p);
    cout << p2 << endl;

    Polinom p3(5,3);
    cout << p3 << endl;

    vector<double> k{11,12,13};
    vector<int> s{1,2,3};
    Polinom p4(k,s);
    cout << p4 << endl;

    p4 = p3;
    cout << p4 << endl;*/

  // neki testni primjeri
    //(3x-(-x-1))(x^3-2x^2+1)''
    //2x+2x*$(3x+(5x^2-3)'+11)dx*x^2
    //$(2x^2-1(3x^2+4)''+2x)dx
    //22-1x^2{$((2x^2-1)($(3-1x^4)dx($(2x^4*2x)dx-2))')dx}''


    Polinom p1;

    cin >> p1;
    cout << p1;
    return 0;
}
