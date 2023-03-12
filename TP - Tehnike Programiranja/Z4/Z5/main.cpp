//TP 2021/2022: Zadaća 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>

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
    std::map<int,Student*> mapa_korisnika;
    std::map<int,Knjiga*> mapa_knjiga;
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
        auto student=new Student(*(pok->second));
        mapa_korisnika.insert({pok->first,student});
    }
    for(auto pok=biblioteka.mapa_knjiga.begin();pok!=biblioteka.mapa_knjiga.end();pok++){
        auto knjiga=new Knjiga(*(pok->second));
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
        for(auto pok=mapa_korisnika.begin();pok!=mapa_korisnika.end();pok++) delete pok->second;
        for(auto pok=mapa_knjiga.begin();pok!=mapa_knjiga.end();pok++) delete pok->second;
        mapa_korisnika.clear(); mapa_knjiga.clear();
        //mapa_korisnika=mapa_s;     
        //mapa_knjiga=mapa_k;
        for(auto pok=biblioteka.mapa_korisnika.begin();pok!=biblioteka.mapa_korisnika.end();pok++){
            auto student=new Student(*(pok->second));
            mapa_korisnika.insert({pok->first,student});
            student=nullptr;
        }
        for(auto pok=biblioteka.mapa_knjiga.begin();pok!=biblioteka.mapa_knjiga.end();pok++){
            auto knjiga=new Knjiga(*(pok->second));
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
        for(auto pok=mapa_korisnika.begin();pok!=mapa_korisnika.end();pok++) delete pok->second;
        for(auto pok=mapa_knjiga.begin();pok!=mapa_knjiga.end();pok++) delete pok->second;
        mapa_korisnika.clear(); mapa_knjiga.clear();
        //mapa_korisnika=mapa_s;     
        //mapa_knjiga=mapa_k;
        for(auto pok=biblioteka.mapa_korisnika.begin();pok!=biblioteka.mapa_korisnika.end();pok++){
            auto student=new Student(*(pok->second));
            mapa_korisnika.insert({pok->first,student});
            student=nullptr;
        }
        for(auto pok=biblioteka.mapa_knjiga.begin();pok!=biblioteka.mapa_knjiga.end();pok++){
            auto knjiga=new Knjiga(*(pok->second));
            mapa_knjiga.insert({pok->first,knjiga});
            knjiga=nullptr;
        }
    }
    return *this;
}
Biblioteka::~Biblioteka(){
    for(auto pok=mapa_korisnika.begin();pok!=mapa_korisnika.end();pok++) delete pok->second;
    for(auto pok=mapa_knjiga.begin();pok!=mapa_knjiga.end();pok++) delete pok->second;
}
void Biblioteka::RegistrirajNovogStudenta(int broj_indeksa,std::string ime,std::string prezime,int godina_studija,std::string adresa,std::string telefon){
    Student *student;
    student=new Student;
    student->ime=ime;
    student->prezime=prezime;
    student->adresa=adresa;
    student->godina_studija=godina_studija;
    student->telefon=telefon;
    student->broj_indeksa=broj_indeksa;
    auto pom_par=std::make_pair(broj_indeksa,student);
    if(std::count_if(mapa_korisnika.begin(),mapa_korisnika.end(),[broj_indeksa](std::pair<int,Student*> x){
        if(x.first==broj_indeksa) return true;
        return false;
    })!=0){
        delete student;
        student=nullptr;
        throw std::logic_error("Vec postoji student s tim brojem indeksa");
    }
    else mapa_korisnika.insert(pom_par);
}
void Biblioteka::RegistrirajNovuKnjigu(int evidencijski_broj,std::string naslov,std::string pisac,std::string zanr,int godina_izdavanja){
    Knjiga *knjiga;
    knjiga=new Knjiga(naslov,pisac,zanr,godina_izdavanja);
    auto pom_par=std::make_pair(evidencijski_broj,knjiga);
    if(std::count_if(mapa_knjiga.begin(),mapa_knjiga.end(),[evidencijski_broj](std::pair<int,Knjiga*> x){
        if(x.first==evidencijski_broj) return true;
        return false;
    })!=0){
        delete knjiga;
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
    Biblioteka Paromlinska16;
    std::cout<<"Pozdrav :)\nOvo je simulator biblioteka u Sarajevu. Trenutno je dostupna biblioteka Paromlinska 16...\n";
    std::cout<<"\nIzaberite opciju:\n";
    std::cout<<"\nIspiši:\n1 - sve knjige\n2 - sve korisnike\n3 - sva zaduženja (x - broj indeksa) studenta\n \nPretraži:\n4 - (x - broj indeksa) studenta\n5 - (x - evidencijski broj) knjigu\n\nNova registracija:\n6 - knjige\n7 - studenta\n\nNova obrada:\n8 - zaduži knjigu\n9 - razduži knjigu\n\n0 - kraj\n";
    for(;;){
        unos:
        std::cout<<"\nUnesite opciju: "; int n; std::cin>>n;
        if(n==1){
            Paromlinska16.IzlistajKnjige();
        }
        else if(n==2){
            Paromlinska16.IzlistajStudente();
        }
        else if(n==3){
            int x;
            std::cout<<"Unesi x: "; std::cin>>x;
            try{
                Paromlinska16.PrikaziZaduzenja(x);
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==4){
            int x;
            std::cout<<"Unesi x: "; std::cin>>x;
            try{
                Student s=Paromlinska16.NadjiStudenta(x);
                std::cout<<"Student je u sistemu.";
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==5){
            int x;
            std::cout<<"Unesi x: "; std::cin>>x;
            try{
                Paromlinska16.NadjiKnjigu(x);
                std::cout<<"Knjiga je u sistemu.";
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==6){
            try{
            int evidencijski_broj, godina_izdavanja; std::string naslov, pisac, zanr;
            std::cout<<"Unesi:\n";
            std::cout<<"evidencijski broj, naslov, pisca, zanr i godinu izdavanja... (napomena: jedno ispod drugog - enter za unos sljedećeg)\n";
            std::cin>>evidencijski_broj; std::cin.ignore(1000,'\n');
            std::getline(std::cin,naslov); //std::cin.ignore(1000,'\n');
            std::getline(std::cin,pisac); //std::cin.ignore(1000,'\n');
            std::getline(std::cin,zanr); //std::cin.ignore(1000,'\n');
            std::cin>>godina_izdavanja; 
            Paromlinska16.RegistrirajNovuKnjigu(evidencijski_broj,naslov,pisac,zanr,godina_izdavanja);
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==7){
            try{
            int broj_indeksa, godina_studija; std::string ime, prezime, adresa, telefon;
            std::cout<<"Unesi:\n";
            std::cout<<"broj indeksa, ime, prezime, godinu studija, adresa i telefon... (napomena: jedno ispod drugog - enter za unos sljedećeg)\n";
            std::cin>>broj_indeksa; std::cin.ignore(1000,'\n');
            std::getline(std::cin,ime); //std::cin.ignore(1000,'\n');
            std::getline(std::cin,prezime); //std::cin.ignore(1000,'\n');
            std::cin>>godina_studija; std::cin.ignore(1000,'\n');
            std::getline(std::cin,adresa); //std::cin.ignore(1000,'\n');
            std::getline(std::cin,telefon); //std::cin.ignore(1000,'\n');
            Paromlinska16.RegistrirajNovogStudenta(broj_indeksa,ime,prezime,godina_studija,adresa,telefon);
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==8){
            try{
            int broj_indeksa,evidencijski_broj;
            std::cout<<"Unesite studenta koji zadužuje knjigu (broj indeksa): "; std::cin>>broj_indeksa;
            std::cout<<"Unesite knjigu koju zadužuje (evidencijski_broj): "; std::cin>>evidencijski_broj;
            Paromlinska16.ZaduziKnjigu(evidencijski_broj,broj_indeksa);
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==9){
            try{
            int broj_indeksa,evidencijski_broj;
            //std::cout<<"Unesite studenta koji razdužuje knjigu (broj indeksa): "; std::cin>>broj_indeksa;
            std::cout<<"Unesite knjigu koja se razdužuje (evidencijski_broj): "; std::cin>>evidencijski_broj;
            Paromlinska16.RazduziKnjigu(evidencijski_broj);
            }catch(std::logic_error eror){
                std::cout<<eror.what();
            }
        }
        else if(n==0){
            break;
        }
        else{
            std::cout<<"\nPogrešna komanda!";
        }
    }
    std::cout<<"Ugodan dan želimo :)";
	return 0;
}
