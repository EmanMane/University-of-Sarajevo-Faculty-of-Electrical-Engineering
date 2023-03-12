/* 
    TP 16/17 (LV 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <iomanip>

class Krug{
    double r;
    public:
    explicit Krug(double x){
        if(x<=0) throw std::domain_error("Neispravan poluprecnik");
        r=x;
    }
    void Postavi(double x){
        if(x<=0) throw std::domain_error("Neispravan poluprecnik");
        r=x;
    }
    double DajPoluprecnik() const{
        return r;
    }
    double DajObim() const{
        return 2*r*4*std::atan(1);
    }
    double DajPovrsinu() const{
        return r*r*4*std::atan(1);
    }
    void Skaliraj(double faktor){
        if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
        r=r*faktor;
    }
    void Ispisi() const{
        std::cout<<std::setw(5)<<std::setprecision(5)<<std::fixed<<"R="<<r<<" O="<<DajObim()<<" P="<<DajPovrsinu();
    }
    friend class Valjak;
};

class Valjak{
    double visina;
    Krug baza;
    public:
    Valjak (double r_baze, double H) : baza(r_baze), visina(H){
        if(r_baze<0) throw std::domain_error("Neispravan poluprecnik");
        if(H<0) throw std::domain_error("Neispravna visina");
        baza=Krug(r_baze);
        visina=H;
    }
    void Postavi(double r_baze, double H){
        if(r_baze<0) throw std::domain_error("Neispravan poluprecnik");
        if(H<0) throw std::domain_error("Neispravna visina");
        baza=Krug(r_baze);
        visina=H;
    }
    Krug DajBazu() const{
        return baza;
    }
    double DajPoluprecnikBaze() const{
        return baza.DajPoluprecnik();
    }
    double DajVisinu() const{
        return visina;
    }
    double DajPovrsinu() const{
        return 2*baza.DajPovrsinu()+visina*baza.DajObim();
    }
    double DajZapreminu() const{
        return baza.DajPovrsinu()*visina;
    }
    void Skaliraj(double faktor){
        if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
        baza.r=baza.r*faktor;
    }
    void Ispisi() const{
        std::cout<<std::setw(5)<<std::setprecision(5)<<std::fixed<<"R="<<baza.r<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
    }
};

int main ()
{
	return 0;
}