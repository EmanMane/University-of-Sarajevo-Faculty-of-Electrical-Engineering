/*U što manje linija koda napraviti funkciju:

bool provjeri_zagrade(string tekst)

koja provjerava da li je svaka otvorena zagrada u primljenom stringu korektno zatvorena.
Dozvoljena su tri tipa zagrada: obične (), uglaste [] i vitičaste {}. Funkcija treba vratiti true za string
kao što je: “[()]{}{[()()]()}”. Međutim, treba vratiti false ako se jedna vrsta zagrada ukrštava sa
drugim, npr. ako string glasi “[(])” treba vratiti false. U stringu se mogu javljati i drugi karakteri
(koje treba zanemariti).
Pri provjeri nije potrebno pridržavati se pravila iz matematike da se uglasta nalazi unutar vitičaste a
obična unutar uglaste, samo se provjerava da li je svaki tip otvorene zagrade korektno zatvoren i da
li ima ukrštanja.*/



#include<iostream>
#include<string>
#include<stack>

bool provjeri_zagrade(std::string tekst){
    std::stack<char> stek;
    for(int i=0;i<tekst.length();i++){
        if(tekst.at(i)=='{' || tekst.at(i)=='[' || tekst.at(i)=='(') stek.push(tekst.at(i));
        if(tekst.at(i)=='}' || tekst.at(i)==']' || tekst.at(i)==')'){
            if(tekst.at(i)=='}' && stek.top()!='{') return 0;
            if(tekst.at(i)==']' && stek.top()!='[') return 0;
            if(tekst.at(i)==')' && stek.top()!='(') return 0;
            stek.pop();
        }
    }
    if(stek.size()!=0) return 0;
    return true;
}

int main(){
    std::string s;
    std::cout<<"Unesite string: "; std::cin>>s;
    if(provjeri_zagrade(s)) std::cout<<"Zagrade su OK";
    else std::cout<<"Zagrade nisu OK";
}