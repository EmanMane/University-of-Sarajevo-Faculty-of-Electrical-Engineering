#include <iostream>
#include <stdexcept>

using namespace std;

template<typename TipKljuca,typename TipVrijednosti>
class Mapa{
    public:
    Mapa<TipKljuca,TipVrijednosti>(){};
    virtual ~Mapa(){};
    virtual TipVrijednosti& operator[](TipKljuca kljuc)=0;
    virtual TipVrijednosti operator[](TipKljuca kljuc) const=0;
    virtual int brojElemenata() const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca& kljuc)=0;
};

template<typename TipKljuca,typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca,TipVrijednosti>{
    std::pair<TipKljuca,TipVrijednosti> **niz;
    int vel;
    int kapacitet;
    public:
    NizMapa() : Mapa<TipKljuca,TipVrijednosti>(){
        niz=new std::pair<TipKljuca,TipVrijednosti>*[100]{};
        kapacitet=100;
        vel=0;
    }
    NizMapa<TipKljuca,TipVrijednosti>(NizMapa<TipKljuca,TipVrijednosti> const &x){
        niz=new std::pair<TipKljuca,TipVrijednosti>*[x.kapacitet]{};
        kapacitet=x.kapacitet;
        vel=x.vel;
        for(int i=0;i<vel;i++) niz[i]=new std::pair<TipKljuca,TipVrijednosti>(*x.niz[i]);
    }
    NizMapa &operator=(NizMapa &x){
        if(this==&x) return *this;
        obrisi();
        delete[] niz;
        niz=new std::pair<TipKljuca,TipVrijednosti>*[x.kapacitet]{};
        kapacitet=x.kapacitet;
        vel=x.vel;
        for(int i=0;i<vel;i++) niz[i]=new std::pair<TipKljuca,TipVrijednosti>(*x.niz[i]);
        return *this;
    }
    ~NizMapa(){
        for(int i=0;i<vel;i++) delete niz[i];
        delete[] niz;
        vel=0;
    }
    TipVrijednosti& operator[](TipKljuca kljuc){
        if(vel==0){
            std::pair<TipKljuca,TipVrijednosti> x;
            x.first=kljuc;
            niz[0]=new std::pair<TipKljuca,TipVrijednosti>(x);
            vel++;
            TipVrijednosti& y=niz[0]->second;
            return y;
        }
        else{
            int pozicija=-1;
            for(int i=0;i<vel;i++) if(niz[i]->first==kljuc) pozicija=i;
            if(pozicija>=0){
                TipVrijednosti& y=niz[pozicija]->second;
                return y;
            }
            else{
                if(vel==kapacitet){
                    //alokacija dodatnog prostora
                    kapacitet+=100;
                    std::pair<TipKljuca,TipVrijednosti> **niz2=new std::pair<TipKljuca,TipVrijednosti>*[kapacitet]{};
                    for(int i=0;i<vel;i++) niz2[i]=niz[i];
                    auto brisi=niz;
                    niz=niz2;
                    delete[] brisi;
                }
                std::pair<TipKljuca,TipVrijednosti> x;
                x.first=kljuc;
                niz[vel]=new std::pair<TipKljuca,TipVrijednosti>(x);
                TipVrijednosti& y=niz[vel]->second;
                vel++;
                return y;
            }
        }
    }
    TipVrijednosti operator[](TipKljuca kljuc) const{
        int pozicija=-1;
        for(int i=0;i<vel;i++) if(niz[i]->first==kljuc) pozicija=i;
        if(pozicija>=0){
            TipVrijednosti y=niz[pozicija]->second;
            return y;
        }
        else{
            return TipVrijednosti();
        }
    }
    int brojElemenata() const{
        return vel;
    }
    void obrisi(){
        for(int i=0;i<vel;i++) delete niz[i];
        vel=0;
    }
    void obrisi(const TipKljuca& kljuc){
        int pozicija=-1;
        for(int i=0;i<vel;i++) if(niz[i]->first==kljuc) pozicija=i;
        if(pozicija>=0){
            auto brisanje=niz[pozicija];
            if(vel==1){
                delete brisanje;
                vel=0;
                goto end;
            }
            for(int i=pozicija;i<vel-1;i++) niz[i]=niz[i+1];
            niz[vel-1]=nullptr;
            vel--;
            delete brisanje;
            end:;
        }
        else throw std::domain_error("Nema elementa u nizu");
    }
};

bool Test1(){
    NizMapa<std::string,std::string> m;
    m["Berlin"]="Njemačka";
    m["Paiz"]="Francuska";
    NizMapa<std::string,std::string> m1;
    m1=m;
    if(m1.brojElemenata()==m.brojElemenata()) return 1;
    return 0;
}

bool Test2(){
    NizMapa<std::string,std::string> m;
    m["Berlin"]="Njemačka";
    m["Paiz"]="Francuska";
    NizMapa<std::string,std::string> m1(m);
    if(m1.brojElemenata()==m.brojElemenata()) return 1;
    return 0;
}

bool Test3(){
    NizMapa<std::string,std::string> m;
    m["Berlin"]="Njemačka";
    m["Paiz"]="Francuska";
    if(2==m.brojElemenata()) return 1;
    return 0;
}

bool Test4(){
    NizMapa<int,int> m;
    for(int i=0;i<300;i++) m[i]=i;
    if(300==m.brojElemenata()) return 1;
    return 0;
}

bool Test5(){
    NizMapa<int,int> m;
    for(int i=0;i<300;i++) m[i]=i;
    m.obrisi();
    if(0==m.brojElemenata()) return 1;
    return 0;
}

int main(){
    if(Test1() && Test2() && Test3() && Test4() && Test5()) std::cout<<"Prošli testovi!!!";
    else std::cout<<"Nešto nije okej...";
    return 0;
}