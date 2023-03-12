//TP 2021/2022: LV 3, Zadatak 4
#include <iostream>
#include <deque>
#include <cmath>

typedef std::deque<int> Dek;

Dek IzdvojiElemente(Dek a, bool parnost){
    Dek b;
    if(parnost){
        for(int i=0;i<a.size();i++){
            int broj=a.at(i);
            int S=0;
            while(broj!=0){
                int cifra=broj%10;
                broj/=10;
                S+=cifra;
            }
            broj=a.at(i);
            if(S%2==0) b.push_front(broj);
        }
    }
    else {
        for(int i=0;i<a.size();i++){
            int broj=a.at(i);
            int S=0;
            while(broj!=0){
                int cifra=broj%10;
                broj/=10;
                S+=cifra;
            }
            broj=a.at(i);
            if(S%2!=0) b.push_front(broj);
        }
    }
    return b;
}

int main ()
{
    std::cout<<"Koliko zelite unijeti elemenata: ";
    int n;
    std::cin>>n;
    if(n<=0){
        std::cout<<"Broj elemenata mora biti veci od 0!";
        return 0;
    }
    int rstn=n;
    std::cout<<"Unesite elemente: ";
    Dek a;
    while(n!=0){
        int x;
        std::cin>>x;
        a.push_back(x);
        n--;
    }
    n=rstn;

    Dek b(n);
    Dek c(n);

    b=IzdvojiElemente(a,true);
    c=IzdvojiElemente(a,false);

    if(b.size()>0){
        for(int i=0;i<b.size()-1;i++){
            std::cout<<b[i]<<",";
        }
        std::cout<<b[b.size()-1]<<std::endl;
    }

    if(c.size()>0){
        for(int i=0;i<c.size()-1;i++){
            std::cout<<c[i]<<",";
        }
        std::cout<<c[c.size()-1]<<std::endl;
    }
	return 0;
}