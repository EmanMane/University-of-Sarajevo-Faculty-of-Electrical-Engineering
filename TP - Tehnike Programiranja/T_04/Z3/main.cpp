//TP 2021/2022: LV 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>

void IzdvojiKrajnjeRijeci(std::vector<std::string> s,std::string &prvi,std::string &drugi){
    if(s.size()==0) goto ende;
    prvi=s.at(0);
    drugi=s.at(0);
    for(int i=0;i<s.size();i++){
        char slovo=toupper(s.at(i).at(0));
        char prvislovo=toupper(prvi.at(0));
        char drugislovo=toupper(drugi.at(0));
        if(s.at(i).at(0)<='z' && s.at(i).at(0)>='a') slovo=toupper(s.at(i).at(0));
        if(prvi.at(0)<='z' && prvi.at(0)>='a') prvislovo=toupper(prvi.at(0));
        if(drugi.at(0)<='z' && drugi.at(0)>='a') drugislovo=toupper(drugi.at(0));
            if(slovo<prvislovo) prvi=s.at(i);
            if(slovo==prvislovo){
                for(int j=0;j<s.at(i).length();j++){
                    for(int k=0;k<prvi.length();k++){
                        if(s.at(i).at(j)<='z' && s.at(i).at(j)>='a') slovo=toupper(s.at(i).at(j));
                        else slovo=s.at(i).at(j);
                        if(prvi.at(k)<='z' && prvi.at(k)>='a') prvislovo=toupper(prvi.at(k));
                        else slovo=prvi.at(k);
                        if(slovo<prvislovo) prvi=s.at(i);
                    }
                }
            }
            slovo=toupper(s.at(i).at(0));
            if(slovo>drugislovo) drugi=s.at(i);
            if(slovo==drugislovo){
                for(int j=0;j<s.at(i).length();j++){
                    for(int k=0;k<drugi.length();k++){
                        if(s.at(i).at(j)<='z' && s.at(i).at(j)>='a') slovo=toupper(s.at(i).at(j));
                        else slovo=s.at(i).at(j);
                        if(drugi.at(k)<='z' && drugi.at(k)>='a') drugislovo=toupper(drugi.at(k));
                        else slovo=drugi.at(k);
                        if(slovo>drugislovo) drugi=s.at(i);
                    }
                }
            }
    }
    ende:;
}

void  ZadrziDuplikate(std::vector<std::string> &s){
    bool imaliduplikata=false;
    for(int i=0;i<s.size();i++){
        for(int j=i+1;j<s.size();j++){
            if(s.at(i)==s.at(j)){
                imaliduplikata=true;
                for(int k=j;k<s.size()-1;k++){
                    s.at(k)=s.at(k+1);
                }
                int trenutnisize=s.size();
                s.resize(trenutnisize-1);
                j--;
            }
        }
        if(imaliduplikata==false){
            for(int k=i;k<s.size()-1;k++){
                    s.at(k)=s.at(k+1);
                }
                int trenutnisize=s.size();
                s.resize(trenutnisize-1);
                i--;
        }
        imaliduplikata=false;
    }
}

int main (){
    std::cout<<"Koliko zelite unijeti rijeci: ";
    int n;
    std::cin>>n;
    std::cin.ignore(10000,'\n');
    std::cout<<"Unesite rijeci: ";
    std::string recenica;
    std::getline(std::cin,recenica);
    std::vector<std::string> vektorrijeci(n);
    int k=0;
    for(int i=0;i<n;i++){
        for(int j=k;j<recenica.length();j++){
            vektorrijeci.at(i).push_back(recenica.at(j));
            if(recenica.at(j)==' ' || j==recenica.length()-1){
                k=j+1;
                break;
            } 
        }
    }

    std::string prva,zadnja;
    IzdvojiKrajnjeRijeci(vektorrijeci,prva,zadnja);
    std::cout<<"Prva rijec po abecednom poretku je: "<<prva<<std::endl;
    std::cout<<"Posljednja rijec po abecednom poretku je: "<<zadnja<<std::endl;
    std::cout<<"Rijeci koje se ponavljaju su: ";
    ZadrziDuplikate(vektorrijeci);
    for(int i=0;i<vektorrijeci.size();i++){
        std::cout<<vektorrijeci.at(i)<<" ";
    }

	return 0;
}