//TP 2016/2017: LV 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    double a;
    for(;;){
        pocetak:
        std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
        std::cin>>a;
        if(a<0 || !std::cin || a-(int)a!=0){
            std::cout<<"Niste unijeli prirodan broj!\n";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            goto pocetak;
        }
        if(a==0) break;
        int S=0,i;
        for(i=1;i<a;i++){
            if((int)a%i==0) S+=i;
        }
        if(S==a) std::cout<<"Broj "<<a<<" je savrsen!";
        else if(S<a) std::cout<<"Broj "<<a<<" je manjkav!";
        else std::cout<<"Broj "<<a<<" je obilan!";
        std::cout<<"\n";
    }
    std::cout<<"Dovidjenja!";
	return 0;
}