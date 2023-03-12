//TP 2021/2022: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <vector>

std::array<std::vector<std::string>,100> RazvrstajRijeciPoDuzini(std::string recenica){
    std::array<std::vector<std::string>,100> moderniniz;
    if(recenica.length()!=1){
        for(int i=0;i<recenica.length();i++){
            if(isalpha(recenica.at(i)) || isdigit(recenica.at(i))){                               //Kad naletimo na slovo, udjemo u granu
                int pocetakrijeci=i;
                int brojslova=0;
                while(isalpha(recenica.at(i)) || isdigit(recenica.at(i))){                        //Brojanje slova trenutne rijeci
                    brojslova++;
                    i++;
                    if(i==recenica.length()) break;
                }
                if(brojslova>99){
                    throw std::range_error("Predugacka rijec!");
                    return moderniniz;
                } 
                int krajrijeci=i;
                i=pocetakrijeci;

                int brojredovavektora=moderniniz.at(brojslova).size();                                                      //Promjena velicine
                moderniniz.at(brojslova).resize(brojredovavektora+1);                                                       //vektora, kako bi imali gdje ubaciti rijec
                while(isalpha(recenica.at(i)) || isdigit(recenica.at(i))){                                                         
                    moderniniz.at(brojslova).at(brojredovavektora).push_back(toupper(recenica.at(i)));                               //Ubacivanje rijeci u 'moderniniz'
                    i++;
                    if(i==recenica.length()) break;
                }
                i=krajrijeci;                                            //nakon sto je rijec zavrsena, 'i' se postavlja na kraj rijeci odakle nastavlja potragu za novom zrtvom (novom rijeci)
                if(i==recenica.length()) return moderniniz;
            }
        }
    }
    else{                                                               //Rjesenje problema koji se javlja kada string sadrzi samo jedno slovo/broj
        moderniniz.at(1).resize(1);
        moderniniz.at(1).at(0).push_back(recenica.at(0));
    } 
    return moderniniz;
}

int main ()
{
    std::cout<<"Unesite recenicu: ";
    std::string recenica;
    std::getline(std::cin,recenica);
    std::array<std::vector<std::string>,100> niz;
    try{
        niz=RazvrstajRijeciPoDuzini(recenica);
    }
    catch(std::range_error greska){
        std::cout<<std::endl;
        std::cout<<"Greska: Recenica sadrzi predugacku rijec!";
        return 0;
    }
    for(int i=0;i<100;i++){
        if(niz.at(i).size()>0){
            std::cout<<std::endl<<"Duzina "<<i<<": ";
            for(int j=0;j<niz.at(i).size();j++){
                for(int z=0;z<niz.at(i).at(j).length();z++){
                    std::cout<<niz.at(i).at(j).at(z);
                }
                std::cout<<" ";
            }
            std::cout<<std::endl;
        }
    }

	return 0;
}