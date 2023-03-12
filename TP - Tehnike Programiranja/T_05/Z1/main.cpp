/* 
    TP 2018/2019: LV 5, Zadatak 1
	
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
int main ()
{
    std::cout<<"Unesite recenicu: ";
    char niz[1001],slovo,*p=niz,*rstp=niz;
    int rijeci=0;
    std::cin.getline(niz,1000);
    std::cout<<"Recenica bez prve rijeci glasi: ";
    while(*p!='\0'){                                                //fazon je da izbaci prvu rijec iz stringa
        if(isalpha(*p) && p!=rstp && *(p-1)==' ') rijeci++;         //to radi tako sto se pokazivacem krece kroz string i ispisuje ono na sta on pokazuje ukoliko je broj rijeci veci od 1 
        if(isalpha(*p) && p==rstp) rijeci++;
        if(rijeci>1) std::cout<<*p;
        p++;
    }
    std::cout<<std::endl;
    return 0;
}