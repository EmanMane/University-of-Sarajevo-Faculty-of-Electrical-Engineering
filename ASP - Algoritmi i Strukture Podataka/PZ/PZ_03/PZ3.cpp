#include<iostream>
#include<stdexcept>

using namespace std;

int izuzetak=0;

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

void TestKonstruktora1(){
    Stek<int> s1;
    if(s1.brojElemenata()!=0) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestKonstruktora2(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    Stek<int> s2(s1);
    if(s1.brojElemenata()!=s2.brojElemenata()) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestOperatora(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    Stek<int> s2;
    s2=s1;
    if(s1.brojElemenata()!=s2.brojElemenata()) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestBrisi(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    s1.brisi();
    if(s1.brojElemenata()!=0) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestStavi(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    if(s1.vrh()!=3) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestSkini(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    if(s1.skini()!=3) std::cout<<"Not OK\n";
    else{
        if(s1.vrh()!=2) std::cout<<"Not OK\n";
        else std::cout<<"OK\n";
    }
    s1.brisi();
    try{
        s1.skini();
    }
    catch(...){
        izuzetak++;
    }
}

void TestVrh(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    if(s1.vrh()!=3 && s1.brojElemenata()!=3) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
    s1.brisi();
    try{
        s1.vrh();
    }
    catch(...){
        izuzetak++;
    }
}

void TestBrojElemenata(){
    Stek<int> s1;
    s1.stavi(1); s1.stavi(2); s1.stavi(3);
    if(s1.brojElemenata()!=3) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

int main(){
    TestKonstruktora1();
    TestKonstruktora2();
    TestOperatora();
    TestBrisi();
    TestStavi();
    TestSkini();
    TestVrh();
    TestBrojElemenata();
    if(izuzetak==2) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
    return 0;
}