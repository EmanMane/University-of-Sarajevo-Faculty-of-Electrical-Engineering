/* 
    TP 16/17 (LV 10, Zadatak 1)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>

class StedniRacun{
    double stanje;
    public:
    StedniRacun(double s=0){
        if(s<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        stanje=s;
    }
    void Ulozi(double x){
        if(x<0) if(fabs(x)>stanje) throw std::logic_error("Transakcija odbijena");
        stanje+=x;
    }
    void Podigni(double x){
        if(stanje<=x) throw std::logic_error("Transakcija odbijena");
        stanje-=x;
    }
    double DajStanje() const{
        return stanje;
    }
    void ObracunajKamatu(double kamatna_stopa){
        if(kamatna_stopa<=0) throw std::logic_error("Nedozvoljena kamatna stopa");
        stanje+=stanje*kamatna_stopa/100;
    }
};

int main ()
{
    try{
        StedniRacun Emanovo_stanje(100);
        Emanovo_stanje.Ulozi(100);
        Emanovo_stanje.Podigni(150);
        std::cout<<"Stanje na racunu: "<<Emanovo_stanje.DajStanje();
        Emanovo_stanje.ObracunajKamatu(5);
        std::cout<<std::endl<<"Kamata za 5%: "<<Emanovo_stanje.DajStanje();
    }
    catch(std::logic_error greska){
        std::cout<<greska.what();
    }
	return 0;
}