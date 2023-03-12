//TP 2021/2022: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <set>
#include <map>

typedef std::map<std::string,std::set<int>> Mapa;

Mapa KreirajIndeksPojmova(std::string tekst){
    Mapa index;
    for(int i=0;i<tekst.size();i++){
        while(i<tekst.size() && !isalpha(tekst.at(i)) && !isdigit(tekst.at(i))) i++;
        if(i==tekst.size()) break;//Zbog .end() ako je na kraju puno razmaka
        std::string pom_string={};
        std::set<int> pom_skup={};
        while(i<tekst.size() && (isalpha(tekst.at(i)) || isdigit(tekst.at(i)))){
            if(pom_skup.size()==0) pom_skup.insert(i);
            pom_string.push_back(tolower(tekst.at(i)));
            i++;
        }
        int zapamti_i=i;
        i-=pom_string.size();
        auto p=pom_string.begin(); auto q=tekst.begin()+i;
        //std::cout<<"While"<<std::endl;
        while(q!=tekst.end()){
            //std::cout<<"Za i="<<i<<" q je "<<*q<<", ";
            if(tolower(*q)==tolower(*p)){
                //std::cout<<"p je "<<*p<<". ";
                int zapamti_nakratko_i=i;
                auto zapamti_q=q;
                if(q!=tekst.begin()){
                    q--;
                    if(isalpha(*q) || isdigit(*q)){q++; goto dalje;}
                    q++;
                }
                for(;;){
                    //std::cout<<"(q,p)="<<*q<<","<<*p<<". ";
                    if(p==pom_string.end()){
                        if(!isalpha(*q) && !isdigit(*q)) {
                            pom_skup.insert(zapamti_nakratko_i);
                            goto nije;
                        }
                        else goto nije;
                    }
                    if(tolower(*q)!=tolower(*p)){
                        nije:;
                        q=zapamti_q;
                        i=zapamti_nakratko_i;
                        p=pom_string.begin();
                        goto dalje;
                    }
                    p++;q++;i++;
                    if(i>tekst.size()) break;
                }
                dalje:;
            }
            q++; i++;
            if(q==tekst.end()) break;
        }
        if(index.find(pom_string)==index.end()) index.insert({pom_string,pom_skup});
        i=zapamti_i;
    }
    return index;
}

std::set<int> PretraziIndeksPojmova(std::string rijec,Mapa index){
    std::set<int> skup;
    for(int i=0;i<rijec.size();i++) rijec.at(i)=tolower(rijec.at(i));
    auto p=index.find(rijec);
    if(p==index.end()) throw std::logic_error("Pojam nije nadjen");
    skup=p->second;
    return skup;
}

void IspisiIndeksPojmova(Mapa index){
    for(auto it=index.begin();it!=index.end();it++){
        std::cout<<it->first<<": ";
        auto p=(it->second).begin();
        while(p!=(it->second).end()){
            if(p!=(it->second).begin()) std::cout<<",";
            std::cout<<*p; 
            p++;
        }
        std::cout<<std::endl;
    }
}

int main ()
{    
    std::cout<<"Unesite tekst: ";
    std::string tekst;
    std::getline(std::cin,tekst);
    Mapa pojmovi=KreirajIndeksPojmova(tekst);
    IspisiIndeksPojmova(pojmovi);
    for(;;){
        std::cout<<"Unesite rijec: ";
        std::string unos;
        std::getline(std::cin,unos);
        if(unos==".") break;
        try{
            std::set<int> skup=PretraziIndeksPojmova(unos,pojmovi);
            for(auto x : skup) std::cout<<x<<" ";
            std::cout<<std::endl;
        }
        catch(...){
            std::cout<<"Unesena rijec nije nadjena!";
            std::cout<<std::endl;
        }
    }
	return 0;
}
