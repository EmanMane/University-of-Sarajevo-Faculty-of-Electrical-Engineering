/*Napisati funkciju:

int presjek(Stek<Tip> s1, Stek<Tip> s2)

koja prima dva sortirana generička steka (tako da se na vrhu steka nalazi najmanji element), a vraća
broj elemenata u njihovom presjeku odnosno broj elemenata koji se javljaju u oba steka.
Pretpostaviti da se elementi ne ponavljaju u istom steku.

Primjer: Neka su u prvom steku elementi A C D F, a u drugom B C D E F G. Funkcija treba vratiti
broj 3 pošto postoje tri elementa koji se nalaze u oba steka (a to su C D F).*/

#include<iostream>
#include<string>
#include<stack>

template<typename NekiTip>
int presjek(std::stack<NekiTip> s1, std::stack<NekiTip> s2){
    int istih_ima=0;
    while(1){
        if(s1.top()<s2.top()){
            s1.pop();
        }
        else if(s1.top()>s2.top()){
            s2.pop();
        }
        else if(s1.top()==s2.top()){
            s1.pop(); s2.pop(); 
            istih_ima++;
        }
        if(s1.empty() || s2.empty()) break;
    }
    return istih_ima;
}

int main(){
    std::stack<char> s1,s2;
    s1.push('F');
    s1.push('D');
    s1.push('C');
    s1.push('A');
    
    s2.push('G');
    s2.push('F');
    s2.push('E');
    s2.push('D');
    s2.push('C');
    s2.push('B');
    std::cout<<"Zajednickih elemenata je "<<presjek(s1,s2);
}