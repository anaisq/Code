#include <iostream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

class produs{
    private:
        char denumire[256];
        char unit[256];
        float cantitate;
        char date[256];
        float pret_per_unit;
    public:
        produs(char[],char[],float,char[],float);
        ~produs();
        void set_denumire(char den[256]){strcpy(denumire,den);};
        char* get_denumire(){return denumire;};
        void set_unit(char uni[256]){strcpy(unit,uni);};
        char* get_unit(){return unit;};
        void set_cantitate(float c){cantitate=c;};
        float get_cantitate(){return cantitate;};
        void set_date(char d[256]){strcpy(date,d);};
        char* get_date(){return date;};
        void set_pret_per_unit(float f){pret_per_unit=f;};
        float get_pret_per_unit(){return pret_per_unit;};
        produs& operator=(produs &p);

 };


class magazin{
    private:
        int nr_produse;
        produs *p;
    public:
        magazin();
        //magazin(int,produs*);
        ~magazin();
        void afisare();
        int verifica_data(char *);
        void set_produse(int produse){nr_produse=produse;};
        void set_p(int n,produs P[3]){for(int i=0;i<n;i++) p[i]=P[i];};
        int get_produse(){return nr_produse;}
        void citire(istream &in);
        void afisare(ostream &out);
        friend istream& operator>>(istream &in, magazin &m);
        friend ostream& operator<<(ostream &out, magazin &m);
        int stergere(char*);
        void modifica_pret(int, float);
 };

 produs::produs(char denumire[256]="",char unit[256]="",float cantitate=0,char date[256]="",float pret_per_unit=0)
 {
          strcpy(this->denumire,denumire);
          strcpy(this->unit,unit);
          this->cantitate=cantitate;
          strcpy(this->date,date);
          this->pret_per_unit=pret_per_unit;
 }

 produs::~produs()
 {        strcpy(denumire,"");
          strcpy(unit,"");
          cantitate=0;
          strcpy(date,"");
          pret_per_unit=0;
 }

 produs& produs::operator=(produs &p)
         {strcpy(denumire,p.denumire);
          strcpy(unit,p.unit);
          cantitate=p.cantitate;
          strcpy(date,p.date);
          pret_per_unit=p.pret_per_unit;
          }
//Metode magazin


magazin::magazin()
{
   nr_produse=0;
   p=new produs[10];
   // p=new produs[100];
}

/*magazin::magazin(int n,produs* P)
{
    p=new produs[n];
    int i=0;
    for(i=0;i<n;i++)
    {
     p[i]=P[i];
    }
} */
magazin::~magazin()
{
    nr_produse=0;
    delete []p;
}
 void magazin::citire(istream &in)
{
    //cout<<"Nr produse:";
    //in>>nr_produse;
    char aux[256];float n;
    for(int i=0;i<nr_produse;i++)
    {
    cout<<"Denumirea produs: ";
    in.sync();
    in.getline(aux,256);
    p[i].set_denumire(aux);
    strcpy(aux,"");
    cout<<"Unitatea de masura(kg/litru/bucata): ";
    in.sync();
    in.getline(aux,256);
    p[i].set_unit(aux);
    strcpy(aux,"");
    cout<<"Cantitate produs: ";
    in>>n;
    p[i].set_cantitate(n);
    cout<<"Data la care intra in magazin(DD.MM.YYYY): ";
    in.sync();
    in.getline(aux,256);
    p[i].set_date(aux);
    strcpy(aux,"");
    cout<<"Pretul per "<<p[i].get_unit()<<": ";
    n=0;
    in>>n;
    p[i].set_pret_per_unit(n);
    strcpy(aux,"");
    }
}
istream& operator>>(istream &in,magazin &m)
{
    m.citire(in);
    return in;
}
void magazin::afisare(ostream &out)
{out<<"Are "<<nr_produse<<" produse:"<<endl;
for(int i=0;i<nr_produse;i++)
{out<<" - Pe data de "<<p[i].get_date()<<", magazinul primaeste "<<p[i].get_cantitate();
out<<" de "<<p[i].get_unit()<<" de "<<p[i].get_denumire()<<", la pretul de ";
out<<p[i].get_pret_per_unit()<<" de lei pe "<<p[i].get_unit();
 out<<endl;
}
}
ostream& operator<<(ostream &out,magazin &m)
{
    m.afisare(out);
    return out;
}

int magazin::verifica_data(char *data)
{
 int ok=0;
    for(int i=0;i<nr_produse;i++)
    {
        if(strcmp(data,p[i].get_date())==0)
           {
            cout<<" - Pe data de "<<p[i].get_date();
            cout<<", se primaeste "<<p[i].get_cantitate();
            cout<<" de "<<p[i].get_unit()<<" de "<<p[i].get_denumire();
            cout<<", la pretul de "<<p[i].get_pret_per_unit();
            cout<<" de lei pe "<<p[i].get_unit();
            cout<<endl;
            ok=1;
            }
    }
    return ok;
}

int magazin::stergere(char *sir)
{int ok=0;
    for(int i=0;i<nr_produse;i++)
        if(strcmp(p[i].get_denumire(),sir)==0)
    {
        ok=1;
        nr_produse--;
        for(int j=i;j<nr_produse;j++)
            p[j]=p[j+1];
        i--;
    }
 return ok;
}

void magazin::modifica_pret(int i,float pret_nou)
{
    p[i-1].set_pret_per_unit(pret_nou);
}
//////////////////
void menu_output()
{
    cout<<"\n FLOREA ANA 211 - Test1 Bonus -: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Adaugati un magazin nou cu produsele comercializate"<<endl;
    cout<<"2. Afisati toate magazinele"<<endl;
    cout<<"3. Afisati toate produsele primite la o anumita data"<<endl;
    cout<<"4. Stergeti un produs din magazin in functie de nume"<<endl;
    cout<<"5. Modificati pretul unui produs"<<endl;
    cout<<"6. Afisarea magazinului cu cele mai multe produse"<<endl;
    cout<<"0. Iesire."<<endl;
}


void menu()
{
    int n,i,a,j;
  //  produs p1("lapte","L",345,"19.03.2020",4);
  //  produs p2("oua","buc",325,"19.03.2020",0.7);
  //  produs p3("rosii","kg",445,"20.03.2020",2.5);
  //  produs p[2];
  //  p[0]=p1;p[1]=p2;p[2]=p3;

    magazin M[30];
    cout<<"Numar de magazine: ";
    cin>>n;
    //n=3;
    a=0;
  /*  for(i=0;i<n;i++)
    {
        cout<<"Nr de produse in magazinul "<<i+1<<": ";
        a++;
        M[i].set_produse(a);
        cout<<M[i].get_produse();
        M[i].set_p(a,p);
        cout<<endl<<endl;
    } */
    for(i=0;i<n;i++)
    {
        cout<<"Nr de produse in magazinul "<<i+1<<": ";
        cin>>a;
        M[i].set_produse(a);
        cin>>M[i];
        cout<<endl<<endl;
    }

 char d[256];

    int option=0;
do
    {
        menu_output();
        cout<<endl<<"Introduceti numarul actiunii: ";
        cin>>option;

        if(option==1)
        {
         n++;

         cout<<"Nr de prouse din noul magazin: ";
         cin>>j;
         M[n-1].set_produse(j);
         cout<<"Scrieti datele noului magazin: "<<endl;
         cin>>M[n-1];
        }

        if(option==2)
        {
            for(i=0;i<n;i++)
              {
                cout<<"Magazin "<<i+1<<":"<<endl;
                cout<<M[i];
                cout<<endl;
              }
        }

        if(option==3)
        {
           cout<<"Intorduceti data cautata: ";
           strcpy(d,"");
           cin.sync();
           cin.getline(d,256);
           cout<<endl;
           for(i=0;i<n;i++)
           {
               if(M[i].verifica_data(d)==1)
               {
                   cout<<"Produse din Magazinul "<<i+1;
                   cout<<endl;
               }
               else
               {
                   cout<<"Nu exista produse venite in data respectiva;"
               }
           }
        }
        if(option==4)
        {
            strcpy(d,"");
            cout<<"Introduceti nr magazinului din care vreti sa stergeti un produs ";
            cin>>a;
            cout<<"Introduceti denumirea produsului ";
            cin.sync();
            cin.getline(d,256);
            if(M[a-1].stergere(d))
                cout<<"Produsul a fost sters"<<endl;
            else
                cout<<"Produsul n-a fost gasit"<<endl;
        }

        if(option==5)
        {
            float pretnou;
            cout<<"Alegeti numarul magazinul ";
            cin>>a;
            cout<<"Scrieti indicele produsului pt care vreti sa modificati pretul ";
            cin>>i;
            cout<<"Scrieti noul pret ";
            cin>>pretnou;
            if(a>0&&a<=n)
               if(i>0&&i<=M[a-1].get_produse())
                {
                    M[a-1].modifica_pret(i,pretnou);
                    cout<<"Pretul a fost modificat";
                }
                else
                cout<<"Indice produs invalid";
            else
                cout<<"Nr magazin invalid";
        }

        if(option==6)
        {
            int MAX=0;
            for(i=0;i<n;i++)
             if(M[i].get_produse()>MAX)
              {MAX=M[i].get_produse();
              j=i;
              }
         cout<<endl<<"Magazinul cu numarul "<<j+1<<" are cele mai multe produse, "<<MAX<<" produse.";
         cout<<endl;
        }

        if (option==0)
            cout<<endl<<"EXITING!"<<endl;

        if (option<0||option>6)
            cout<<endl<<"Selectie invalida"<<endl;

        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);


}

///////////////////
int main()
{
   menu();

    return 0;
}
