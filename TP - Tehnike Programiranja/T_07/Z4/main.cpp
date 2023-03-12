/* 
    TP 16/17 (LV 7, Zadatak 4)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <memory>

typedef std::shared_ptr<std::string> DijeljeniString;

int main ()
{
    std::cout<<"Koliko zelite recenica: ";
    int n;
    std::cin>>n;
    std::cin.ignore(10000,'\n');
    std::cout<<"Unesite recenice:"<<std::endl;
    try{
        std::unique_ptr<DijeljeniString[]> spisakrecenica(new DijeljeniString [n]);
        for(int i=0;i<n;i++) spisakrecenica[i]=nullptr;
        try{
            for(int i=0;i<n;i++){
                spisakrecenica[i]=std::make_shared<std::string>();
                std::getline(std::cin,*spisakrecenica[i]);
            }
        }catch(...){
            for(int i=0;i<n;i++) spisakrecenica[i]=nullptr;
            spisakrecenica=nullptr;
            throw;
        }
        std::sort(spisakrecenica.get(),spisakrecenica.get()+n,[](DijeljeniString x,DijeljeniString y){return *x<*y;});
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0;i<n;i++){
            std::cout<<*spisakrecenica[i]<<std::endl;
        }
        for(int i=0;i<n;i++) spisakrecenica[i]=nullptr;
        spisakrecenica=nullptr;
    }catch(...){
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}