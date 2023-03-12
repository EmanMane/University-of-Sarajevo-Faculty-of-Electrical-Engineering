#include <bits/c++config.h>
#include <iostream>
/* 
    TP 2018/2019: LV 5, Zadatak 2
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
template<typename Tip1>

Tip1 RazmijeniBlokove(Tip1 p1, Tip1 p2, Tip1 p3){
    while(p1!=p2){
        auto pom=*p1;
        *p1=*p3;
        *p3=pom;
        p1++; p3++;
    }
    return p3;
}


int main ()
{
    int a[8]={0,1,2,3,4,5,6,7},b[8]={9,9,9,9,9,9,9,9};
    RazmijeniBlokove(std::begin(a),std::end(a),std::begin(b));
    for(int i=0;i<8;i++) std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    for(int i=0;i<8;i++) std::cout<<b[i]<<" ";
    std::cout<<std::endl;
    
    std::string c("Eman"),d("Mane");
    RazmijeniBlokove(std::begin(c),std::end(c),std::begin(d));
    std::cout<<c<<" "<<std::endl;
    std::cout<<d<<" "<<std::endl;
	return 0;
}