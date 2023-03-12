//TP 2021/2022: Zadaća 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <list>
#include <string>

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> vektor_djece,int broj_timova){
    if(broj_timova<1 || broj_timova>vektor_djece.size()) throw std::logic_error("Razvrstavanje nemoguce");
    std::vector<std::set<std::string>> spisak_po_timovima={};
    std::list<std::string> lista_djece;
    for(int i=0;i<vektor_djece.size();i++){
        lista_djece.push_back(vektor_djece.at(i));
    }
    //return spisak_po_timovima;
    //prvih mod(𝑛, 𝑘) 
    //timova ima ⌊𝑛/𝑘⌋ + 1 članova, a preostali timovi ⌊𝑛/𝑘⌋ članova (ovdje mod(𝑛, 𝑘) označava 
    //ostatak pri dijeljenju 𝑛 sa 𝑘, a ⌊… ⌋ označava cijeli dio). Ova strategija garantira da će se broj 
    //članova u pojedinim timovima razlikovati najviše za 1. Recimo, ukoliko je 𝑛 = 22 i 𝑘 = 5, tada je 
    //mod(𝑛, 𝑘) = 2 i ⌊𝑛/𝑘⌋ = 4, tako da će prva dva tima imati 5 članova a preostala 3 tima 4 člana.
    int prvi_timovi=vektor_djece.size()%broj_timova;
    auto string_dijete_pok=lista_djece.begin();
    int korak=0;
    for(int i=0;i<prvi_timovi;i++){
        std::set<std::string> skup;
        int brojclanova=(vektor_djece.size()/broj_timova)+1;
        while(brojclanova>0){
            for(int i=0;i<korak;i++){
                string_dijete_pok++;
                if(string_dijete_pok==lista_djece.end()) string_dijete_pok=lista_djece.begin();
            }
            korak=0;
            std::string string_dijete=*string_dijete_pok;
            auto p=string_dijete.begin();
            while(p!=string_dijete.end()){
                if(isalpha(*p) || isdigit(*p)) korak++;
                p++;
            }
            skup.insert(string_dijete);
            korak--;
            string_dijete_pok=lista_djece.erase(string_dijete_pok);
            if(string_dijete_pok==lista_djece.end()) string_dijete_pok=lista_djece.begin();
            brojclanova--;
        }
        spisak_po_timovima.push_back(skup);
    }
    for(int i=0;i<broj_timova-prvi_timovi;i++){
        std::set<std::string> skup;
        int brojclanova=vektor_djece.size()/broj_timova;
        while(brojclanova>0){
            for(int i=0;i<korak;i++){
                string_dijete_pok++;
                if(string_dijete_pok==lista_djece.end()) string_dijete_pok=lista_djece.begin();
            }
            korak=0;
            std::string string_dijete=*string_dijete_pok;
            auto p=string_dijete.begin();
            while(p!=string_dijete.end()){
                if(isalpha(*p) || isdigit(*p)) korak++;
                p++;
            }
            skup.insert(string_dijete);
            korak--;
            string_dijete_pok=lista_djece.erase(string_dijete_pok);
            if(string_dijete_pok==lista_djece.end()) string_dijete_pok=lista_djece.begin();
            brojclanova--;
        }
        spisak_po_timovima.push_back(skup);
    }
    return spisak_po_timovima;
}


int main ()
{
    int k,n;
    std::cout<<"Unesite broj djece: "; std::cin>>n;
    std::cout<<"Unesite imena djece: "<<std::endl;
    std::cin.ignore(1000,'\n');
    std::vector<std::string> vektor_djece={};
    for(int i=0;i<n;i++){
        std::string dijete;
        std::getline(std::cin,dijete);
        vektor_djece.push_back(dijete);
    }
    std::cout<<"Unesite broj timova: "; std::cin>>k;
    try{
        std::vector<std::set<std::string>> razvrstani=Razvrstavanje(vektor_djece,k);
        for(int i=0;i<razvrstani.size();i++){
            auto p=razvrstani.at(i).begin();
            std::cout<<"Tim "<<i+1<<": ";
            while(p!=razvrstani.at(i).end()){
                if(p!=razvrstani.at(i).begin()) std::cout<<", ";
                std::cout<<*p;
                p++;
            }
            std::cout<<std::endl;
        }
    }
    catch(std::logic_error izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
	return 0;
}