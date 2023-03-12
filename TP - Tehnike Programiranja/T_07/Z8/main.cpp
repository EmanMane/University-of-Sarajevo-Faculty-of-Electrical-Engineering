/* 
    TP 16/17 (LV 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <algorithm>
#include <iostream>

std::string IzvrniBezRazmaka(std::string str){
    std::string novi;
    std::remove_copy(str.rbegin(), str.rend(), std::back_inserter(novi),' ');
    return novi;
}

int main ()
{
    std::string s1={"Eman ide na faks, umire..."};
    std::string s2=IzvrniBezRazmaka(s1);
    std::cout<<s2;
	return 0;
}