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
        for(Cvor<NekiTip> *pok=pocetni;pok;pok=pok->sljedeci){
            if(i==j) return pok->vrijednost;
            j++;
        }
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
NekiTip dajMaksimum(const Lista<NekiTip>& n){
    if(n.brojElemenata()==0) throw std::domain_error("Nema Elemenata!");
    DvostrukaLista<NekiTip> *l=(DvostrukaLista<NekiTip>*)(&n);
    Iterator<NekiTip> *it=new Iterator<NekiTip>(*l);
    it->pocetak(); int max=it->sljedeci();
    do{
        if(it->trenutni()>max) max=it->trenutni();
    }while(it->sljedeci());
    delete it;
    return max;
}

void TestKonstruktora1(){
    DvostrukaLista<int> l;
    if(l.brojElemenata()!=0) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestKonstruktora2(){
    DvostrukaLista<int> l;
    l.dodajIspred(5);
    DvostrukaLista<int> l1(l);
    if(l1.brojElemenata()!=l.brojElemenata()) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestOperatoraJednako(){
    DvostrukaLista<int> l;
    l.dodajIspred(5);
    DvostrukaLista<int> l1;
    l1=l;
    if(l1.brojElemenata()!=l.brojElemenata()) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestOperatoraUglasteZagrade(){
    DvostrukaLista<int> l;
    l.dodajIspred(5);
    if(l[0]!=5) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestBrojElemenata(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8);
    if(l.brojElemenata()!=2) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestTrenutni(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8);
    if(l.trenutni()!=5) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestPrethodni(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8); l.prethodni();
    if(l.prethodni()) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestSljedeci(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8); l.sljedeci();
    if(l.sljedeci()) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestPocetak(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8); l.pocetak();
    if(l.trenutni()!=8) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestKraj(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8); l.kraj();
    if(l.trenutni()!=5) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestObrisi(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8); l.obrisi(); l.obrisi();
    if(l.brojElemenata()!=0) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestDodajIspred(){
    DvostrukaLista<int> l;
    l.dodajIspred(5); l.dodajIspred(8); l.pocetak();
    if(l.trenutni()!=8) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestDodajIza(){
    DvostrukaLista<int> l;
    l.dodajIza(5); l.dodajIza(8); l.pocetak();
    if(l.trenutni()!=5) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
void TestDajMaksimum(){
    DvostrukaLista<int> l;
    l.dodajIza(5); l.dodajIza(8); l.dodajIza(999); l.dodajIza(-8); 
    if(dajMaksimum(l)!=999) std::cout<<"Not OK";
    else  std::cout<<"OK";
}
int main(){
    TestKonstruktora1(); std::cout<<"\n";
    TestKonstruktora2(); std::cout<<"\n";
    TestOperatoraJednako(); std::cout<<"\n";
    TestOperatoraUglasteZagrade(); std::cout<<"\n";
    TestBrojElemenata(); std::cout<<"\n";
    TestTrenutni(); std::cout<<"\n";
    TestPrethodni(); std::cout<<"\n";
    TestSljedeci(); std::cout<<"\n";
    TestPocetak(); std::cout<<"\n";
    TestKraj(); std::cout<<"\n";
    TestObrisi(); std::cout<<"\n";
    TestDodajIspred(); std::cout<<"\n";
    TestDodajIza(); std::cout<<"\n";
    TestDajMaksimum(); 
}