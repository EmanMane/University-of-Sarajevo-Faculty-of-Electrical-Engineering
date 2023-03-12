/* 
    TP 2018/2019: LV 5, Zadatak 3
	
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
#include <algorithm>
#include <cmath>

void Unos(int &broj) {                  
    std::cin>>broj;
    }

bool ProvjeriKvadrat (int x){
    if(std::sqrt(x)==(int)std::sqrt(x)) return 1;           //Ako je kvadrat cio broj vrati tacno
    else return 0;
}

bool Uporedi (int a,int b){
    if(int(std::log10(abs(a)))+1<int(std::log10(abs(b)))+1) return true;        
    else return false;
}

bool Trocifren (int x){
    if(int(std::log10(abs(x)))+1==3) return true;       //log10(x)+1 -> Broj cifara nekog broja
    else return false;
}

void Ispis(int x){
    std::cout<<x<<" ";
}

int main ()
{
    std::cout<<"Unesite broj elemenata (max. 1000): ";
    int n;
    std::cin>>n;
    int niz[1000];
    int broj;
    std::cout<<"Unesite elemente: ";
    std::for_each(niz,niz+n,Unos);
    int *maksimalni=std::max_element(niz,niz+n);
    std::cout<<"Najveci element niza je "<<*maksimalni<<std::endl;
    int *minimalni=std::min_element(niz,niz+n);
    std::cout<<"Najmanji element niza se pojavljuje "<<std::count(niz,niz+n,*minimalni)<<" puta u nizu"<<std::endl;
    std::cout<<"U nizu ima "<<std::count_if(niz, niz+n, ProvjeriKvadrat)<<" brojeva koji su potpuni kvadrati"<<std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(niz,niz+n,Uporedi)<<std::endl;
    int *p=std::remove_if(niz,niz+n,Trocifren);
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(niz,p,Ispis);
	return 0;
}

