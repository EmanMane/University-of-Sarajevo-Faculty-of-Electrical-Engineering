//TP 2021/2022: LV 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

typedef std::vector<int> vektor;
typedef std::vector<vektor> matrica;

matrica KroneckerovProizvod(vektor a, vektor b){
    matrica c;
    int x=a.size();
    int y=b.size();
    c.resize(x,std::vector<int>(b));
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            c[i][j]=a.at(i)*b.at(j);
        }
    }
    return c;
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
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int m;
    std::cin>>m;
    std::cout<<"Unesite elemente prvog vektora: ";
    vektor a(m);
    for(int i=0;i<m;i++){
        int clan;
        std::cin>>clan;
        a.at(i)=clan;
    }

    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite elemente drugog vektora: ";
    vektor b(n);
    for(int i=0;i<n;i++){
        int clan;
        std::cin>>clan;
        b.at(i)=clan;
    }

    matrica c=KroneckerovProizvod(a,b);
    int x=NajvecaSirina(c);

    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            std::cout<<std::right<<std::setw(x+1)<<c[i][j];
        }
        std::cout<<std::endl;
    }
	return 0;
}