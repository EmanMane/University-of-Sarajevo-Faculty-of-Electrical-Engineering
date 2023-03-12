//TP 2021/2022: LV 3, Zadatak 7
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iomanip>

typedef std::vector<int> vektor;
typedef std::vector<vektor> matrica;

matrica PascalovTrougao(int n){
    matrica m;
    if(n==0){
        m.resize(0);         //Prazna matrica
        return m;
    } 
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    m.resize(n,vektor(n));              //Pocinjemo sa vmatricom nxn
    m[0].resize(1);                     //Prvi red sada ima jednu kolonu
    m[0][0]=1;                          //Ciji je clan jednak nuli
    for(int i=1;i<n;i++){
        m[i].resize(i+1);               //Prije bilo kakvog rada u i-redu, moramo mu promijeniti velicinu
        for(int j=0;j<i+1;j++){
            if(j==0 || j==i) m[i][j]=1;
            else{
                m[i][j]=m[i-1].at(j-1)+m[i-1].at(j);
            }
        }
    }
    return m;
}

int NajvecaSirina(matrica m){
    int max_sirina=0;
    int x=m.size();
    for(int i=0;i<x;i++){
        int y=m[i].size();
        for(int j=0;j<y;j++){
            int k=0;
            int clan=m[i][j];
            if(clan<0) k++;
            while(clan!=0){
                clan/=10;
                k++;
            }
            if(k>max_sirina) max_sirina=k;
        }
    }
    return max_sirina;
}

int main ()
{
    std::cout<<"Unesite broj redova: ";
    int n;
    std::cin>>n;
    matrica p=PascalovTrougao(n);
    int x=NajvecaSirina(p);
    for(int i=0;i<n;i++){
        for(int j=0;j<p[i].size();j++){
            std::cout<<std::right<<std::setw(x+1)<<p[i][j];
        }
        std::cout<<std::endl;
    }
	return 0;
}