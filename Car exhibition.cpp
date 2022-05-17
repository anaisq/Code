#include <iostream>
#include <utility>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

class Masina{
    protected:
           string culoare;
           string marca;
           static int numara;
    public:
          Masina(string cul="",string mar=""){numara++;culoare=cul;marca=mar;}
          virtual ~Masina(){ culoare="";marca=""; };
          virtual void citire(istream &in){cout<<"culoare: ";in>>culoare; cout<<"marca: ";in>>marca; }
          virtual void afisare(ostream &out){out<<"CULOARE: "<<culoare<<"\n"<<"MARCA: "<<marca<<endl; }
          ///friend istream & operator>>(istream &in, Masina &m);
          Masina & operator =(const Masina &m){culoare=m.culoare;marca=m.marca; }
          virtual void model(){cout<<"Masina"; };
          static int num(){return numara;}
          virtual void write_type()const{cout<<"Masina";}
          string get_culoare() const { return culoare;}
          string get_marca() const{ return marca;}
          virtual string get_type() const{ return "Masina";}
};
int Masina::numara=0;

class COUPE:public Masina{
    public:
        COUPE(string cul="",string mar=""):Masina(cul,mar){ }
        ~COUPE(){culoare="";marca=""; }
        void citire(istream &in){ Masina::citire(in);}
        void afisare(ostream &out){ Masina::afisare(out);}
        COUPE & operator =(COUPE &C){Masina::operator=(C);}
        void write_type()const{cout<<"COUPE";}
        string get_type() const{ return "COUPE";}
};
class HOT_HATCH:public Masina{
    private:
        string motor;
    public:
        HOT_HATCH(string c="",string m="",string ta=""):Masina(c,m){motor=ta;}
        ~HOT_HATCH(){motor=""; culoare="";marca="";}
        void citire(istream &in){Masina::citire(in); cout<<"motor: ";in>>motor; }
        void afisare(ostream &out){Masina::afisare(out);out<<"MOTOR: "<<motor;}
        HOT_HATCH & operator =(const HOT_HATCH &H){Masina::operator=(H);motor=H.motor;}
        void write_type()const{cout<<"HOT HATCH";}
        string get_type() const{ return "HOTHATCH";}

};
class CABRIO:public Masina{
    private:
        string tip_acoperis;
    public:
        CABRIO(string c="",string m="",string ta=""):Masina(c,m){tip_acoperis=ta;}
        ~CABRIO(){tip_acoperis=""; culoare="";marca="";};
        void citire(istream &in){Masina::citire(in);cout<<"tip acoperis(metalic/textil/altceva): ";in>>tip_acoperis; }
        void afisare(ostream &out){Masina::afisare(out);out<<"TIPUL ACOPERISULUI: "<<tip_acoperis;}
        CABRIO & operator =(const CABRIO &C){Masina::operator=(C);tip_acoperis=C.tip_acoperis;}
        void write_type()const{cout<<"CABRIO";}
        string get_type() const{ return "CABRIO";}


};
class SUPERSPORT:public Masina{
    private:
        double pret;
    public:
        SUPERSPORT(string c="",string m="",double p=0):Masina(c,m){pret=p;}
        ~SUPERSPORT(){ pret=0;culoare="";marca="";};
        SUPERSPORT &operator =(const SUPERSPORT &S){Masina::operator=(S); pret=S.pret;}
        void citire(istream &in){Masina::citire(in); cout<<"pret in mii(eur): ";in>>pret;}
        void afisare(ostream &out){Masina::afisare(out);out<<"PRET: "<<pret;}
        void write_type()const{cout<<"SUPERSPORT";}
        friend bool operator==(SUPERSPORT &S1,SUPERSPORT &S2)
        { string s=S1.get_culoare(); string m=S1.get_marca();
            if(s.compare(S2.get_culoare())==0 && m.compare(S2.get_marca())==0 && S1.pret==S2.pret)
                return 1;
            else
                return 0;
        }
        double get_pret(){return pret;}
        string get_type() const{ return "SUPERSPORT";}

};
template<class T> class Expozitie{
 private: static int nrMasini;
          int nr;
          T *masini;
 public:
         Expozitie(int n=0, T *p=NULL){
             nr=n;
             nrMasini=nrMasini+nr;
             if(nr!=0)
             {
                 masini=new T[nr];
                 for(int i=0;i<nr;i++)
                 {
                     masini[i]=p[i];
                 }
             }
          }

        ~Expozitie(){
          delete []masini;
          nr=0;

         }
        void citire(istream &in){
             cout<<"Nr de masini la expozitie: ";
             in>>nr;
             nrMasini=nr+nrMasini;
             masini=new T[nr];
             cout<<endl;
             for(int i=0;i<nr;i++)
             {
                 cout<<i+1<<". ";
                 in>>masini[i];
                 cout<<endl;
             }
            }
        void afisare(ostream &out){
        for(int i=0;i<nr;i++)
            {
             out<<"\n"<<masini[i];
            }

         }
        friend istream& operator>>(istream &in, Expozitie <T> &E){
             E.citire(in);
             return in;
         }
        friend ostream& operator<<(ostream &out, Expozitie <T> &E){
                E.afisare(out);
                return out;
            }

        Expozitie & operator=(const Expozitie <T> &E){
             nrMasini=E.nrMasini;
           for(int i=0;i<nrMasini;i++)
            masini[i]=E.masini[i];
         }
         static void total(){cout<<nrMasini;}
};

template <class T>
int Expozitie<T>::nrMasini=0;


template <> class Expozitie<SUPERSPORT>{
  private:
     static int nrStoc;
     static int nrVandute;
     vector <SUPERSPORT> masiniStoc;
     vector <SUPERSPORT> masiniVandute;
     vector <pair<SUPERSPORT, double> > evidenta;
  public:
      Expozitie(){ }
      Expozitie(vector <SUPERSPORT> m){
       nrStoc=nrStoc+m.size();
       masiniStoc=m;
       pair<SUPERSPORT, double> p;

       for(int i=0;i<m.size();i++)
       {
           p=make_pair(m[i],-1);
           evidenta.push_back(p);
       }
      }
      Expozitie(vector<SUPERSPORT> v1,vector <SUPERSPORT> v2){
          pair <SUPERSPORT, double> p;
          p.second=-1;
          nrStoc=nrStoc+v1.size();
          nrVandute=nrVandute+v2.size();
          if(!v1.empty())
          {
              for(vector <SUPERSPORT>::iterator i=v1.begin();i!=v1.end();++i)
              {
                  masiniStoc.push_back(*i);
                  p.first=(*i);
                  evidenta.push_back(p);
              }

          }
          if(!v2.empty())
          {
              for(vector <SUPERSPORT>::iterator i=v2.begin();i!=v2.end();++i)
              {
                  masiniVandute.push_back(*i);
                  p.second=i->get_pret();
                  p.first=(*i);
                  evidenta.push_back(p);
              }
          }
      }
      ~Expozitie(){
        masiniStoc.clear();
        masiniVandute.clear();
        evidenta.clear();
      }
      static void nrV(){cout<<nrVandute;}
      static void nrS(){cout<<nrStoc;}
      void citire(istream &in){
          pair <SUPERSPORT, double> p;
          int nr1,nr2;
          SUPERSPORT s1,s2;
          cout<<"Nr masini in stoc: ";
          in>>nr1;
          p.second=-1;
          cout<<"\nIntorduceti pe rand masinile din stoc: ";
          for(int i=0;i<nr1;i++)
          {
              s1.citire(in);
              p.first=s1;
              evidenta.push_back(p);
              masiniStoc.push_back(s1);
          }

          cout<<"\Nr masini vandute: ";
          in>>nr2;
          cout<<"\nIntorduceti pe rand masinile din stoc: ";
          for(int i=0;i<nr2;i++)
          {
              s2.citire(in);
              p.second=s2.get_pret();
              p.first=s2;
              masiniVandute.push_back(s2);
          }
      }
      void afisare(ostream &out){
          out<<"\nSTOC :\n";int j=0;
          for(vector<SUPERSPORT>::iterator i=masiniStoc.begin();i!=masiniStoc.end();++i)
            {   j++;
               out<<j<<") "; (*i).afisare(out); out<<"\n";

            }
         if(masiniVandute.size())
        {   out<<"\nVANDUTE: \n"; j=0; int k;
            for(vector <SUPERSPORT>::iterator i=masiniVandute.begin();i!=masiniVandute.end();++i)
            {
               out<<j+1<<") "; (*i).afisare(out);
               for(k=0;k<(masiniStoc.size()+masiniVandute.size());k++)
               {
                   if(evidenta[k].first==(*i))
                    {
                        break;
                    }
               }
               out<<"\nPretul de vanzare: "<<evidenta[k].second;
               out<<"\n";
               j++;

            }
        }
      }
      Expozitie &operator=(Expozitie <SUPERSPORT> &G){
          for(vector <SUPERSPORT>::iterator i=(G.masiniStoc).begin();i!=(G.masiniStoc).end();++i)
          {
              masiniStoc.push_back(*i);

          }
          for(vector <SUPERSPORT>::iterator i=(G.masiniVandute).begin();i!=(G.masiniVandute).end();++i)
          {
              masiniVandute.push_back(*i);


          }
          evidenta=G.evidenta;
    }
      Expozitie& operator-=(const int nr){
        if(nr<masiniStoc.size()){
        SUPERSPORT S=masiniStoc[nr];
        vector <SUPERSPORT>::iterator i;int n,ok=0; int ask=0;
        pair <SUPERSPORT,double> p;
        do{
          for(i=masiniStoc.begin();i!=masiniStoc.end();++i)
           {
              if(*i==S)
              {

                  cout<<"Valoarea masinii este de "<<i->get_pret();
                  cout<<"\nDoriti sa o vindeti cu alt pret? (1-Da/0-Nu)";
                  cin>>ask;
                  if(ask==1)
                  {
                      double bani;
                      cout<<"\nIntroduceti noul pret in mii: "; cin>>bani;
                      p=make_pair((*i),bani);
                  }
                  else
                  p=make_pair((*i),(i->get_pret()));

                  for(int j=0;j<(masiniStoc.size()+masiniVandute.size());j++)
                  {  if(evidenta[j].first==(*i))
                      {
                          evidenta[j]=p;
                       cout<<"Masina vanduta! :)";
                       ok=1;
                       masiniVandute.push_back(*i);

                       nrStoc--;
                       nrVandute++;
                       masiniStoc.erase(i);
                       return (*this);
                       }
                  }
              }
           }
           }while(ok==0);
      }
      }

      friend istream& operator>>(istream &in, Expozitie <SUPERSPORT> &E){
             E.citire(in);
             return in;
         }
      friend ostream& operator<<(ostream &out, Expozitie <SUPERSPORT> &E){
                E.afisare(out);
                return out;
            }
};
template <>
int Expozitie<SUPERSPORT>::nrStoc=0;
int Expozitie<SUPERSPORT>::nrVandute=0;



/////////
////////////
//////////////citire/afisare
istream & operator>>(istream &in, Masina &m)
 {m.citire(in); return in;}

ostream & operator<<(ostream &out,Masina &m)
 {m.afisare(out); return out;}

 istream & operator>>(istream &in,SUPERSPORT &m)
 {m.citire(in); return in;}

ostream & operator<<(ostream &out,SUPERSPORT &m)
 {m.afisare(out); return out;}

 //////////////////
 ///////////
 //////

 void tip(Masina *&m, int &i){
     string s;
     cout<<"\n(COUPE/HOTHATCH/CABRIO/SUPERSPORT):";
     cout<<"Model nr. "<<i+1<<": ";
     cin>>s;

     try{
         if(s=="COUPE"){

            m=new COUPE;
            cin>>*m;
            i++;
         }
         else{
             if(s=="HOTHATCH"){
                    m=new HOT_HATCH;
                    cin>>*m;
                    i++;
                }
            else{
                if(s=="CABRIO"){
                       m=new CABRIO;
                       cin>>*m;
                       i++;
                    }
                else{
                    if(s=="SUPERSPORT"){
                            m=new SUPERSPORT;
                            cin>>*m;
                            i++;

                        }
                    else{
                        throw 10;
                    }
                }

            }
         }
       }
       catch(bad_alloc bad){
        cout<<"Allocation failure";
        exit(EXIT_FAILURE);
       }
       catch(int n){
        cout<<"Nu exista acest model\n";
       }
 }
 void menu_output(){
    printf("\n FLOREA ANA 211 - Proiect 3- TEMA 5 \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    cout<<"1. Citeste modele"<<endl;
    cout<<"2. Expoztitie de COUPE"<<endl;
    cout<<"3. Expozitie de HOT HATCH"<<endl;
    cout<<"4. Expozitie de CABRIO"<<endl;
    cout<<"5. Expozitie de SUPERSPORT "<<endl;
    cout<<"6. Vinde masina SUPERSPORT"<<endl;
    cout<<"7. Expozitie SUPERSPORT actuala"<<endl;
    cout<<"8. Afiseaza toate modelele de masini"<<endl;
    cout<<"0. Iesire"<<endl;
    cout<<"\n===========================================\n"<<endl;
}
void menu(){
    int option=0,k,n,i,unic=0,u[4];
    Masina **M;
    Expozitie <SUPERSPORT>E2;

    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        cout<<endl;

        if (option==1)
        {
            cout<<"Intorduceti nr de modele: ";
            cin>>n;
            try{
                M=new Masina*[n];
            }
            catch(bad_alloc bad)
            {
                cout<<"Allocation faliure"; exit(EXIT_FAILURE);
            }
            for(i=0;i<n; )
             tip(M[i],i);
         for(i=0;i<4;i++) u[i]=0;
        // if(u[3]!=0){ E2.~Expozitie(); u[3]=0;}
        }

        if (option==2)
        {
            if(u[option-2]==0){
            k=0;
            for(i=0;i<n;i++)
              if(M[i]->get_type()=="COUPE") k++;

            if(k!=0)
            {COUPE c[k]; COUPE *adr;
            k=0;
            for(i=0;i<n;i++)
            {
                adr=dynamic_cast <COUPE*> (M[i]);

              if(adr){
                    c[k]=*adr;
                    k++;
              }
            }
             Expozitie <COUPE> ExpCOUPE(k,c);
            cout<<"Expozitie COUPE:\n-------------------";
            cout<<endl<<ExpCOUPE;
            }
            else {cout<<"Nu exista nicio masina la aceasta expozitie";}

            u[option-2]=1;
            }
            else cout<<"Deja citita";


        }

        if (option==3){
          if(u[option-2]==0){
         k=0;
         for(i=0;i<n;i++)
           if(M[i]->get_type()=="HOTHATCH") k++;
           if(k!=0)
            {HOT_HATCH c[k]; HOT_HATCH *adr;
            k=0;
            for(i=0;i<n;i++)
            {
                adr=dynamic_cast <HOT_HATCH*> (M[i]);

                if(adr){ c[k]=*adr; k++;}
            }

            Expozitie <HOT_HATCH> ExpHOT(k,c);
            cout<<"Expozitie HOT HATCH:\n-------------------";
            cout<<endl<<ExpHOT;
            }
            else {cout<<"Nu exista nicio masina la aceasta expozitie";}
           u[option-2]=1;
          }
          else cout<<"Deja citita";

         }


        if(option==4){
         if(u[option-2]==0){
         k=0;
         for(i=0;i<n;i++)
           if(M[i]->get_type()=="CABRIO") k++;
           if(k!=0){
            CABRIO c[k]; CABRIO *adr;
            k=0;
            for(i=0;i<n;i++)
            {
                adr=dynamic_cast <CABRIO*> (M[i]);

                if(adr){ c[k]=*adr; k++;}
            }

            Expozitie <CABRIO> ExpCABRIO(k,c);
            cout<<"Expozitie CABRIO:\n-------------------";
            cout<<endl<<ExpCABRIO;
           }
           else {cout<<"Nu exista nicio masina la aceasta expozitie";}
           u[option-2]=1;
         }
         else cout<<"Deja citita";

        }


        if(option==5){
            if(u[option-2]==0){
              vector <SUPERSPORT> c;

            SUPERSPORT *adr;
            k=0;
            for(i=0;i<n;i++)
            {
                adr=dynamic_cast <SUPERSPORT*> (M[i]);
                 if(adr){ c.push_back(*adr); k++;}
            }
            if(k!=0)
            {Expozitie <SUPERSPORT> ExpSS(c);
            E2=ExpSS;
            unic=1;
            cout<<"Expozitie SUPERSPORT:\n-------------------";
            cout<<endl<<ExpSS;}
            else {cout<<"Nu exista nicio masina la aceasta expozitie";}
            u[option-2]=1;
          }
          else cout<<"Expozitia a fost deja creata o data";
        }

        if(option==6){
        cout<<"Expozitia SUPERSPORT \n---------------------------\n";
        cout<<E2;
        if(unic==1)
        {int nr;
        cout<<"Ce masina supersport se vinde? Introduceti indicele: ";
        cin>>nr;
        nr--;
        E2-=nr;
        }
        else cout<<"\nNu ati creat inca expozitia SUPERSPORT. (optiunea 5)";
        }

        if(option==7)
        {
            cout<<E2;
            cout<<endl;
            cout<<"S-au vandut: ";  Expozitie <SUPERSPORT>::nrV();
            cout<<"\nMai sunt: ";   Expozitie <SUPERSPORT>::nrS();
        }

        if(option==8)
        {
            for(i=0;i<n;i++)
            {
                cout<<i+1<<". "<<M[i]->get_type()<<"\n------------\n";
                cout<<*M[i];
                cout<<endl<<"---------------------";
                cout<<endl;

            }



        }

        if (option==0)
        {
            cout<<endl<<"~~EXITING~~"<<endl;
        }
        if (option<0||option>8)
        {
            printf("\nSelectie invalida\n");
        }
        cout<<endl;
        system("pause");
        system("cls");
    }
    while(option!=0);
}

int main()
{
    menu();
    return 0;
}
