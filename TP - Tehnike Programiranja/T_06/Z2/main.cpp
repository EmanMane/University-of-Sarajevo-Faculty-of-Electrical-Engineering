#include <iostream>
#include <new>
#include <type_traits>
#include <vector>
/* 
    TP 2018/2019: LV 6, Zadatak 2
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
template<typename Tip>
auto KreirajIzvrnutiNiz(Tip poc,Tip kraj)->typename std::remove_reference<decltype (*poc)>::type*{
    int i=0;
    auto rstpoc=poc, rstkraj=kraj;
    typename std::remove_reference<decltype (*poc)>::type *izvrnuti=nullptr;
    while(poc!=kraj){
        i++;
        poc++;
    }
    poc=rstpoc;
    try{
        izvrnuti = new typename std::remove_reference<decltype (*poc)>::type [i];
        while(poc!=kraj){
            i--;
            izvrnuti[i]=*poc;
            poc++; 
        }
        return izvrnuti;
    }
    catch(...){
        throw;
    }
}

int main ()
{
    std::cout<<"Koliko zelite elemenata: ";
    int n;
    std::cin>>n;
    double *kreirani=nullptr;
    try{
        std::vector<double> vektor(n);
        std::cout<<"Unesite elemente: ";
        for(int i=0;i<n;i++){
            double clan;
            std::cin>>clan;
            vektor.at(i)=clan;
        }
        kreirani=KreirajIzvrnutiNiz(vektor.begin(),vektor.end());
        std::cout<<"Kreirani niz: ";
        for(int i=0;i<n;i++){
            std::cout<<kreirani[i]<<" ";
        }
        delete[] kreirani;
    }
    catch(...){
        std::cout<<"Nedovoljno memorije!";
    }
	return 0;
}