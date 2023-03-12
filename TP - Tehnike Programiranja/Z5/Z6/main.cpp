//TP 2021/2022: Zadaća 5, Zadatak 6
#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>
#include <stdexcept>

template <typename TipElemenata>
void SortirajBinarnuDatoteku(const char ime_datoteke[],std::function<bool(TipElemenata, TipElemenata)> kriterij=std::less<TipElemenata>()){
    std::fstream ulaz(ime_datoteke,std::ios::binary|std::ios::in|std::ios::out);
    if(!ulaz) throw std::logic_error("Datoteka ne postoji");
    //iz predavanja, saznati duzinu datoteke u bajtima
    ulaz.seekg(0,std::ios::end);
    int velicina_datoteke=ulaz.tellg();
    int broj_elemenata=velicina_datoteke/sizeof(TipElemenata);
    //std::cout<<"Broj elemenata="<<broj_elemenata<<"\n";
    TipElemenata podatak1,podatak2;
    for(int i=0;i<broj_elemenata;i++){
        ulaz.clear();
        ulaz.seekg(0,std::ios::beg);
        for(int j=0;j<broj_elemenata-i-1;j++){
            ulaz.read(reinterpret_cast<char*>(&podatak1),sizeof(TipElemenata));
            //std::cout<<"Podatak1="<<podatak1<<" ";
            //if(!ulaz) break;
            ulaz.read(reinterpret_cast<char*>(&podatak2),sizeof(TipElemenata));
            //std::cout<<"Podatak2="<<podatak2<<" ";
            //if(!ulaz) break;
            if(!kriterij(podatak1,podatak2)){
                //std::cout<<"Rotacija\n";
                ulaz.clear();
                ulaz.seekp(-2*int(sizeof(TipElemenata)),std::ios::cur);
                ulaz.write(reinterpret_cast<char*>(&podatak2),sizeof(TipElemenata));
                ulaz.write(reinterpret_cast<char*>(&podatak1),sizeof(TipElemenata));
            }
            ulaz.seekg(-int(sizeof(podatak1)),std::ios::cur);
            //std::cout<<"\n";
        }
        //std::cout<<"\n";
    }
    if(ulaz.bad()) throw std::logic_error("Problemi u pristupu datoteci"); 
    //std::cout<<"\n";
}


int main ()
{
    std::ofstream izlaz("Eman.dat",std::ios::binary);
    for(double i=100;i>0;i--) izlaz.write((char*)&(i),sizeof(double));
    izlaz.close();
    SortirajBinarnuDatoteku<double>("Eman.dat");
    double podatak;
    std::ifstream ulaz("Eman.dat",std::ios::binary);
    for(;;){
        ulaz.read((char*)&podatak,sizeof(double));
        if(!ulaz) break;
        std::cout<<podatak<<" ";
    }
	return 0;
}

/*int main ()
{//AT 8: Sortiranje, *zanimljivo*, obrce redoslijed datoteke, kakva god da je

std::ofstream fo ("dat.bin", std::ios::binary);
short niz[] = {1, 2, 3, 4};
size_t vel = sizeof niz / sizeof *niz;
for (size_t i = 0; i < vel; ++i)
    fo.write ((char *)&niz[i], sizeof niz[i]);
fo.close();

//ako kriterij vrati false, to znaci da elemente treba mijenjati...
SortirajBinarnuDatoteku<short> ("dat.bin", [](short, short) {return false;});
std::ifstream fi ("dat.bin", std::ios::binary);
short p = -1;
while (fi.read ((char *)&p, sizeof p)) std::cout << p << " ";
}*/

