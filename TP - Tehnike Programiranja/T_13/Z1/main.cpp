/* 
    TP 16/17 (LV 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <cctype>
#include <iostream>
#include <memory>
#include <cmath>
#include <vector>

double PI=std::atan(1)*4;

class Lik{
    public:
    virtual void IspisiSpecificnosti() const=0;
    virtual double DajObim() const=0;
    virtual double DajPovrsinu() const=0;
    void Ispisi() const{
        IspisiSpecificnosti();
        std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;
    }
    virtual ~Lik(){}
};

class Krug: public Lik{
    double r;
    bool Ispravnost(double r){
        if(r<=0) return false;
        return true;
    }
    public:
    Krug(double r){
        if(!Ispravnost(r)) throw std::domain_error("Neispravni parametri");
        Krug::r=r;
    }
    void IspisiSpecificnosti() const{
        std::cout<<"Krug poluprecnika "<<r<<std::endl;
    }
    double DajObim() const{
        return PI*r*2;
    }
    double DajPovrsinu() const{
        return std::pow(r,2)*PI;
    }
};

class Pravougaonik: public Lik{
    double a,b;
    bool Ispravnost(double a, double b){
        if(a<=0 || b<=0) return false;
        return true;
    }    public:
    Pravougaonik(double a, double b){
        if(!Ispravnost(a,b)) throw std::domain_error("Neispravni parametri");
        Pravougaonik::a=a;
        Pravougaonik::b=b;
    }
    void IspisiSpecificnosti() const{
        std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;
    }
    double DajObim() const{
        return a+a+b+b;
    }
    double DajPovrsinu() const{
        return a*b;
    }
};

class Trougao: public Lik{
    double a,b,c;
    bool Ispravnost(double a, double b, double c){
        if(a<=0 || b<=0 || c<=0 || a+b<=c || b+c<=a || c+a<=b) return false;
        return true;
    }    
    public:
    Trougao(double a, double b, double c){
        if(!Ispravnost(a,b,c)) throw std::domain_error("Neispravni parametri");
        Trougao::a=a;
        Trougao::b=b;
        Trougao::c=c;
    }
    void IspisiSpecificnosti() const{
        std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<std::endl;
    }
    double DajObim() const{
        return a+b+c;
    }
    double DajPovrsinu() const{
        double s=DajObim()/2;
        return std::sqrt(s*(s-a)*(s-b)*(s-c));
    }
};

int main ()
{
    std::cout<<"Koliko zelite likova: "; int n;
    std::cin>>n; std::cin.ignore();
    std::vector<std::shared_ptr<Lik>> v;
    for(int i=0;i<n;i++){
        ponovi_unos:
        std::cout<<"\nLik "<<i+1<<": "<<std::endl;
        std::string komanda;
        std::getline(std::cin,komanda);
        auto p=komanda.begin();
        while(p!=komanda.end()){
            if(*p=='K'){
                p++;
                double r;
                std::string broj;
                while(p!=komanda.end()){
                    if(!std::isdigit(*p) && *p!='.'){
                        std::cout<<"Pogresni podaci, ponovite unos!";
                        goto ponovi_unos;
                    }
                    broj.push_back(*p);
                    p++;
                }
                r=std::stod(broj);
                try{
                    std::shared_ptr<Krug> spK(new Krug(r));
                    v.push_back(spK);
                }catch(...){
                    std::cout<<"Pogresni podaci, ponovite unos!";
                    goto ponovi_unos;
                }
            }
            else if(*p=='P'){
                p++;
                double a=-1,b=-1;
                int zarez=0;
                std::string broj;
                while(p!=komanda.end()){
                    if(*p==',') zarez++;
                    //std::cout<<" X ";
                    if((!std::isdigit(*p) && *p!='.' && *p!=',') || zarez==2){
                        std::cout<<"Pogresni podaci, ponovite unos!";
                        goto ponovi_unos;
                    }
                    if(a==-1 && zarez==1){ 
                        //std::cout<<" a ";
                        a=std::stod(broj);
                        broj={};
                    }
                    if(std::isdigit(*p) || *p=='.') broj.push_back(*p);
                    p++;
                }
                b=std::stod(broj);
                try{
                    std::shared_ptr<Pravougaonik> spP(new Pravougaonik(a,b));
                    v.push_back(spP);
                }catch(...){
                    std::cout<<"Pogresni podaci, ponovite unos!";
                    goto ponovi_unos;
                }
            }
            else if(*p=='T'){
                p++;
                double a=-1,b=-1,c=-1;
                int zarez=0;
                std::string broj;
                while(p!=komanda.end()){
                    if(*p==',') zarez++;
                    if((!std::isdigit(*p) && *p!='.' && *p!=',') || zarez==3){
                        std::cout<<"Pogresni podaci, ponovite unos!";
                        goto ponovi_unos;
                    }
                    if(std::isdigit(*p) || *p=='.') broj.push_back(*p);
                    if(a==-1 && zarez==1){ 
                        a=std::stod(broj);
                        broj={};
                    }
                    if(b==-1 && zarez==2){ 
                        b=std::stod(broj);
                        broj={};
                    }
                    p++;
                }
                c=std::stod(broj);
                try{
                    std::shared_ptr<Trougao> spT(new Trougao(a,b,c));
                    v.push_back(spT);
                }catch(...){
                    std::cout<<"Pogresni podaci, ponovite unos!";
                    goto ponovi_unos;
                }
            }
            else{
                std::cout<<"Pogresni podaci, ponovite unos!";
                goto ponovi_unos;
            }
        }
    }
    for(int i=0;i<n;i++){
        std::cout<<std::endl;
        v[i]->Ispisi();
    }
	return 0;
}