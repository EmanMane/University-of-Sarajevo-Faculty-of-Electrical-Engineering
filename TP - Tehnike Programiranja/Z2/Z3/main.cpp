//TP 2021/2022: Zadaća 2, Zadatak 3
#include <iostream>
#include <vector>
template<typename TipKontejnera1,typename TipKontejnera2>
auto ZbirKontejnera(TipKontejnera1 kanta1,TipKontejnera2 kanta2)->std::vector<decltype(*(kanta1.begin())+*(kanta2.begin()))>{
    std::vector<decltype(*(kanta1.begin())+*(kanta2.begin()))> Zbirni;
    int duzinakante1=0,duzinakante2=0;
    auto kanta1_poc=kanta1.begin(); auto kanta2_poc=kanta2.begin();
    while(kanta1_poc!=kanta1.end()){
        duzinakante1++; kanta1_poc++;
    }
    while(kanta2_poc!=kanta2.end()){
        duzinakante2++; kanta2_poc++;
    }
    if(duzinakante1<duzinakante2) Zbirni.resize(duzinakante2); else Zbirni.resize(duzinakante1);
    int i=0;
    kanta1_poc=kanta1.begin(); kanta2_poc=kanta2.begin();
    while(kanta1_poc!=kanta1.end() && kanta2_poc!=kanta2.end()){
        auto nesto=*kanta1_poc+*kanta2_poc;
        Zbirni.at(i)=nesto; i++; kanta1_poc++; kanta2_poc++;
    }
    if(duzinakante1<duzinakante2) while(kanta2_poc!=kanta2.end()){
        typename std::remove_reference<decltype(*(kanta1.begin()))>::type VarijablaZaHarisa={};   //ekvivalentno: decltype(*(kanta1.begin())+*(kanta1.begin())) VarijablaZaHarisa={};
        Zbirni.at(i)=*kanta2_poc+VarijablaZaHarisa; i++; kanta2_poc++;
    }
    if(duzinakante2<duzinakante1) while(kanta1_poc!=kanta1.end()){
        typename std::remove_reference<decltype(*(kanta2.begin()))>::type VarijablaZaHarisa={};
        Zbirni.at(i)=*kanta1_poc+VarijablaZaHarisa; i++; kanta1_poc++;
    }
    return Zbirni;
}
int main ()
{
    int n1,n2; std::vector<double> kanta1,kanta2; double clan;
    std::cout<<"Duzina prvog kontejnera: "; std::cin>>n1;
    std::cout<<"Elementi prvog kontejnera: "; 
    for(int i=0;i<n1;i++){std::cin>>clan; kanta1.push_back(clan);}
    std::cout<<"Duzina drugog kontejnera: "; std::cin>>n2;
    std::cout<<"Elementi drugog kontejnera: "; 
    for(int i=0;i<n2;i++){std::cin>>clan; kanta2.push_back(clan);}
    std::vector<double> Zbir=ZbirKontejnera(kanta1,kanta2);
    std::cout<<"Zbir kontejnera: "; 
    for(int i=0;i<Zbir.size();i++) std::cout<<Zbir.at(i)<<" ";
	return 0;
}