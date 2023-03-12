/*
    TP 16/17 (LV 9, Zadatak 4)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <stdexcept>
#include <iomanip>

class Sat{
    int sati,minute,sekunde;
    public:
    static bool DaLiJeIspravno(int sati, int minute, int sekunde){
        if(sati<0 || minute<0 || sekunde<0 || sati>23 || minute>59 || sekunde>59) return false;
        return true;
    }
    void Postavi(int h,int min,int sec){
        if(!DaLiJeIspravno(h,min,sec)) throw std::domain_error("Neispravno vrijeme");
        sati=h; minute=min; sekunde=sec;
    }
    void PostaviNormalizirano(int h,int min,int sec){
        while(sec<0){
            sec+=60; min--;
        }
        while(sec-59>0){
            sec-=60; min++;
        }
        while(min<0){
            min+=60; h--;
        }
        while(min-59>0){
            min-=60; h++;
        }
        while(h<0){
            h+=24;
        }
        while(h-23>0){
            h-=24;
        }
        Sat::sati=h;
        Sat::minute=min;
        Sat::sekunde=sec;
    }
    Sat &Sljedeci(){
        Sat::sekunde++;
        PostaviNormalizirano(Sat::sati,Sat::minute,Sat::sekunde);
        return *this;
    }
    Sat &Prethodni(){
        Sat::sekunde--;
        PostaviNormalizirano(Sat::sati,Sat::minute,Sat::sekunde);
        return *this;
    }
    Sat PomjeriZa(int kolicina){
        Sat::sekunde+=kolicina;
        PostaviNormalizirano(Sat::sati,Sat::minute,Sat::sekunde);
        return *this;
    }
    void Ispisi() const {
        std::cout<<std::setw(2)<<std::setfill('0')<<sati<<":"<<std::setw(2)<<std::setfill('0')<<minute<<":"<<std::setw(2)<<std::setfill('0')<<sekunde;
    }
    int DajSate() const {return sati;}
    int DajMinute() const {return minute;}
    int DajSekunde() const {return sekunde;}
    friend int BrojSekundiIzmedju(Sat s1, Sat s2);
    static int Razmak(Sat s1, Sat s2);
};

int BrojSekundiIzmedju(Sat s1, Sat s2){
    return (s1.sati*3600+s1.minute*60+s1.sekunde)-(s2.sati*3600+s2.minute*60+s2.sekunde);
}

int Sat::Razmak(Sat s1, Sat s2){
    return (s1.sati*3600+s1.minute*60+s1.sekunde)-(s2.sati*3600+s2.minute*60+s2.sekunde);
}

int main ()
{
    Sat s1;
    s1.Postavi(22,34,55);
    s1.Ispisi();
    Sat s2;
    s2.PostaviNormalizirano(222222,222,2);
    int br=BrojSekundiIzmedju(s1,s2);
    std::cout<<s1.DajSate()<<s1.DajMinute()<<s1.DajSekunde();
    s1.PomjeriZa(7);
    s2.Prethodni();
    s2.Sljedeci();
	return 0;
}