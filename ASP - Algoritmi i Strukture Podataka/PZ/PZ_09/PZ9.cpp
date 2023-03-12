#include <cstdlib>
#include<iostream>
#include <stdexcept>
#include <utility>
#include<string>

using namespace std;

/*** - - - - - - - MAPA - - - - - - - ***/

template<typename TipKljuca,typename TipVrijednosti>
class Mapa{
    public:
    Mapa<TipKljuca,TipVrijednosti>(){};
    virtual ~Mapa(){};
    virtual TipVrijednosti& operator[](TipKljuca kljuc)=0;
    virtual TipVrijednosti operator[](const TipKljuca kljuc) const=0;
    virtual int brojElemenata() const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca& kljuc)=0;
};


/*** - - - - - - - BINSTABLOMAPA - - - - - - - ***/

template<typename TipKljuca,typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca,TipVrijednosti>{
    int vel=0;
    struct Cvor{
        TipKljuca k;
        TipVrijednosti v;
        Cvor *roditelj=nullptr;
        Cvor *l_dijete=nullptr;
        Cvor *d_dijete=nullptr;
    };    
    Cvor *vrh=nullptr;
    public:

    BinStabloMapa(){}

    ~BinStabloMapa(){
        obrisi();
    }

    //Trazi cvor sa zadatim kljucem i brise ga
    void obrisi(const TipKljuca &x){

        //Potraga za cvorom
        Cvor *pom=vrh,*pom_dijete=nullptr,*pom_roditelj=nullptr;
        while(pom!=nullptr && pom->k!=x){
            pom_roditelj=pom;
            if(pom->k<x) pom=pom->d_dijete;
            else pom=pom->l_dijete;
        }
        if(pom==nullptr) return;

        if(pom->l_dijete==nullptr) pom_dijete=pom->d_dijete; //prvi slucaj: ako ne postoji lijevo dijete ili ako ne postoji niti jedno
        else{
            if(pom->d_dijete==nullptr) pom_dijete=pom->l_dijete; //drugi slucaj: ako ne postoji desno dijete
            else{
                pom_dijete=pom->l_dijete;
                Cvor *dijete_pom_djeteta=pom_dijete->d_dijete,*p=pom;
                while(dijete_pom_djeteta){
                    p=pom_dijete;
                    pom_dijete=dijete_pom_djeteta;
                    dijete_pom_djeteta=pom_dijete->d_dijete;
                }
                if(pom!=p){
                    p->d_dijete=pom_dijete->l_dijete;
                    pom_dijete->l_dijete=pom->l_dijete;
                }
                pom_dijete->d_dijete=pom->d_dijete;
            }
        }

        //spajanje pom_roditelja sa pom_djetetom (ako nema djece (prvi slucaj) spojit ce se nullptr i roditelj)
        if(pom_roditelj==nullptr) vrh=pom_dijete;
        else{
            if(pom_roditelj->l_dijete==pom) pom_roditelj->l_dijete=pom_dijete;
            else pom_roditelj->d_dijete=pom_dijete;
        }
        vel--;
        delete pom;
    }

    void obrisi(){
        while(vrh) obrisi(vrh->k);
    }

    TipVrijednosti operator [](const TipKljuca kljuc) const{
        auto pom=vrh;
        while(pom){
            if(pom->k==kljuc) return pom->v;
            else if(pom->k<kljuc) pom=pom->d_dijete;
            else pom=pom->l_dijete;
        }
        TipVrijednosti vrijednost=TipVrijednosti();
        return vrijednost;    
    }

    TipVrijednosti &operator [](TipKljuca kljuc){
        auto pom=vrh;
        while(pom){
            if(pom->k==kljuc) return pom->v;
            else if(pom->k<kljuc) pom=pom->d_dijete;
            else pom=pom->l_dijete;
        }

        if(pom==nullptr){
            vel++;
            auto pom1=vrh,pom2=vrh; pom2=nullptr;
            TipVrijednosti vrijednost=TipVrijednosti();
            pom=new Cvor;
            pom->k=kljuc; pom->v=vrijednost;
            while(pom1){
                pom2=pom1;
                if(pom1->k>pom->k) pom1=pom1->l_dijete;
                else pom1=pom1->d_dijete;
            }
            if(pom2==nullptr) vrh=pom;
            else if(pom2->k>pom->k){
                pom2->l_dijete=pom;
                pom->roditelj=pom2;
            }
            else{
                pom2->d_dijete=pom;
                pom->roditelj=pom2;
            }
        }
        return pom->v;
    }

    int brojElemenata() const{
        return vel;
    }

    void kopiranje(Cvor *pom){
        if(pom!=nullptr){
            (*this)[pom->k]=pom->v;
            kopiranje(pom->l_dijete);
            kopiranje(pom->d_dijete);
        }
    }

    BinStabloMapa &operator =(const BinStabloMapa<TipKljuca,TipVrijednosti> &stablo){
        if(this==&stablo) return *this;
        obrisi();
        kopiranje(stablo.vrh);
        vel=stablo.brojElemenata();
        return *this;
    }

    BinStabloMapa(BinStabloMapa<TipKljuca,TipVrijednosti> &stablo){
        if(stablo.vel!=0) kopiranje(stablo.vrh);
        vel=stablo.brojElemenata();
    }
};


/*** - - - - - - - NIZMAPA - - - - - - - ***/
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


/*** - - - - - - - HASHMAPA - - - - - - - ***/
template<typename TipKljuca,typename TipVrijednosti>
class HashMapa : public Mapa<TipKljuca,TipVrijednosti>{
    int vel,max;
    pair<TipKljuca,TipVrijednosti> *hash_mapa;
    bool *oznacen;
    unsigned int (*funkcija)(TipKljuca,unsigned int)=0;
    
    public:
    HashMapa<TipKljuca,TipVrijednosti>(){
        max=2;
        vel=0;
        oznacen=new bool[max];
        for(int i=0;i<2;i++) oznacen[i]=false;
        hash_mapa=new pair<TipKljuca,TipVrijednosti>[max];
    }

    HashMapa(const HashMapa<TipKljuca,TipVrijednosti> &mapa){
        hash_mapa=new pair<TipKljuca,TipVrijednosti>[mapa.max];
        oznacen=new bool[mapa.max];
        funkcija=mapa.funkcija;
        for(int i=0;i<mapa.vel;i++){
            oznacen[i]=mapa.oznacen[i];
            hash_mapa[i]=mapa.hash_mapa[i];
        }        
        max=mapa.max;
        vel=mapa.vel;
    }

    ~HashMapa(){
        delete[] hash_mapa;
        delete[] oznacen;
    }

    void prosiri(){
        max*=2;
        pair<TipKljuca,TipVrijednosti> *p=new pair<TipKljuca,TipVrijednosti>[max];
        for(int i=0;i<vel;i++) p[i]=hash_mapa[i];
        delete [] hash_mapa;
        hash_mapa=p;
    }

    TipVrijednosti& operator[](TipKljuca kljuc){
        if(funkcija){
            for(int i=0;i<vel;i++) if(kljuc==hash_mapa[i].first) return hash_mapa[i].second;
            if(vel==max) prosiri();
            TipVrijednosti x=TipVrijednosti();
            hash_mapa[vel].first=kljuc;
            hash_mapa[vel].second=x;
            vel++;
            return hash_mapa[vel-1].second;
        }
        else throw ("Nije definisana hash funkcija");
    }

    TipVrijednosti operator[](const TipKljuca kljuc) const{
        if(funkcija){
            int index=funkcija(kljuc,max);
            if(kljuc==hash_mapa[index].first) return hash_mapa[index].second;
            TipVrijednosti x=TipVrijednosti();
            int novi=index;
            novi++;
            while(novi<max){
                if(kljuc==hash_mapa[novi].first){
                    x=hash_mapa[novi].second;
                    goto dalje;
                }
                novi++;
            }
            novi=0;
            while(novi<index){
                if(kljuc==hash_mapa[novi].first){
                    x=hash_mapa[novi].second;
                    goto dalje;
                }
                novi++;
            }
            dalje:
            return x;

        }
        else throw ("Nije definisana hash funkcija");
    }

    int brojElemenata() const{
        return vel;
    }

    void obrisi(){
        max=2;
        vel=0;
        delete[] hash_mapa;
        delete[] oznacen;
        oznacen=new bool[max];
        for(int i=0;i<2;i++) oznacen[i]=false;
        hash_mapa=new pair<TipKljuca,TipVrijednosti>[max];
    }

    void obrisi(const TipKljuca& kljuc){
        int index;
        for(int i=0;i<vel;i++) 
            if(kljuc==hash_mapa[i].first){
                index=i;
                goto dalje;
            }
        throw "Nepostojeci index";
        dalje:;
        oznacen[index]=false;
        for(int i=0;i<vel;i++){
            if(kljuc==hash_mapa[i].first){
                vel--;
                for(int j=i;j<vel;j++) hash_mapa[j]=hash_mapa[j+1];
                break;
            }
        }
    }

    void definisiHashFunkciju(unsigned int (*h_funkcija)(TipKljuca ulaz,unsigned int raspon)){
        funkcija=h_funkcija;
    }

    HashMapa &operator =(const HashMapa<TipKljuca,TipVrijednosti> &mapa){
        if(&mapa==this) return *this;
        delete[] oznacen;
        delete[] hash_mapa;
        vel=mapa.vel;
        oznacen=new bool[max];
        hash_mapa=new pair<TipKljuca,TipVrijednosti>[mapa.max];
        max=mapa.max;
        funkcija=mapa.funkcija;
        for(int i=0;i<vel;i++){
            oznacen[i]=mapa.oznacen[i];
            hash_mapa[i]=mapa.hash_mapa[i];
        }
        return *this;
    }
};


/*** - - - - - - - HASH Funkcija- - - - - - - ***/
unsigned int hash(string ulaz, unsigned int max) {
    unsigned int x=max-10;
    x=x+x;
    x/=2;
    return x;
}


void test_brzine(){
    NizMapa<int,int> nm;
    BinStabloMapa<int,int> bsm;

    clock_t t1,t2,t3,t4,t5,t6,t7,t8;

    //popunjavanje mapa
    for(int i=0;i<9999;i++){
        nm[rand()]=rand();
        bsm[rand()]=rand();
    }
    //na poziciji 7577 sigurno imamo element, dok na poziciji 10 000 sigurno nemamo
    nm[7577]=69;
    bsm[7577]=69;

    t1=clock();
    nm[10000]=rand();
    t2=clock();

    t3=clock();
    bsm[10000]=rand();
    t4=clock();

    t5=clock();
    nm[7577]=rand();
    t6=clock();

    t7=clock();
    bsm[7577]=rand();
    t8=clock();

    std::cout<<"Dodavanje 10 000 - og elementa u:\nAVLMapu:  "<<(float)(t2-t1)/(CLOCKS_PER_SEC/1000)<<"\nBinStabloMapu: "<<(float)(t4-t3)/(CLOCKS_PER_SEC/1000)<<std::endl;
    std::cout<<"Pristup 7 577 - om elementu u:\nAVLMapi:  "<<(float)(t6-t5)/(CLOCKS_PER_SEC/1000)<<"\nBinStabloMapi: "<<(float)(t8-t7)/(CLOCKS_PER_SEC/1000)<<std::endl;
}

//BinStabloMapa za nijansu brza u oba testa kada se koristi randomiziranje





int main(){
HashMapa<std::string,std::string> m;
// Nije definisana hash funkcija!
std::string s1("Sarajevo"), s2("Zagreb");
m[s1] = "BiH";
m[s2] = "Hrvatska";
std::cout << m.brojElemenata() << " " << m[s2];
    //test_brzine();
    return 0;
}