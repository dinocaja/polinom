#include<vector>
#include<stack>
#include<cmath>
#include<iostream>
#include"Polinom.h"


void Polinom::init(){
    glava = new Monom(0,-1);
    rep = new Monom(0,-1,glava);
    glava -> sljedeci = rep;
    broj_elemenata = 0;
}

void Polinom::Dodaj(double k,int s){
    rep->prethodni->sljedeci = new Monom(k,s,rep->prethodni,rep);
    rep->prethodni = rep->prethodni->sljedeci;
    broj_elemenata++;
}

void Polinom::Ukloni(){
    Monom *obrisi = pocetak();
    if(obrisi == rep){
        broj_elemenata = 0;
        return;
    }
    pocetak()->sljedeci->prethodni = glava;
    glava->sljedeci = obrisi->sljedeci;
    delete obrisi;
    broj_elemenata --;
}

Polinom::Polinom(double n,int m){
    init();
    Dodaj(n,m);
}

Polinom::Polinom(const vector<double> &k,const vector<int> &s){
    init();
    for(int i = 0; i < k.size();i++){
        if(i >= s.size()){
            Dodaj(k[i],0);
        }
        else{
            Dodaj(k[i],s[i]);
        }
    }
}

Polinom::Polinom(const Polinom &p){
    init();
    for(Monom* m = p.glava -> sljedeci; m != p.rep; m = m->sljedeci){
        Dodaj(m->koeficijent,m->stepen);
    }
}

Polinom& Polinom::operator =(Polinom &p){
    if(glava -> sljedeci == rep)
        init();
    else{
        while(!(prazno())){
            Ukloni();
        }
    }

    for(Monom* m = p.pocetak(); m != p.rep; m = m->sljedeci){
        Dodaj(m->koeficijent,m->stepen);
    }

    return *this;
}

Polinom::~Polinom(){
    while(!prazno())
        Ukloni();
    glava = nullptr;
    rep = nullptr;
}

void Polinom::sortiraj(){
    vector<double> koeficijent;
    vector<int> stepeni;

    for(Monom* m = pocetak(); m != rep; m = m->sljedeci){
        stepeni.push_back(m->stepen);
        koeficijent.push_back(m->koeficijent);
    }

    for(int i = 0; i < stepeni.size();i++){
        for(int j = i+1; j < stepeni.size();j++){
            if(stepeni[i] > stepeni[j]){
                swap(stepeni[i],stepeni[j]);
                swap(koeficijent[i],koeficijent[j]);
            }
        }
    }

    Polinom novi(koeficijent,stepeni);


    *this = novi;

}

void Polinom::preuredi(){

    sortiraj();

    for(Monom* m = pocetak(); m != rep; m = m->sljedeci){
        if(m->stepen == m->prethodni->stepen){
            Monom* c = m->prethodni;
            m->koeficijent += m->prethodni->koeficijent;
            m->prethodni->prethodni->sljedeci = m;
            m->prethodni = m->prethodni->prethodni;
            delete c;
            broj_elemenata--;
        }
    }
}

Polinom& Polinom::operator += (Polinom &p){
    for(Monom* m = p.pocetak(); m != p.rep; m = m->sljedeci){
        if(m->stepen != -1)
            Dodaj(m->koeficijent,m->stepen);
    }
    preuredi();
}

Polinom& Polinom::operator -= (Polinom &p){
    for(Monom* m = p.pocetak(); m != p.rep; m = m->sljedeci){
        if(m->koeficijent > 0)
            m->koeficijent = (m->koeficijent)-(m->koeficijent)-(m->koeficijent);
        else
            m->koeficijent = abs(m->koeficijent);
        Dodaj(m->koeficijent,m->stepen);
    }
    preuredi();
}

Polinom& Polinom::operator *= (Polinom &p){
    Polinom novi;
    for(Monom* m = pocetak(); m != rep; m = m->sljedeci){
        for(Monom* n = p.pocetak(); n != p.rep; n = n->sljedeci){
            if(m->stepen == 0){
                novi.Dodaj(m->koeficijent * n->koeficijent, n->stepen);
            }
            else if(n->stepen == 0){
                novi.Dodaj(m->koeficijent * n->koeficijent, m->stepen);
            }
            else{
                novi.Dodaj(m->koeficijent * n->koeficijent, m->stepen + n->stepen);
            }
        }
    }

    *this = novi;
    preuredi();
}

Polinom& Polinom::operator ~ (){   //IZVOD
    for(Monom* m = pocetak(); m != rep; m = m->sljedeci){
        double novi = m->stepen * m->koeficijent;
        m->koeficijent = novi;
        m->stepen--;
    }
    return *this;
}

Polinom& Polinom::operator & (){   //INTEGRAL
    for(Monom* m = pocetak(); m != rep; m = m->sljedeci){
        double k = m->koeficijent;
        int b = ++m->stepen;
        if(b != 0){
            double r = k/b;
            m->koeficijent = r;
        }

    }
    return *this;
}

ostream& operator << (ostream& cout,Polinom &p){
    int br(0);
    for(Monom* m = p.pocetak(); m != p.rep; m = m->sljedeci){
        br++;
        if(m->koeficijent == 0)
        continue;
        else if(m->stepen == 0)
            cout << m->koeficijent ;
        else if(m->koeficijent == 1 && m->stepen == 1)
            cout << "X";
        else if(m->koeficijent == 1)
            cout << "X^" << m->stepen;
        else if(m->koeficijent == -1 && m->stepen == 1)
            cout << "-X";
        else if(m->koeficijent == -1)
            cout << "(-X)^" << m->stepen;
        else if(m->koeficijent < 0 && m->stepen == 1)
            cout << "(" << m->koeficijent << "X)";
        else if(m->stepen == 1)
            cout << m->koeficijent << "X";
        else if(m->koeficijent < 0)
            cout << "(" << m->koeficijent << "X)^" << m->stepen;
        else{
            cout << m->koeficijent << "X^" << m->stepen ;
        }
        if(br != p.velicina()){
            cout << "+";
        }
    }
    return cout;
}

bool jeLiBroj(char znak){
    return ((znak>='0' && znak<='9') || (znak == 'x' || znak == 'X'));
}

bool jeLiOtvorena(char znak){
    return znak=='(' || znak=='[' || znak=='{';
}

bool jeLiZatvorena(char znak){
    return znak==')' || znak==']' || znak=='}';
}

char dajOtvorenu(char zagrada){
    switch (zagrada){
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    }
    return '0';
}

int prioritet(char op){
    if (op=='+' || op=='-')
        return 1;
    if (op=='*')
        return 2;
    if (op=='$')
        return 4;
    return 0;
}


Polinom rezultat(Polinom operand1, Polinom operand2, char operacija){
    switch (operacija){
    case '+':
        operand1+=operand2;
        return operand1;
    case '-':
        operand1-=operand2;
        return operand1;
    case '*':
        operand1*=operand2;
        return operand1;
    }
    return Polinom(0,0);

}


void izvrsiOperaciju(stack<char>& znakovi, stack<Polinom>& brojevi){
    if (znakovi.empty() || prioritet(znakovi.top())==0)
        throw "Izraz nije validan";

    char operacija(znakovi.top());
    znakovi.pop();

    if (operacija == '$'){ //INTEGRAL
        if (brojevi.empty())
            throw "Izraz nije validan";

        Polinom operand(brojevi.top());

        brojevi.pop();

        &operand;

        brojevi.push(operand);
    } else {
        if (brojevi.size()<2)
            throw "Izraz nije validan";

        Polinom operand2(brojevi.top());
        brojevi.pop();
        Polinom operand1(brojevi.top());
        brojevi.pop();
        brojevi.push(rezultat(operand1, operand2, operacija));
    }
}

istream& operator >> (istream& cin,Polinom &p){

    enum Simbol {otvorenaZ, zatvorenaZ, integral, binarniOp, broj};
        try{
            while(!p.prazno())
                p.Ukloni();

            int brojacInt(0); //brojac integrala
            stack<char> znakovi;
            stack<Polinom> brojevi;
            Simbol prethodni(otvorenaZ);

            while (cin.peek()!='\n'){
                    while(int(cin.peek())==int(' '))
                        cin.get();

                if (jeLiOtvorena(cin.peek())){
                    if (prethodni==broj || prethodni==zatvorenaZ)
                        znakovi.push('*');

                    znakovi.push(cin.get());
                    prethodni=otvorenaZ;
                } else if (jeLiZatvorena(cin.peek())){
                    if (prethodni==otvorenaZ || prethodni==integral || prethodni==binarniOp)
                        throw "Ne moze zatvorena zagrada nakon operacije ili otvorene zagrade";

                    while (!znakovi.empty() && !jeLiOtvorena(znakovi.top())){
                        izvrsiOperaciju(znakovi, brojevi);
                        if (znakovi.empty())
                            throw "Zatvorena zagrada nema odgovarajucu otvorenu";
                    }
                    if (dajOtvorenu(cin.peek())!=znakovi.top())
                        throw "Zatvorena zagrada nema odgovarajucu otvorenu";

                    prethodni=zatvorenaZ;
                    znakovi.pop();
                    cin.get();
                    if(!znakovi.empty()){
                        char znak = znakovi.top();
                        if(znak == '$'){
                            brojacInt--;
                            if(cin.get() != 'd'){
                                throw "Na kraju integrala se treba nalaziti dx";
                            }
                            if(cin.get() != 'x'){
                                throw "Na kraju integrala se treba nalaziti dx";
                            }
                        }
                    }
                    if(cin.peek() == char(39)){
                        while(cin.peek() == char(39)){
                            Polinom m(brojevi.top());
                            brojevi.pop();
                            ~m;             //IZVOD
                            brojevi.push(m);
                            cin.get();
                        }
                    }
                } else if (jeLiBroj(cin.peek())){
                    if (prethodni==zatvorenaZ){
                        throw "Ne moze polinom poslije zatvorene zagrade";
                    }

                    double b(1);
                    if(cin.peek() == 'X' || cin.peek() == 'x'){
                        cin.get();
                        if(((jeLiOtvorena(cin.peek()) || jeLiZatvorena(cin.peek()) || prioritet(cin.peek()) != 0) || cin.peek() == '\n') && cin.peek() != '$'){
                            brojevi.push(Polinom(b,1));
                        }
                        else{
                            char znak = cin.peek();
                            if(cin.get() != '^' && !jeLiBroj(cin.peek())){
                                    throw "poslije X-a mora ici operacija za stepen, te realan broj koji predstavlja stepen";
                                }
                                int d;
                                cin >> d;
                                brojevi.push(Polinom(b,d));
                        }
                    }
                    else{
                        cin>>b;
                        if(cin.peek() != 'X' && cin.peek() != 'x'){
                            brojevi.push(Polinom(b,0));
                        }
                        else{
                            cin.get();
                            if(((jeLiOtvorena(cin.peek()) || jeLiZatvorena(cin.peek()) || prioritet(cin.peek()) != 0) || cin.peek() == '\n') && cin.peek() != '$'){
                                brojevi.push(Polinom(b,1));
                            }
                            else{
                                if(cin.get() != '^' && !jeLiBroj(cin.peek())){
                                    throw "poslije X-a mora ici operacija za stepen, te realan broj koji predstavlja stepen";
                                }
                                int d;
                                cin >> d;
                                brojevi.push(Polinom(b,d));
                            }
                        }
                    }

                    prethodni=broj;
                } else {
                    if (prioritet(cin.peek())==0){
                        if(char(cin.peek()) == char(39))
                            throw "Operator izvoda mora biti iza zatvorene zagrade";
                        cout << char(cin.peek());
                        throw "Nedozvoljen znak";
                    }

                    if(cin.peek() == '-' && prethodni == otvorenaZ){
                        brojevi.push(Polinom(0,0));
                    }
                    else if ((prethodni==otvorenaZ || prethodni==binarniOp || prethodni==integral) && cin.peek() != '$'){
                        throw "Ne moze operator poslije otvorene zagrade ili operatora";
                    }
                    else if (prethodni==integral && cin.peek() == '$'){
                        throw "Ne moze integral iza integrala";
                    }

                    char znak(cin.get());

                    if (znak == '$'){
                        brojacInt++;
                        znakovi.push(znak);
                        prethodni=integral;
                    }
                    else {
                        while (!znakovi.empty() && prioritet(znakovi.top())>=prioritet(znak))
                            izvrsiOperaciju(znakovi, brojevi);

                        znakovi.push(znak);
                        prethodni=binarniOp;
                    }
                }
            }
            while (!znakovi.empty()){
                if (jeLiOtvorena(znakovi.top()))
                    throw "Nedostaje zatvorena zagrada";
                izvrsiOperaciju(znakovi, brojevi);
            }
            if(brojacInt != 0){
                throw "Greska sa integralom";
            }

            if (brojevi.size()!=1){
                    throw "Izraz nije balansiran";
            }

            Polinom k = brojevi.top();

            for(Monom* m = k.pocetak(); m != k.rep; m = m->sljedeci){
                p.Dodaj(m->koeficijent,m->stepen);
            }
            cin.ignore(1000, '\n');
        } catch (const char poruka[]){
            cout<<poruka<<endl;
            cin.ignore(1000, '\n');
        }

}




