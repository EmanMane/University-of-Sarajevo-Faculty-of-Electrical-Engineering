//TP 2020/2021: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>

bool DaLiJeProst (int n){
    if(n<=1) return false;
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0) return false;
    }
    return true;
}

std::vector<int> ProstiBrojeviUOpsegu (int a, int b){
    std::vector<int> c(b-a+1);     //+1 u slucaju da je a==b
    int j=0;
    for(int i=a;i<b;i++){
        if(DaLiJeProst(i)){
            c[j]=i;
            j++;
        }
    }
    if(DaLiJeProst(b)){           //glup uslov, ali ga moramo dodati jer da smo u liniji 17 pisali <=b ne bi radilo za test sa max vrijednosti int-a tj ako je i==b==maxint pri i++ stvara se greška
        c[j]=b;
        j++;
    }
    c.resize(j);                  //nije bitno koliko veliko je j, bitno je da je makar zadnji član 0 jer se oni svakako zanemare pri ispisu 
    return c;
}

int main ()
{
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    int a,b;
    std::cin>>a>>b;
    std::vector<int> c=ProstiBrojeviUOpsegu(a,b);
    if(c.size()>0){
        std::cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0;i<c.size();i++){
            if(c[i]!=0 && i==0){       //zanemarivanje zadnjih članova jednakih 0
                std::cout<<c[i];
            }
            else if(c[i]!=0){
                std::cout<<", "<<c[i];
            }
        }
        std::cout << std::endl;
    }
    else std::cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!\n";
    return 0;
}