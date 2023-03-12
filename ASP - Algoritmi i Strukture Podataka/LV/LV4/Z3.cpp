/*
ZADATAK3

Napisati funkciju koja prima red, listu i varijablu n tipa int i modifikuje red tako da elementi iz
liste i reda budu naizmjenično poredani gdje je svaki isprepleteni dio reda i liste veličine n a počinje
se sa elementima reda. U slučaju razlike u dužini reda i liste, višak elemenata se postavlja na kraj
reda. Primjer 1: Neka je dat red sa elementima {1, 2, 3, 4} gdje je element 1 na čelu reda i lista sa
elementima {1, 2, 3, 4} i neka je n=1. Rezultantni red je {1, 1, 2, 2, 3, 3, 4, 4}. Primjer 2: Neka je
dat red sa elementima {A, A, A, A, A, A, A} gdje je element A na čelu reda i lista sa elementima
{B, B, B, B} i neka je n=2. Rezultantni red je {A, A, B, B, A, A, B, B, A, A, A}.

Napomena: Zadatak riješiti koristeći samo ulazne parametre, nije dozvoljeno korištenje pomoćnih
kolekcija. Također, nije dozvoljena ni modifikacija liste.
*/

#include<iostream>
#include<queue>
#include<list>

template<typename NekiTip>
void zadatak3(std::queue<NekiTip> &red, std::list<NekiTip> &lista, int n){
    auto i=lista.begin(); int m=red.size()+lista.size(),k=0; bool prekidac=0;
    for(int j=0;j<m;j++){
        if(k==n){
            if(prekidac) prekidac=0;
            else prekidac=1;
            k=0;
        }
        if(i==lista.end()) k=0; //ako smo dosli do kraja liste k se vraca na 0 kako ne bi bilo vise switchanja sa prekidacem
        if(!prekidac){
            red.push(red.front()); red.pop();
            k++;
        }
        else if(i!=lista.end()){
            red.push(*i);
            i++;
            k++;
        }
    }
}

int main(){
    std::queue<int> red;
    red.push(1); red.push(2); red.push(3); red.push(4);
    std::list<int> lista={1,2,3,4};
    zadatak3(red,lista,1);
    std::cout<<"Finalni red1: ";
    for(int i=0;i<red.size();i++){
        std::cout<<red.front()<<" ";
        red.push(red.front());
        red.pop();
    }
/*---------------------------------------------------------*/
    std::queue<char> red1;
    red1.push('A'); red1.push('A'); red1.push('A'); red1.push('A'); red1.push('A'); red1.push('A'); red1.push('A');
    std::list<char> lista1={'B','B','B','B'};
    zadatak3(red1,lista1,2);
    std::cout<<"\nFinalni red2: ";
    for(int i=0;i<red1.size();i++){
        std::cout<<red1.front()<<" ";
        red1.push(red1.front());
        red1.pop();
    }
    return 0;
}