//TP 2020/2021: Tutorijal 2, Zadatak 4
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
        std::cout<<"R"<<i<<" = ";
        double R;
        std::cin>>R;
        std::cout<<"X"<<i<<" = ";
        double X;
        std::cin>>X;
        DoubleKompleksni Z(R,X);
        S+=pow(Z,(-1));
    }
    S=pow(S,(-1));
    std::cout<<"Paralelna veza ovih elemenata ima R = "<<S.real()<<" i X = "<<S.imag()<<".";
    return 0;
}