/* 
    TP 16/17 (LV 10, Zadatak 5)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cmath>

const double PI=4*atan(1);

class Ugao{
    //double ugao;
    int stepeni,minute,sekunde;
    void Pretvori(double &divlji_ugao){
        while(divlji_ugao<0) divlji_ugao+=2*PI;
        while(divlji_ugao>=2*PI) divlji_ugao-=2*PI;
    }
    public:
    Ugao(double radijani = 0.){
        double ugao=radijani*180./PI; 
        stepeni=ugao;
        ugao=(ugao-stepeni)*60.;
        minute=ugao;
        ugao=(ugao-minute)*60.;
        sekunde=ugao;
        ugao=radijani;
        Postavi(stepeni,minute,sekunde);
    }
    Ugao(int step, int min, int sek){
        stepeni=step; minute=min; sekunde=sek;
    }
    void Postavi(double radijani){
        double ugao=radijani*180./PI; 
        stepeni=ugao;
        ugao=(ugao-stepeni)*60.;
        minute=ugao;
        ugao=(ugao-minute)*60.;
        sekunde=ugao;
        ugao=radijani;
        Postavi(stepeni,minute,sekunde);
        Pretvori(radijani);

    }
    void Postavi(int step, int min, int sek){
        while(sek>60){
            sek-=60; min++;
        }
        while(sek<0){
            sek+=60; min--;
        }
        while(min>60){
            min-=60; step++;
        }
        while(min<0){
            min+=60; step--;
        }
        while(step<0) step+=360;
        while(step>=360) step-=360;
        stepeni=step;
        minute=min;
        sekunde=sek;
    }
    double DajRadijane() const{
        return (stepeni+minute/60.+sekunde/3600.)*PI/180.;
    }
    void OcitajKlasicneJedinice(int &step, int &min, int &sek){
        step=stepeni;
        min=minute;
        sek=sekunde;
    }
    int DajStepene() const{
        int step=stepeni,min=minute,sek=sekunde;
        while(sek>60){
            sek-=60; min++;
        }
        while(sek<0){
            sek+=60; min--;
        }
        while(min>60){
            min-=60; step++;
        }
        while(min<0){
            min+=60; step--;
        }
        while(step<0) step+=360;
        while(step>=360) step-=360;
        return step;
    }
    int DajMinute() const{
        int step=stepeni,min=minute,sek=sekunde;
        while(sek>60){
            sek-=60; min++;
        }
        while(sek<0){
            sek+=60; min--;
        }
        while(min>60){
            min-=60; step++;
        }
        while(min<0){
            min+=60; step--;
        }
        while(step<0) step+=360;
        while(step>=360) step-=360;
        return min;
    }
    int DajSekunde() const{
        int step=stepeni,min=minute,sek=sekunde;
        while(sek>60){
            sek-=60; min++;
        }
        while(sek<0){
            sek+=60; min--;
        }
        while(min>60){
            min-=60; step++;
        }
        while(min<0){
            min+=60; step--;
        }
        while(step<0) step+=360;
        while(step>=360) step-=360;
        return sek;
    }
    void Ispisi() const{
        std::cout<<std::setw(5)<<std::setprecision(5)<<std::fixed<<DajRadijane();
    }
    void IspisiKlasicno() const{
        std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec ";
    }
    Ugao &SaberiSa(const Ugao &u){
        stepeni+=u.stepeni;
        minute+=u.minute;
        sekunde+=u.sekunde;
        Postavi(stepeni,minute,sekunde);
        return *this;
    }
    Ugao &PomnoziSa(double x){
        double ugao=DajRadijane()*x;
        Pretvori(ugao);
        Postavi(ugao);
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