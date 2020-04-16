#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;


class Monom{
    private: int grad;
             float coef;
    public: Monom(int g=0, float c=0) { grad=g; coef=c;}
            ~Monom() { grad=0; coef=0;}
            Monom(Monom &x) { grad=x.grad; coef=x.coef;}
            Monom& operator=(Monom &x) {grad=x.grad; coef=x.coef;}
            friend istream& operator>>(istream &in,Monom &x);
            friend ostream& operator<<(ostream &out,Monom &y);
            friend bool operator>(Monom &x, float n);
            int get_grad(){return grad;}
            float get_coef(){return coef;}

};
class Polinom{
    protected: int nr_monoame;
             Monom *m;
             static int n;
    public: Polinom() {n++; nr_monoame=0; m=new Monom[1]; }//m=NULL;}
            Polinom(int nr, Monom *x);
            ~Polinom();
            Polinom(Polinom &P);
            Polinom& operator=(Polinom &P);
            friend istream& operator>>(istream &in,Polinom &x);
            friend ostream& operator<<(ostream &out,Polinom &y);
            virtual void citire(istream &in);
            virtual void afisare(ostream &out);
            static void nrPolinoame(){cout<<n;}
            void sortare_grad();
            int Cmmdc(int n,int *v);
            virtual void WhereAmI() {cout<<"Polinom";}
            int Eisenstein(){return 0;};
            virtual void afisare_produs(){ cout<<"Trebuie sa stii daca polinomul e reductibil";}
};
class Polinom_ireductibil:public Polinom{

    public: Polinom_ireductibil(int nr, Monom *x):Polinom(nr,x){}
            Polinom_ireductibil():Polinom(){}
            ~Polinom_ireductibil() {}
            Polinom_ireductibil(Polinom_ireductibil & x):Polinom(x){}
            Polinom_ireductibil(Polinom & x):Polinom(x){}
            Polinom_ireductibil& operator=(Polinom_ireductibil &P);
            friend istream& operator>>(istream &in,Polinom_ireductibil &x);
            friend ostream& operator<<(ostream &out,Polinom_ireductibil &y);
            void citire(istream &in);
            void afisare(ostream &out);
            int Eisenstein();
            void WhereAmI(){cout<<"Polinom_ireductibil";}
            void afisare_produs();

};
class Polinom_reductibil:public Polinom{

    public:Polinom_reductibil(int nr, Monom *x):Polinom(nr,x){}
            Polinom_reductibil():Polinom(){}
            ~Polinom_reductibil() {}
            Polinom_reductibil(Polinom_ireductibil& x):Polinom(x){}
            Polinom_reductibil(Polinom & x):Polinom(x){}
            Polinom_reductibil& operator=(Polinom_reductibil &P);
            friend istream& operator>>(istream &in,Polinom_reductibil &x);
            friend ostream& operator<<(ostream &out,Polinom_reductibil &y);
            void citire(istream &in);
            void afisare(ostream &out);
            int Eisenstein();
            void WhereAmI(){cout<<"Polinom_reductibil";}
            void afisare_produs();
};
///////////
int Polinom:: n;
///////////Polinom
Polinom::Polinom(int nr, Monom *x){n++;
 nr_monoame=nr;
 m=new Monom[nr_monoame];
 for(int i=0;i<nr;i++)
    m[i]=x[i];
 }
 Polinom::Polinom(Polinom &P){
     nr_monoame=P.nr_monoame;
     for(int i=0;i<nr_monoame;i++)
        m[i]=P.m[i];
 }
Polinom::~Polinom(){
 //   Monom M[nr_monoame];
   // for(int i=0;i<nr_monoame;i++)
     //  m[i]=M[i];
    delete []m;
    nr_monoame=0;
    }
 Polinom& Polinom::operator=(Polinom &P){
     nr_monoame=P.nr_monoame;
     for(int i=0;i<nr_monoame;i++)
        m[i]=P.m[i];
 }
 void Polinom::citire(istream&in){
    cout<<"Nr de monoame: ";
     in>>nr_monoame;
     m=new Monom[nr_monoame];
     for(int i=0;i<nr_monoame;i++)
     {
         cout<<"Monom nr. "<<i+1;
         in>>m[i];
     }
 }
 istream& operator>>(istream &in, Polinom &x) {
  x.citire(in);
  return in;
 }
 void Polinom::afisare(ostream&out){
     sortare_grad();
     out<<m[0];
     for(int i=1;i<nr_monoame;i++)
      {
          if(m[i]>0)
            out<<"+"<<m[i];
          else
            out<<m[i];
      }
 }
 ostream& operator<<(ostream &out, Polinom &x){
     x.afisare(out);
     return out;
 }
void Polinom::sortare_grad(){
  int i,j;
  Monom aux;
    for(i=0;i<nr_monoame-1;i++)
    {
      for(j=i;j<nr_monoame;j++)
       {if(m[i].get_grad()<m[j].get_grad())
          {aux=m[i];
           m[i]=m[j];
           m[j]=aux;
          }


      }
    }
}
//////////// Monom
istream& operator>>(istream &in, Monom &x){
    cout<<" grad: ";
    in>>x.grad;
    cout<<" coeficient ";
    in>>x.coef;
    return in;
}
ostream& operator<<(ostream &out, Monom &x){
    if(x.grad!=0)
    out<<x.coef<<"X^"<<x.grad;
    else
    out<<x.coef;
    return out;
}
bool operator>(Monom &x, float n){
    return x.coef>n;
}
////////////Polinom_ireductibil
void Polinom_ireductibil::citire(istream &in){
    cout<<"Clasa Polinom_ireductibil :"<<endl;
    cout<<"Nr de monoame: ";
     in>>nr_monoame;
     m=new Monom[nr_monoame];
     for(int i=0;i<nr_monoame;i++)
     {
         cout<<"Monom nr. "<<i+1;
         in>>m[i];
     }
         if(Eisenstein()==10)

     while(Eisenstein()==0 || Eisenstein()==10)
     {
         if(Eisenstein()==0)
         cout<<"Atentie, nu se poate spune daca polinomul este ireductibil sau nu";
         else cout<<"Atentie, polinomul este reductibil";
         cout<<endl<<"Introduceti altul: ";
         delete []m;
         in>>nr_monoame;
         m=new Monom[nr_monoame];
         for(int i=0;i<nr_monoame;i++)
         {
         cout<<"Monom nr. "<<i+1;
         in>>m[i];
         }
     }
}
void Polinom_ireductibil::afisare(ostream &out){
        sortare_grad();
         try{
         if(Eisenstein()==0)
            throw 13;
         if(Eisenstein()==10)
                throw 17;
        }
        catch(int x)
        {
            if(x==13)
            {out<<"Nu se poate spune sigur daca este ireductibi, intorduceti coeficenti nenul pt siguranta";
            exit(EXIT_FAILURE);}
            else
            out<<"Polinomul introdus reductibil "<<endl;
        }
        //out<<"Eisen: "<<Eisenstein();
     out<<m[0];
     for(int i=1;i<nr_monoame-1;i++)
      {
          if(m[i]>0)
            out<<"+"<<m[i];
          else
            out<<m[i];
      }


            if(m[nr_monoame-1]>0)
            out<<"+"<<m[nr_monoame-1];
          else
            out<<m[nr_monoame-1];

      }
Polinom_ireductibil& Polinom_ireductibil::operator=(Polinom_ireductibil &P){
     Polinom::operator=(P);
    /* nr_monoame=P.nr_monoame;
     for(int i=0;i<nr_monoame;i++)
        m[i]=P.m[i];*/
}
istream& operator>>(istream &in,Polinom_ireductibil &x){
    x.citire(in);
    return in;
}
ostream& operator<<(ostream &out,Polinom_ireductibil &x){
    x.afisare(out);
    return out;
}
int Polinom_ireductibil::Eisenstein(){
 sortare_grad();
 int w[nr_monoame],copie,i,j,p,c=0;
 int mini=m[nr_monoame-1].get_grad();

 if(mini!=0) return 10;
 //pas 1
 for(i=0;i<nr_monoame;i++)
    if(m[i].get_coef()<0)
        w[i]=0-(int)(m[i].get_coef());
        else
        w[i]=(int)m[i].get_coef();

 //pas 2
 //int minim=(int)mini;
  if(Cmmdc(nr_monoame,w)!=1) return 0;
  int minim=w[nr_monoame-1];
//cout<<minim<<" "<<w[0];
       for(i=2;i<=minim;i++)
        {c=0;
            if(minim%i==0 && w[0]%i!=0 && minim%(i*i)!=0)
            {
                //cout<<"iiiiiii"<<i<<" bb "<<minim%(i*i)<<" bb "<<endl;
                for(j=1;j<nr_monoame;j++)
                {
                    if(w[j]%i==0)
                    {
                      // p=i;
                       c++;
                    }
                }
                //cout<<"ccccc: "<<c<<endl;
            if(c==nr_monoame-1)
            {
                 //if(Cmmdc(nr_monoame,w)==1)
                  //  {
                        return 1;
                 //   }
               //  else return -1;

            }
            }
        }
        return 0;


}
void Polinom_ireductibil::afisare_produs(){ cout<<"Esti intr-un polinom ireductibil, nu se poate";}
////////////Polinom_reductibil
void Polinom_reductibil::citire(istream &in){
    cout<<"Clasa Polinom_reductibil :"<<endl;
    cout<<"Nr de monoame: ";
     in>>nr_monoame;
     m=new Monom[nr_monoame];
     for(int i=0;i<nr_monoame;i++)
     {
         cout<<"Monom nr. "<<i+1;
         in>>m[i];
     }
     while(Eisenstein()==1)
        {cout<<"Polinomul introdus nu este reductibil";
         cout<<"\nIntroduceti altul : ";
         cout<<"Nr de monoame: ";
         delete []m;
        in>>nr_monoame;
        m=new Monom[nr_monoame];
     for(int i=0;i<nr_monoame;i++)
     {
         cout<<"Monom nr. "<<i+1;
         in>>m[i];
     }
        }
    //cout<<"Atentie, acesst polinom poate fi ireductibil";

}
void Polinom_reductibil::afisare(ostream &out){
  sortare_grad();
   try{
         if(Eisenstein()==1)
            throw 13;
        }
        catch(int x)
        {
            cout<<"Polinomul introdus nu este reductibil";
            exit(EXIT_FAILURE);
        }
     out<<m[0];
     for(int i=1;i<nr_monoame-1;i++)
      {
          if(m[i]>0)
            out<<"+"<<m[i];
          else
            out<<m[i];
      }


            if(m[nr_monoame-1]>0)
            out<<"+"<<m[nr_monoame-1];
          else
            out<<m[nr_monoame-1];

}
Polinom_reductibil& Polinom_reductibil::operator=(Polinom_reductibil &P){
     Polinom::operator=(P);
    /* nr_monoame=P.nr_monoame;
     for(int i=0;i<nr_monoame;i++)
        m[i]=P.m[i];*/
}
istream& operator>>(istream &in,Polinom_reductibil &x){
    x.citire(in);
    return in;
}
ostream& operator<<(ostream &out,Polinom_reductibil &x){
    x.afisare(out);
    return out;
}
int Polinom_reductibil::Eisenstein(){
 sortare_grad();
 int w[nr_monoame],copie,i,j,p,c=0;
 int mini=m[nr_monoame-1].get_grad();

 if(mini!=0) return 10;
 //pas 1
 for(i=0;i<nr_monoame;i++)
    if(m[i].get_coef()<0)
        w[i]=0-(int)(m[i].get_coef());
        else
        w[i]=(int)m[i].get_coef();

 //pas 2
 //int minim=(int)mini;
  if(Cmmdc(nr_monoame,w)!=1) return 0;
  int minim=w[nr_monoame-1];
//cout<<minim<<" "<<w[0];
       for(i=2;i<=minim;i++)
        {c=0;
            if(minim%i==0 && w[0]%i!=0 && minim%(i*i)!=0)
            {
                //cout<<"iiiiiii"<<i<<" bb "<<minim%(i*i)<<" bb "<<endl;
                for(j=1;j<nr_monoame;j++)
                {
                    if(w[j]%i==0)
                    {
                      // p=i;
                       c++;
                    }
                }
              //  cout<<"ccccc: "<<c<<endl;
            if(c==nr_monoame-1)
            {
                 //if(Cmmdc(nr_monoame,w)==1)
                  //  {
                        return 1;
                 //   }
               //  else return -1;

            }
            }
        }
        return 0;

}
void Polinom_reductibil::afisare_produs(){
    sortare_grad();
    if(m[0].get_coef()!=1) {cout<<"\nCoeficientul monomului principal trebuie sa fie 0\n"; exit(0);}
    int grad_max=m[0].get_grad(),p=0,grad_min=m[nr_monoame-1].get_grad();
    int w[grad_max+1],i,coef_min=(int)m[nr_monoame-1].get_coef();
    w[grad_max]=(int)m[0].get_coef();
    if(coef_min<0)
        coef_min=(-1)*coef_min;

    for(i=0;i<grad_max;i++)
        {w[i]=0; }
    for(i=1;i<nr_monoame;i++)
       {
           w[m[i].get_grad()]=(int)m[i].get_coef();
       }
    int sum=0;

    for(i=1;i<=coef_min;i++)
    { sum=0;
        if(coef_min%i==0)
        { //cout<<endl<<"IIII::: "<<i<<" ";
            for(int j=0;j<nr_monoame;j++)
            {
                sum=sum+((int)m[j].get_coef())*pow(i,m[j].get_grad());
            }
           // cout<<" "<<sum;
            if(sum==0)
               {p=i;
             break;
               }
            if(sum!=0)
            { sum=0;
                for(int j=0;j<nr_monoame;j++)
            {
                if((int)m[j].get_grad()%2==0)
                sum=sum+((int)m[j].get_coef())*pow(i,m[j].get_grad());
                else
                sum=sum-((int)m[j].get_coef())*pow(i,m[j].get_grad());
            }
               // cout<<" "<<sum;
                if(sum==0)
               {p=(-1)*i;
                break;
               }
            }
        }
      //  cout<<endl<<sum<<" "<<p<<endl;
      //  if(sum==0 && p!=0) break;
    }

   for(i=grad_max-1;i>=0;i--)
    {
        w[i]=p*w[i+1]+w[i];
    }

    if(grad_min==0)
    {
        if(p<=0)
        cout<<"(X+"<<p*(-1)<<")("<<w[grad_max]<<"X^"<<grad_max-1;
        else
            cout<<"(X"<<p*(-1)<<")("<<w[grad_max]<<"X^"<<grad_max-1;
        for(i=grad_max-1;i>0;i--)
            if(w[i]>=0)
              cout<<"+"<<w[i]<<"X^"<<i-1;
            else
              cout<<w[i]<<"X^"<<i-1;
            cout<<")";
    }
    else
    {
        cout<<"X("<<m[0].get_coef()<<"X^"<<m[0].get_grad()-1;
        for(i=1;i<nr_monoame;i++)
            if(m[i].get_coef()>0)
              cout<<"+"<<m[i].get_coef()<<"X^"<<m[i].get_grad()-1;
            else
              cout<<m[i].get_coef()<<"X^"<<m[i].get_grad()-1;
            cout<<")";
    }

}
//////////Functii exterioare
int Polinom::Cmmdc(int n,int *w){
   int i,cmmdc=w[0];


   for(i=1;i<n;i++)
   {
       int copie=w[i];
       while(copie!=cmmdc)
       {
           if(copie>cmmdc)
           {
               copie=copie-cmmdc;
           }
           else cmmdc=cmmdc-copie;
       }
   }
   return cmmdc;
}
///////////
void tip(Polinom *&P, int &i) {
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul polinomului(P/Pi/Pr) "<<i+1<<": ";
    cin>>s;
    try{
        if(s=="P"){
                P=new Polinom;
                cin>>*P;
                i++;
        }
        else
            if(s=="Pi"){
                P=new Polinom_ireductibil;
                cin>>*P;
                i++;
            }
            else
                if (s=="Pr"){
                    P=new Polinom_reductibil;
                    cin>>*P;
                    i++;
                }
                else
                    throw 10;
    }
    catch (bad_alloc var){
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j){
        cout<<"Nu ati introdus un post valid. Incercati P,Pr,Pi.\n ";
    }
}

///////////Meniu
void menu_output(){
    printf("\n FLOREA ANA 211 - Proiect 2- TEMA 13 \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    cout<<"1.Introduceti un polinom(polinom/polinom_ireductibil/polinom_reductibil"<<endl;
    cout<<"2.Afisati toate polinoamele"<<endl;
    cout<<"3.Afisati polinoamele reductibile ca produs de 2 polinoame"<<endl;
    cout<<"4.Downcast"<<endl;
    cout<<"0.Iesire. "<<endl;
    cout<<"\n===========================================\n"<<endl;
}
void menu(){
    int option=0;
    Polinom **v;
    int n;

    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        cout<<endl;

        if (option==1)
        {
          cout<<"Introduceti numarul de polinoame citite: ";
          cin>>n;

    try{
        v=new Polinom*[n];
        for(int i=0;i<n;)
            tip(v[i],i);

        }
    catch (bad_alloc var){
        cout<<"Numarul introdus trebuie sa fie pozitiv. Bad Alloc!\n";
        exit(EXIT_FAILURE);
    }

        }

        if (option==2)
        {
        for(int i=0;i<n;i++){
            cout<<"\n";
            cout<<*v[i]<<" ";
            v[i]->WhereAmI();}
        }

        if (option==3)
        {
         int ind;
         cout<<endl<<"Alegeti un polinom reductibil : ";
         cin>>ind;
         while(v[ind-1]->Eisenstein()!=0)
         {
             cout<<"Introduceti un polinom reductibil valid";
             cin>>ind;
         }
         //Polinom_ireductibil IRE()
         v[ind-1]->afisare_produs();
        }
        if(option==4)
        {
            int op,ind;
            cout<<"Polinom_ireductibil -> Polinom (1)\n";
            cout<<endl<<"Polinom_reductibil -> Polinom (2)\n";
            cin>>op;

            if(op==1)
            {
                Polinom_ireductibil *d=new Polinom_ireductibil;
                cout<<"\n In momentul actual constructorul din Polinom s-a apelat de ";
                Polinom::nrPolinoame();
                cout<<endl;
                cout<<" Acum sunt -> ";
                d->WhereAmI();cout<<endl;
                d=(Polinom_ireductibil*)new Polinom;
                cout<<"\n Acum sunt -> ";
                d->WhereAmI(); cout<<endl;

            }
            if(op==2)
            {  Polinom_reductibil *d=new Polinom_reductibil;
            cout<<"\n In momentul actual constructorul din Polinom s-a apelat de ";
               Polinom::nrPolinoame();
                cout<<" ori. "<<endl;
                cout<<" Acum sunt -> ";
                d->WhereAmI();cout<<endl;
                d=(Polinom_reductibil*)new Polinom;
                cout<<"\n Acum sunt -> ";
                d->WhereAmI(); cout<<endl;


            }
            cout<<"\n Dupa downcast s-a apelat de ";
            Polinom::nrPolinoame();

        }
        if (option==0)
        {
            cout<<endl<<"~~EXITING~~"<<endl;
        }
        if (option<0||option>4)
        {
            printf("\nSelectie invalida\n");
        }
        cout<<endl;
        system("pause");
        system("cls");
    }
    while(option!=0);


}

////////////
int main()
{
   menu();

    return 0;
}
