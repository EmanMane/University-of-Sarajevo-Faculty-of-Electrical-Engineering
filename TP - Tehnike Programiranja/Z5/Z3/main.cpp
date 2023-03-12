//TP 2021/2022: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

/***********************************************************/
class Spremnik{
    protected:
    double tezina;
    std::string ime_sadrzaja;
    public:
    Spremnik(double tezina,std::string ime):tezina(tezina),ime_sadrzaja(ime){}
    virtual double DajTezinu() const{return tezina;}
    virtual double DajUkupnuTezinu() const=0;
    virtual void Ispisi() const=0;
    virtual ~Spremnik(){}
    virtual Spremnik* DajKopiju() const=0;
};
/////////////////////////////////////////////////////////////
class Sanduk : public Spremnik{
    std::vector<double> tezine_predmeta;
    public:
    Sanduk(double tezina,std::string ime,std::vector<double> vektor_tezine):Spremnik(tezina,ime){
        tezine_predmeta=vektor_tezine;
    }
    double DajUkupnuTezinu() const override;
    void Ispisi() const override;
    Spremnik* DajKopiju() const override{
        return new Sanduk(*this);
    }
};
double Sanduk::DajUkupnuTezinu() const{
    double ukupna=tezina;
    for(int i=0;i<tezine_predmeta.size();i++) ukupna+=tezine_predmeta.at(i);
    return ukupna;
}
void Sanduk::Ispisi() const{
    std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
    std::cout<<"Sadrzaj: "<<ime_sadrzaja<<std::endl;
    std::cout<<"Tezine predmeta: ";
    for(int i=0;i<tezine_predmeta.size();i++) std::cout<<tezine_predmeta.at(i)<<" ";
    std::cout<<"(kg)"<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
}
/////////////////////////////////////////////////////////////
class Vreca : public Spremnik{
    double tezina_materije;
    public:
    Vreca(double tezina,std::string ime,double tezina_m):Spremnik(tezina,ime),tezina_materije(tezina_m){}
    double DajUkupnuTezinu() const override;
    void Ispisi() const override;
    Spremnik* DajKopiju() const override{
        return new Vreca(*this);
    }
};
double Vreca::DajUkupnuTezinu() const{
    return tezina+tezina_materije;
}
void Vreca::Ispisi() const{
    std::cout<<"Vrsta spremnika: Vreca"<<std::endl;
    std::cout<<"Sadrzaj: "<<ime_sadrzaja<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
    std::cout<<"Tezina pohranjene materije: "<<tezina_materije<<" (kg)"<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
}
/////////////////////////////////////////////////////////////
class Bure : public Spremnik{
    double gustina,zapremina;
    public:
    Bure(double tezina,std::string ime,double tezina_m,double zapremina_m):Spremnik(tezina,ime),gustina(tezina_m),zapremina(zapremina_m){}
    double DajUkupnuTezinu() const override;
    void Ispisi() const override;
    Spremnik* DajKopiju() const override{
        return new Bure(*this);
    }
};
double Bure::DajUkupnuTezinu() const{
    return tezina+gustina*zapremina/1000;
}
void Bure::Ispisi() const{
    std::cout<<"Vrsta spremnika: Bure"<<std::endl;
    std::cout<<"Sadrzaj: "<<ime_sadrzaja<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
    std::cout<<"Specificna tezina tecnosti: "<<gustina<<" (kg/m^3)"<<std::endl;
    std::cout<<"Zapremina tecnosti: "<<zapremina<<" (l)"<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
}
/////////////////////////////////////////////////////////////
/***********************************************************/
class Skladiste{
    std::vector<std::shared_ptr<Spremnik>> vektor_pokazivaca;
    public:
    Skladiste(){}
    Skladiste(const Skladiste &skladiste){
        for(int i=0;i<skladiste.vektor_pokazivaca.size();i++) 
            vektor_pokazivaca.push_back(std::shared_ptr<Spremnik>(skladiste.vektor_pokazivaca[i]->DajKopiju()));
    }
    Skladiste& operator=(const Skladiste &skladiste){
        vektor_pokazivaca.resize(0);
        for(int i=0;i<skladiste.vektor_pokazivaca.size();i++) 
            vektor_pokazivaca.push_back(std::shared_ptr<Spremnik>(skladiste.vektor_pokazivaca[i]->DajKopiju()));
        return *this;
    }
    Spremnik* DodajSanduk(double tezina,std::string ime,std::vector<double> vektor){
        vektor_pokazivaca.push_back(std::make_shared<Sanduk>(tezina,ime,vektor));
        return &(*vektor_pokazivaca.back());
    }
    Spremnik* DodajVrecu(double tezina,std::string ime,double vektor){
        vektor_pokazivaca.push_back(std::make_shared<Vreca>(tezina,ime,vektor));
        return &(*vektor_pokazivaca.back());
    }
    Spremnik* DodajBure(double tezina,std::string ime,double gust,double vektor){
        vektor_pokazivaca.push_back(std::make_shared<Bure>(tezina,ime,gust,vektor));
        return &(*vektor_pokazivaca.back());
    }
    Spremnik* DodajSpremnik(Spremnik* spremnik,bool vlasnistvo_klase){
        if(vlasnistvo_klase) vektor_pokazivaca.push_back(std::shared_ptr<Spremnik>(spremnik));
        else vektor_pokazivaca.push_back(std::shared_ptr<Spremnik>(spremnik->DajKopiju()));
        return &(*vektor_pokazivaca.back());
    }
    void BrisiSpremnik(Spremnik* spremnik){
        for(int i=0;i<vektor_pokazivaca.size();i++) 
            if(spremnik==&(*vektor_pokazivaca[i])){
                vektor_pokazivaca.erase(vektor_pokazivaca.begin()+i); i--;
            }
    }
    Spremnik& DajNajlaksi(){
        if(vektor_pokazivaca.size()==0) throw std::range_error("Skladiste je prazno");
        return **min_element(vektor_pokazivaca.begin(),vektor_pokazivaca.end(),
        [](std::shared_ptr<Spremnik> x,std::shared_ptr<Spremnik> y){
            if(x->DajTezinu()<y->DajTezinu()) return true;
            return false;
        });
    }
    Spremnik& DajNajtezi(){
        if(vektor_pokazivaca.size()==0) throw std::range_error("Skladiste je prazno");
        return **max_element(vektor_pokazivaca.begin(),vektor_pokazivaca.end(),
        [](std::shared_ptr<Spremnik> x,std::shared_ptr<Spremnik> y){
            if(x->DajTezinu()<y->DajTezinu()) return true;
            return false;
        });
    }
    int BrojPreteskih(int granica) const{
        return std::count_if(vektor_pokazivaca.begin(),vektor_pokazivaca.end(),
        [granica](std::shared_ptr<Spremnik> x){
            return x->DajUkupnuTezinu()>granica;
        });
    }
    void IzlistajSkladiste() const{
        Skladiste pom=*this;
        std::sort(pom.vektor_pokazivaca.begin(),pom.vektor_pokazivaca.end(),
        [](std::shared_ptr<Spremnik> x,std::shared_ptr<Spremnik> y){
            return x->DajUkupnuTezinu()>y->DajUkupnuTezinu();
        });
        for(int i=0;i<pom.vektor_pokazivaca.size();i++) pom.vektor_pokazivaca[i]->Ispisi();
    }
    void UcitajIzDatoteke(std::string ime_datoteke){
        Skladiste NovoSkladiste;
        std::ifstream ulaz(ime_datoteke);
        if(!ulaz) throw std::logic_error("Trazena datoteka ne postoji");
        std::string red1,red2;
        while(std::getline(ulaz,red1)){
            std::getline(ulaz,red2);
            std::istringstream red2_tok(red2);
            if(red1[0]=='S'){
                int br_predmeta;
                double pom_tezina,s_tezina;
                red2_tok>>s_tezina>>br_predmeta;
                if(!red2_tok) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                std::vector<double> pom_v_tezina;
                while(red2_tok>>pom_tezina) pom_v_tezina.push_back(pom_tezina);
                if(!red2_tok.eof() || br_predmeta!=pom_v_tezina.size()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                NovoSkladiste.DodajSanduk(s_tezina,red1.substr(2,red1.size()),pom_v_tezina);
            }
            if(red1[0]=='V'){
                //std::cout<<"USAO";
                double pom_tezina,v_tezina;
                red2_tok>>v_tezina>>pom_tezina;
                if(!red2_tok) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                if(!red2_tok.eof()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                NovoSkladiste.DodajVrecu(v_tezina,red1.substr(2,red1.size()),pom_tezina);
            }
            if(red1[0]=='B'){
                //std::cout<<"USAO";
                double pom_tezina,b_tezina,pom_zapremina;
                red2_tok>>b_tezina>>pom_tezina>>pom_zapremina;
                if(!red2_tok) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                if(!red2_tok.eof()) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                NovoSkladiste.DodajBure(b_tezina,red1.substr(2,red1.size()),pom_tezina,pom_zapremina);
            }
        }
        
        *this=NovoSkladiste;
    }
};
/***********************************************************/
int main ()
{
    Skladiste s;
    try{
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    }
    catch(std::logic_error iz){
        std::cout<<iz.what();
    }
    catch(std::range_error iz){
        std::cout<<iz.what();
    }
	return 0;
}
