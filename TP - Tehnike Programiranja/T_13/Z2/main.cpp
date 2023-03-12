/* 
    TP 16/17 (LV 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
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

int main ()
{
	return 0;
}