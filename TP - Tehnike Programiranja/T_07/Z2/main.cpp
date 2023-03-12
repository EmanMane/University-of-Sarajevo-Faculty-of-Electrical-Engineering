/* 
    TP 16/17 (LV 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
int main ()
{
    std::cout<<"Koliko zelite recenica: ";
    int n;
    std::cin>>n;
    std::cin.ignore(10000,'\n');
    std::cout<<"Unesite recenice:"<<std::endl;
    char ** spisakrecenica=nullptr;
    try{
        spisakrecenica=new char* [n];
        for(int i=0;i<n;i++) spisakrecenica[i]=nullptr;
        try{
            for(int i=0;i<n;i++){
                char recenica[1000];
                std::cin.getline(recenica,1000);
                spisakrecenica[i]=new char [std::strlen(recenica)+1];
                for(int j=0;j<std::strlen(recenica)+1;j++){
                    spisakrecenica[i][j]=recenica[j];
                }
            }
        }catch(...){
            for(int i=0;i<n;i++) delete[] spisakrecenica[i];
            delete[] spisakrecenica;
            throw;
        }
        std::sort(spisakrecenica,spisakrecenica+n,[](char* x,char* y){return std::strcmp(x,y)<0;});
        std::cout<<"Sortirane recenice:"<<std::endl;
        for(int i=0;i<n;i++){
            std::cout<<spisakrecenica[i]<<std::endl;
        }
        for(int i=0;i<n;i++) delete[] spisakrecenica[i];
        delete[] spisakrecenica;
    }catch(...){
        std::cout<<"Problemi s memorijom!";
    }
	return 0;
}