//TP 2021/2022: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>

double PI=std::atan(1)*4;
long double e=pow(10,-10);
int broj_presjecanja=0;
int j=0;

class Kugla{
    double x,y,z,r;
    void ProvjeriR(double r){
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
    }
    public:
    explicit Kugla(double r = 0){
        try{ProvjeriR(r);}catch(...){throw;}
        Kugla::r=r;
        x=0; y=0; z=0;
    }
    Kugla(double x, double y, double z, double r = 0){
        try{ProvjeriR(r);}catch(...){throw;}
        Kugla::r=r;
        Kugla::x=x; Kugla::y=y; Kugla::z=z;
    }
    explicit Kugla(const std::tuple<double, double, double> &centar, double r = 0){
        try{ProvjeriR(r);}catch(...){throw;}
        Kugla::r=r;
        x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar);
    }
    double DajX() const{
        return x;
    }
    double DajY() const{
        return y;
    }
    double DajZ() const{
        return z;
    }
    std::tuple<double, double, double> DajCentar() const{
        std::tuple<double, double, double> centar(DajX(),DajY(),DajZ());
        return centar;
    }
    double DajPoluprecnik() const{
        return r;
    }
    double DajPovrsinu() const{
        return pow(r,2)*PI*4;
    }
    double DajZapreminu() const{
        return pow(r,3)*PI*4./3;
    }
    Kugla &PostaviX(double x){
        Kugla::x=x;
        return *this;
    }
    Kugla &PostaviY(double y){
        Kugla::y=y;
        return *this;
    }
    Kugla &PostaviZ(double z){
        Kugla::z=z;
        return *this;
    }
    Kugla &PostaviCentar(double x, double y, double z){
        Kugla::x=x;
        Kugla::y=y;
        Kugla::z=z;
        return *this;
    }
    Kugla &PostaviCentar(const std::tuple<double, double, double> &centar){
        x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar);
        return *this;
    }
    Kugla &PostaviPoluprecnik(double r){
        try{ProvjeriR(r);}catch(...){throw;}
        Kugla::r=r;
        return *this;
    }
    void Ispisi() const{
        std::cout<<"{("<<x<<","<<y<<","<<z<<"),"<<r<<"}"<<std::endl;
    }
    void Transliraj(double delta_x, double delta_y, double delta_z){
        x+=delta_x; y+=delta_y; z+=delta_z;
    }
    friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
    bool DaLiSadrzi(const Kugla &k) const{
        double duzina1=r-k.r,duzina2=sqrt(pow(k.x-x,2)+pow(k.y-y,2)+pow(k.z-z,2));
        if(duzina1<0 || duzina1<duzina2) return false;
        return true;
    }
    friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};

bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2){
    if(fabs(k1.r-k2.r)>e*(fabs(k1.r)+fabs(k2.r)) || fabs(k1.x-k2.x)>e*(fabs(k1.x)+fabs(k2.x)) || fabs(k1.y-k2.y)>e*(fabs(k1.y)+fabs(k2.y)) || fabs(k1.z-k2.z)>e*(fabs(k1.z)+fabs(k2.z))) return false;
    return true;
}
bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2){
    if(fabs(k1.r-k2.r)>e*(fabs(k1.r)+fabs(k2.r))) return false;
    return true; 
}
bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2){
    if(fabs(k1.x-k2.x)>e*(fabs(k1.x)+fabs(k2.x)) || fabs(k1.y-k2.y)>e*(fabs(k1.y)+fabs(k2.y)) || fabs(k1.z-k2.z)>e*(fabs(k1.z)+fabs(k2.z))) return false;
    return true;
}
bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2){
    double duzina1=k1.r+k2.r,duzina2=sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2));
    if(fabs(duzina1-duzina2)>e*(fabs(duzina1)+fabs(duzina2))) return false;
    return true;
}
bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2){
    double duzina1=fabs(k1.r-k2.r),duzina2=sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2));
    if(fabs(duzina1-duzina2)>e*(fabs(duzina1)+fabs(duzina2))) return false;
    return true;
}
double RastojanjeCentara(const Kugla &k1, const Kugla &k2){
    return sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2));
}
bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2){
    //|C1C2|<R1+R2
    //|C1C2|>|R1-R2|
    double duzina1=fabs(k1.r-k2.r),duzina2=sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2)),duzina3=k1.r+k2.r;
    if(RastojanjeCentara(k1,k2)<duzina3 && !DaLiSeDodirujuIznutra(k1,k2) && !DaLiSeDodirujuIzvana(k1,k2) && !k1.DaLiSadrzi(k2) && !k2.DaLiSadrzi(k1)) return true;
    return false;
}
bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2){
    //double duzina1=k1.r+k2.r,duzina2=sqrt(pow(k2.x-k1.x,2)+pow(k2.y-k1.y,2)+pow(k2.z-k1.z,2));
    if(DaLiSeSijeku(k1,k2)==true || k1.DaLiSadrzi(k2)==true || k2.DaLiSadrzi(k1)==true || DaLiSuIdenticne(k1,k2)==true || DaLiSuKoncentricne(k1,k2)==true || DaLiSeDodirujuIznutra(k1,k2)==true) return true;
    return false;
}



int main ()
{
    int n;
    std::cout<<"Unesite broj kugla: "; std::cin>>n;
    std::vector<std::shared_ptr<Kugla>> v(n);
    for(int i=0;i<n;i++){
        unos:;
        std::cout<<"Unesite centar "<<i+1<<". kugle: ";
        double x,y,z;
        std::cin>>x>>y>>z;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite poluprecnik "<<i+1<<". kugle: ";
        double r;
        std::cin>>r;
        std::cin.ignore(1000,'\n');
        try{
            v.at(i)=std::make_shared<Kugla>();
            v.at(i)->PostaviPoluprecnik(r);
            v.at(i)->PostaviCentar(x,y,z);
        }
        catch(std::domain_error error){
            std::cout<<error.what()<<std::endl;
            goto unos;
        }
    }
    std::cout<<"Unesite parametre translacije (delta_x,delta_y,delta_z): ";
    double delta_x,delta_y,delta_z;
    std::cin>>delta_x>>delta_y>>delta_z;
    std::transform(v.begin(),v.end(),v.begin(),[delta_x,delta_y,delta_z](std::shared_ptr<Kugla> k){
        k->Transliraj(delta_x,delta_y,delta_z);
        return k;
    });
    std::sort(v.begin(),v.end(),[](std::shared_ptr<Kugla> k1,std::shared_ptr<Kugla> k2){
        if(k1->DajZapreminu()>k2->DajZapreminu()) return false;
        else if(fabs(k1->DajZapreminu()-k2->DajZapreminu())<e*(fabs(k1->DajZapreminu())+fabs(k2->DajZapreminu()))){
            if(sqrt(pow(k1->DajX(),2)+pow(k1->DajY(),2)+pow(k2->DajZ(),2))<sqrt(pow(k2->DajX(),2)+pow(k2->DajY(),2)+pow(k2->DajZ(),2))) return true;
            return false;
        }
        return true;
    });
    std::cout<<"Kugle nakon obavljenje transformacije imaju sljedece vrijednosti: ";
    std::for_each(v.begin(),v.end(),[](std::shared_ptr<Kugla> k){
        k->Ispisi();
    });
    std::shared_ptr<Kugla> maxKugla=*(std::max_element(v.begin(),v.end(),[](std::shared_ptr<Kugla> k1,std::shared_ptr<Kugla> k2){
        return k1.get()->DajPovrsinu()<k2.get()->DajPovrsinu();
    }));
    std::cout<<"Kugla sa najvecom povrsinom je: ";
    maxKugla.get()->Ispisi();
    std::for_each(v.begin()+j,v.end(),[v](std::shared_ptr<Kugla> k1){
        std::for_each(v.begin()+j+1,v.end(),[k1](std::shared_ptr<Kugla> k2){
            if(DaLiSeSijeku(*k1,*k2)==true){
                std::cout<<"Presjecaju se kugle: ";
                k1->Ispisi();
                k2->Ispisi();
                broj_presjecanja++;
            }
        });
        j++;
    });
    if(broj_presjecanja==0) std::cout<<"Ne postoje kugle koje se presjecaju!";
	return 0;
}
