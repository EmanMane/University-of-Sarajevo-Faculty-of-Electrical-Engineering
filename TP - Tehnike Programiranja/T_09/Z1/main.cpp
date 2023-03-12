/* 
    TP 16/17 (LV 9, Zadatak 1)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d{
    double x,y,z;
    public:
    void Postavi(double x, double y, double z){
        Vektor3d::x=x;
        Vektor3d::y=y;
        Vektor3d::z=z;
    }
    void PostaviX(double x){Vektor3d::x=x;}
    void PostaviY(double y){Vektor3d::y=y;}
    void PostaviZ(double z){Vektor3d::z=z;}
    void Ocitaj(double &x, double &y, double &z) const {
        x=Vektor3d::x;
        y=Vektor3d::y;
        z=Vektor3d::z;
    }
    void Ispisi() const {std::cout<<"{"<<x<<","<<y<<","<<z<<"}";}
    double DajX() const {return x;}
    double DajY() const {return y;}
    double DajZ() const {return z;}
    double DajDuzinu() const {return sqrt(x*x+y*y+z*z);}
    Vektor3d PomnoziSaSkalarom(double skalar){
        x*=skalar;
        y*=skalar;
        z*=skalar;
        return *this;
    }
    Vektor3d SaberiSa(Vektor3d &v){
        x+=v.x;
        y+=v.y;
        z+=v.z;
        return *this;
    }
    friend Vektor3d ZbirVektora(Vektor3d &v1, Vektor3d &v2);
};

Vektor3d ZbirVektora(Vektor3d &v1, Vektor3d &v2){
        Vektor3d v3;
        v3.x=v1.x+v2.x;
        v3.y=v1.y+v2.y;
        v3.z=v1.z+v2.z;
        return v3;
    }

int main ()
{
    Vektor3d v1,v2,v3;
    v1.PostaviX(1);
    v1.PostaviY(1);
    v1.PostaviZ(1);
    std::cout<<"Vektor1=("<<v1.DajX()<<","<<v1.DajY()<<","<<v1.DajZ()<<")"<<std::endl;
    v2.Postavi(2,2,2);
    std::cout<<"Vektor2=("<<v2.DajX()<<","<<v2.DajY()<<","<<v2.DajZ()<<")"<<std::endl;
    std::cout<<"v1+=v2:"<<std::endl;
    v1.SaberiSa(v2).Ispisi();
    std::cout<<std::endl<<"Duzina v2="<<v2.DajDuzinu()<<std::endl;
    v3=ZbirVektora(v1,v2);
    std::cout<<"v1+v2=";
    v3.Ispisi();
    v2.PomnoziSaSkalarom(4);
    std::cout<<std::endl<<"v2*=4: "; 
    v2.Ispisi();
	return 0;
}