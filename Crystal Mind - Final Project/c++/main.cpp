#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Persoana
{
public:

    string nume;
    string prenume;
    int varsta;

    virtual void    afisareInformatii();
};

class Elev : public Persoana
{
    public:
    float medie;
    string clasa;
    int id, varsta;

    void    citire();

    void    afisareInformatii();

};

class Profesor : public Persoana
{
    public:
    string materie_predata;

    void    citire();

    void    afisareInformatii();

};

void    Persoana::afisareInformatii()
{
    cout << "Nume: " << nume << endl;
    cout << "Prenume: " << prenume << endl;
    cout << "Varsta: " << varsta << endl;
}

void    Elev::citire()
{
    cout << "Nume = ";cin >> nume;
    cout << "Prenume = ";cin >> prenume;
    cout << "Medie = ";cin >> medie;
    cout << "Varsta = ";cin >> varsta;
    cout << "Clasa = ";cin >> clasa;
    cout << "ID = ";cin >> id;
}
void    Elev::afisareInformatii()
{
    cout << "Nume: " << nume << endl;
    cout << "Prenume: " << prenume << endl;
    cout << "Varsta: " << varsta << endl;
    cout << "Medie = " << medie << endl;
    cout << "Clasa = " << clasa << endl;
    cout << "ID = " << id << endl;
}

void    Profesor::citire()
{
    cout << "Nume = ";cin >> nume;
    cout << "Prenume = ";cin >> prenume;
    cout << "Varsta = ";cin >> varsta;
    cout << "Materie predata = ";cin >> materie_predata;
}

void    Profesor::afisareInformatii()
{
    cout << "Nume: " << nume << endl;
    cout << "Prenume: " << prenume << endl;
    cout << "Varsta: " << varsta << endl;
    cout << "Materie predata = " << materie_predata << endl;
}


vector<Elev*> Elevi;
int e_i = 0;
vector<Profesor*> Profesori;
int p_i = 0;



void    init();
int     is_alphabet(string str);
int     is_space(string str);
int     elev_valid(Elev* elev);
int     profesor_valid(Profesor* profesor);
void    citire_elev();
void    citire_profesor();
void     introducere_date();
void    cautare_elev();
bool     sub_str(string str1, string str2, int m, int n);
void    cautare_profesor();
void     cautare_date();
void     afisare_informatii();
void     meniu_principal();

void    init()
{
    ifstream elev_file, profesor_file;

    elev_file.open("elev.in");
    profesor_file.open("profesor.in");



    string elev_nume, elev_prenume, elev_clasa, profesor_nume, profesor_prenume, profesor_materie_predata;
    float elev_medie;
    int     elev_id, elev_varsta, profesor_varsta;



    while(elev_file >> elev_nume >> elev_prenume >> elev_varsta >> elev_medie >> elev_clasa >> elev_id)
    {
        Elev *elev = new Elev;

        elev -> nume = elev_nume;
        elev -> prenume = elev_prenume;
        elev -> varsta = elev_varsta;
        elev -> medie = elev_medie;
        elev -> clasa = elev_clasa;
        elev -> id = elev_id;

        Elevi.push_back(elev);
    }


    while(profesor_file >> profesor_nume >> profesor_prenume >> profesor_varsta >> profesor_materie_predata)
    {
        Profesor *profesor = new Profesor;

        profesor -> nume = profesor_nume;
        profesor -> prenume = profesor_prenume;
        profesor -> materie_predata = profesor_materie_predata;

        Profesori.push_back(profesor);
    }

    elev_file.close();
    profesor_file.close();
}

int     is_alphabet(string str)
{
    unsigned int i;

    i = 0;
    while(i < str.size())
    {
        if(isalpha(str[i++]))
            return 1;
    }
    return 0;
}

int     is_space(string str)
{
    unsigned int i;

    i = 0;
    while(i < str.size())
    {
        if(isspace(str[i++]))
            return 0;
    }
    return 1;
}
int     elev_valid(Elev* elev)
{
    if(!is_alphabet(elev -> nume) || !is_alphabet(elev -> prenume) || !is_alphabet(elev -> clasa))
        return 0;
    if(!is_space(elev -> nume) || !is_space(elev -> prenume) || !is_space(elev -> clasa))
        return 0;
    for(unsigned int i=0;i<Elevi.size();i++)
    {
        if(Elevi[i] -> id == elev -> id)
            return 0;
    }
    return (1);
}

int     profesor_valid(Profesor* profesor)
{
    if(!is_alphabet(profesor -> nume) || !is_alphabet(profesor -> prenume) || !is_alphabet(profesor -> materie_predata))
        return 0;
    if(!is_space(profesor -> nume) || !is_space(profesor -> prenume) || !is_space(profesor -> materie_predata))
        return 0;
    return (1);
}

void    citire_elev()
{
    int citire = false;
    char input;

    ofstream elev_file("elev.in", ios::app);

    do
    {
        system("cls");

        Elev *elev = new Elev;

        elev -> citire();

        if(elev_valid(elev))
        {
            elev_file << elev -> nume << " " << elev -> prenume << " " << elev -> varsta << " " << elev -> medie << " " << elev -> clasa << " " << elev-> id << endl;
            cout << "Elev introdus ! ! !" << endl;
            Elevi.push_back(elev);
        }
        else
        {
            cout << "Input incorect ! ! !" << endl;
        }
        do
        {
            cout << "Doriti sa introduceti un nou elev (D/N)?";
            cin >> input;
            if(input == 'D')
                citire = true;
            else if(input == 'N')
            {
                citire = false;
                elev_file.close();
                meniu_principal();
            }

        }while(input != 'D' && input != 'N');
    }while(citire);


}

void    citire_profesor()
{
    int citire = false;
    char input;

    ofstream profesor_file("profesor.in", ios::app);

    do
    {
        system("cls");

        Profesor *profesor = new Profesor;

        profesor -> citire();

        if(profesor_valid(profesor))
        {
            profesor_file << profesor -> nume << " " << profesor -> prenume << " " << profesor -> varsta << " " << profesor -> materie_predata << endl;
            cout << "Profesor introdus ! ! !" << endl;
        }
        else
        {
            cout << "Input incorect ! ! !" << endl;
        }

        do
        {
            cout << "Doriti sa introduceti un nou profesor (D/N)?";
            cin >> input;
            if(input == 'D')
                citire = true;
            else if(input == 'N')
            {
                citire = false;
                profesor_file.close();
                meniu_principal();
            }
        }while(input != 'D' && input != 'N');
    }while(citire);

    profesor_file.close();
}

void     introducere_date()
{
    system("cls");
    cout << "***** Introducere date *****" << endl;
    int n;
    cout << "1. Elevi\n2. Profesori\n3. Intoarcere la meniul principal\n";
    cout << "Optiune = "; cin >> n;
    if(n==1)
        citire_elev();
    if(n==2)
        citire_profesor();
    if(n==3)
        meniu_principal();
}

void    cautare_elev()
{
    system("cls");
    int id;
    cout << "ID = ";cin >> id;

    for(unsigned int i=0;i<Elevi.size();i++)
    {
        if(id == Elevi[i] -> id)
        {
            Elevi[i] -> afisareInformatii();
            return ;
        }
    }
    cout << "Nu exista elev cu ID ul " << id;

}

bool sub_str(string str1, string str2, int m, int n)
{
   int j = 0;
   for (int i=0; i<n&&j<m; i++)
       if (str1[j] == str2[i])
         j++;
   return (j==m);
}

void    cautare_profesor()
{
    string str;
    string search;
    cout << "Nume = ";cin >> search;
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    for(unsigned i = 0;i < Profesori.size();i++)
    {
        str = Profesori[i] -> nume;
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        if(sub_str(str, search, str.size(), search.size()));
        {
            Profesori[i] -> afisareInformatii();
            cout << endl;
        }
    }
}

void     cautare_date()
{
    system("cls");
    cout << "***** Cautare_date *****\n";

    int n;
    cout << "1. Elevi\n2. Profesori\n3. Intoarcere la meniul principal\n";
    cout << "Optiune = "; cin >> n;
    if(n==1)
        cautare_elev();
    if(n==2)
        cautare_profesor();
    if(n==3)
        meniu_principal();
}

void     afisare_informatii()
{
    system("cls");
    cout << "***** Afisare informatii *****\n";

    unsigned int i = 0;
    for(i=0;i<Elevi.size();i++)
    {
        Elevi[i] -> afisareInformatii();
    }

    for(i=0;i<Profesori.size();i++)
    {
        Profesori[i] -> afisareInformatii();
    }
}

void     meniu_principal()
{
    system("cls");
    cout << "***** Meniul Principal *****\n";
    int n ;
    cout << "1 - Introducere date\n2 - Cautare date\n3 - Afisare informatii\n4 - Incheiere program\n";
    n = 0;
    cout << "Optiune = "; cin >> n;
    if(n == 1)
        introducere_date();
    else if(n == 2)
        cautare_date();
    else if(n == 3)
        afisare_informatii();
    else if(n == 4)
        exit (EXIT_FAILURE);
    else
        meniu_principal();
}


int main()
{
    init();
    meniu_principal();
    return 0;
}
