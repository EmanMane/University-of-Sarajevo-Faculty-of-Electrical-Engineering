/* 
    TP 2018/2019: LV 6, Zadatak 6
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <vector>
#include <deque>
typedef std::deque<int> Dek;
typedef std::vector<Dek> VektorDekova;

template<typename NekiTip>
auto KreirajDinamickuKopiju2D(NekiTip a)->typename std::remove_reference<decltype(a.at(0).at(0))>::type**{
    int brredova=a.size();
    int brclanova=0;
    if(brredova==0) return nullptr;
    for(int i=0;i<brredova;i++){
        for(int j=0;j<a.at(i).size();j++){
            brclanova++;
        }
    }
    typename std::remove_reference<decltype(a[0][0])>::type** matrica=nullptr;
    try{
        matrica=new typename std::remove_reference<decltype(a[0][0])>::type* [brredova];
        try{
            matrica[0]=new typename std::remove_reference<decltype(a[0][0])>::type [brredova * (brclanova/brredova)];
            for(int i=1;i<brredova;i++) matrica[i]=matrica[i-1]+a.at(i-1).size();
        }
        catch(...){
            delete[] matrica;
            throw;
        }
        for(int i=0;i<brredova;i++){
            for(int j=0;j<a.at(i).size();j++){
                matrica[i][j]=a[i][j];
            }
        }
    }
    catch(...){
        throw;
    }
    return matrica;
}

int main ()
{
    std::cout<<"Unesite broj redova kvadratne matrice: ";
    int n;
    std::cin>>n;
    try{
        VektorDekova x;
        x.resize(n);
        std::cout<<"Unesite elemente matrice: ";
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int clan;
                std::cin>>clan;
                x.at(i).push_back(clan);
            }
        }
        int **matrica=KreirajDinamickuKopiju2D(x);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                std::cout<<matrica[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        delete[] matrica[0];
        delete[] matrica;
    }
    catch(...){
        std::cout<<"Nedovoljno memorije";
    }
	return 0;
}