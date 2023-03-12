/* 
    TP 16/17 (LV 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <list>

template<typename Tip>
void SortirajListu (std::list<Tip> &lista){
    auto p=lista.begin();
    while(p!=lista.end()){
        auto q=p;
        while(q!=lista.end()){
            if(*q<*p){
                auto temp=*p;
                *p=*q;
                *q=temp;
            }
            q++;
        }
        p++;
    }
}

int main ()
{
    std::cout<<"Koliko ima elemenata: "; int n; std::cin>>n;
    std::list<int> lista(n);
    std::cout<<"Unesite elemente: "<<std::endl;
    auto p=lista.begin();
    while(p!=lista.end()){
        int broj;
        std::cin>>broj;
        *p=broj;
        p++;
    }
    SortirajListu(lista);
    std::cout<<"Sortirana lista: ";
    for(auto x : lista) std::cout << x << " ";
	return 0;
}