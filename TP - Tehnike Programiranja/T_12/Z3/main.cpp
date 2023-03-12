/* 
    TP 16/17 (LV 12, Zadatak 3)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
//slucajno pisao u zadatku 4 pa ga prekopirao ovdje iz zadatka 4
#include <iostream> 

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

Dani &operator ++(Dani &x){
    return x=Dani((int (x) + 1)%7);
}

Dani operator ++(Dani &x,int){
    ++x;
    return x;
}

Dani operator +(Dani x,int broj){
    return Dani((int (x) + broj)%7);
}

std::ostream& operator <<(std::ostream &tok,Dani x){
    std::string d[7]={"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
    return tok<<d[x];
} 

int main ()
{
    for(Dani d = Ponedjeljak; d <= Petak; d++) std::cout << d << std::endl;
	return 0;
}