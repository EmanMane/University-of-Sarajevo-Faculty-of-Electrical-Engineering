/* 
    TP 16/17 (LV 10, Zadatak 4)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <iomanip>

const double PI=4*atan(1);

class Ugao{
    double ugao;
    void Pretvori(double &divlji_ugao){
        while(divlji_ugao<0) divlji_ugao+=2*PI;
        while(divlji_ugao>=2*PI) divlji_ugao-=2*PI;
    }
    public:
    Ugao(double radijani = 0.){
        ugao=radijani;
        Pretvori(ugao);
    }
    Ugao(int stepeni, int minute, int sekunde){
        ugao=(stepeni+minute/60.+sekunde/3600.)*PI/180.;
        Pretvori(ugao);
    }
    void Postavi(double radijani){
        ugao=radijani;
        Pretvori(ugao);
    }
    void Postavi(int stepeni, int minute, int sekunde){
        ugao=(stepeni+minute/60.+sekunde/3600.)*PI/180.;
        Pretvori(ugao);
    }
    double DajRadijane() const{
        return ugao;
    }
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
        ugao*=180./PI; 
        stepeni=ugao;
        ugao=(ugao-stepeni)*60.;
        minute=ugao;
        ugao=(ugao-minute)*60.;
        sekunde=ugao;
    }
    int DajStepene() const{
        return int(ugao*180./PI);
    }
    int DajMinute() const{
        double stepeni=ugao*180./PI;
        return int((stepeni-int(stepeni))*60.);
    }
    int DajSekunde() const{
        double e=0.0000000001;
        double stepeni=ugao*180./PI;
        double sec=(((stepeni-int(stepeni))*60.-int((stepeni-int(stepeni))*60.))*60.);
        sec+=e;
        return int(sec);
    }
    void Ispisi() const{
        std::cout<<std::setw(5)<<std::setprecision(5)<<std::fixed<<ugao;
    }
    void IspisiKlasicno() const{
        std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec ";
    }
    Ugao &SaberiSa(const Ugao &u){
        ugao+=u.ugao;
        Pretvori(ugao);
        return *this;
    }
    Ugao &PomnoziSa(double x){
        ugao*=x;
        Pretvori(ugao);
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
    Ugao u3;
    u3.Postavi(u1.DajRadijane()+u2.DajRadijane());
    return u3;
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
    Ugao novi;
    novi.Postavi(u.DajRadijane()*x);
    return novi;
}

int main ()
{
    Ugao u1(1,2,3),u2(60);
    u1.SaberiSa(u2);
    u2.Ispisi();
    u1.IspisiKlasicno();
    Ugao p=ProduktUglaSaBrojem(u1, 22);
    std::cout<<p.DajRadijane()<<" "<<p.DajStepene()<<" "<<p.DajMinute()<<" "<<p.DajSekunde();
	return 0;
}