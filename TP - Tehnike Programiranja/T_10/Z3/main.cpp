/* 
    TP 16/17 (LV 10, Zadatak 3)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>

class Vektor3d{
    //double x,y,z;
    double koordinate[3];
    mutable int brojac_ispisa=0;
    public:
    Vektor3d(double x, double y, double z){
        Vektor3d::koordinate[0]=x;
        Vektor3d::koordinate[1]=y;
        Vektor3d::koordinate[2]=z;
        brojac_ispisa=0;
    }
    Vektor3d(){
        brojac_ispisa=0;
        Vektor3d::koordinate[0]=0;
        Vektor3d::koordinate[1]=0;
        Vektor3d::koordinate[2]=0;
    }
    Vektor3d(const Vektor3d &v){
        brojac_ispisa=0;
        Vektor3d::koordinate[0]=v.koordinate[0];
        Vektor3d::koordinate[1]=v.koordinate[1];
        Vektor3d::koordinate[2]=v.koordinate[2];
    }
    void Postavi(double x, double y, double z){
        Vektor3d::koordinate[0]=x;
        Vektor3d::koordinate[1]=y;
        Vektor3d::koordinate[2]=z;
    }
    void PostaviX(double x){Vektor3d::koordinate[0]=x;}
    void PostaviY(double y){Vektor3d::koordinate[1]=y;}
    void PostaviZ(double z){Vektor3d::koordinate[2]=z;}
    void Ocitaj(double &x, double &y, double &z) const {
        x=Vektor3d::koordinate[0];
        y=Vektor3d::koordinate[1];
        z=Vektor3d::koordinate[2];
    }
    void Ispisi() const {std::cout<<"{"<<Vektor3d::koordinate[0]<<","<<Vektor3d::koordinate[1]<<","<<Vektor3d::koordinate[2]<<"}"; brojac_ispisa++;}
    int DajBrojIspisa() const {return brojac_ispisa;}
    double DajX() const {return Vektor3d::koordinate[0];}
    double DajY() const {return Vektor3d::koordinate[1];}
    double DajZ() const {return Vektor3d::koordinate[2];}
    double DajDuzinu() const {return sqrt(Vektor3d::koordinate[0]*Vektor3d::koordinate[0]+Vektor3d::koordinate[1]*Vektor3d::koordinate[1]+Vektor3d::koordinate[2]*Vektor3d::koordinate[2]);}
    Vektor3d &PomnoziSaSkalarom(double skalar){
        Vektor3d::koordinate[0]*=skalar;
        Vektor3d::koordinate[1]*=skalar;
        Vektor3d::koordinate[2]*=skalar;
        return *this;
    }
    Vektor3d SaberiSa(Vektor3d &v){
        Vektor3d::koordinate[0]+=v.koordinate[0];
        Vektor3d::koordinate[1]+=v.koordinate[1];
        Vektor3d::koordinate[2]+=v.Vektor3d::koordinate[2];
        return *this;
    }
    friend Vektor3d ZbirVektora(Vektor3d &v1, Vektor3d &v2){
        Vektor3d v3;
        v3.koordinate[0]=v1.koordinate[0]+v2.koordinate[0];
        v3.koordinate[1]=v1.koordinate[1]+v2.koordinate[1];
        v3.Vektor3d::koordinate[2]=v1.koordinate[2]+v2.Vektor3d::koordinate[2];
        return v3;
    }
};

int main ()
{
    Vektor3d v1; v1.Postavi(1,2,3); v1.Ispisi(); v1.Ispisi(); v1.Ispisi();
    Vektor3d v2(v1); v2.Ispisi(); v2.Ispisi();
	return 0;
}