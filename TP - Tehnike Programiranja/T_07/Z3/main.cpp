/* 
    TP 16/17 (LV 7, Zadatak 3)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
int main ()
{
    std::cout<<"Koliko zelite recenica: ";
    int n;
    std::cin>>n;
    std::cin.ignore(10000,'\n');
    std::cout<<"Unesite recenice:"<<std::endl;
    std::string ** spisakrecenica=nullptr;
    try{
        spisakrecenica=new std::string* [n];
        for(int i=0;i<n;i++) spisakrecenica[i]=nullptr;
        try{
            for(int i=0;i<n;i++){
                spisakrecenica[i]=new std::string;
                std::getline(std::cin,*spisakrecenica[i]);
            }
        }catch(...){
            for(int i=0;i<n;i++) delete spisakrecenica[i];
            delete[] spisakrecenica;
            throw;
        }
        std::sort(spisakrecenica,spisakrecenica+n,[](std::string* x,std::string* y){return *x<*y;});
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0;i<n;i++){
            std::cout<<*spisakrecenica[i]<<std::endl;
        }
        for(int i=0;i<n;i++) delete spisakrecenica[i];
        delete[] spisakrecenica;
    }catch(...){
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}