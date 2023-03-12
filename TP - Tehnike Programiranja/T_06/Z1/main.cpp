#include<iostream>
#include<limits>
#include <stdexcept>
/* 
    TP 2018/2019: LV 6, Zadatak 1
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
template<typename Tip>
Tip *GenerirajStepeneDvojke(int n){
    if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    Tip *dinamicki_niz=nullptr;
    try{
        dinamicki_niz=new Tip[n];
        }
    catch(...){
        throw std::runtime_error("Alokacija nije uspjela");
    }
    Tip x=1;
    for(int i=0;i<n;i++){
        if(i!=n-1 && x>std::numeric_limits<Tip>::max()/2){
            delete[] dinamicki_niz;
            throw std::overflow_error("Prekoracen dozvoljeni opseg");
        }
        dinamicki_niz[i]=x;
        x=x*2;
    }
    return dinamicki_niz;
}

int main ()
{
    std::cout<<"Koliko zelite elemenata: ";
    int n;
    std::cin>>n;
    unsigned long int *pok=nullptr;
    try{
        pok=GenerirajStepeneDvojke<unsigned long int>(n);
        unsigned long int *rstpok=pok;
        while(pok<rstpok+n){
            std::cout<<*pok<<" ";
            pok++;
        }
        pok=rstpok;
        delete[] pok;
    }
    catch(std::domain_error negativno_n){
        std::cout<<"Izuzetak: "<<negativno_n.what();
    }
    catch(std::overflow_error predug_broj){
        std::cout<<"Izuzetak: "<<predug_broj.what();
        delete[] pok;
    }
	return 0;
}