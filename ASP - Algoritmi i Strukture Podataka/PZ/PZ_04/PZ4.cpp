#include<iostream>
#include <stdexcept>

using namespace std;

template<typename NekiTip>
struct Cvor{
    NekiTip vrijednost;
    Cvor<NekiTip> *sljedeci;
};

template<typename NekiTip>
class Red{
    NekiTip vrijednost;
    Cvor<NekiTip> *pocetak=nullptr;
    Cvor<NekiTip> *kraj=nullptr;
    int broj_elemenata=0;
    public:
    Red(){}
    ~Red(){
        brisi();
    }
    Red(const Red &red){
        Cvor<NekiTip> *pomocni=red.pocetak;
        while(pomocni){
            stavi(pomocni->vrijednost);
            pomocni=pomocni->sljedeci;
        }
        broj_elemenata=red.broj_elemenata;
    }
    Red &operator=(Red &red){
        if(this==&red) return *this;
        brisi();
        Cvor<NekiTip> *pomocni=red.pocetak;
        while(pomocni){
            stavi(pomocni->vrijednost);
            pomocni=pomocni->sljedeci;
        }
        broj_elemenata=red.broj_elemenata;
        return *this;
    }
    void brisi(){
        while(pocetak){
            skini();
        }
    }
    NekiTip skini(){
        if(broj_elemenata==0) throw std::domain_error("Prazan red!");
        NekiTip x=pocetak->vrijednost;
        Cvor<NekiTip> *y=pocetak->sljedeci;
        delete pocetak;
        pocetak=y;
        broj_elemenata--;
        return x;
    }
    void stavi(const NekiTip& el){
        Cvor<NekiTip> *x=new Cvor<NekiTip>;
        x->vrijednost=el; x->sljedeci=nullptr;
        if(broj_elemenata==0){
            pocetak=x; kraj=x;
        }
        else{
            kraj->sljedeci=x;
            kraj=x;
        }
        broj_elemenata++;
    }
    NekiTip &celo(){
        if(broj_elemenata==0) throw std::domain_error("Prazan red!");
        return pocetak->vrijednost;
    }
    int brojElemenata(){
        return broj_elemenata;
    }
};

void TestKonstruktor1(Red<int> r1){
    if(r1.brojElemenata()!=0) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestKonstruktor2(Red<int> r1, Red<int> r2){
    while(r1.brojElemenata()!=0 || r2.brojElemenata()!=0){
        if(r1.skini()!=r2.skini()){ 
            std::cout<<"Not OK\n";
            goto dalje;
        }
    }
    std::cout<<"OK\n";
    dalje:;
}

void TestOperator(Red<int> r1, Red<int> r2){
    while(r1.brojElemenata()!=0 || r2.brojElemenata()!=0){
        if(r1.skini()!=r2.skini()){ 
            std::cout<<"Not OK\n";
            goto dalje;
        }
    }
    std::cout<<"OK\n";
    dalje:;
}

void TestBrisi(Red<int> r1){
    r1.brisi();
    if(r1.brojElemenata()!=0) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestSkini(Red<int> r1){
    r1.skini();
    if(r1.celo()!=2 || r1.brojElemenata()!=4) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestStavi(){
    Red<int> r1;
    r1.stavi(99);
    if(r1.celo()!=99 || r1.brojElemenata()!=1) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestCelo(Red<int> r1){
    if(r1.celo()!=1) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

void TestBrojElemenata(Red<int> r1){
    if(r1.brojElemenata()!=5) std::cout<<"Not OK\n";
    else std::cout<<"OK\n";
}

int main(){
    Red<int> red1,red2;
    TestKonstruktor1(red1);
    red2.stavi(1); red2.stavi(2); red2.stavi(3); red2.stavi(4); red2.stavi(5);
    red1=red2;
    Red<int> red3(red2);
    TestKonstruktor2(red2,red3);
    TestOperator(red2,red3);
    TestBrisi(red3);
    TestBrojElemenata(red2);
    TestCelo(red2);
    TestStavi();
    TestSkini(red2);
    return 0;
}