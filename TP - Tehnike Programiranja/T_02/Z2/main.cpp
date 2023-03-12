//TP 2020/2021: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>

typedef std::vector<double> DoubleVektor;

bool TestPerioda(DoubleVektor v, int p){
    if(p==0) return false;                  //period jednak nuli nije realan
    int vel=v.size();
    if(vel==1) return false;                //niz sa jednim clanom ne moze imati nikakav period jer se nista ne ponavlja
    if(p>=vel) return false;                //ako je period veci od broja clanova, period ne postoji
    for(int i=1;i<=vel/p;i++){              //vel/p predstavlja max moguci broj ponavljanja tj. perioda
        for(int j=0;j<p;j++){
            if((j+(p*i)==vel)) break;       //prekid ispitivanja ukoliko dosegnemo kraj vektora
            else if(v[j]!=v[j+(p*i)]){
                return false;
            }
        }
    }
    return true;
}

int OdrediOsnovniPeriod(DoubleVektor v){
    for(int i=1;i<=v.size();i++)
        if(TestPerioda(v,i)) return i;
    return 0;
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    DoubleVektor v;
    for(;;){
        double a;
        std::cin>>a;
        if(a==0) break;
        v.push_back(a);
    }
    int p=OdrediOsnovniPeriod(v);
    if(p==0) std::cout<<"Slijed nije periodican!";
    else std::cout<<"Slijed je periodican sa osnovnim periodom "<<p<<".";
    return 0;
}