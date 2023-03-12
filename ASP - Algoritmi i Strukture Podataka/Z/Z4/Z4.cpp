#include <cstdlib>
#include<iostream>

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

/*** - - - - - - - AVLSTABLOMAPA - - - - - - - ***/

template<typename TipKljuca,typename TipVrijednosti>
class AVLStabloMapa : public Mapa<TipKljuca,TipVrijednosti>{
    int vel=0;
    struct Cvor{
        TipKljuca k;
        TipVrijednosti v;
        Cvor *roditelj=nullptr;
        Cvor *l_dijete=nullptr;
        Cvor *d_dijete=nullptr;
        int balans=0; //dodat balans
    };
    Cvor *vrh=nullptr;
    public:

    AVLStabloMapa(){}

    ~AVLStabloMapa(){
        if(vel!=0) obrisi();
    }

    //Trazi cvor sa zadatim kljucem i brise ga (za AVL dodan balans)
    void obrisi(const TipKljuca &x){

        //Potraga za cvorom
        Cvor *pom=vrh,*pom_dijete=nullptr,*pom_roditelj=nullptr;
        while(pom!=nullptr && pom->k!=x){
            pom_roditelj=pom;
            if(pom->k<x) pom=pom->d_dijete;
            else pom=pom->l_dijete;
        }
        if(pom==nullptr) return;

        Cvor *dijete_pom_djeteta,*p;

        if(pom->l_dijete==nullptr){ //prvi slucaj: ako ne postoji lijevo dijete ili ako ne postoji niti jedno
            pom_dijete=pom->d_dijete;
            p=pom_roditelj;
        } 
        else{
            if(pom->d_dijete==nullptr){ //drugi slucaj: ako ne postoji desno dijete
                pom_dijete=pom->l_dijete;
                p=pom_roditelj;
            } 
            else{
                pom_dijete=pom->l_dijete;
                dijete_pom_djeteta=pom_dijete->d_dijete;
                p=pom;
                while(dijete_pom_djeteta){
                    p=pom_dijete;
                    pom_dijete=dijete_pom_djeteta;
                    dijete_pom_djeteta=pom_dijete->d_dijete;
                }
                if(pom!=p){
                    p->d_dijete=pom_dijete->l_dijete;
                    if(pom_dijete->l_dijete) pom_dijete->l_dijete->roditelj=p;
                    pom_dijete->l_dijete=pom->l_dijete;
                    if(pom->l_dijete) pom->l_dijete->roditelj=pom_dijete;
                }
                pom_dijete->d_dijete=pom->d_dijete;
                if(pom->d_dijete) pom->d_dijete->roditelj=pom_dijete;
            }
        }

        //spajanje pom_roditelja sa pom_djetetom (ako nema djece (prvi slucaj) spojit ce se nullptr i roditelj)
        if(pom_roditelj==nullptr) vrh=pom_dijete;
        else{
            if(pom_roditelj->l_dijete==pom){ 
                pom_roditelj->l_dijete=pom_dijete;
                pom_roditelj->balans-=1;
            }
            else {
                pom_roditelj->d_dijete=pom_dijete;
                pom_roditelj->balans+=1;
            }
        }

        if(pom_dijete) pom_dijete->roditelj=pom_roditelj;
        pom->d_dijete=nullptr;
        pom->l_dijete=nullptr;
        pom->roditelj=nullptr;
        vel--;
        delete pom;
    }

    //ista kao kod binarnog stabla
    void obrisi(){
        while(vrh) obrisi(vrh->k);
    }

    //ista kao kod binarnog stabla
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

/**FUNKCIJE ZA ROTACIJU U LIJEVO I DESNO + AZURIRANJE BALANSA REKURZIJOM**/
    void rotirajKorijenLijevo(Cvor *novi){
        Cvor *lijevi_desnog;
        lijevi_desnog=novi->d_dijete->l_dijete;
        novi->balans=0;
        Cvor *desni=novi->d_dijete, *desni_roditelj=novi->roditelj;
        desni->roditelj=desni_roditelj;
        desni->l_dijete=novi;

        if(desni->roditelj==nullptr) vrh=desni;
        else if(desni_roditelj->d_dijete==novi) desni->roditelj->d_dijete=desni;
        else desni->roditelj->l_dijete=desni;

        desni->balans=0;
        if(lijevi_desnog) lijevi_desnog->roditelj=novi;
        novi->d_dijete=lijevi_desnog;
        novi->roditelj=desni;
    }

    void rotirajKorijenDesno(Cvor *novi){
        Cvor *desni_lijevog;
        desni_lijevog=novi->l_dijete->d_dijete;
        novi->balans=0;
        Cvor *lijevi=novi->l_dijete, *lijevi_roditelj=novi->roditelj;
        lijevi->roditelj=lijevi_roditelj;
        lijevi->d_dijete=novi;

        if(lijevi->roditelj==nullptr) vrh=lijevi;
        else if(lijevi_roditelj->d_dijete==novi) lijevi->roditelj->d_dijete=lijevi;
        else lijevi->roditelj->l_dijete=lijevi;

        lijevi->balans=0;
        if(desni_lijevog) desni_lijevog->roditelj=novi;
        novi->l_dijete=desni_lijevog;
        novi->roditelj=lijevi;
    }

    void azurirajBalans(Cvor *novi, bool x=0){
        if(!novi) return; //trivijalni slucaj kad je korijeni
        else if(x) novi->balans-=1;
        else novi->balans+=1;
        int balans=novi->balans;
        if(novi->roditelj){
            if(novi->roditelj->d_dijete==novi) x=true;
            else x=false;
        }

        //za -2 ili 2 rotacije
        if(balans==2){
            if(novi->l_dijete->balans==1) rotirajKorijenDesno(novi);
            else{
                rotirajKorijenLijevo(novi->l_dijete);
                rotirajKorijenDesno(novi);
            }
        }
        else if(balans==-2){
            if(novi->d_dijete->balans==-1) rotirajKorijenLijevo(novi);
            else{
                rotirajKorijenDesno(novi->d_dijete);
                rotirajKorijenLijevo(novi);
            }
        }
        else{
            if(!balans) return;
            azurirajBalans(novi->roditelj,x);
        }
    }
/**-------------------------------------------------------------------------**/
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
            if(pom2==nullptr) return pom->v;
            //Treba azurirati balans
            if(pom2->l_dijete && pom2->d_dijete) pom2->balans=0; //oba djeteta
            else{
                bool dijete;
                if(pom2->l_dijete) dijete=0;
                if(pom2->d_dijete) dijete=1;
                azurirajBalans(pom2,dijete);
            }
        }
        return pom->v;
    }

    //ista kao kod binarnog stabla
    int brojElemenata() const{
        return vel;
    }

    void kopiranje(Cvor *&pom1, Cvor *pom2){
        if(pom2!=nullptr){
            pom1=new Cvor;
            pom1->k=pom2->k;
            pom1->v=pom2->v;
            pom1->roditelj=pom2->roditelj;
            pom1->l_dijete=nullptr;
            pom1->d_dijete=nullptr;
            pom1->balans=pom2->balans;
            kopiranje(pom1->l_dijete,pom2->l_dijete);
            kopiranje(pom1->d_dijete,pom2->d_dijete);
        }
    }

    AVLStabloMapa &operator =(const AVLStabloMapa<TipKljuca,TipVrijednosti> &stablo){
        if(this==&stablo) return *this;
        obrisi();
        kopiranje(vrh, stablo.vrh);
        vel=stablo.brojElemenata();
        return *this;
    }

    AVLStabloMapa &operator =(AVLStabloMapa<TipKljuca,TipVrijednosti> &&stablo){
        if(this==&stablo) return *this;
        obrisi();
        vrh=stablo.vrh;
        vel=stablo.brojElemenata();
        return *this;
    }

    AVLStabloMapa(const AVLStabloMapa<TipKljuca,TipVrijednosti> &stablo){
        kopiranje(vrh,stablo.vrh);
        vel=stablo.brojElemenata();
    }
};


void test_brzine(){
    AVLStabloMapa<int,int> nm;
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
    test_brzine();
    return 0;
}