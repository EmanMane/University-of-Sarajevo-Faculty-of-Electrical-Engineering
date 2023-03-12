/* 
    TP 2018/2019: LV 5, Zadatak 5
	
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
#include <iomanip>
#include <cmath>

double f(double x){
    return sin(x);
}

double g(double x){
    return pow(x,3);
}

double h(double x){
    return 1./x;
}

double TrapeznoPravilo(double fun(double x),double a,double b,int n){
    double S=0;
    int i=1;
    while(i<n){
        S=S+(fun(a+((b-a)/double(n))*i));
        i++;
    }
    double formula=((b-a)/n)*(fun(a)/2.+fun(b)/2.+S);
    return formula;
}



int main ()
{
    double pi=4*atan(1);
    std::cout<<"Unesite broj podintervala: ";
    int n;
    std::cin>>n;
    std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:"<<std::endl;
    std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo(f,0,pi,n)<<std::endl;
    std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::fixed<<std::setprecision(2)<<TrapeznoPravilo(g,0,10,n)<<std::endl;
    std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo(h,1,2,n)<<std::endl;
	return 0;
}