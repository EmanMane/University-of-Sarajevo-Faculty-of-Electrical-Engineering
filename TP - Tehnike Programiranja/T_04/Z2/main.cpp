//TP 2021/2022: LV 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>


void IzvrniString(std::string &tekst){
    for(int i=0;i<tekst.size()/2;i++){
        char temp=tekst.at(i);
        tekst.at(i)=tekst.at(tekst.length()-1-i);
        tekst.at(tekst.length()-1-i)=temp;
    }
}

int main ()
{
    std::cout<<"Unesi string: ";
    std::string s;
    std::getline(std::cin,s);
    IzvrniString(s);
    std::cout<<"Izvrnuti string je: ";
    std::cout << s;
	return 0;
}