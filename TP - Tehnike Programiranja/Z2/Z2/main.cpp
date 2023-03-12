//TP 2021/2022: Zadaća 2, Zadatak 2
#include <iostream>
#include <stdexcept>

int Goldbach(int n, int &p, int &q){
    if(n<=2) throw std::logic_error("Rastava ne postoji");
    p=q=0;
    for(int i=2;i<n;i++){
        for(int j=2;j<i;j++){
            if(i%j==0 && i!=j) goto dalje;
        }
        p=i;
        for(int k=n;k>1;k--){
            for(int j=2;j<k;j++){
                if(k%j==0 && k!=j) goto dalje1;
            }
            q=k;
            if(p+q==n) goto ende;
            else if(p+q<n){
                p=q=0;
                goto dalje;
            }
            dalje1:;
        }
        dalje:;
    }
    ende:
    if(p==0 && q==0) throw std::logic_error("Rastava ne postoji");
    return 0;
}

int main ()
{
    std::cout<<"Unesi broj: "; int n; std::cin>>n;
    int p,q;
    try{
        Goldbach(n,p,q);
        if(p!=0 && q!=0) std::cout<<n<<" je zbir prostih brojeva "<<p<<" i "<<q;
    }
    catch(std::logic_error izuzetak){
        std::cout<<n<<" nije zbir dva prosta broja!";
    }
	return 0;
}