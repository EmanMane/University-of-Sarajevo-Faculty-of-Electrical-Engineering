/* 
    TP 16/17 (LV 12, Zadatak 5)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main ()
{
    std::cout<<"Koliko zelite elemenata: ";
    int n; std::cin>>n;
    std::vector<double> v(n);
    std::cout<<"Unesite elemente: ";
    for(int i=0;i<n;i++){
        double clan;
        std::cin>>clan;
        v.at(i)=clan;
    }
    std::transform(v.begin(),v.end(),v.begin(),std::bind(std::divides<double>(),1,std::placeholders::_1));
    std::cout<<"Transformirani elementi: ";
    for(int i=0;i<n;i++){
        std::cout<<v.at(i)<<" ";
    }
	return 0;
}