/*
ZADATAK2

Napisati funkciju koja prima stek, red i varijablu pocetnaDuzinaReda tipa int koja će
elemente iz reda ubaciti na dno steka u obrnutom redoslijedu. Primjer: Neka je dat red sa
elementima {1, 2, 3, 4} gdje je element 1 na čelu reda i stek sa elementima {5, 6, 7, 8} gdje je
element 8 na vrhu steka. Rezultantni stek se sastoji od elemenata {1, 2, 3, 4, 5, 6, 7, 8} gdje je
element 8 na vrhu steka. Ustanoviti koja je vremenska kompleksnost rješenja.

Napomena: Zadatak riješiti koristeći samo ulazne parametre, nije dozvoljeno korištenje pomoćnih
kolekcija.
*/


#include<iostream>
#include<queue>
#include<stack>

template<typename NekiTip>
void zadatak2(std::stack<NekiTip> &stek, std::queue<NekiTip> &red, int pocetnaDuzinaReda){
    while(!stek.empty()){           //sve iz steka prebaci u red (na kraj reda) {1,2,3,4,5,6,7,8} lijevo je prvi
        pocetnaDuzinaReda++;        //Uvecava se do velicine koja je u sustini stek.size()+red.size();
        red.push(stek.top());
        stek.pop();
    }
    for(int i=0;i<pocetnaDuzinaReda;i++){       //sve elemente iz reda vrati u stek {8,7,6,5,4,3,2,1} 8 je na vrhu
        stek.push(red.front());
        red.pop();
    }
    for(int i=0;i<pocetnaDuzinaReda;i++){       //sve elemente iz steka vrati u red {8,7,6,5,4,3,2,1} 8 je prvi
        red.push(stek.top());
        stek.pop();
    }
    for(int i=0;i<pocetnaDuzinaReda;i++){       //sve elemente iz reda vrati u stek {1,2,3,4,5,6,7,8} 1 je na vrhu
        stek.push(red.front());
        red.pop();
    }
}

int main(){
    std::queue<int> red;
    red.push(1); red.push(2); red.push(3); red.push(4);
    std::stack<int> stek;
    stek.push(8); stek.push(7); stek.push(6); stek.push(5);
    zadatak2(stek,red,stek.size());
    std::cout<<"Finalni stek: ";
    for(int i=0;i<stek.size()+i;i++){
        std::cout<<stek.top()<<" ";
        stek.pop();
    }
    return 0;
}