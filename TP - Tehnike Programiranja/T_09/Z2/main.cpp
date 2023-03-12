/* 
    TP 16/17 (LV 9, Zadatak 2)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d{
    //double x,y,z;
    double koordinate[3];
    public:
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
    void Ispisi() const {std::cout<<"{"<<Vektor3d::koordinate[0]<<","<<Vektor3d::koordinate[1]<<","<<Vektor3d::koordinate[2]<<"}";}
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