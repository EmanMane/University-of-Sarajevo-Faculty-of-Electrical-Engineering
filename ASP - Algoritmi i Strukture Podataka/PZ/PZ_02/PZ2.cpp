#include<iostream>
#include <stdexcept>

template<typename NekiTip>
class Lista{
    public:
    virtual ~Lista(){};
    virtual int brojElemenata() const=0;
    virtual NekiTip trenutni() const=0;
    virtual NekiTip &trenutni()=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual bool obrisi()=0;
    virtual bool dodajIspred(const NekiTip &element)=0;
    virtual bool dodajIza(const NekiTip &element)=0;
    virtual NekiTip operator[](int i) const=0;
    virtual NekiTip &operator[](int i)=0;
};

template<typename NekiTip>
class NizLista : public Lista<NekiTip>{
    NekiTip **GlavniPok;
    int vel=10000;
    int broj_elemenata=0;
    int trenutna_pozicija=0;
    public:
    NizLista(){
        GlavniPok=new(NekiTip *[10000]){nullptr};
    }
    NizLista(const NizLista<NekiTip> &niz){
        GlavniPok=new NekiTip *[niz.vel]{nullptr};
        for(int i=0;i<niz.broj_elemenata;i++){
            GlavniPok[i]=new NekiTip(niz[i]);
        }
        vel=niz.vel;
        broj_elemenata=niz.broj_elemenata;
        trenutna_pozicija=niz.trenutna_pozicija;
    }
    NizLista &operator=(NizLista niz){
        std::swap(GlavniPok,niz.GlavniPok);
        for(int i=0;i<niz.broj_elemenata-1;i++) std::swap(GlavniPok[i],niz.GlavniPok[i]);
        broj_elemenata=niz.broj_elemenata;
        return *this;
    }
    ~NizLista() override {
        for(int i=0;i<broj_elemenata;i++){
            delete GlavniPok[i];
        }
        delete[] GlavniPok;
    }
    int brojElemenata() const override{
        return broj_elemenata;
    }
    NekiTip trenutni() const override {
        return *GlavniPok[trenutna_pozicija];
    }
    NekiTip &trenutni() override {
        return *GlavniPok[trenutna_pozicija];
    }
    bool prethodni() override {
        if(trenutna_pozicija==0) return 0;
        else{
            trenutna_pozicija--; return 1;
        }
    }
    bool sljedeci() override {
        if(trenutna_pozicija==broj_elemenata-1) return 0;
        else{
            trenutna_pozicija++; return 1;
        }
    }
    void pocetak() override {
        trenutna_pozicija=0;
    }
    void kraj() override {
        trenutna_pozicija=broj_elemenata-1;
    }
    bool obrisi() override {
        if(broj_elemenata==0) throw std::length_error("NizLista je već prazna!!!");
        delete GlavniPok[trenutna_pozicija];
        for(int i=trenutna_pozicija;i<broj_elemenata;i++) GlavniPok[i]=GlavniPok[i+1];
        if(trenutna_pozicija==broj_elemenata-1 && trenutna_pozicija!=0) trenutna_pozicija--;
        broj_elemenata--;
        return 1;
    }
    bool dodajIspred(const NekiTip &element) override {
        if(broj_elemenata+1>=vel){
            vel+=100000;
            auto **pomocni(new NekiTip *[vel]);
            int pombr=broj_elemenata,pomtrn=trenutna_pozicija;
            for(int i=0;i<broj_elemenata;i++){
                pomocni[i]=new NekiTip(*GlavniPok[i]);
                delete GlavniPok[i];
                GlavniPok[i]=nullptr;
            }
            delete[] GlavniPok;
            GlavniPok=pomocni; broj_elemenata=pombr; trenutna_pozicija=pomtrn;
            for(int i=0;i<broj_elemenata;i++) GlavniPok[i]=pomocni[i];
        }
        if(broj_elemenata!=0){
            for(int i=broj_elemenata;i>trenutna_pozicija;i--) GlavniPok[i]=GlavniPok[i-1];
            GlavniPok[trenutna_pozicija]=new NekiTip(element);
            trenutna_pozicija++;
        }
        else GlavniPok[0]=new NekiTip(element);
        broj_elemenata++;
        return 1;        
    }
    bool dodajIza(const NekiTip &element) override {
        if(broj_elemenata!=0){
            for(int i=broj_elemenata;i>trenutna_pozicija;i--) GlavniPok[i]=GlavniPok[i-1];
            GlavniPok[trenutna_pozicija+1]=new NekiTip(element);
        }
        else GlavniPok[0]=new NekiTip(element);
        broj_elemenata++;  
        return 1;        
    }
    NekiTip operator[](int i) const override {
        return *GlavniPok[i];
    }
    NekiTip &operator[](int i) override {
        return *GlavniPok[i];
    }
};

template<typename NekiTip>
struct Cvor{
    NekiTip vrijednost;
    Cvor<NekiTip> *sljedeci;
};

template<typename NekiTip>
class JednostrukaLista : public Lista<NekiTip>{
    int broj_elemenata=0;
    Cvor<NekiTip> *trenutniCvor=nullptr;
    Cvor<NekiTip> *pocetniCvor=nullptr;
    public:
    JednostrukaLista()=default;
    JednostrukaLista(const JednostrukaLista<NekiTip> &lista){
        pocetniCvor=new Cvor<NekiTip>({lista.pocetniCvor->vrijednost,nullptr});
        pocetniCvor->sljedeci=new Cvor<NekiTip>();
        auto p=pocetniCvor->sljedeci,q=lista.pocetniCvor->sljedeci;
        while(q){
            if(q==lista.trenutniCvor) trenutniCvor=p;
            p->vrijednost=q->vrijednost;
            p->sljedeci=new Cvor<NekiTip>();
            p=p->sljedeci; q=q->sljedeci;
        }
        p=nullptr;
        broj_elemenata=lista.broj_elemenata;
    }
    JednostrukaLista &operator=(const JednostrukaLista &lista){
        pocetniCvor=new Cvor<NekiTip>({lista.pocetniCvor->vrijednost,nullptr});
        pocetniCvor->sljedeci=new Cvor<NekiTip>();
        auto p=pocetniCvor->sljedeci,q=lista.pocetniCvor->sljedeci;
        while(q){
            if(q==lista.trenutniCvor) trenutniCvor=p;
            p->vrijednost=q->vrijednost;
            p->sljedeci=new Cvor<NekiTip>();
            p=p->sljedeci; q=q->sljedeci;
        }
        p=nullptr;
        broj_elemenata=lista.broj_elemenata;
        return *this;
    }
    ~JednostrukaLista() override {
        auto *p=pocetniCvor;
        Cvor<NekiTip> *pomocni;
        while(p){
            pomocni=p->sljedeci;
            delete p;
            p=pomocni;
        }
        p=nullptr;
    }
    int brojElemenata() const  override {
        return broj_elemenata;
    }
    NekiTip trenutni() const override {
        return trenutniCvor->vrijednost;
    }
    NekiTip &trenutni() override {
        return trenutniCvor->vrijednost;
    }
    bool prethodni() override {
        for(auto p=pocetniCvor;p!=trenutniCvor;p=p->sljedeci){
            if(p->sljedeci==trenutniCvor){
                trenutniCvor=p;
                return 1;
            }
        }
        return 0;
    }
    bool sljedeci() override {
        if(!trenutniCvor->sljedeci) return 0;
        trenutniCvor=trenutniCvor->sljedeci; return 1;
    }
    void pocetak() override {
        trenutniCvor=pocetniCvor;
    }
    void kraj() override {
        auto p=pocetniCvor;
        while(p->sljedeci){
            p=p->sljedeci;
        }
        trenutniCvor=p;
    }
    bool obrisi() override {
        if(broj_elemenata==1){
            delete trenutniCvor;
            trenutniCvor=nullptr; pocetniCvor=nullptr;
        }
        else if(trenutniCvor->sljedeci==nullptr){
            Cvor<NekiTip> *predzadnji{};
            for(auto p=pocetniCvor;p!=trenutniCvor;p=p->sljedeci){
                if(p->sljedeci==trenutniCvor) predzadnji=p;
            }
            predzadnji->sljedeci=nullptr; delete trenutniCvor; trenutniCvor=predzadnji;
        }
        else{
            Cvor<NekiTip> *prethodni{};
            auto sljedeci=trenutniCvor->sljedeci;
            for(auto p=pocetniCvor;p!=trenutniCvor;p=p->sljedeci){
                if(p->sljedeci==trenutniCvor) prethodni=p;
            }
            if(prethodni){
                prethodni->sljedeci=sljedeci;
            }
            else{
                pocetniCvor=sljedeci;
            }
            delete trenutniCvor;
            trenutniCvor=sljedeci;
        }
        broj_elemenata--;
        return 1;
    }
    bool dodajIspred(const NekiTip &element) override {
        if(broj_elemenata==0){
            auto cvor=new Cvor<NekiTip>({element,nullptr});
            pocetniCvor=cvor;
            trenutniCvor=cvor;
        }
        else{
            Cvor<NekiTip> *prethodni{};
            auto cvor=new Cvor<NekiTip>({element,trenutniCvor});
            for(auto p=pocetniCvor;p!=trenutniCvor;p=p->sljedeci){
                if(p->sljedeci==trenutniCvor) prethodni=p;
            }
            if(prethodni) prethodni->sljedeci=cvor;
            else pocetniCvor=cvor;
        }
        broj_elemenata++;
        return 1;        
    }
    bool dodajIza(const NekiTip &element) override {
        if(broj_elemenata==0){
            auto cvor=new Cvor<NekiTip>({element,nullptr});
            pocetniCvor=cvor;
            trenutniCvor=cvor;
        }
        else{
            auto cvor=new Cvor<NekiTip>({element,nullptr});
            if(trenutniCvor->sljedeci){
                cvor->sljedeci=trenutniCvor->sljedeci;
            }
            trenutniCvor->sljedeci=cvor;
        }
        broj_elemenata++; 
        return 1;        
    }
    NekiTip &operator[](int i) override {
        auto p=pocetniCvor;
        for(int j=0;j<i;j++) p=p->sljedeci;
        return p->vrijednost;
    }
    NekiTip operator[](int i) const override {
        auto p=pocetniCvor;
        for(int j=0;j<i;j++) p=p->sljedeci;
        return p->vrijednost;
    }
};

int main(){
    std::cout<<"__________PROVJRA1__________\n";
    NizLista<int> N_L1;
    N_L1.pocetak();
    for(int i=0;i<10;i++){
        N_L1.dodajIspred(i);
    } 
    N_L1.pocetak();
    std::cout<<"Niz je: ";
    for(int i=0;i<N_L1.brojElemenata();i++) std::cout<<N_L1[i]<<" ";
    std::cout<<"\nBroj elemenata je: "<<N_L1.brojElemenata();
    N_L1.kraj(); N_L1.obrisi();
    std::cout<<"\nNiz nakon brisanja zadnjeg elemenata je: ";
    for(int i=0;i<N_L1.brojElemenata();i++) std::cout<<N_L1[i]<<" ";
    N_L1.pocetak(); N_L1.obrisi();
    std::cout<<"\nNiz nakon brisanja pocetnog elemenata je: ";
    for(int i=0;i<N_L1.brojElemenata();i++) std::cout<<N_L1[i]<<" ";
    N_L1.pocetak(); N_L1.dodajIspred(1);
    std::cout<<"\nNiz nakon vracanja pocetnog elemenata je: ";
    for(int i=0;i<N_L1.brojElemenata();i++) std::cout<<N_L1[i]<<" ";
    N_L1.kraj(); N_L1.dodajIza(10);
    std::cout<<"\nNiz nakon dodavanja elemenata poslije zadnjeg: ";
    for(int i=0;i<N_L1.brojElemenata();i++) std::cout<<N_L1[i]<<" ";
    std::cout<<"\nBroj elemenata je: "<<N_L1.brojElemenata()<<"\n\n";
    NizLista<int> N_L2;
    NizLista<int> N_L3(N_L1);
    N_L2=N_L1;
    std::cout<<"Provjera operatora = i konstruktora:";
    std::cout<<"\nPrvi niz: "; for(int i=0;i<N_L1.brojElemenata();i++) std::cout<<N_L1[i]<<" "; std::cout<<"Broj elemenata je: "<<N_L1.brojElemenata();
    std::cout<<"\nDrugi niz (kopija_1): "; for(int i=0;i<N_L2.brojElemenata();i++) std::cout<<N_L1[i]<<" "; std::cout<<"Broj elemenata je: "<<N_L2.brojElemenata();
    std::cout<<"\nTreci niz (kopija_2): "; for(int i=0;i<N_L3.brojElemenata();i++) std::cout<<N_L3[i]<<" "; std::cout<<"Broj elemenata je: "<<N_L3.brojElemenata();

    std::cout<<"\n\n__________PROVJRA2__________\n";
    JednostrukaLista<int> J_L1;
    J_L1.pocetak();
    for(int i=0;i<10;i++){
        J_L1.dodajIspred(i);
    } 
    J_L1.pocetak();
    std::cout<<"Niz je: ";
    for(int i=0;i<J_L1.brojElemenata();i++) std::cout<<J_L1[i]<<" ";
    std::cout<<"\nBroj elemenata je: "<<J_L1.brojElemenata();
    J_L1.kraj(); J_L1.obrisi();
    std::cout<<"\nNiz nakon brisanja zadnjeg elemenata je: ";
    for(int i=0;i<J_L1.brojElemenata();i++) std::cout<<J_L1[i]<<" ";
    J_L1.pocetak(); J_L1.obrisi();
    std::cout<<"\nNiz nakon brisanja pocetnog elemenata je: ";
    for(int i=0;i<J_L1.brojElemenata();i++) std::cout<<J_L1[i]<<" ";
    J_L1.pocetak(); J_L1.dodajIspred(1);
    std::cout<<"\nNiz nakon vracanja pocetnog elemenata je: ";
    for(int i=0;i<J_L1.brojElemenata();i++) std::cout<<J_L1[i]<<" ";
    J_L1.kraj(); J_L1.dodajIza(10);
    std::cout<<"\nNiz nakon dodavanja elemenata poslije zadnjeg: ";
    for(int i=0;i<J_L1.brojElemenata();i++) std::cout<<J_L1[i]<<" ";
    std::cout<<"\nBroj elemenata je: "<<J_L1.brojElemenata()<<"\n\n";
    JednostrukaLista<int> J_L2;
    JednostrukaLista<int> J_L3(J_L1);
    J_L2=J_L1;
    std::cout<<"Provjera operatora = i konstruktora:";
    std::cout<<"\nPrvi niz: "; for(int i=0;i<J_L1.brojElemenata();i++) std::cout<<J_L1[i]<<" "; std::cout<<"Broj elemenata je: "<<J_L1.brojElemenata();
    std::cout<<"\nDrugi niz (kopija_1): "; for(int i=0;i<J_L2.brojElemenata();i++) std::cout<<J_L1[i]<<" "; std::cout<<"Broj elemenata je: "<<J_L2.brojElemenata();
    std::cout<<"\nTreci niz (kopija_2): "; for(int i=0;i<J_L3.brojElemenata();i++) std::cout<<J_L3[i]<<" "; std::cout<<"Broj elemenata je: "<<J_L3.brojElemenata();

    return 0;
}