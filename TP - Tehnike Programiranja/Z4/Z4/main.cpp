//TP 2021/2022: Zadaća 4, Zadatak 4
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <vector>

//evidencija jednog polaska
class Polazak{
    std::string odrediste;
    int broj_voza,broj_perona,sat_polaska,minute_polaska,trajanje_voznje,kasnjenje=0;
    bool brzi_voz;
    public:
    Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz, int sat_polaska, int minute_polaska, int trajanje_voznje);
    void PostaviKasnjenje(int kasnjenje);
    bool DaLiKasni() const;
    int DajTrajanjeVoznje() const;
    std::pair<int, int> DajOcekivanoVrijemePolaska() const;
    std::pair<int, int> DajOcekivanoVrijemeDolaska() const;
    void Ispisi() const;
};
/****************************************************************************/
Polazak::Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz,
int sat_polaska, int minute_polaska, int trajanje_voznje):odrediste(odrediste),broj_voza(broj_voza),
broj_perona(broj_perona),sat_polaska(sat_polaska),minute_polaska(minute_polaska),
trajanje_voznje(trajanje_voznje),kasnjenje(0){
    int keks=std::log10(abs(broj_voza));keks++;
    Polazak::brzi_voz=brzi_voz;
    //std::cout<<"ALO, broj perona je "<<broj_perona;
    if(keks>5 || broj_perona<1 || broj_perona>6
    || minute_polaska>=60 || sat_polaska>=24 || minute_polaska<0
    || sat_polaska<0 || broj_voza<0 || trajanje_voznje<0) throw std::domain_error("Emanov Error");

}
void Polazak::PostaviKasnjenje(int kasnjenje){
    Polazak::kasnjenje=kasnjenje;
}
bool Polazak::DaLiKasni() const{
    if(kasnjenje>0) return true;
    return false;
}
int Polazak::DajTrajanjeVoznje() const{
    return trajanje_voznje;
}
std::pair<int, int> Polazak::DajOcekivanoVrijemePolaska() const{
    std::pair<int, int> vrijeme;
    int min=minute_polaska+kasnjenje,h=0; if(min>=60){h++; min-=60;}
    h+=sat_polaska;
    if(h>=24) h-=24;
    vrijeme.first=h; vrijeme.second=min;
    return vrijeme;
}
std::pair<int, int> Polazak::DajOcekivanoVrijemeDolaska() const{
    std::pair<int, int> vrijeme;
    int min=minute_polaska+kasnjenje+trajanje_voznje,h=0; 
    if(min>=60){
        while(min>=60){
            h++; min-=60;
        }
    }
    h+=sat_polaska;
    if(h>=24) h-=24;
    vrijeme.first=h; vrijeme.second=min;
    return vrijeme;
}
void Polazak::Ispisi() const{
    if(kasnjenje==0){
        if(brzi_voz==true) std::cout<<"Brzi voz "; else std::cout<<"Lokalni voz ";
        std::cout<<"broj "<<broj_voza;
        std::cout<<", odrediste "<<odrediste;
        std::cout<<", polazi sa perona "<<broj_perona<<" u ";
        if(sat_polaska<10){std::cout<<"0"<<sat_polaska<<":";}
        else{std::cout<<sat_polaska<<":";}
        if(minute_polaska<10){std::cout<<"0"<<minute_polaska;}
        else{std::cout<<minute_polaska;}
        std::cout<<", a na odrediste stize u ";
        std::pair<int, int> dolazak=DajOcekivanoVrijemeDolaska();
        if(dolazak.first<10){std::cout<<"0"<<dolazak.first<<":";}
        else{std::cout<<dolazak.first<<":";}
        if(dolazak.second<10){std::cout<<"0"<<dolazak.second;}
        else{std::cout<<dolazak.second;}
        std::cout<<". Putnicima i voznom osoblju zelimo ugodno putovanje."<<std::endl;
    }
    else{
        if(brzi_voz) std::cout<<"Brzi voz "; else std::cout<<"Lokalni voz ";
        std::cout<<"broj "<<broj_voza;
        std::cout<<", odrediste "<<odrediste;
        std::cout<<", sa predvidjenim vremenom polaska u ";
        if(sat_polaska<10){std::cout<<"0"<<sat_polaska<<":";}
        else{std::cout<<sat_polaska<<":";}
        if(minute_polaska<10){std::cout<<"0"<<minute_polaska;}
        else{std::cout<<minute_polaska;}
        std::cout<<", kasni oko "<<kasnjenje<<" minuta, te ce poci oko ";
        std::pair<int, int> polazak=DajOcekivanoVrijemePolaska();
        if(polazak.first<10){std::cout<<"0"<<polazak.first<<":";}
        else{std::cout<<polazak.first<<":";}
        if(polazak.second<10){std::cout<<"0"<<polazak.second;}
        else{std::cout<<polazak.second;}
        std::cout<<". Ocekuje se da voz stigne na odrediste oko ";
        std::pair<int, int> dolazak=DajOcekivanoVrijemeDolaska();
        if(dolazak.first<10){std::cout<<"0"<<dolazak.first<<":";}
        else{std::cout<<dolazak.first<<":";}
        if(dolazak.second<10){std::cout<<"0"<<dolazak.second;}
        else{std::cout<<dolazak.second;}
        std::cout<<". Izvinjavamo se putnicima zbog eventualnih neugodnosti."<<std::endl;
    }
}




/****************************************************************************/
//evidencija svih polazaka
class RedVoznje{
    std::vector<std::shared_ptr<Polazak>> polasci;
    //int broj_polazaka,max_broj_polazaka;
    public:
    explicit RedVoznje()=default;
    RedVoznje(std::initializer_list<Polazak> lista_polazaka);
    ~RedVoznje();
    RedVoznje(const RedVoznje &red_voznje);
    RedVoznje(RedVoznje &&red_voznje);
    RedVoznje &operator =(const RedVoznje &red_voznje);
    RedVoznje &operator =(RedVoznje &&red_voznje);
    void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje);
    void RegistrirajPolazak(std::shared_ptr<Polazak> polazak);
    int DajBrojPolazaka() const;
    int DajBrojPolazakaKojiKasne() const;
    int DajProsjecnoTrajanjeVoznji() const;
    Polazak &DajPrviPolazak() const;
    Polazak &DajPosljednjiPolazak() const;
    void IsprazniRedVoznje();
    void Ispisi(int sati, int minute) const;
};
/****************************************************************************/

/*RedVoznje::RedVoznje(int max_broj_polazaka){
    RedVoznje::max_broj_polazaka=max_broj_polazaka;
    RedVoznje::broj_polazaka=0;
    polasci=nullptr;
    polasci=new Polazak*[max_broj_polazaka]{};
}*/

RedVoznje::RedVoznje(std::initializer_list<Polazak> lista_polazaka){
    for(auto iter=lista_polazaka.begin();iter!=lista_polazaka.end();iter++){
        polasci.push_back(std::make_shared<Polazak>(*iter));
    }
}

RedVoznje::~RedVoznje(){
    for(int i=0;i<polasci.size();i++) polasci[i]=nullptr;
}

RedVoznje::RedVoznje(const RedVoznje &red_voznje){
    for(int i=0;i<red_voznje.polasci.size();i++)
        RedVoznje::polasci.push_back(std::make_shared<Polazak>(*(red_voznje.polasci[i])));
    
    /*max_broj_polazaka=red_voznje.max_broj_polazaka;
    broj_polazaka=red_voznje.broj_polazaka;
    polasci=new Polazak*[red_voznje.broj_polazaka];
    try{
        for(int i=0;i<broj_polazaka;i++) polasci[i]=new Polazak(*red_voznje.polasci[i]);
    }
    catch(...){
        for(int i=0;i<broj_polazaka;i++) delete polasci[i];
        delete[] polasci;
        polasci=nullptr;
    }*/
}

RedVoznje::RedVoznje(RedVoznje &&red_voznje){
    RedVoznje::polasci=red_voznje.polasci;
    red_voznje.polasci.resize(0);
    /*broj_polazaka=red_voznje.broj_polazaka;
    polasci=red_voznje.polasci;
    red_voznje.polasci=nullptr;*/
}

RedVoznje& RedVoznje::operator =(const RedVoznje &red_voznje){
    if(&red_voznje!=this){
        //polasci=red_voznje.polasci;
        RedVoznje::polasci.resize(0);
        for(int i=0;i<red_voznje.polasci.size();i++)
            RedVoznje::polasci.push_back(std::make_shared<Polazak>(*(red_voznje.polasci[i])));
    }
    return *this;
}

RedVoznje& RedVoznje::operator =(RedVoznje &&red_voznje){
    if(&red_voznje!=this){
        //std::swap(polasci,red_voznje.polasci);
        RedVoznje::polasci.resize(0);
        RedVoznje::polasci=red_voznje.polasci;
        red_voznje.polasci.resize(0);
    }
    return *this;
}

void RedVoznje::RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
    Polazak x(odrediste,broj_voza,broj_perona,brzi_voz,sat_polaska,minute_polaska,trajanje_voznje);
    RedVoznje::polasci.push_back(std::make_shared<Polazak>(x));
}
void RedVoznje::RegistrirajPolazak(std::shared_ptr<Polazak> polazak){
    RedVoznje::polasci.push_back(polazak);
}
int RedVoznje::DajBrojPolazaka() const{
    return RedVoznje::polasci.size();
}
int RedVoznje::DajBrojPolazakaKojiKasne() const{
    int kasne=std::count_if(polasci.begin(),polasci.end(),[](std::shared_ptr<Polazak> x){
        if(x->DaLiKasni()) return true;
        return false;
    });
    return kasne;
}
int RedVoznje::DajProsjecnoTrajanjeVoznji() const{
    double prosjek=0;
    for(int i=0;i<RedVoznje::polasci.size();i++) prosjek+=polasci[i]->DajTrajanjeVoznje();
    prosjek/=RedVoznje::polasci.size();
    return prosjek;
}
Polazak& RedVoznje::DajPrviPolazak() const{
    auto prvi=std::max_element(polasci.begin(),polasci.end(),[](std::shared_ptr<Polazak> x,std::shared_ptr<Polazak> y){
        std::pair<int,int> polazak1=x->DajOcekivanoVrijemePolaska(),polazak2=y->DajOcekivanoVrijemePolaska();
        if(polazak1.first>polazak2.first) return true;
        if(polazak1.first==polazak2.first) if(polazak1.second>polazak2.second) return true;
        return false;
    });
    return **prvi;
}
Polazak& RedVoznje::DajPosljednjiPolazak() const{
    auto posljednji=std::min_element(polasci.begin(),polasci.end(),[](std::shared_ptr<Polazak>x,std::shared_ptr<Polazak> y){
        std::pair<int,int> polazak1=x->DajOcekivanoVrijemePolaska(),polazak2=y->DajOcekivanoVrijemePolaska();
        if(polazak1.first>polazak2.first) return true;
        if(polazak1.first==polazak2.first) if(polazak1.second>polazak2.second) return true;
        return false;
    });
    return **posljednji;
}
void RedVoznje::IsprazniRedVoznje(){
    polasci.resize(0);
}
void RedVoznje::Ispisi(int sati, int minute) const{
    /*RedVoznje pomocni=*this;   
    for(auto pok=pomocni.polasci.begin();pok!=pomocni.polasci.begin();pok++){
        pok->get()->Ispisi();
    }*/
    auto pom=polasci;   //zbog crasha
    std::sort(pom.begin(),pom.end(),[](std::shared_ptr<Polazak> x,std::shared_ptr<Polazak> y){
        std::pair<int,int> polazak1=x.get()->DajOcekivanoVrijemePolaska(),polazak2=y.get()->DajOcekivanoVrijemePolaska();
        if(polazak1.first>polazak2.first) return false;
        if(polazak1.first==polazak2.first) if(polazak1.second>polazak2.second) return false;
        return true;
    });
    //RedVoznje::polasci[1]->Ispisi();
    //temp.polasci[1]->Ispisi();
    for(int i=0;i<pom.size();i++){
        std::pair<int,int> poredbeni=pom[i]->DajOcekivanoVrijemePolaska();
        if(poredbeni.first>sati) pom[i]->Ispisi();
        else if(poredbeni.first==sati) if(poredbeni.second>minute) pom[i]->Ispisi();
    }
}
/****************************************************************************/

int main ()
{
    RedVoznje v1;
    v1.RegistrirajPolazak("Mostar", 123, true, 5,  12, 30, 120);
    v1.RegistrirajPolazak("Bihać", 124, false, 4, 10, 20,  180);
    v1.RegistrirajPolazak("Zenica", 125, false, 1,  6, 30, 120);
    v1.RegistrirajPolazak("Banja Luka", 127, false, 2,  20, 30, 120);
    std::shared_ptr<Polazak> polazak(new Polazak("Sarajevo", 129, 3, false, 22, 30, 120));
    v1.RegistrirajPolazak(polazak);
    RedVoznje v2(std::move(v1));
    std::cout<<"Broj polazaka: "<<v2.DajBrojPolazaka()<<std::endl;
    std::cout<<"Broj kašnjenja: "<<v2.DajBrojPolazakaKojiKasne()<<std::endl;
    std::cout<<"Prosjecno trajanje: "<<v2.DajProsjecnoTrajanjeVoznji()<<std::endl;
    Polazak prvi=v2.DajPrviPolazak();
    Polazak posljednji=v2.DajPosljednjiPolazak();
    std::cout<<"Prvi polazak: "; prvi.Ispisi(); std::cout<<std::endl;
    std::cout<<"Posljednji polazak: "; posljednji.Ispisi(); std::cout<<std::endl;
    v2.Ispisi(0,0);
    return 0;
}