//TP 2021/2022: Zadaća 2, Zadatak 4
#include <iostream>
#include <vector>
#include <algorithm>
template<typename TipUKontejneru>
bool Kriterij(std::vector<TipUKontejneru> a,std::vector<TipUKontejneru> b){
    if(a.size()==0) return false; if(b.size()==0) return true;
    typename std::remove_reference<decltype(a.at(0))>::type S1=a.at(0),S2=b.at(0);
    for(int i=1;i<a.size();i++) S1+=a.at(i);
    for(int i=1;i<b.size();i++) S2+=b.at(i);
    if(S1>S2) return true;
    return false;
}

template<typename TipUKontejneru>
void SortirajPoSumiRedova(std::vector<std::vector<TipUKontejneru>> &mat){
    std::sort(mat.begin(),mat.end(),Kriterij<TipUKontejneru>);
}
int main (){
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa):"<<std::endl;
    double clan,i=0;
    std::vector<std::vector<double>> matrica;
    for(;;){
        while(std::cin>>clan){
            matrica.resize(i+1);
            matrica.at(i).push_back(clan);
        }
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        if(matrica.size()==i) break;
        i++;
    }
    SortirajPoSumiRedova(matrica);
    std::cout<<std::endl<<"Matrica nakon sortiranja: "<<std::endl;
    for(int i=0;i<matrica.size();i++){
        for(int j=0;j<matrica.at(i).size();j++){
            std::cout<<matrica.at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
    }
	return 0;
}