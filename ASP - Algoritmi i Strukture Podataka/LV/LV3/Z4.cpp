/*Napisati funkciju:
int spoji(Stek<int> s1, Stek<int> s2, Stek<int>& s3)
Funkcija prima stek s1 koji je sortiran rastući, stek s2 koji je sortiran opadajući i s3 koji je prazan.
Potrebno je prebaciti elemente iz steka s1 i s2 u stek s3 tako da stek bude sortiran rastući pri čemu
je dozvoljeno koristiti samo tri data steka, tj. nisu dozvoljene dodatne kolekcije.
Primjer: Neka je stek s1: {1, 3, 5, 8} a s2: {9, 6, 4, 2} (prvi element je na dnu steka). 
Nakon pozvane funkcije spoji stek s3 treba da bude {1, 2, 3, 4, 5, 6, 8, 9}.*/

#include<iostream>
#include<string>
#include<stack>

void spoji(std::stack<int> s1, std::stack<int> s2, std::stack<int>& s3){
    int istih_ima=0;
    while(!s2.empty()){
        s3.push(s2.top());
        s2.pop();
    }
    while(1){
        if(s3.empty() && s1.empty()) break;
        else if(s3.empty()){
            s2.push(s1.top());
            s1.pop();
        }
        else if(s1.empty()){
            s2.push(s3.top());
            s3.pop();
        }
        else if(s3.top()>s1.top()){
            s2.push(s3.top());
            s3.pop();
        }
        else{
            s2.push(s1.top());
            s1.pop();
        }
    }
    while(!s2.empty()){
        s3.push(s2.top());
        s2.pop();
    }
}

int main(){
    std::stack<int> s1,s2,s3;
    s1.push(1);
    s1.push(3);
    s1.push(5);
    s1.push(8);
    
    s2.push(9);
    s2.push(6);
    s2.push(4);
    s2.push(2);

    spoji(s1,s2,s3);
    int n=s3.size();
    std::cout<<"Treci stek je:\n";
    for(int i=0;i<n;i++){
        std::cout<<s3.top()<<" ";
        s3.pop();
    }
}