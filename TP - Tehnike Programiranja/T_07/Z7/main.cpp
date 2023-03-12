/* 
    TP 16/17 (LV 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>

template<typename Tip>
std::set<Tip> Presjek(std::set<Tip> set1,std::set<Tip> set2){
    std::set<Tip> novi;
    auto p=set1.begin();
    auto q=set2.begin();
    while(p!=set1.end() && q!=set2.end()){
        if(*p==*q) novi.insert(*p);
        if(*p<*q) p++; 
        else if(*q<*p) q++;
        else{p++; q++;}
    }
    return novi;
}

template<typename Tip>
std::set<Tip> Unija(std::set<Tip> set1,std::set<Tip> set2){
    std::set<Tip> novi;
    auto p=set1.begin();
    auto q=set2.begin();
    while(p!=set1.end() || q!=set2.end()){
        if(p!=set1.end()) novi.insert(*p);
        if(q!=set2.end()) novi.insert(*q);
        if(p!=set1.end()) p++; 
        if(q!=set2.end()) q++;
    }
    return novi;
}

int main ()
{
    std::set<std::string> skup1={{"Eman"},{"jede"},{"halvu"},{"za"},{"Ramazan"}};
    std::set<std::string> skup2={{"bananu"},{"Ramazan"}};
    std::set<std::string> unija=Unija(skup1,skup2);
    std::set<std::string> presjek=Presjek(skup1,skup2);
    std::cout<<"Unija:"<<std::endl;
    for(auto x : unija) std::cout << x << " ";
    std::cout<<std::endl<<"Presjek:"<<std::endl;
    for(auto x : presjek) std::cout << x << " ";
	return 0;
}