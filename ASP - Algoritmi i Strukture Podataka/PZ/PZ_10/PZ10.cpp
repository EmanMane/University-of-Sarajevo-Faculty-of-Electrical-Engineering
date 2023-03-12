#include<iostream>
#include<vector>
#include<queue>

using namespace std;

template<typename TipOznake>
class Grana;
template<typename TipOznake>
class Cvor;
template<typename TipOznake>
class GranaIterator;

template<typename TipOznake>
class UsmjereniGraf{
    public:
    UsmjereniGraf(){}
    UsmjereniGraf(int broj_cvorova){}
    virtual ~UsmjereniGraf(){}
    virtual int dajBrojCvorova() const=0;
    virtual void postaviBrojCvorova(int broj_cvorova)=0;
    virtual void dodajGranu(int c1,int c2, double tezina)=0;
    virtual void obrisiGranu(int c1,int c2)=0;
    virtual void postaviTezinuGrane(int c1,int c2, double tezina)=0;
    virtual double dajTezinuGrane(int c1,int c2) const=0;
    virtual bool postojiGrana(int c1,int c2)=0;
    virtual void postaviOznakuCvora(int broj_cvora,TipOznake oznaka)=0;
    virtual TipOznake dajOznakuCvora(int broj_cvora) const=0;
    virtual void postaviOznakuGrane(int c1,int c2,TipOznake oznaka)=0;
    virtual TipOznake dajOznakuGrane(int c1,int c2) const=0;
    virtual Cvor<TipOznake> dajCvor(int c)=0;
    virtual Grana<TipOznake> dajGranu(int c1,int c2)=0;
    virtual GranaIterator<TipOznake> dajSljedecuGranu(int k1,int k2)=0;
    GranaIterator<TipOznake> dajGranePocetak(){
        GranaIterator<TipOznake> pom(this,0,-1);
        return ++pom;
    }
    GranaIterator<TipOznake> dajGraneKraj(){
        GranaIterator<TipOznake> pom(this,-1,-1);
        return pom;
    }
};

template<typename TipOznake>
class Cvor{
    UsmjereniGraf<TipOznake> *pok;
    int broj;
    public:
    Cvor(UsmjereniGraf<TipOznake> *p, int broj_cvora) : pok(p), broj(broj_cvora){}
    TipOznake dajOznaku() const{
        return pok->dajOznakuCvora(broj);
    }
    void postaviOznaku(TipOznake oznaka){
        pok->postaviOznakuCvora(broj,oznaka);
    }
    int dajRedniBroj() const{
        return broj;
    }
};

template<typename TipOznake>
class Grana{
    UsmjereniGraf<TipOznake> *pok;
    int c1,c2;
    public:

    Grana(UsmjereniGraf<TipOznake> *p,int c1,int c2) : pok(p), c1(c1), c2(c2){}

    double dajTezinu() const{
        return pok->dajTezinuGrane(c1,c2);
    }

    void postaviTezinu(double tezina){
        pok->postaviTezinuGrane(c1,c2,tezina);
    }

    TipOznake dajOznaku() const{
        return pok->dajOznakuGrane(c1,c2);
    }

    void postaviOznaku(TipOznake oznaka){
        pok->postaviOznakuGrane(c1,c2,oznaka);
    }

    Cvor<TipOznake> dajPolazniCvor() const{
        return pok->dajCvor(c1);
    }

    Cvor<TipOznake> dajDolazniCvor() const{
        return pok->dajCvor(c2);
    }
};

template<typename TipOznake>
class GranaIterator{
    UsmjereniGraf<TipOznake> *pok;
    int koordinata1,koordinata2;
    public:

    GranaIterator<TipOznake> (UsmjereniGraf<TipOznake> *p,int koordinata1,int koordinata2) : pok(p), koordinata1(koordinata1), koordinata2(koordinata2){}

    Grana<TipOznake> operator*(){
        return pok->dajGranu(koordinata1,koordinata2);
    }
    
    bool operator ==(const GranaIterator<TipOznake> &it) const{
        if(it.pok==pok && it.koordinata1==koordinata1 && it.koordinata2==koordinata2) return 1;
        return 0;
    }

    bool operator !=(const GranaIterator<TipOznake> &it) const{
        if(*this==it) return 0;
        return 1;
    }

    GranaIterator& operator++(){
        int sljk1,sljk2;
        GranaIterator<TipOznake> sljedeci=pok->dajSljedecuGranu(koordinata1,koordinata2);
        sljk1=sljedeci.koordinata1;
        koordinata1=sljk1;
        sljk2=sljedeci.koordinata2;
        koordinata2=sljk2;
        return *this;
    }

    GranaIterator operator++(int){
        GranaIterator<TipOznake> pom=(*this);
        ++(*this);
        return pom;
    }
};

template<typename TipOznake>
class MatricaGraf : public UsmjereniGraf<TipOznake>{
    vector<TipOznake> c;
    struct Element{
        double tezina;
        TipOznake oznaka;
        int broj_cvora=0;
        Element(){}
        Element(int x){
            broj_cvora=x;
        }
        Element(int x,double t){
            broj_cvora=x;
            tezina=t;
        }
    };
    vector<vector<Element>> mat;
    public:

    MatricaGraf(){}

    MatricaGraf(int broj_cvorova){
        if(broj_cvorova<0) throw "Error";
        mat.resize(broj_cvorova);
        for(int i=0;i<broj_cvorova;i++){
            Element e(0);
            mat.at(i).resize(broj_cvorova,e);
        }
        c.resize(broj_cvorova);
    }

    ~MatricaGraf(){}

    int dajBrojCvorova() const{
        return mat.size();
    }

    void postaviBrojCvorova(int broj_cvorova){
        if(mat.size()>broj_cvorova){
            c.resize(broj_cvorova);
            std::vector<Element> pom(broj_cvorova);
            for(int i=0;i<broj_cvorova;i++){
                Element e(0);
                pom.at(i)=e;
            }
            mat.resize(broj_cvorova);
            for(int i=0;i<mat.size();i++) mat.at(i)=pom;
        }
        else throw "Error";
    }

    void dodajGranu(int c1,int c2, double tezina){
        Element e(1,tezina);
        mat.at(c1).at(c2)=e;
    }

    void obrisiGranu(int c1,int c2){
        mat.at(c1).at(c2).broj_cvora=0;
    }

    void postaviTezinuGrane(int c1,int c2, double tezina){
        mat.at(c1).at(c2).tezina=tezina;
    }

    double dajTezinuGrane(int c1,int c2) const{
        return mat.at(c1).at(c2).tezina;
    }

    bool postojiGrana(int c1,int c2){
        return mat.at(c1).at(c2).broj_cvora;
    }

    void postaviOznakuCvora(int broj_cvora,TipOznake oznaka){
        c.at(broj_cvora)=oznaka;
    }

    TipOznake dajOznakuCvora(int broj_cvora) const{
        return c.at(broj_cvora);
    }

    void postaviOznakuGrane(int c1,int c2,TipOznake oznaka){
        mat.at(c1).at(c2).oznaka=oznaka;
    }

    TipOznake dajOznakuGrane(int c1,int c2) const{
        return mat.at(c1).at(c2).oznaka;
    }

    Cvor<TipOznake> dajCvor(int c){
        if(c<dajBrojCvorova() && c>=0){
            Cvor<TipOznake> x=Cvor<TipOznake>(this,c);
            return x;
        }
        else throw "Error";
    }

    Grana<TipOznake> dajGranu(int c1,int c2){
        if(postojiGrana(c1,c2) && c1>=0 && c1<dajBrojCvorova() && c2>=0 && c2<dajBrojCvorova()){
            Grana<TipOznake> x(this,c1,c2);
            return x;
        }
        else throw "Error";
    }

    GranaIterator<TipOznake> dajSljedecuGranu(int c1,int c2){
        int k1,k2;
        UsmjereniGraf<TipOznake> *pom=this;
        for(int i=c1;i<mat.size();i++){
            for(int j=0;j<mat.size();j++){
                if(i==c1 && j<=c2) continue;
                else if(mat.at(i).at(j).broj_cvora){
                    k1=i;
                    k2=j;
                    return GranaIterator<TipOznake>(pom,k1,k2);
                }
            }
        }
        return GranaIterator<TipOznake>(pom,-1,-1);
    }
};

template<typename TipOznake>
void bfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake>> &bfso, Cvor<TipOznake> c){
    c.postaviOznaku(1);
    bfso.push_back(c);
    queue<Cvor<TipOznake>> red;
    red.push(c);
    while(!red.empty()){
        Cvor<TipOznake> pom=red.front(); red.pop();
        for(GranaIterator<TipOznake> p=graf->dajGranePocetak();p!=graf->dajGraneKraj();p++){
            Cvor<TipOznake> polazni=*p.dajPolazniCvor(),dolazni=*p.dajDolazniCvor();
            if(dolazni.dajOznaku()!=1 && polazni.dajRedniBroj()==pom.dajRedniBroj()){
                dolazni.postaviOznaku(1);
                bfso.push_back(dolazni);
                red.push(dolazni);
            }
        }
    }
}

template<typename TipOznake>
void dfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake>> &dfso, Cvor<TipOznake> c){
    c.postaviOznaku(1);
    dfso.push_back(c);
    GranaIterator<TipOznake> p=graf->dajGranePocetak();
    p++;
    for(;p!=graf->dajGraneKraj();p++){
        Cvor<TipOznake> dolazni=*p.dajDolazniCvor();
        if(*p.dajPolazniCvor().dajRedniBroj()==c.dajRedniBroj() && dolazni.dajOznaku()!=1) dfs(graf,dfso,dolazni);
    }
}

int main(){
    try {
        UsmjereniGraf<bool> *g = new MatricaGraf<bool>(3);
        g->dodajGranu(0, 1, 2.5);
        g->dodajGranu(1, 0, 1.2);
        g->dodajGranu(1, 2, 0.1);
        g->dodajGranu(0, 0, 3.14);
        for (GranaIterator<bool> iter = g->dajGranePocetak();
        iter != g->dajGraneKraj(); ++iter)
        cout << (*iter).dajPolazniCvor().dajRedniBroj() << " "
        << (*iter).dajDolazniCvor().dajRedniBroj() << " "
        << (*iter).dajTezinu() << endl;
        delete g;
    } catch (const char izuzetak[]) {
        cout << izuzetak << endl;
    }

    return 0;
}