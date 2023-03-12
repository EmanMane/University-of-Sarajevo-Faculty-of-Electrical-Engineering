//TP 2021/2022: Zadaća 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <memory>


struct Dijete{
    std::string ime;
    std::shared_ptr<Dijete> sljedeci;
};

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> vektor_djece,int broj_timova){
    if(broj_timova<1 || broj_timova>vektor_djece.size()) throw std::logic_error("Razvrstavanje nemoguce");
    std::vector<std::set<std::string>> spisak_po_timovima={};
    //return spisak_po_timovima;
    std::shared_ptr<Dijete> pocetak=nullptr,prethodni=nullptr;
    for(int i=0;i<vektor_djece.size();i++){
        auto novi=std::make_shared<Dijete>();
        novi.get()->ime=vektor_djece.at(i); novi.get()->sljedeci=nullptr;
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
    }
    if(vektor_djece.size()>0) prethodni->sljedeci=pocetak;
    prethodni=nullptr;
    int prvi_timovi=vektor_djece.size()%broj_timova;
    auto string_dijete_pok=pocetak;
    pocetak=nullptr;
    prethodni=nullptr;
    //return spisak_po_timovima;


    int korak=0;


    //prvi timovi
    for(int i=0;i<prvi_timovi;i++){
        //std::cout<<"skup"<<i<<":"<<std::endl;
        std::set<std::string> skup;
        int brojclanova=(vektor_djece.size()/broj_timova)+1;
        while(brojclanova>0){
            //std::cout<<"Clan"<<brojclanova<<":"<<std::endl;
            for(int i=0;i<korak;i++) string_dijete_pok=string_dijete_pok->sljedeci;
            korak=0;
            std::string string_dijete=string_dijete_pok->ime;
            auto p=string_dijete.begin();
            while(p!=string_dijete.end()){
                if(isalpha(*p) || isdigit(*p)) korak++;
                p++;
            }
            skup.insert(string_dijete);
            korak--;
            auto za_brisanje=string_dijete_pok;
            while(string_dijete_pok->sljedeci!=za_brisanje) string_dijete_pok=string_dijete_pok->sljedeci;
            auto prethodni=string_dijete_pok;
            string_dijete_pok=string_dijete_pok->sljedeci; string_dijete_pok=string_dijete_pok->sljedeci;
            //std::cout<<"    za_brisanje="<<za_brisanje->ime<<std::endl;
            //std::cout<<"    prethodni="<<prethodni->ime<<std::endl;
            //std::cout<<"    string_dijete_pok="<<string_dijete_pok->ime<<std::endl;
            if(za_brisanje->sljedeci==prethodni->sljedeci){string_dijete_pok->sljedeci=nullptr; prethodni=nullptr; za_brisanje=nullptr;} //delete prethodni;
            else prethodni->sljedeci=string_dijete_pok;
            brojclanova--;
        }
        spisak_po_timovima.push_back(skup);
    }

    //drugi timovi
    for(int i=0;i<broj_timova-prvi_timovi;i++){
        //std::cout<<"skup"<<i<<":"<<std::endl;
        std::set<std::string> skup;
        int brojclanova=vektor_djece.size()/broj_timova;
        while(brojclanova>0){
            //std::cout<<"Clan"<<brojclanova<<":"<<std::endl;
            for(int i=0;i<korak;i++) string_dijete_pok=string_dijete_pok->sljedeci;
            korak=0;
            std::string string_dijete=string_dijete_pok->ime;
            auto p=string_dijete.begin();
            while(p!=string_dijete.end()){
                if(isalpha(*p) || isdigit(*p)) korak++;
                p++;
            }
            skup.insert(string_dijete);
            korak--;
            auto za_brisanje=string_dijete_pok;
            while(string_dijete_pok->sljedeci!=za_brisanje) string_dijete_pok=string_dijete_pok->sljedeci;
            auto prethodni=string_dijete_pok;
            string_dijete_pok=string_dijete_pok->sljedeci; string_dijete_pok=string_dijete_pok->sljedeci;
            //std::cout<<"    za_brisanje="<<za_brisanje->ime<<std::endl;
            //std::cout<<"    prethodni="<<prethodni->ime<<std::endl;
            //std::cout<<"    string_dijete_pok="<<string_dijete_pok->ime<<std::endl;
            if(za_brisanje->sljedeci==prethodni->sljedeci){string_dijete_pok->sljedeci=nullptr; prethodni=nullptr; za_brisanje=nullptr;} //delete prethodni;
            else prethodni->sljedeci=string_dijete_pok;//delete za_brisanje;
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