#include <iostream>
#include <stdexcept>
#include <ctime>

void Goldbach(int n,int& p,int& q){
    for(int i=2;i<n/2;i++){
        int j;
        for(int k=2;k<i/2;k++){
            if(i%k==0) goto ako_nije1;
        }
        j=n-i;
        for(int k=2;k<j/2;k++){
            if(j%k==0) goto ako_nije2;
        }
        p=i; q=j;
        break;
        ako_nije1:;
        ako_nije2:;
    }
}


int main(){
    int n,p=0,q=0;
    std::cout<<"Unesite n: "; std::cin>>n;
    try{
    if(n<=2 || n%2!=0) throw std::domain_error("Pogrešno unesen n!!!");
    clock_t vrijeme1 = clock();
    Goldbach(n,p,q);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout<<"\nVrijeme izvrsenja: "<<ukvrijeme<<" ms."<<std::endl;
    if(p!=0) std::cout<<n<<" se može napisati kao zbir prostih brojeva "<<p<<" i "<<q;
    else std::cout<<n<<" se ne može napisati kao zbir prostih brojeva.";
    }catch(std::domain_error is){
        std::cout<<is.what();
    }
    return 0;
}