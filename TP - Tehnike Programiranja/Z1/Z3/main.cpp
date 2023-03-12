//TP 2021/2022: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>

typedef std::vector<bool> vektor;
typedef std::vector<vektor> matrica;

bool DaLiSeDameNapadaju(matrica ploca){
    int maxred=0;
    int brojred=ploca.size();

    for(int i=0;i<brojred;i++){                                //U slucaju da su prvi redovi prazni, brišemo ih jer nam ne trebaju sve do reda gdje ima bar 1 clan
        if(ploca.at(i).size()==0){
            ploca.erase(ploca.begin()+i);
            brojred=ploca.size();
            i--;
            }
        else break;
    }

    for(int i=0;i<brojred;i++){                                //Petlja koja traži najveci broj kolona u redu
        if(ploca.at(i).size()>maxred) maxred=ploca.at(i).size();
    }
    
    for(int i=0;i<brojred;i++){                                //Petlja koja pretvara GRBAVU matricu u NORMALNU matricu ciji je broj kolona dosao iz maximalnog moguceg
        ploca.at(i).resize(maxred,false);
    }

   

    std::vector<int> horizontalno_ponavljanje(brojred),vertikalno_ponavljanje(maxred);              //Provjera da li se dvije kraljice nalaze na istoj horizontali/vertikali
    for(int i=0;i<brojred;i++){
        for(int j=0;j<maxred;j++){
            if(ploca.at(i).at(j)==true){
                horizontalno_ponavljanje.at(i)++;
                vertikalno_ponavljanje.at(j)++;
            }
        }
    }
    for(int i=0,j=0;i<brojred && j<maxred;i++,j++){
        if(horizontalno_ponavljanje.at(i)>1 || vertikalno_ponavljanje.at(j)>1) return true;
    }
    
    for(int i=0;i<brojred;i++){                                                                     //Provjera dijagonala:
        for(int j=0;j<maxred;j++){
            if(ploca.at(i).at(j)==true){
                for(int x=j,y=i;x>-1 && y>-1;x--,y--){                                              //Provjera Sjeverozapada
                    if(ploca.at(i).at(j)==ploca.at(y).at(x) && x!=j && y!=i) return true;
                }
                for(int x=j,y=i;x<maxred && y>-1;x++,y--){                                          //Provjera Sjeveroistoka
                    if(ploca.at(i).at(j)==ploca.at(y).at(x) && x!=j && y!=i) return true;
                }
                for(int x=j,y=i;x>-1 && y<brojred;x--,y++){                                         //Provjera Jugozapada
                    if(ploca.at(i).at(j)==ploca.at(y).at(x) && x!=j && y!=i) return true;
                }
                for(int x=j,y=i;x<maxred && y<brojred;x++,y++){                                     //Provjera Jugoistoka
                    if(ploca.at(i).at(j)==ploca.at(y).at(x) && x!=j && y!=i) return true;
                }
            }
        }
    }

    return false;
}

int main ()
{
    std::cout<<"Unesite opis sahovske ploce:"<<std::endl<<"(Q za kraljicu, bilo sta drugo za prazno polje, ENTER naprazno za kraj unosa):"<<std::endl;
    int maxduzina=0;
    matrica ploca;
    int i=0;
    for(;;){
        std::string red;
        std::getline(std::cin,red);
        if(red.length()==0) break;
        if(maxduzina<red.length()) maxduzina=red.length();

        ploca.resize(i+1,std::vector<bool>(maxduzina,false));
        for(int j=0;j<red.length();j++){
            if(red.at(j)=='Q') ploca.at(i).at(j)=true;
            else ploca.at(i).at(j)=false;
        }
        i++;
    }
        bool pitanje=DaLiSeDameNapadaju(ploca);
    if(pitanje==true) std::cout<<"Dame se medjusobno napadaju.";
    else std::cout<<"Dame se medjusobno ne napadaju.";
    return 0;
}