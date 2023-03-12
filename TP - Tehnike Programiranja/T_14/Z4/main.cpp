//TP 2021/2022: LV 14, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <fstream>

void IzvrniDatoteku(std::string ime_datoteke){
    std::fstream ulazni_tok1(ime_datoteke,std::ios::in|std::ios::out|std::ios::binary);
    if(!ulazni_tok1) throw std::logic_error("Datoteka ne postoji");
    std::fstream ulazni_tok2(ime_datoteke,std::ios::in|std::ios::out|std::ios::binary);
    double sadrzaj1,sadrzaj2;
    int jedan_double_u_bajtima=sizeof(double);
    int i=2;
    ulazni_tok2.seekg(-jedan_double_u_bajtima,std::ios::end);
    for(;;){
        if(ulazni_tok1.tellg()>=ulazni_tok2.tellg()) break; //idemo do pola
        //procitaj
        ulazni_tok1.read(reinterpret_cast<char*>(&sadrzaj1),jedan_double_u_bajtima);
        ulazni_tok2.read(reinterpret_cast<char*>(&sadrzaj2),jedan_double_u_bajtima);
        //postavi
        ulazni_tok1.seekp(-(int)jedan_double_u_bajtima,std::ios::cur);
        ulazni_tok2.seekp(-ulazni_tok1.tellp()-int(jedan_double_u_bajtima),std::ios::end);
        //zapisi obrnuto
        ulazni_tok2.write(reinterpret_cast<char*>(&sadrzaj1),jedan_double_u_bajtima);
        ulazni_tok1.write(reinterpret_cast<char*>(&sadrzaj2),jedan_double_u_bajtima);
        //postavi
        ulazni_tok2.seekg(-i*int(jedan_double_u_bajtima),std::ios::end);
        i+=1;
        if(!ulazni_tok1 || !ulazni_tok2) throw std::logic_error("Problemi pri citanju datoteke");
    }
}

int main ()
{
    int jedan_double_u_bajtima=sizeof(double);
    std::ofstream izlazni_tok("Eman.txt",std::ios::binary);
    for(double i=0;i<100;i++) izlazni_tok.write(reinterpret_cast<char*>(&i),jedan_double_u_bajtima);
    izlazni_tok.close();
    IzvrniDatoteku("Eman.txt");
    std::ifstream ulazni_tok("Eman.txt",std::ios::binary);
    std::cout<<"Izvrnuti podaci: ";
    for(int i=0;i<100;i++){
        double broj;
        ulazni_tok.read(reinterpret_cast<char*>(&broj),jedan_double_u_bajtima);
        std::cout<<broj<<", ";
    }
	return 0;
}
