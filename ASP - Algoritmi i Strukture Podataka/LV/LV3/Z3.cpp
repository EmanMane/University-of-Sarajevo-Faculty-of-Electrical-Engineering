/*Napisati kod funkcije čiji je prototip
bool palindrom(const Lista<char>& rijec)
koja vraća true ako riječ sadržana u Listi tipa char predstavlja palindrom (jednaka je s početka i
kraja), a false ako ne predstavlja. Primjer palindroma:
RATAR
ANAVOLIMILOVANA
Pretpostaviti da string sadrži isključivo velika slova engleske abecede.
Napomena: Za ovaj zadatak je potrebno koristiti klase Lista razvijene na prošlom tutorijalu. Ako
ima nepopravljenih grešaka u ovim klasama, potrebno ih je najprije popraviti.*/

#include<iostream>
#include<string>
#include<list>
#include<stack>

bool palindrom(const std::list<char>& rijec){
    auto lijevi=rijec.begin(),desni=rijec.end();
    desni--;
    while(lijevi!=desni){
        if(*lijevi!=*desni) return false;
        lijevi++; desni--;
    }
    return true;
}

int main(){
    std::list<char> rijec={'A','N','A','V','O','L','I','M','I','L','O','V','A','N','A'};
    if(palindrom(rijec)) std::cout<<"Palindrom je";
    else std::cout<<"Palindrom nije";
    return 0;
}