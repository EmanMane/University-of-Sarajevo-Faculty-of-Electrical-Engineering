#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<typename NekiTip>
struct Cvor{
    NekiTip vrijednost;
    Cvor<NekiTip> *donji;
};

template<typename NekiTip>
class Stek{
    int broj_clanova=0;
    Cvor<NekiTip> *Vrh=nullptr;
    public:
    Stek(){};
    Stek(const Stek &stek){
        Cvor<NekiTip> *pomocni=stek.Vrh;
        Cvor<NekiTip> *stari=stek.Vrh;
        while(pomocni){
            auto trenutni=new Cvor<NekiTip>; trenutni->vrijednost=pomocni->vrijednost; trenutni->donji=nullptr;
            if(pomocni!=stek.Vrh){
                stari->donji=trenutni;
            }
            else Vrh=trenutni;
            stari=trenutni;
            pomocni=pomocni->donji;
        }
        broj_clanova=stek.broj_clanova;
    }
    Stek &operator=(const Stek &stek){
        if(this==&stek) return *this;
        brisi();
        Cvor<NekiTip> *pomocni=stek.Vrh;
        Cvor<NekiTip> *stari=stek.Vrh;
        while(pomocni){
            auto trenutni=new Cvor<NekiTip>; trenutni->vrijednost=pomocni->vrijednost; trenutni->donji=nullptr;
            if(pomocni!=stek.Vrh){
                stari->donji=trenutni;
            }
            else Vrh=trenutni;
            stari=trenutni;
            pomocni=pomocni->donji;
        }
        broj_clanova=stek.broj_clanova;
        return *this;
    }
    ~Stek(){
        brisi();
    }
    void brisi(){
        if(broj_clanova!=0){
            while(Vrh->donji){
                NekiTip x=skini();
            }
            delete Vrh;
        }
        broj_clanova=0;
    }
    void stavi(const NekiTip& element){
        Cvor<NekiTip> *pomocni=new Cvor<NekiTip>;
        pomocni->donji=nullptr;
        pomocni->vrijednost=element;
        if(broj_clanova==0) Vrh=pomocni;
        else{
            pomocni->donji=Vrh;
            Vrh=pomocni;
        }
        broj_clanova++;
    }
    NekiTip skini(){
        if(broj_clanova==0) throw std::domain_error("Stek je prazan!");
        NekiTip vrijednost=Vrh->vrijednost;
        Cvor<NekiTip> *pomocni=Vrh->donji;
        delete Vrh;
        Vrh=pomocni;
        broj_clanova--;
        return vrijednost;
    }
    NekiTip &vrh(){
        if(broj_clanova==0) throw std::domain_error("Stek je prazan!");
        return Vrh->vrijednost;
    }
    int brojElemenata() const{
        return broj_clanova;
    }
};

int binarna_pretraga(vector<int> v, int poc, int kraj, int e){
    if(kraj>=poc){
        int sr=poc+(kraj-poc)/2;
        if(v[sr]==e) return sr;
        else if(v[sr]>e) return binarna_pretraga(v,poc,sr-1,e);
        return binarna_pretraga(v,sr+1,kraj,e);
    }
    return -1;
}

void pretraga(Stek<vector<int>>& s, int trazeni){
    if(s.brojElemenata()==0) std::cout<<"Nema elementa";
    else{
        std::vector<int> pom=s.skini();
        bool prisutan=0;
        if(std::find(pom.begin(),pom.end(),trazeni)!=pom.end()){
            int i=binarna_pretraga(pom,0,pom.size()-1,trazeni);
            std::cout<<i<<" "<<s.brojElemenata();
            prisutan=1;
        }
        if(std::find(pom.begin(),pom.end(),trazeni)==pom.end() && s.brojElemenata()==0){
            std::cout<<"Nema elementa";
        }
        if(s.brojElemenata()!=0 && !prisutan) pretraga(s,trazeni);
        s.stavi(pom);
    }
}

void test1(){
    std::vector<int> x={1,2,3,4,5,6,7,8,9,10};
    Stek<vector<int>> s;
    s.stavi(x);
    std::cout<<"Ocekivano: 4 0\nIzlaz: ";
    pretraga(s,5);
}

void test2(){
    std::vector<int> x={1,2,3,4,5,6,7,8,9,10},x2={11,12,13,14,15,16,17,18,19,20};
    Stek<vector<int>> s;
    s.stavi(x); s.stavi(x2);
    std::cout<<"Ocekivano: 9 1\nIzlaz: ";
    pretraga(s,20);
}

void test3(){
    std::vector<int> x={1,2,3,4,5,6,7,8,9,10},x2={11,12,13,14,15,16,17,18,19,20},x3={21,22,23,24,25,26,27,28,29,30};
    Stek<vector<int>> s;
    s.stavi(x); s.stavi(x2); s.stavi(x3);
    std::cout<<"Ocekivano: 5 2\nIzlaz: ";
    pretraga(s,26);
}


int main(){
    std::cout<<"----------TEST1----------\n";
    test1();
    std::cout<<"\n----------TEST2----------\n";
    test2();
    std::cout<<"\n----------TEST3----------\n";
    test3();
    return 0;
}