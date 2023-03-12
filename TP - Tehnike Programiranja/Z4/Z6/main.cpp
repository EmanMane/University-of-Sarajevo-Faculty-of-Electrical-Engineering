//TP 2021/2022: Zadaća 4, Zadatak 6
#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <utility>
#include <string>
#include <algorithm>
#include <stdexcept>

struct Student{
    int broj_indeksa, godina_studija;
    std::string ime,prezime,adresa,telefon;
};

class Knjiga{
    std::string naslov,pisac,zanr;
    int godina_izdavanja;
    Student* zaduzenje=nullptr;
    public:
    Knjiga(std::string naslov,std::string pisac,std::string zanr,int godina_izdavanja):naslov(naslov),pisac(pisac),zanr(zanr),godina_izdavanja(godina_izdavanja),zaduzenje(nullptr){}
    std::string DajNaslov() const {return naslov;}
    std::string DajAutora() const {return pisac;}
    std::string DajZanr() const {return zanr;}
    int DajGodinuIzdavanja() const {return godina_izdavanja;}
    void ZaduziKnjigu(Student& student){zaduzenje=&student;}
    void RazduziKnjigu(){zaduzenje=nullptr;}
    bool DaLiJeZaduzena() const{
        if(zaduzenje==nullptr) return false;
        return true;
    }
    Student& DajKodKogaJe() const{
        if(zaduzenje==nullptr) throw std::domain_error("Knjiga nije zaduzena");
        return *zaduzenje;
    }
    Student* DajPokKodKogaJe() const{
        return zaduzenje;
    }
};

class Biblioteka{
    std::map<int,std::shared_ptr<Student>> mapa_korisnika;
    std::map<int,std::shared_ptr<Knjiga>> mapa_knjiga;
    public:
    Biblioteka()=default;
    Biblioteka(const Biblioteka &biblioteka);
    Biblioteka(Biblioteka &&biblioteka);
    Biblioteka &operator=(const Biblioteka &biblioteka);
    Biblioteka &operator=(Biblioteka &&biblioteka);
    ~Biblioteka();
    void RegistrirajNovogStudenta(int broj_indeksa,std::string ime,std::string prezime,int godina_studija,std::string adresa,std::string telefon);
    void RegistrirajNovuKnjigu(int evidencijski_broj,std::string naslov,std::string pisac,std::string zanr,int godina_izdavanja);
    Student& NadjiStudenta(int broj_indeksa) const;
    Knjiga& NadjiKnjigu(int evidencijski_broj) const;
    void IzlistajStudente() const;
    void IzlistajKnjige() const;
    void ZaduziKnjigu(int evidencijski_broj,int broj_indeksa);
    void RazduziKnjigu(int evidencijski_broj);
    void PrikaziZaduzenja(int broj_indeksa) const;
};
/******************************************************************************************************************/
Biblioteka::Biblioteka(const Biblioteka &biblioteka){
    for(auto pok=biblioteka.mapa_korisnika.begin();pok!=biblioteka.mapa_korisnika.end();pok++){
        auto student=std::make_shared<Student>(*(pok->second));
        mapa_korisnika.insert({pok->first,student});
    }
    for(auto pok=biblioteka.mapa_knjiga.begin();pok!=biblioteka.mapa_knjiga.end();pok++){
        auto knjiga=std::make_shared<Knjiga>(*(pok->second));
        mapa_knjiga.insert({pok->first,knjiga});
    }
}
Biblioteka::Biblioteka(Biblioteka &&biblioteka){
    std::swap(mapa_korisnika,biblioteka.mapa_korisnika);
    std::swap(mapa_knjiga,biblioteka.mapa_knjiga);
}
Biblioteka& Biblioteka::operator=(const Biblioteka &biblioteka){
    if(&biblioteka!=this){
        //std::map<int,Student*> mapa_s;
        //std::map<int,Knjiga*> mapa_k;
        for(auto pok=mapa_korisnika.begin();pok!=mapa_korisnika.end();pok++) pok->second=nullptr;
        for(auto pok=mapa_knjiga.begin();pok!=mapa_knjiga.end();pok++) pok->second=nullptr;
        mapa_korisnika.clear(); mapa_knjiga.clear();
        //mapa_korisnika=mapa_s;     
        //mapa_knjiga=mapa_k;
        for(auto pok=biblioteka.mapa_korisnika.begin();pok!=biblioteka.mapa_korisnika.end();pok++){
            auto student=std::make_shared<Student>(*(pok->second));
            mapa_korisnika.insert({pok->first,student});
            student=nullptr;
        }
        for(auto pok=biblioteka.mapa_knjiga.begin();pok!=biblioteka.mapa_knjiga.end();pok++){
            auto knjiga=std::make_shared<Knjiga>(*(pok->second));
            mapa_knjiga.insert({pok->first,knjiga});
            knjiga=nullptr;
        }
    }
    return *this;
}
Biblioteka& Biblioteka::operator=(Biblioteka &&biblioteka){
    if(&biblioteka!=this){
        //std::map<int,Student*> mapa_s;
        //std::map<int,Knjiga*> mapa_k;
        for(auto pok=mapa_korisnika.begin();pok!=mapa_korisnika.end();pok++) pok->second=nullptr;
        for(auto pok=mapa_knjiga.begin();pok!=mapa_knjiga.end();pok++) pok->second=nullptr;
        mapa_korisnika.clear(); mapa_knjiga.clear();
        //mapa_korisnika=mapa_s;     
        //mapa_knjiga=mapa_k;
        for(auto pok=biblioteka.mapa_korisnika.begin();pok!=biblioteka.mapa_korisnika.end();pok++){
            auto student=std::make_shared<Student>(*(pok->second));
            mapa_korisnika.insert({pok->first,student});
            student=nullptr;
        }
        for(auto pok=biblioteka.mapa_knjiga.begin();pok!=biblioteka.mapa_knjiga.end();pok++){
            auto knjiga=std::make_shared<Knjiga>(*(pok->second));
            mapa_knjiga.insert({pok->first,knjiga});
            knjiga=nullptr;
        }
    }
    return *this;
}
Biblioteka::~Biblioteka(){
    for(auto pok=mapa_korisnika.begin();pok!=mapa_korisnika.end();pok++) pok->second=nullptr;
    for(auto pok=mapa_knjiga.begin();pok!=mapa_knjiga.end();pok++) pok->second=nullptr;
}
void Biblioteka::RegistrirajNovogStudenta(int broj_indeksa,std::string ime,std::string prezime,int godina_studija,std::string adresa,std::string telefon){
    auto student=std::make_shared<Student>();
    student->ime=ime;
    student->prezime=prezime;
    student->adresa=adresa;
    student->godina_studija=godina_studija;
    student->telefon=telefon;
    student->broj_indeksa=broj_indeksa;
    auto pom_par=std::make_pair(broj_indeksa,student);
    if(std::count_if(mapa_korisnika.begin(),mapa_korisnika.end(),[broj_indeksa](std::pair<int,std::shared_ptr<Student>> x){
        if(x.first==broj_indeksa) return true;
        return false;
    })!=0){
        student=nullptr;
        throw std::logic_error("Vec postoji student s tim brojem indeksa");
    }
    else mapa_korisnika.insert(pom_par);
}
void Biblioteka::RegistrirajNovuKnjigu(int evidencijski_broj,std::string naslov,std::string pisac,std::string zanr,int godina_izdavanja){
    auto knjiga=std::make_shared<Knjiga>(naslov,pisac,zanr,godina_izdavanja);
    auto pom_par=std::make_pair(evidencijski_broj,knjiga);
    if(std::count_if(mapa_knjiga.begin(),mapa_knjiga.end(),[evidencijski_broj](std::pair<int,std::shared_ptr<Knjiga>> x){
        if(x.first==evidencijski_broj) return true;
        return false;
    })!=0){
        knjiga=nullptr;
        throw std::logic_error("Knjiga s tim evidencijskim brojem vec postoji");
    }
    else mapa_knjiga.insert(pom_par);
}
Student& Biblioteka::NadjiStudenta(int broj_indeksa) const{
    auto pok=mapa_korisnika.find(broj_indeksa);
    if(pok!=mapa_korisnika.end()) return *(pok->second);
    else throw std::logic_error("Student nije nadjen");
}
Knjiga& Biblioteka::NadjiKnjigu(int evidencijski_broj) const{
    auto pok=mapa_knjiga.find(evidencijski_broj);
    if(pok!=mapa_knjiga.end()) return *(pok->second);
    else throw std::logic_error("Knjiga nije nadjena");
}
void Biblioteka::IzlistajStudente() const{
    auto pok=mapa_korisnika.begin();
    while(pok!=mapa_korisnika.end()){
        std::cout<<"Broj indeksa: "<<pok->first<<std::endl;
        std::cout<<"Ime i prezime: "<<pok->second->ime<<" "<<pok->second->prezime<<std::endl;
        std::cout<<"Godina studija: "<<pok->second->godina_studija<<std::endl;
        std::cout<<"Adresa: "<<pok->second->adresa<<std::endl;
        std::cout<<"Broj telefona: "<<pok->second->telefon<<std::endl;
        pok++;
    }
}
void Biblioteka::IzlistajKnjige() const{
    auto pok=mapa_knjiga.begin();
    while(pok!=mapa_knjiga.end()){
        std::cout<<"Evidencijski broj: "<<pok->first<<std::endl;
        std::cout<<"Naslov: "<<pok->second->DajNaslov()<<std::endl;
        std::cout<<"Pisac: "<<pok->second->DajAutora()<<std::endl;
        std::cout<<"Zanr: "<<pok->second->DajZanr()<<std::endl;
        std::cout<<"Godina izdavanja: "<<pok->second->DajGodinuIzdavanja()<<std::endl;
        if(pok->second->DaLiJeZaduzena()){
            std::cout<<"Zaduzena kod studenta: "<<pok->second->DajKodKogaJe().ime<<" "<<pok->second->DajKodKogaJe().prezime<<" ("<<pok->second->DajKodKogaJe().broj_indeksa<<")"<<std::endl;
        }
        pok++;
    }
}
void Biblioteka::ZaduziKnjigu(int evidencijski_broj,int broj_indeksa){
    auto pok_s=mapa_korisnika.find(broj_indeksa);
    auto pok_k=mapa_knjiga.find(evidencijski_broj);
    if(pok_k==mapa_knjiga.end()) throw std::logic_error("Knjiga nije nadjena");
    if(pok_s==mapa_korisnika.end()) throw std::logic_error("Student nije nadjen");
    if(pok_k->second->DaLiJeZaduzena()) throw std::logic_error("Knjiga vec zaduzena");
    pok_k->second->ZaduziKnjigu(*(pok_s->second));
}
void Biblioteka::RazduziKnjigu(int evidencijski_broj){
    auto pok_k=mapa_knjiga.find(evidencijski_broj);
    if(pok_k==mapa_knjiga.end()) throw std::logic_error("Knjiga nije nadjena");
    if(pok_k->second->DaLiJeZaduzena()==false) throw std::logic_error("Knjiga nije zaduzena");
    pok_k->second->RazduziKnjigu();
}
void Biblioteka::PrikaziZaduzenja(int broj_indeksa) const{
    int ispis=0;
    auto pok_s=mapa_korisnika.find(broj_indeksa);
    if(pok_s==mapa_korisnika.end()) throw std::logic_error("Student nije nadjen");
    auto pok=mapa_knjiga.begin();
    while(pok!=mapa_knjiga.end()){
        if(pok->second->DaLiJeZaduzena()==true && pok->second->DajKodKogaJe().broj_indeksa==broj_indeksa){
            ispis++;
            std::cout<<"Evidencijski broj: "<<pok->first<<std::endl;
            std::cout<<"Naslov: "<<pok->second->DajNaslov()<<std::endl;
            std::cout<<"Pisac: "<<pok->second->DajAutora()<<std::endl;
            std::cout<<"Zanr: "<<pok->second->DajZanr()<<std::endl;
            std::cout<<"Godina izdavanja: "<<pok->second->DajGodinuIzdavanja()<<std::endl;
        }
        pok++;
    }
    if(ispis==0) std::cout<<"Nema zaduzenja za tog studenta!";
}

int main ()
{
    std::cout<<"Topić";
	return 0;
}
