//TP 2021/2022: LV 14, Zadatak 2
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <new>

class Spremnik{
    protected:
    char ime_sadrzaja[20];
    double tezina_spremnika;
    public:
    Spremnik(const char* ime,double tezina):tezina_spremnika(tezina){
        std::strcpy(ime_sadrzaja,ime);
    }
    double DajTezinu() const{
        return tezina_spremnika;
    }
    virtual double DajUkupnuTezinu() const=0;
    virtual void Ispisi() const=0;
    virtual ~Spremnik(){}
    virtual Spremnik* DajKopiju() const=0;
};
class Sanduk : public Spremnik{
    double tezina_predmeta;
    int broj_predmeta;
    public:
    Sanduk(double tezina,const char* ime,int broj,double tezina_pr):
    Spremnik(ime,tezina),tezina_predmeta(tezina_pr),broj_predmeta(broj){
    }
    double DajUkupnuTezinu() const override{
        return DajTezinu()+(broj_predmeta*tezina_predmeta);
    }
    void Ispisi() const override{
        std::string ime=ime_sadrzaja;
        std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
        std::cout<<"Sadrzaj: "<<ime<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
    Spremnik* DajKopiju() const override{
        return new Sanduk(*this);
    }
};
class Bure : public Spremnik{
    double tezina_tecnosti;
    public:
    Bure(double tezina,const char* ime,double tezina_pr):
    Spremnik(ime,tezina),tezina_tecnosti(tezina_pr){
    }
    double DajUkupnuTezinu() const override{
        return DajTezinu()+tezina_tecnosti;
    }
    void Ispisi() const override{
        std::string ime=ime_sadrzaja;
        std::cout<<"Vrsta spremnika: Bure"<<std::endl;
        std::cout<<"Sadrzaj: "<<ime<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
    Spremnik* DajKopiju() const override{
        return new Bure(*this);
    }
};
class Skladiste{
    Spremnik** Glavni_pok;
    int max_broj,trenutni_broj;
    public:
    explicit Skladiste(int max): max_broj(max),trenutni_broj(0),Glavni_pok(new Spremnik*[max]{}){}
    ~Skladiste(){
        for(int i=0;i<max_broj;i++) delete Glavni_pok[i]; delete[] Glavni_pok;
    }
    Skladiste(const Skladiste &x) : max_broj(x.max_broj),trenutni_broj(x.trenutni_broj),Glavni_pok(new Spremnik*[x.max_broj]{}){
        for(int i=0;i<x.trenutni_broj;i++) Glavni_pok[i]=x.Glavni_pok[i]->DajKopiju(); 
    }
    Skladiste(Skladiste &&x) : max_broj(x.max_broj),trenutni_broj(x.trenutni_broj),Glavni_pok(x.Glavni_pok){
        x.Glavni_pok=nullptr;
    }
    Skladiste& operator=(const Skladiste &x){
        Spremnik** pomS=new Spremnik*[x.max_broj]{};

        for(int i=0;i<x.trenutni_broj;i++){
            pomS[i]=x.Glavni_pok[i]->DajKopiju();
        }
        for(int i=0;i<trenutni_broj;i++) delete Glavni_pok[i]; delete[] Glavni_pok;
        trenutni_broj=x.trenutni_broj; max_broj=x.max_broj;
        Glavni_pok=pomS;
        return *this;
    }
    Skladiste& operator=(Skladiste &&x){
        std::swap(Glavni_pok,x.Glavni_pok);
        std::swap(max_broj,x.max_broj);
        std::swap(trenutni_broj,x.trenutni_broj);
        return *this;
    }
    void DodajSanduk(double tezina,const char* ime,int broj,double tezina_pr){
        Sanduk* pomS=new Sanduk(tezina,ime,broj,tezina_pr);
        if(trenutni_broj==max_broj) throw std::domain_error("Popunjeno skladiste");
        Glavni_pok[trenutni_broj++]=pomS;
    }
    void DodajBure(double tezina,const char* ime,double tezina_pr){
        Bure* pomB=new Bure(tezina,ime,tezina_pr);
        if(trenutni_broj==max_broj) throw std::domain_error("Popunjeno skladiste");
        Glavni_pok[trenutni_broj++]=pomB;
    }
    Spremnik& DajNajlaksi() const{
        if(trenutni_broj==0) throw std::range_error("Skladiste je prazno");
        return **std::min_element(Glavni_pok,Glavni_pok+trenutni_broj,[](Spremnik* x,Spremnik* y){
            if(x->DajTezinu()>y->DajTezinu()) return false;
            else if(x->DajUkupnuTezinu()>y->DajUkupnuTezinu()) return false;
            return true;
        });
    }
    Spremnik& DajNajtezi() const{
        if(trenutni_broj==0) throw std::range_error("Skladiste je prazno");
        return **std::max_element(Glavni_pok,Glavni_pok+trenutni_broj,[](Spremnik* x,Spremnik* y){
            if(x->DajTezinu()>y->DajTezinu()) return false;
            return true;
        });
    }
    int BrojPreteskih(int granica) const{
        return std::count_if(Glavni_pok,Glavni_pok+trenutni_broj,[granica](Spremnik* x){
            if(x->DajUkupnuTezinu()>granica) return true;
            return false;
        });
    }
    void IzlistajSkladiste() const{
        std::vector<Spremnik*> pom;
        std::copy(Glavni_pok,Glavni_pok+trenutni_broj,std::back_inserter(pom));
        std::sort(pom.begin(),pom.end(),[](Spremnik* x,Spremnik* y){
            return x->DajUkupnuTezinu()>y->DajUkupnuTezinu();
        });
        std::for_each(pom.begin(),pom.end(),[](Spremnik* x){
            x->Ispisi();
        });
    }
    void UcitajIzDatoteke(std::string ime_datoteke){
        std::ifstream ulazni_tok(ime_datoteke);
        if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
        for(int i=0;i<max_broj;i++) delete Glavni_pok[i]; delete[] Glavni_pok;
        for(;;){
            std::string prvi,drugi;
            std::getline(ulazni_tok,prvi); std::getline(ulazni_tok,drugi);
            if(!ulazni_tok) break;
            max_broj++;
        }
        ulazni_tok.clear();
        ulazni_tok.seekg(0);
        Glavni_pok=new Spremnik*[max_broj]{};
        trenutni_broj=0;
        char znak1,znak2,ime[20]; 
        for(;;){
            ulazni_tok>>znak1;
            ulazni_tok.get(znak2);
            ulazni_tok.getline(ime,sizeof ime);
            if(!ulazni_tok){
                break;
            } 
            if(znak1=='B'){
                double tezina1,tezina2;
                ulazni_tok>>tezina1>>tezina2;
                if(!ulazni_tok)throw std::logic_error("Datoteka sadrzi besmislene podatke");
                Glavni_pok[trenutni_broj++]=new Bure(tezina1,ime,tezina2);
                ulazni_tok.ignore(1000,'\n');
            }
            else if(znak1=='S'){
                double tezina1,tezina2; int br;
                ulazni_tok>>tezina1>>br>>tezina2;
                if(!ulazni_tok)throw std::logic_error("Datoteka sadrzi besmislene podatke");
                Glavni_pok[trenutni_broj++]=new Sanduk(tezina1,ime,br,tezina2);
                ulazni_tok.ignore(1000,'\n');
            }
            else throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
        if(ulazni_tok.bad()) throw std::logic_error("Problemi pri citanju datoteke");
    }
};

int main ()
{
	return 0;
}
