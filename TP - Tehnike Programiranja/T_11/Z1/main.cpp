/* 
    TP 16/17 (LV 11, Zadatak 1)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

class NeobicnaKlasa{
    public:
    explicit NeobicnaKlasa(double x){std::cout<<"Direktna inicijalizacija"<<std::endl;}
    NeobicnaKlasa(int x){std::cout<<"Kopirajuca inicijalizacija"<<std::endl;}
};

int main ()
{
    NeobicnaKlasa k1(5.5); // Proizvodi ispis "Direktna inicijalizacija"
    NeobicnaKlasa k2 = 5; // Proizvodi ispis "Kopirajuca inicijalizacija"
	return 0;
}