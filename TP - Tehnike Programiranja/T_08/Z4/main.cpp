//TP 2021/2022: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <map>

std::string ZamijeniPremaRjecniku(std::string recenica, std::map<std::string, std::string> rijeci){
    std::string pom,nova_recenica;
    for(int i=0;i<recenica.size();i++){
        while(recenica[i]!=' ' && i<recenica.size()){
            pom.push_back(recenica[i]);
            i++;
        } 
        auto p=rijeci.find(pom);
        if(p!=rijeci.end()) pom=p->second;
        for(int i=0;i<pom.size();i++){
            nova_recenica.push_back(pom[i]);
        }
        if(recenica[i]==' ') nova_recenica.push_back(' ');
        pom={};
    }
    return nova_recenica;
}

int main ()
{
    std::map<std::string, std::string> moj_rjecnik{{"jabuka", "apple"}, {"da", "yes"},{"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
    std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);
	return 0;
}
