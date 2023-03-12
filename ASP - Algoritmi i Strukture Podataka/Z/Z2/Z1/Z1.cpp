#include<iostream>
#include <stdexcept>

using namespace std;

template<typename NekiTip>
struct Cvor{
    NekiTip vrijednost;
    Cvor<NekiTip> *sljedeci;
    Cvor<NekiTip> *prethodni;
};

template<typename NekiTip>
class Iterator;

template<typename NekiTip>
class Lista{
    public:
    Lista(){}
    virtual ~Lista(){}
    virtual int brojElemenata() const=0;
    virtual NekiTip trenutni() const=0;
    virtual NekiTip &trenutni()=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const NekiTip &element)=0;
    virtual void dodajIza(const NekiTip &element)=0;
    virtual NekiTip &operator[](int i) const=0;
    virtual NekiTip &operator[](int i)=0;
};

template<typename NekiTip>
class DvostrukaLista : public Lista<NekiTip>{
    Cvor<NekiTip> *tekuci=nullptr,*pocetni=nullptr,*krajnji=nullptr;
    int broj_elemenata=0,tekuci_pozicija=-1; 
    public:
    DvostrukaLista(){}
    DvostrukaLista &operator=(const DvostrukaLista &l){
        if(&l==this) return *this;
        if(broj_elemenata!=0){
            pocetak();
            for(int i=0;i<broj_elemenata;i++) obrisi();
        }
        for(int i=0;i<l.broj_elemenata;i++){
            dodajIza(l[i]);
            sljedeci();
        }
        for(int i=0;i<l.broj_elemenata;i++) sljedeci();
        return *this;
    }
    DvostrukaLista(const DvostrukaLista &l){
        for(int i=0;i<l.broj_elemenata;i++){
            dodajIza(l[i]);
            sljedeci();
        }
        for(int i=0;i<l.broj_elemenata;i++) sljedeci();
    }
    int brojElemenata() const{
        return broj_elemenata;
    }
    ~DvostrukaLista(){
        while(tekuci) obrisi();
    }
    NekiTip &trenutni(){
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        else return tekuci->vrijednost;
    }
    NekiTip trenutni() const{
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        else return tekuci->vrijednost;
    }
    bool prethodni(){
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        else if(tekuci!=pocetni){ 
            tekuci=tekuci->prethodni;
            tekuci_pozicija--;
            return true;
        }
        return false;
    }
    bool sljedeci(){
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        else if(tekuci!=krajnji){ 
            tekuci=tekuci->sljedeci;
            tekuci_pozicija++;
            return true;
        }
        return false;
    }
    void pocetak(){
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        tekuci=pocetni;
        tekuci_pozicija=0;
    }
    void kraj(){
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        tekuci=krajnji;
        tekuci_pozicija=broj_elemenata-1;
    }
    void obrisi(){
        if(broj_elemenata==0) throw std::domain_error("Nema Elemenata!");
        if(broj_elemenata==1){
            delete tekuci;
            tekuci=nullptr;
            pocetni=nullptr;
            krajnji=nullptr;
            tekuci_pozicija--;
        }
        else if(tekuci==pocetni){
            tekuci=tekuci->sljedeci;
            delete pocetni;
            pocetni=tekuci;
            pocetni->prethodni=nullptr;
            tekuci_pozicija++;
        }
        else if(tekuci==krajnji){
            tekuci=tekuci->prethodni;
            delete krajnji;
            krajnji=tekuci;
            krajnji->sljedeci=nullptr;
            tekuci_pozicija--;
        }
        else{
            Cvor<NekiTip> *pom1=tekuci->prethodni,*pom2=tekuci->sljedeci;
            delete tekuci;
            pom1->sljedeci=pom2; pom2->prethodni=pom1; tekuci=pom2;
            tekuci_pozicija--;
        }
        broj_elemenata--;
    }
    NekiTip &operator[](int i) const{
        if(broj_elemenata==0 || i<0) throw std::domain_error("Greska!");
        int j=0;
        Cvor<NekiTip> *pok=pocetni;
        for(pok=pocetni;pok;pok=pok->sljedeci){
            if(i==j) return pok->vrijednost;
            j++;
        }
        return pok->vrijednost;
    }
    NekiTip &operator[](int i){
        if(broj_elemenata==0 || i<0) throw std::domain_error("Greska!");
        int j=0; 
        for(Cvor<NekiTip> *pok=pocetni;pok;pok=pok->sljedeci){
            if(i==j) return pok->vrijednost;
            j++;
        }
        return trenutni(); 
    }
    void dodajIspred(const NekiTip &element){
        Cvor<NekiTip> *novi=new Cvor<NekiTip>;
        novi->vrijednost=element;
        if(broj_elemenata==0){
            pocetni=novi;
            krajnji=novi;
            tekuci=novi;
            tekuci_pozicija++;
        } 
        else if(tekuci==pocetni){
            novi->sljedeci=tekuci;
            tekuci->prethodni=novi;
            pocetni=novi;
        }
        else{
            Cvor<NekiTip> *pom=tekuci->prethodni;
            tekuci->prethodni=novi;
            pom->sljedeci=novi;
            novi->prethodni=pom;
            novi->sljedeci=tekuci;
        }
        broj_elemenata++;
    }
    void dodajIza(const NekiTip &element){
        Cvor<NekiTip> *novi=new Cvor<NekiTip>;
        novi->vrijednost=element;
        if(broj_elemenata==0){
            pocetni=novi;
            krajnji=novi;
            tekuci=novi;
            tekuci_pozicija++;
        } 
        else if(tekuci==krajnji){
            novi->prethodni=tekuci;
            tekuci->sljedeci=novi;
            krajnji=novi;
        }
        else{
            Cvor<NekiTip> *pom=tekuci->sljedeci;
            tekuci->sljedeci=novi;
            pom->prethodni=novi;
            novi->sljedeci=pom;
            novi->prethodni=tekuci;
        }
        broj_elemenata++;
    }
    friend class Iterator<NekiTip>;
};

template<typename NekiTip>
class Iterator{
    const DvostrukaLista<NekiTip> *pok_na_listu;
    Cvor<NekiTip> *pok_na_cvor;
    public:
    Iterator(const DvostrukaLista<NekiTip> &l){
        pok_na_listu=&l;
        pok_na_cvor=l.tekuci;
    }
    NekiTip& trenutni(){
        if(pok_na_listu->brojElemenata()==0) throw std::domain_error("Nema Elemenata!");
        return pok_na_cvor->vrijednost;
    }
    bool prethodni(){
        if(pok_na_listu->brojElemenata()==0) throw std::domain_error("Nema Elemenata!");
        if(pok_na_cvor==pok_na_listu->pocetni) return false;
        pok_na_cvor=pok_na_cvor->prethodni;
        return true;
    }
    bool sljedeci(){
        if(pok_na_listu->brojElemenata()==0) throw std::domain_error("Nema Elemenata!");
        if(pok_na_cvor==pok_na_listu->krajnji) return false;
        pok_na_cvor=pok_na_cvor->sljedeci;
        return true;
    }
    void pocetak(){
        if(pok_na_listu->brojElemenata()==0) throw std::domain_error("Nema Elemenata!");
        pok_na_cvor=pok_na_listu->pocetni;
    }
    void kraj(){
        if(pok_na_listu->brojElemenata()==0) throw std::domain_error("Nema Elemenata!");
        pok_na_cvor=pok_na_listu->krajnji;
    }
};


template<typename NekiTip>
class DvostraniRed{
    DvostrukaLista<NekiTip> clanovi;
    public:
    DvostraniRed(){
        clanovi=DvostrukaLista<NekiTip>();
    }
    ~DvostraniRed(){
        brisi();
    }
    DvostraniRed(const DvostraniRed &r){
        clanovi=r.clanovi;
    }
    DvostraniRed &operator=(const DvostraniRed &r){
        if(this!=&r) clanovi=r.clanovi;
        return *this;
    }
    void brisi(){
        int n=clanovi.brojElemenata();
        for(int i=0;i<n;i++) clanovi.obrisi();
    }
    NekiTip skiniSaCela(){
        clanovi.kraj();
        NekiTip x=clanovi.trenutni();
        clanovi.obrisi();
        return x;
    }
    void staviNaCelo(const NekiTip &x){
        if(clanovi.brojElemenata()!=0) clanovi.kraj();
        clanovi.dodajIza(x);
    }
    NekiTip &celo(){
        clanovi.kraj();
        return clanovi.trenutni();
    }
    NekiTip skiniSaVrha(){
        clanovi.pocetak();
        NekiTip x=clanovi.trenutni();
        clanovi.obrisi();
        return x;
    }
    void staviNaVrh(const NekiTip &x){
        if(clanovi.brojElemenata()!=0) clanovi.pocetak();
        clanovi.dodajIspred(x);
    }
    NekiTip &vrh(){
        clanovi.pocetak();
        return clanovi.trenutni();
    }
    int brojElemenata(){
        return clanovi.brojElemenata();
    }
};

void TestKonstruktor1(){
    DvostraniRed<int> dr;
    if(dr.brojElemenata()==0) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestKonstruktor2(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5);
    DvostraniRed<int> dr2(dr1);
    if(dr1.brojElemenata()==dr2.brojElemenata()) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestOperator(){
    DvostraniRed<int> dr1,dr2;
    dr1.staviNaCelo(5);
    dr2=dr1;
    if(dr1.brojElemenata()==dr2.brojElemenata()) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestBrisi(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5);
    dr1.brisi();
    if(dr1.brojElemenata()==0) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestSkiniSaCela(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5); dr1.staviNaCelo(2); dr1.skiniSaCela();
    if(dr1.brojElemenata()==1 && dr1.celo()==5) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestStaviNaCelo(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5); dr1.staviNaCelo(2);
    if(dr1.brojElemenata()==2 && dr1.celo()==2) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestCelo(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5); dr1.staviNaCelo(2); dr1.staviNaCelo(6); dr1.staviNaCelo(8);
    if(dr1.celo()==8) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestSkiniSaVrha(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5); dr1.staviNaCelo(2); dr1.skiniSaVrha();
    if(dr1.brojElemenata()==1 && dr1.celo()==2) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestStaviNaVrh(){
    DvostraniRed<int> dr1;
    dr1.staviNaVrh(5); dr1.staviNaVrh(2);
    if(dr1.brojElemenata()==2 && dr1.vrh()==2) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestVrh(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5); dr1.staviNaCelo(2); dr1.staviNaCelo(6); dr1.staviNaCelo(8);
    if(dr1.vrh()==5) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

void TestBrojElemenata(){
    DvostraniRed<int> dr1;
    dr1.staviNaCelo(5); dr1.staviNaCelo(2); dr1.staviNaCelo(6); dr1.staviNaCelo(8);
    if(dr1.brojElemenata()==4) std::cout<<"OK\n";
    else std::cout<<"Not OK\n";
}

int main(){
    TestKonstruktor1();
    TestKonstruktor2();
    TestOperator();
    TestBrisi();
    TestSkiniSaCela();
    TestStaviNaCelo();
    TestCelo();
    TestSkiniSaVrha();
    TestStaviNaVrh();
    TestVrh();
    TestBrojElemenata();
    return 0;
}