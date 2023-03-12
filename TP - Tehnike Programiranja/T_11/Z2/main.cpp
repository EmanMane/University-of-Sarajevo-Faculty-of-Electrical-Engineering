/* 
    TP 16/17 (LV 11, Zadatak 2)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>

class StedniRacun{
    double stanje;

    //static - Koliko god tipova objekata ove klase bude stvoreno,
    //         postoji samo jedan objekat stvoren kao static (brk, bro)

    static int brk, bro;    //deklaracija: brk - broj kreiranih
                            //bro - broj obrisanih 
                            //Važno!!! Inicijalizacija je na dnu (zbog static)

    public:
    StedniRacun(double s){
        if(s<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        stanje=s;
        brk++;              //KONSTRUKTOR - povecaj broj kreiranih
    }
    StedniRacun(){
        stanje=0;
        brk++;              //KONSTRUKTOR - povecaj broj kreiranih
    }
    StedniRacun(const StedniRacun &s){
        stanje=s.stanje;
        brk++;              //KONSTRUKTOR - povecaj broj kreiranih
    }
    void Ulozi(double x){
        if(x<0) if(fabs(x)>stanje) throw std::logic_error("Transakcija odbijena");
        stanje+=x;
    }
    void Podigni(double x){
        if(stanje<x) throw std::logic_error("Transakcija odbijena");
        stanje-=x;
    }
    double DajStanje() const{
        return stanje;
    }
    void ObracunajKamatu(double kamatna_stopa){
        if(kamatna_stopa<=0) throw std::logic_error("Nedozvoljena kamatna stopa");
        stanje+=stanje*kamatna_stopa/100;
    }
    static int DajBrojKreiranih(){
        return brk;
    }
    static int DajBrojAktivnih(){
        return brk-bro;
    }
    ~StedniRacun(){
        bro++;              //DESTRUKTOR - povecaj broj obrisanih
    }
};
int StedniRacun::brk(0);        //inicijalizacija statickih varijabli
int StedniRacun::bro(0);

int main ()
{
//AT3: Testiranje brojaca u situacijama kada se pojavljuje i kopirajuca inicijalizacija

StedniRacun s1(1000), s2(s1), s3(s2), s4(s3), s5(s4);

std::cout << "Broj kreiranih: " << StedniRacun::DajBrojKreiranih() << std::endl;
std::cout << "Broj aktivnih: " << StedniRacun::DajBrojAktivnih() << std::endl;
	
{ StedniRacun s6(s1), s7(1000), s8, s9(s8), s10; }
	
std::cout << "Broj kreiranih: " << StedniRacun::DajBrojKreiranih() << std::endl;
std::cout << "Broj aktivnih: " << StedniRacun::DajBrojAktivnih() << std::endl;
		
try {
		
	StedniRacun s6(s1), s7(1000), s8, s9(s8), s10;
}
	
catch(std::logic_error e)
{
	std::cout << e.what() << std::endl;
}
		
std::cout << "Broj kreiranih: " << StedniRacun::DajBrojKreiranih() << std::endl;
std::cout << "Broj aktivnih: " << StedniRacun::DajBrojAktivnih() << std::endl;
	
StedniRacun s6(s1), s7(1000), s8, s9(s8), s10;
	
std::cout << "Broj kreiranih: " << StedniRacun::DajBrojKreiranih() << std::endl;
std::cout << "Broj aktivnih: " << StedniRacun::DajBrojAktivnih() << std::endl;
return 0;
}