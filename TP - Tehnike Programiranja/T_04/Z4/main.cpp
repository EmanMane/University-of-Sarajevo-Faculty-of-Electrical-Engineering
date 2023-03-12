//TP 2021/2022: LV 4, Zadatak 4
#include <iostream>
#include <cmath>

template <typename NekiTip>

void UnosBroja(std::string  c, std::string  error, NekiTip &broj){
    std::string provjera="Unesite cjelobrojni eksponent: ";
    bool intedzer=false;
    if(c==provjera) intedzer=true;
    broj=0;

    if(intedzer){
    unesix:
        std::cout<<c;
        std::string x;
        prazanstring:
        std::getline(std::cin,x);
        if(x.length()==0) goto prazanstring;
        for(int i=0;i<x.length();i++){
            if((x.at(i)>'9' || x.at(i)<'0') && x.at(i)!='-'){
                std::cout<<error<<std::endl;
                goto unesix;
            }
        }
        int desetica=1;
        double decimala=1;
        int minus=1;
        for(int i=0;i<x.length();i++){
            if(x.at(i)>='0' && x.at(i)<='9'){
                char cifra=x.at(i);
                broj*=desetica;
                cifra-=48;
                broj+=cifra*decimala;
                if(desetica==1 && decimala==1) desetica*=10;
                if(decimala!=1) decimala/=10;
            }
            if(x.at(i)=='-'){
                minus=-1;
            }
        }
        broj*=minus;
    }
    else{
        unesix_1:
        std::cout<<c;
        std::string x;
        prazanstring_1:
        std::getline(std::cin,x);
        if(x.length()==0) goto prazanstring_1;
        for(int i=0;i<x.length();i++){
            if((x.at(i)>'9' || x.at(i)<'0') && x.at(i)!='.' && x.at(i)!='-'){
                std::cout<<error<<std::endl;
                goto unesix_1;
            }
        }
        int desetica=1;
        double decimala=1;
        int minus=1;
        for(int i=0;i<x.length();i++){
            if(x.at(i)>='0' && x.at(i)<='9'){
                char cifra=x.at(i);
                broj*=desetica;
                cifra-=48;
                broj+=cifra*decimala;
                if(desetica==1 && decimala==1) desetica*=10;
                if(decimala!=1) decimala/=10;
            }
            if(x.at(i)=='.'){
                decimala=0.1;
                desetica=1;
            }
            if(x.at(i)=='-'){
                minus=-1;
            }
        }
        broj*=minus;
    }
    
}

int main (){
    double baza;
    int eksp;
    UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...", baza);
    UnosBroja("Unesite cjelobrojni eksponent: ", "Neispravan unos, pokusajte ponovo...", eksp);
    double broj=baza;
    bool unazivnik=false;
    if(eksp<0) unazivnik=true;
    for(int i=1;i<abs(eksp);i++){
        broj*=baza;
    }
    if(unazivnik) broj=1./broj;
    std::cout<<baza<<" na "<<eksp<<" iznosi "<<broj;
	return 0;
}