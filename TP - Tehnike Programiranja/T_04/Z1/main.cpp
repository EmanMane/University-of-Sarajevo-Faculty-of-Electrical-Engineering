//TP 2021/2022: LV 4, Zadatak 1
#include <iostream>
#include <cmath>

int Cifre(long long int x, int &c_min, int &c_max){
    int brc=1;
    c_min=llabs(x%10);
    c_max=llabs(x%10);
    while(x!=0){
        int cifra=x%10;
        if(abs(cifra)<c_min) c_min=abs(cifra);
        if(abs(cifra)>c_max) c_max=abs(cifra);
        x/=10;
        brc++;
    }
    if(brc!=1) brc--;
    return brc;
}

int main ()
{
    int e;
    std::cout<<"Unesite broj: ";
    long long int n;
    std::cin>>n;
    int a,b;
    int duzina = Cifre(n, a, b);
    std::cout<<"Broj "<<n<<" ima "<<duzina<<" cifara, najveca je "<<b<<" a najmanja "<<a<<".";
	return 0;
}
