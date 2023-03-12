//TP 2021/2022: LV 8, Zadatak 6
#include <iostream>
#include <cmath>

template<typename Tip>
struct Cvor{
    Tip element;
    Cvor<Tip>*veza;
};

template <typename TipElemenata> 
 Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni){
    Cvor<TipElemenata>*poc(nullptr),*prethodni;
    for(;;){
        TipElemenata broj;
        std::cin>>broj;
        if(broj==zavrsni) break;
        Cvor<TipElemenata>* novi(new Cvor<TipElemenata>);
        novi->element=broj;
        novi->veza=nullptr;
        if(!poc) poc=novi;
        else prethodni->veza=novi;
        prethodni=novi;
    }
    return poc;
}

template <typename TipElemenata>
 TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak){
    TipElemenata s=0;
    for(auto p=pocetak;p!=nullptr;p=p->veza) s+=p->element;
    return s;
}

template <typename TipElemenata>
 int BrojElemenata(Cvor<TipElemenata> *pocetak){
    int br=0;
    for(auto p=pocetak; p!=nullptr;p=p->veza) br++;
    return br;
}

template <typename TipElemenata>
 int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag){
    int br=0;
     for(auto p=pocetak; p!=nullptr;p=p->veza) if(p->element>prag) br++;
     return br;
}

template <typename TipElemenata>
 void UnistiListu(Cvor<TipElemenata> *pocetak){
    Cvor<TipElemenata> *pom=pocetak,*temp;
    while(pom!=nullptr){
        temp=pom->veza;
        delete pom;
        pom=temp;
    }
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    auto p(KreirajPovezanuListu(double(0)));
    double srednja(SumaElemenata(p)/BrojElemenata(p));
    std::cout<<"U slijedu ima "<<BrojVecihOd(p,srednja)<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(p);
	return 0;
}
