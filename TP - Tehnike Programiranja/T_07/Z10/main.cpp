/* 
    TP 16/17 (LV 7, Zadatak 10)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>

int f(int broj){
    return broj+1;
}


std::function<int(int)> IteriranaFunkcija(std::function<int(int)> funkcija, int n){
    return [funkcija,n](int broj){for(int i=0;i<n;i++) broj=funkcija(broj); return broj;};
}

int main ()
{

    auto g = IteriranaFunkcija(f, 10);
    std::cout << g(5);

    std::cout << IteriranaFunkcija(f, 10)(5);

    std::cout << f(f(f(f(f(f(f(f(f(f(5))))))))));

	return 0;
}