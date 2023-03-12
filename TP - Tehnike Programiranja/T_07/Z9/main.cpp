/* 
    TP 16/17 (LV 7, Zadatak 9)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>

std::function<double(double)> plus2(double a){
    return [a](double b){return a+b;};
}

std::function<std::function<double(double)>(double)> plus3(double a){
    return [a](double b){return [a,b](double c){return a+b+c;};};
}

int main ()
{
    std::cout << plus2(3)(5) << std::endl;
  	std::cout << plus3(3)(5)(6) << std::endl;
	return 0;
}