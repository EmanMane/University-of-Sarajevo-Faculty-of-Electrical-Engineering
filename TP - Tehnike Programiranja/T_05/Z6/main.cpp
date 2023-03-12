/* 
    TP 2018/2019: LV 5, Zadatak 6
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int SumaCifara(int x){
    int S=0;
    S=S+abs(x%10);
    x=x/10;
    if(x!=0) S=S+SumaCifara(x);
    return S;
}

bool Uporedi(int a, int b){
    if(SumaCifara(a)<SumaCifara(b)) return true;
    else if(SumaCifara(a)==SumaCifara(b)){
        if(a<b) return true;
    }
    return false;
}

int main ()
{
    std::cout<<"Unesite broj elemenata: ";
    int n;
    std::cin>>n;
    std::vector<int> v(n);
    std::cout<<"Unesite elemente: ";
    std::for_each(std::begin(v),std::end(v),[](int &broj){std::cin>>broj;});
    std::cout<<"Niz sortiran po sumi cifara glasi: ";
    std::sort(std::begin(v),std::end(v),Uporedi);                                     //da bi binary search radio niz mora biti sortiran
    std::for_each(std::begin(v),std::end(v),[](int &broj){std::cout<<broj<<" ";});
    std::cout<<std::endl<<"Unesite broj koji trazite: ";
    std::cin>>n;
    auto pozicija=std::lower_bound(std::begin(v),std::end(v),n,Uporedi);               //lower_bound vraća poziciju prvog broja većeg ili jednakog od n, 
    if(*pozicija!=n) std::cout<<"Trazeni broj ne nalazi se u nizu!";                  //obzirom da je rijec o poređenju po sumi cifara, to stavljamo kao uslov 
    else{
        std::cout<<"Trazeni broj nalazi se na poziciji "<<pozicija-std::begin(v);          //lower_bound ako ne nađe tražen broj vratit će prvi koji je za jedan veći, zato provjeravamo(linija 50)
    } 
	return 0;
}