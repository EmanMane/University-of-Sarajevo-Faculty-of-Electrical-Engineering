//TP 2021/2022: LV 14, Zadatak 1
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

struct Temperatura{
    int dan,mjesec,godina,minimalna,maximalna; 
    double prosjecna;
    std::string informacija;
    std::vector<int> mjerenja;
};

int main ()
{
    std::ifstream ulazni_tok("TEMPERATURE.TXT");
    std::vector<Temperatura> vektor_temperatura;
    if(!ulazni_tok) std::cout<<"Datoteka TEMPERATURE.TXT ne postoji!\n";
    else{
        for(;;){
            //std::cout<<"\nUSAO";
            int dat1,dat2,dat3;
            double zbir=0;
            std::vector<int> temp;
            std::string informacija;
            char znak1,znak2;
            //ulazni_tok.ignore(1000,'\n');
            ulazni_tok>>dat1>>znak1>>dat2>>znak2>>dat3; if(!ulazni_tok) break;
            //std::cout<<dat1<<znak1<<dat2<<znak2<<dat3;
            ulazni_tok.ignore(1000,'\n');
            
            std::getline(ulazni_tok,informacija);
            //std::cout<<informacija;
            //ulazni_tok.ignore(1000,'\n');
            char provjera;
            for(;;){
                int temperaturica;
                char zarez='.',minus='.';
                //std::cout<<"peek={"<<ulazni_tok.peek()<<"}\n";
                if(ulazni_tok.peek()=='-') ulazni_tok>>minus;
                //std::cout<<"peek={"<<ulazni_tok.peek()<<"}\n";
                //if(!std::isdigit(ulazni_tok.peek())) std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT\n";
                ulazni_tok>>temperaturica;
                zarez=ulazni_tok.get();
                //std::cout<<"\nZarez je: "<<zarez<<"\n";
                if(minus=='-') temperaturica*=-1;
                //std::cout<<" "<<temperaturica<<zarez;
                zbir+=temperaturica;
                temp.push_back(temperaturica);
                if(zarez!=',') break;
            }
            //ulazni_tok.ignore(1000,'\n');
            //if(ulazni_tok.eof()) {std::cout<<"PRESKOK"; goto preskok;}
            //if(!ulazni_tok) break;
            preskok:
            Temperatura temperatura;
            temperatura.dan=dat1;
            temperatura.mjesec=dat2;
            temperatura.godina=dat3;
            temperatura.informacija=informacija;
            temperatura.mjerenja=temp;
            temperatura.minimalna=*std::min_element(temp.begin(),temp.end());
            //std::cout<<"min="<<temperatura.minimalna;
            temperatura.maximalna=*std::max_element(temp.begin(),temp.end());
            //std::cout<<"max="<<temperatura.maximalna;
            temperatura.prosjecna=zbir/temp.size();
            vektor_temperatura.push_back(temperatura);
            //if(ulazni_tok.eof()) break;
            //if(!ulazni_tok) break;
            //ulazni_tok.ignore(1000,'\n');
        }
        if(!ulazni_tok.eof()) std::cout<<"Problemi pri citanju datoteke TEMPERATURE.TXT\n";
        std::sort(vektor_temperatura.begin(),vektor_temperatura.end(),[](Temperatura x,Temperatura y){
            if(x.godina<y.godina) return true;
            else if(x.godina==y.godina){
                if(x.mjesec<y.mjesec) return true;
                else if(x.mjesec==y.mjesec){
                    if(x.dan<y.dan) return true;
                    else if(x.dan==y.dan){
                        if(x.prosjecna<y.prosjecna) return true;
                    }
                }
            }
            return false;
        });
        std::ofstream izlazni_tok("IZVJESTAJ.TXT");
        //std::cout<<"vektor_temperatura je velik: "<<vektor_temperatura.size();
        for(int i=0;i<vektor_temperatura.size();i++){
            izlazni_tok<<vektor_temperatura.at(i).informacija<<std::endl;
            for(int j=0;j<vektor_temperatura.at(i).informacija.size();j++) izlazni_tok<<"-";
            izlazni_tok<<std::endl;
            izlazni_tok<<"Datum mjerenja: "<<vektor_temperatura.at(i).dan<<"/"<<vektor_temperatura.at(i).mjesec<<"/"<<vektor_temperatura.at(i).godina<<std::endl;
            izlazni_tok<<"Minimalna temperatura: "<<vektor_temperatura.at(i).minimalna<<std::endl;
            izlazni_tok<<"Maksimalna temperatura: "<<vektor_temperatura.at(i).maximalna<<std::endl;
            izlazni_tok<<"Prosjecna temperatura: "<<std::fixed<<std::setprecision(2)<<vektor_temperatura.at(i).prosjecna<<std::endl;
            izlazni_tok<<std::endl;
        }
    }
	return 0;
}
