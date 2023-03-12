/* 
    TP 2018/2019: LV 5, Zadatak 4
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>                                 //Bukvalno isto kao predhodni zadatak samo sa par caka:
#include <algorithm>                                //1.Funkcije su smjestene unutar algorithm funkcija (FORMULA: '[]' + 'Funkcija iz predhodnog')
#include <cmath>                                    //2.Pokazivaci su deklarisani sa auto a ne sa int
#include <deque>                                    //3.Koristi se begin() i end() od deka, a ne sami dek kao sto smo imali u prosloj verziji zadatka kod niza

int main ()
{
    std::cout<<"Unesite broj elemenata: ";
    int n;
    std::cin>>n;
    std::deque<int> niz(n);
    int broj;
    std::cout<<"Unesite elemente: ";
    std::for_each(std::begin(niz),std::end(niz),[](int &broj) {std::cin>>broj;});
    std::cout<<"Najveci element deka je "<<*std::max_element(std::begin(niz),std::end(niz))<<std::endl;
    int minimalni=*std::min_element(std::begin(niz),std::end(niz));
    std::cout<<"Najmanji element deka se pojavljuje "<<std::count(std::begin(niz),std::end(niz),minimalni)<<" puta u deku"<<std::endl;
    std::cout<<"U deku ima "<<std::count_if(std::begin(niz),std::end(niz), [](int x){if(std::sqrt(x)==(int)std::sqrt(x))return 1; else return 0;})<<" brojeva koji su potpuni kvadrati"<<std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(std::begin(niz),std::end(niz),[](int a,int b){if(int(std::log10(abs(a))+1)<int(std::log10(abs(b))+1)) return true;else return false;})<<std::endl;
    auto p=std::remove_if(std::begin(niz),std::end(niz),[](int x){if(int(std::log10(abs(x)))+1==3) return true;else return false;});
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(std::begin(niz),p,[](int x){std::cout<<x<<" ";});
	return 0;
}

