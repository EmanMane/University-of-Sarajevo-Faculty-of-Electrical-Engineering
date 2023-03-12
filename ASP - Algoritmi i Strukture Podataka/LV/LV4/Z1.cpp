/*
ZADATAK1

Napisati funkciju koja prima red i modifikuje ga tako da budu izbačene sve vrijednosti veće od
srednje vrijednosti njegovih elemenata. Ustanoviti koja je vremenska kompleksnost rješenja.

Napomena: Zadatak riješiti koristeći samo ulazni red, nije dozvoljeno korištenje pomoćnih
kolekcija.
*/

#include<iostream>
#include<queue>

template<typename NekiTip>
void zadatak1(std::queue<NekiTip> &red){
    NekiTip S=0;
    int velicina_reda=red.size();
    for(int i=0;i<velicina_reda;i++){       //Prvi prolaz - traženje Aritnmeticke sredine
        S+=red.front();
        red.push(red.front());
        red.pop();
    }
    NekiTip Ars=S/velicina_reda;
    for(int i=0;i<velicina_reda;i++){       //Drugi prolaz - Izbacivanje vecih od aritmeticke
        if(red.front()>Ars){
            red.pop(); 
        }
        else{
            red.push(red.front());
            red.pop();
        }
    }
}


int main(){
    std::queue<int> red;
    red.push(1);
    red.push(2);
    red.push(3);
    red.push(4);
    red.push(5);
    red.push(6);
    red.push(7);
    red.push(8);
    red.push(9);
    red.push(10);
    zadatak1(red);
    std::cout<<"Finalni red: ";
    for(int i=0;i<red.size();i++){
        std::cout<<red.front()<<" ";
        red.push(red.front());
        red.pop();
    }
}