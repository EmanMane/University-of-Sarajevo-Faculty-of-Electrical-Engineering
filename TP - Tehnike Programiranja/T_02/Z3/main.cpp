//TP 2020/2021: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>

typedef std::complex<double> DoubleKompleksni;

int main ()
{
    std::cout<<"Unesite broj elemenata: ";
    int n;
    std::cin>>n;
    DoubleKompleksni S=0;
    for(int i=1;i<=n;i++){
        std::cout<<"Z_"<<i<<" = ";
        DoubleKompleksni Z;
        std::cin>>Z;
        S+=pow(Z,(-1));
    }
    S=pow(S,(-1));
    std::cout<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<S<<".";
    return 0;
}