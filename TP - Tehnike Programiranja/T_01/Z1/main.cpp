//TP 2016/2017: LV 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    int a,b,c;
    std::cin>>a>>b>>c;
    std::cout<<"\nUnesite sirinu plocice u centimetrima: ";
    int d;
    std::cin>>d;
    a*=100; b*=100; c*=100; //pretvaranje u centimetre
    int P1,P2,P3; //dijeljenje na 3 površine jer ne možemo uzeti cijelu površinu omotača otvorenog kvadra (pločice nam to ne dozvoljavaju)
    P1=a*b;
    P2=b*c;
    P3=a*c;
    int p;
    p=d*d;

    int br=0;
    if(a%d!=0 || b%d!=0 || c%d!=0) goto ende; //slučaj da se moraju lomiti jer po dužini/širini/visini pločice ne mogu stati na površinu

    while(P1>0){
        P1-=p;
        br++;
    }
    if(P1<0) goto ende;
    while(P2>0){
        P2-=p;
        br+=2; //+2 jer su dva zida iste površine
    }
    if(P2<0) goto ende;
    while(P3>0){
        P3-=p;
        br+=2; //Linija 30
    }
    if(P3<0) goto ende;

    std::cout<<"\nZa poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm\n";
    std::cout<<"potrebno je "<<br<<" plocica.";
    return 0;
    
    ende:
    std::cout<<"\nPoplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm\n";
    std::cout<<"nije izvodljivo bez lomljenja plocica!";
	return 0;
}