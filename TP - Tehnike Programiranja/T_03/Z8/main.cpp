//TP 2021/2022: LV 3, Zadatak 8
#include <iostream>
#include <cmath>
#include <string>


typedef std::string string;

string IzdvojiRijec(string recenica, int rbr){
    string rijec;
    int k=0;
    for(int i=0;i<recenica.length();i++){
        if(i==0 && recenica.at(i)!=' ') k++;
        else if(recenica.at(i)!=' ' && recenica.at(i-1)==' ') k++;

        if(k==rbr && recenica.at(i)!=' '){
            rijec.push_back(recenica.at(i));
        }
    }
    if(k<rbr || rbr<=0) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci!");
    return rijec;
}

int main ()
{
    std::cout<<"Unesite redni broj rijeci: ";
    int n;
    std::cin>>n;
    std::cin.ignore(10000,'\n');                                //Omogucava fin unos (da ga nema, ne bi smo mogli unijeti string)
    std::cout<<"Unesite recenicu: ";
    string recenica;
    std::getline(std::cin,recenica);
    try{                                                        //Pokušaj izvršiti blok (konkretno funkciju)
        string rijec=IzdvojiRijec(recenica,n);                  //AKO funkcija baci grešku, idi na catch, u protivnom ispiši i završi
        std::cout<<"Rijec na poziciji "<<n<<" je "<<rijec;
    }
    catch(std::range_error greska){                             //Uhvati range_error ukoliko je bacen
        std::cout<<greska.what();                               //Funkcija .what() vraca uzrok greske
    }
	return 0;
}