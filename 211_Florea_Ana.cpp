#include <iostream>
#include <math.h>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <ctime>

using namespace std;

class persoana{
    private:
        char *name;
        int birth_year;
        char gender;
    public:
        persoana(char*,int,char);
        ~persoana();

        void set_name(char*);
        void set_birth_year(int);
        void set_gender(char);

        char* get_name() { return name;}
        int get_birth_year() {return birth_year;}
        char get_gender() {return gender;}
        void citire(istream &in);
        void afisare(ostream &out);
        friend istream& operator>>(istream &in, persoana &a);
        friend ostream& operator<<(ostream &out, persoana &a);
        persoana& operator=(const persoana &A);
        friend class baze_de_date;

};

class baze_de_date{
    private:
        int nr_pers;
        persoana *a;

    public:

        baze_de_date(int);
        ~baze_de_date();

        void afisare();
        void adauga_pers(int);
        void eliminare(char*);
        void eliminare(int);
        void eliminare(char);
        void afisare_nume();
        void afisare_varsta();
        int get_pers() {return nr_pers;}
        void set_pers(int n=0) {nr_pers=n;}
        void spatiere();

};


//Functii persoana

 persoana::persoana(char *name="" , int birth_year=0, char gender='\0')
 {
     strcpy(name,name);
     birth_year=birth_year;
     gender=gender;
}

void persoana::set_name(char* name)
{
    strcpy(name,name);
}
void persoana::set_birth_year(int by)
{
    birth_year=by;
}
void persoana::set_gender(char g)
{
    gender=g;
}

void persoana::citire(istream &in){
char num[256];
cout<<"Nume: ";
cin.sync();
in.getline(num,256);
name=new char[strlen(num)+1];
strcpy(name,num);

//time_t now = time(0);
//tm *ltm = localtime(&now);
int ok=0;
do{
    if(ok!=0)
    {
        cout<<endl<<"Again...Please type in a valid birth year";
    }
    cout<<endl<<"Anul nasterii: ";
    in>>birth_year;
    ok=1;
  }while(birth_year<1910 || birth_year>2020);//(1900 + ltm->tm_year));



do{
    if(ok!=1)
    {
        cout<<"The gender should be 'F' or 'M'";
        cout<<endl<<"Ok, next chance:";
    }
   cout<<endl<<"Sexul (F/M): ";
   in>>gender;
   ok=0;
   }while(gender!='F' && gender!='M');

cout<<endl;
cin.sync();

}



istream& operator>>(istream& in, persoana& a){
a.citire(in);
return in;
}

void persoana::afisare(ostream &out){

out<<name<<'\t'<<"   "<<birth_year<<"   "<<'\t'<<"  "<<gender<<"  ";
out<<endl;
}

ostream& operator<<(ostream& out, persoana &a){
a.afisare(out);
return out;
}

persoana& persoana::operator=(const persoana &A){
    if(this!=&A)
    {
    name=new char[strlen(A.name)+1];
    strcpy(this->name,A.name);
    this->birth_year=A.birth_year;
    this->gender=A.gender;

    }
    return *this;
}

persoana::~persoana()
 {
     delete []name;
 }

//Functii pt clasa baze_de_date


baze_de_date::baze_de_date(int n=0){
    if(n!=0)
    {
         a=new persoana[n+1];
    }
    else
        a=new persoana[n+1];

       }

void baze_de_date::afisare()
 {
     cout<<endl<<"In clasa baze de date se afla: "<<endl;
     cout<<"        NUME        "<<'\t'<<"AN NASTERE"<<'\t'<<"SEXUL"<<endl;
     cout<<"***************************************************"<<endl;

         cout<<a[i];
     }
     cout<<endl<<"***************************************************";
     cout<<endl<<"Exista "<<nr_pers<<" persoane in baza de date"<<endl;
 }

baze_de_date::~baze_de_date(){
 delete []a;}

 void baze_de_date::adauga_pers(int n=0)
    {
        int i=nr_pers;
        while(i<n+nr_pers)
        {
            cin>>a[i];
                i++;
        }
        nr_pers=nr_pers+n;
    }

void baze_de_date::eliminare(char *p)
 {
     char spatiu[30]="                            ";
    if(strlen(p)<20)
         {
             int n=20-strlen(p);
             strncat(p,spatiu,n);
         }
     for(int i=0;i<nr_pers;i++)
      {
          if(strcmp(a[i].name,p)==0)
        {
            for(int j=i;j<nr_pers-1;j++)
            a[j]=a[j+1];
           nr_pers--; i--;
        }
      }

 }
 void baze_de_date::eliminare(int by)
 {
     for(int i=0;i<nr_pers;i++)
       {
           if(a[i].birth_year==by)
        {
             for(int j=i;j<nr_pers-1;j++)
               a[j]=a[j+1];
           nr_pers--; i--;
        }
       }
 }

 void baze_de_date::eliminare(char gen)
    {
        for(int i=0;i<nr_pers;i++)
         {
              if(a[i].gender==gen)
           {
               for(int j=i;j<nr_pers-1;j++)
                    a[j]=a[j+1];
            nr_pers--; i--;
           }
         }
    }
void baze_de_date::afisare_nume()
{
    char aux[256],copie[nr_pers][30];

    for(int i=0;i<nr_pers;i++)
    {
        strcpy(copie[i],a[i].name);
    }

    for(int i=1; i<nr_pers; i++)
        {
                for(int j=1; j<nr_pers; j++)
                {
                        if(strcmp(copie[j-1], copie[j])>0)
                        {
                                strcpy(aux, copie[j-1]);
                                strcpy(copie[j-1], copie[j]);
                                strcpy(copie[j], aux);
                        }

                }

        }
        int v[nr_pers]={0};
     cout<<"        NUME        "<<'\t'<<"AN NASTERE"<<'\t'<<"SEXUL"<<endl;
     cout<<"***************************************************"<<endl;
         for(int i=0; i<nr_pers; i++)
        {       cout<<endl;
                cout<<"      "<<copie[i];
                for(int j=0;j<nr_pers;j++)
                {
                    if(strcmp(a[j].name,copie[i])==0 && v[j]!=1)
                    {
                        cout<<"    "<<a[j].birth_year<<"    "<<"   "<<a[j].gender;
                        v[j]=1;
                        break;
                        //j=nr_pers;

                    }

                }
        }
cout<<endl<<"***************************************************"<<endl;
}





void baze_de_date::afisare_varsta()
 {
     cout<<endl;
     cout<<"        NUME        "<<'\t'<<"AN NASTERE"<<'\t'<<"SEXUL"<<endl;
     cout<<"***************************************************"<<endl;
    int ani[nr_pers], aux;

    for(int i=0;i<nr_pers;i++)
        ani[i]=a[i].birth_year;

   for(int i=0;i<nr_pers-1;i++)
    for(int j=i;j<nr_pers;j++)
    if(ani[i]<ani[j])
   {
       aux=ani[i];
       ani[i]=ani[j];
       ani[j]=aux;
   }
    char num[256];
    for(int i=0;i<nr_pers;i++)
        {for(int j=0;j<nr_pers;j++)
            if(ani[i]==a[j].birth_year && strcmp(a[j].name,num)!=0)
                {

                 cout<<"      "<<a[j].name<<"    "<<ani[i]<<"   "<<"   "<<a[j].gender<<endl;
                 strcpy(num,a[j].name);
                 break;

                }
        }
 cout<<endl<<"***************************************************"<<endl;
 }

void baze_de_date::spatiere(){
    char spatiu[30]="                             ";
         for(int i=0;i<nr_pers;i++)
     {
         if(strlen(a[i].name)<20)
         {
             int n=20-strlen(a[i].name);
             strncat(a[i].name,spatiu,n);
         }
     }
}

///////////////////////////////////
void menu_output()
{
    cout<<"\n FLOREA ANA 211 - Proiect - TEMA 13: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Afisati continutul bazei de date"<<endl;
    cout<<"2. Adauga persoane in baza de date"<<endl;
    cout<<"3. Elimina persoana din baza de date in functie de nume"<<endl;
    cout<<"4. Elimina persoana din baza de date in functie de anul nasterii"<<endl;
    cout<<"5. Elimina persoana din baza de date in functie de sex"<<endl;
    cout<<"6. Afiseaza persoanele din baza de date ordonate alfabetic"<<endl;
    cout<<"7. Afiseaza persoanele din baza de date ordonate crescator in functie de varsta"<<endl;
    cout<<"0. Iesire."<<endl;
}


void menu()
{
    int option=0;

    baze_de_date b(100);
    b.set_pers();


    do
    {
        menu_output();
        cout<<endl<<"Introduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            b.afisare();
        }
        if (option==2)
        {
            int n;
            cout<<endl<<"Cate persoane ati dori sa adaugati?"<<endl;
            cin>>n;
            b.adauga_pers(n);
            b.spatiere();
        }

        if (option==3)
        {
           char nume[256];
           int n=b.get_pers();
           cout<<endl<<"Scrieti numele intreg al persoanei pe care doriti sa o eliminati: ";
           cin.clear();
           cin.ignore();
           cin.sync();
           cin.getline(nume,256);
           char nm[256];
           strcpy(nm,nume);
           b.eliminare(nume);
           if(n!=b.get_pers())
            cout<<"Persoana cu numele "<<nm<<" a fost eliminata din baza de date"<<endl;
           else
            cout<<"Persoana cu numele "<<nm<<" nu a fost gasita"<<endl;
        }
        if (option==4)
        {
            int an;
            int n=b.get_pers();
            cout<<endl<<"Scrieti anul nasterii persoanelor pe care doriti sa le eliminati: ";
            cin>>an;
            b.eliminare(an);
            if(n!=b.get_pers())
            cout<<"Persoanele nascute in anul "<<an<<" au fost eliminate din baza de date"<<endl;
           else
            cout<<"Nu a fost gasita nicio persoana nascuta in anul "<<an<<endl;
        }
        if (option==5)
        {
         char gen;
         int n=b.get_pers();
         cout<<endl<<"Scrieti sexul persoanelor pe care doriti sa le eliminati: ";
         cin>>gen;
         b.eliminare(gen);
         if(n!=b.get_pers())
            cout<<"Persoanele de sexul "<<gen<<" au fost eliminate din baza de date"<<endl;
           else
            cout<<"Nu a fost gasita nicio de sex "<<gen<<endl;
        }
        if (option==6)
        {
         cout<<endl<<endl;
         b.afisare_nume();

        }
        if (option==7)
        {
         cout<<endl<<endl;
         b.afisare_varsta();

        }
        if (option==0)
            cout<<endl<<"EXITING!"<<endl;

        if (option<0||option>7)
            cout<<endl<<"Selectie invalida"<<endl;

        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}


///////////////////////////////////
 int main(){
     system("Color 3F");
     menu();


 return 0;
 }
