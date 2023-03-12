/* 
    TP 16/17 (LV 13, Zadatak 3)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ApstraktniStudent{
    std::string ime,prezime;
    int indeks,br_polozenih;
    double prosjecna;
    public:
    ApstraktniStudent(std::string ime,std::string prezime,int indeks):ime(ime),prezime(prezime),indeks(indeks){
        br_polozenih=0; prosjecna=5;
    }
    virtual ~ApstraktniStudent(){}
    std::string DajIme() const{return ime;}
    std::string DajPrezime() const{return prezime;}
    int DajBrojIndeksa() const{return indeks;}
    int DajBrojPolozenih() const{return br_polozenih;}
    double DajProsjek() const{return prosjecna;}
    void RegistrirajIspit(int ocjena);
    void PonistiOcjene();
    virtual void IspisiPodatke() const=0;
    virtual ApstraktniStudent* DajKopiju() const=0;
};
void ApstraktniStudent::RegistrirajIspit(int ocjena){
    if(ocjena<5 || ocjena>10) throw std::domain_error("\nNeispravna ocjena");
    if(ocjena==5) goto kraj;
    br_polozenih++;
    prosjecna=(prosjecna*(br_polozenih-1)+ocjena)/br_polozenih;
    kraj:;
}
void ApstraktniStudent::PonistiOcjene(){
    br_polozenih=0;
    prosjecna=5;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StudentBachelor : public ApstraktniStudent{
    public:
    StudentBachelor(std::string ime,std::string prezime,int indeks) : ApstraktniStudent(ime,prezime,indeks){}
    void IspisiPodatke() const override{
        std::cout<<"\nStudent bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nima prosjek "<<DajProsjek()<<".\n";
    }
    ApstraktniStudent* DajKopiju() const override{return new StudentBachelor(*this);}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StudentMaster : public ApstraktniStudent{
    int datum_polaganja;
    public:
    StudentMaster(std::string ime,std::string prezime,int indeks,int datum) : ApstraktniStudent(ime,prezime,indeks),datum_polaganja(datum){}
    void IspisiPodatke() const override{
        std::cout<<"\nStudent master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<",\nzavrsio bachelor studij godine "<<datum_polaganja<<",ima prosjek "<<DajProsjek()<<".\n";
    }
    ApstraktniStudent* DajKopiju() const override{return new StudentMaster(*this);}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Fakultet{
    std::vector<ApstraktniStudent*> v;
    bool Postojanje(int broj){
        for(int i=0;i<v.size();i++){
            if(v[i]->DajBrojIndeksa()==broj) return true;
        }
        return false;
    }
    public:
    explicit Fakultet()=default;
    ~Fakultet(){for(auto x: v) delete x;}
    Fakultet(const Fakultet &x);
    Fakultet(Fakultet &&x){v=x.v; x.v.clear();}
    Fakultet& operator=(const Fakultet &x);
    Fakultet& operator=(Fakultet &&x);
    void UpisiStudenta(std::string ime,std::string prezime,int indeks);
    void UpisiStudenta(std::string ime,std::string prezime,int indeks,int datum);
    void ObrisiStudenta(int indeks);
    ApstraktniStudent& operator[](int indeks);
    ApstraktniStudent& operator[](int indeks) const;
    void IspisiSveStudente() const;
};

Fakultet::Fakultet(const Fakultet &x){
    for(int i=0;i<x.v.size();i++){
        v.push_back((x.v[i]->DajKopiju()));
    }
}
Fakultet& Fakultet::operator=(const Fakultet &x){
    if(&x!=this){
        for(int i=0;i<v.size();i++) delete v[i];
        v.resize(0);
        for(int i=0;i<x.v.size();i++){
            v.push_back(x.v[i]->DajKopiju());
        }
    }
    return *this;
}
Fakultet& Fakultet::operator=(Fakultet &&x){
    if(&x!=this){
        for(int i=0;i<v.size();i++) delete v[i];
        v.resize(0);
        v=x.v;
        x.v.clear();
    }
    return *this;
}
void Fakultet::UpisiStudenta(std::string ime,std::string prezime,int indeks){
    if(Postojanje(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    auto pok=new StudentBachelor(ime,prezime,indeks);
    v.push_back(pok);
}
void Fakultet::UpisiStudenta(std::string ime,std::string prezime,int indeks,int datum){
    if(Postojanje(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    auto pok=new StudentMaster(ime,prezime,indeks,datum);
    v.push_back(pok);
}
void Fakultet::ObrisiStudenta(int indeks){
    if(!Postojanje(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    for(auto pok=v.begin();pok!=v.end();pok++){
        if((*pok)->DajBrojIndeksa()==indeks){
            delete *pok; v.erase(pok); break;
        }
    }
}
ApstraktniStudent& Fakultet::operator[](int indeks){
    if(!Postojanje(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
    for(auto pok=v.begin();pok!=v.end();pok++){
        if((*pok)->DajBrojIndeksa()==indeks){
            return **pok;
        }
    }
}
ApstraktniStudent& Fakultet::operator[](int indeks) const{
    for(auto pok=v.begin();pok!=v.end();pok++){
        if((*pok)->DajBrojIndeksa()==indeks){
            return **pok;
        }
    }
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
}
void Fakultet::IspisiSveStudente() const{
    std::vector<ApstraktniStudent*> pom(v);
    std::sort(pom.begin(),pom.end(),[](ApstraktniStudent* x,ApstraktniStudent* y){
        if(x->DajProsjek()==y->DajProsjek()) return x->DajBrojIndeksa()<y->DajBrojIndeksa();
        return x->DajProsjek()>y->DajProsjek();
    });
    for(auto x:pom) x->IspisiPodatke();
}
int main ()
{
	return 0;
}