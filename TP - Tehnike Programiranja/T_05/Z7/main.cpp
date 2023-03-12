/* 
    TP 2018/2019: LV 5, Zadatak 7
	
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
#include <deque>
#include <algorithm>

template<typename IterTip>
auto SumaBloka(IterTip poc,IterTip kraj)->decltype(*poc+*poc){
    if(poc==kraj) throw std::range_error("Blok je prazan");
    decltype(*poc+*poc) S (*poc);
    while(++poc!=kraj){
        S+=*poc;
    }
    return S;
}

int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata deka: ";
    std::cin>>n;
    std::deque<int> dek(n);
    std::cout<<"Unesite elemente deka: ";
    std::for_each(dek.begin(),dek.end(),[](int &broj){std::cin>>broj;});
    try{
        std::cout<<"Suma deka je: "<<SumaBloka(dek.begin(),dek.end())<<std::endl;
    }
    catch(std::range_error greska){
        std::cout<<greska.what();
    }
	return 0;
}