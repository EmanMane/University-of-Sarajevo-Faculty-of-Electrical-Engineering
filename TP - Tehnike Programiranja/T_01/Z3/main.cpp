//TP 2016/2017: LV 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <iomanip>
int main ()
{
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    int a,b;
    std::cin>>a>>b;
    int i;
    std::cout<<"\n+---------+----------+----------+-----------+\n";
    std::cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |\n";
    std::cout<<"+---------+----------+----------+-----------+\n";
    for(i=a;i<=b;i++){
        std::cout<<std::fixed;
        std::cout<<"| "<<std::left<<std::setw(8)<<std::setprecision(0)<<i;
        std::cout<<"|"<<std::right<<std::setw(9)<<std::setprecision(0)<<i*i;
        std::cout<<" |"<<std::right<<std::setw(9)<<std::setprecision(3)<<std::sqrt(i);
        std::cout<<" |"<<std::right<<std::setw(10)<<std::setprecision(5)<<std::log(i);
        std::cout<<" |\n";
    }
    std::cout<<"+---------+----------+----------+-----------+\n";
	return 0;
}