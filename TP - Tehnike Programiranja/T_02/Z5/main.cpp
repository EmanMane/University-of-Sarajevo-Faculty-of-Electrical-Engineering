//TP 2020/2021: Tutorijal 2, Zadatak 5
#include <iostream>
#include <complex>

typedef std::complex<double> DoubleKompleksni;

int main ()
{
    std::cout<<"Unesite broj elemenata: ";
    int n;
    std::cin>>n;
    DoubleKompleksni S=0;
    double PI=4*atan(1);
    for(int i=1;i<=n;i++){
        std::cout<<"Z"<<i<<" = ";
        double r;
        std::cin>>r;
        std::cout<<"fi"<<i<<" = ";
        double fi;
        std::cin>>fi;
        DoubleKompleksni Z=std::polar(r,fi*PI/180);
        S+=pow(Z,(-1));
    }
    S=pow(S,(-1));
    std::cout<<"Paralelna veza ovih elemenata ima Z = "<<abs(S)<<" i fi = "<<arg(S)/PI*180<<".";
    return 0;
}