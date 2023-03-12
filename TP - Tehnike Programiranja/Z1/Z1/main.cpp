//TP 2021/2022: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>

typedef std::vector<int> vektor;

int CiklickaPermutacija(vektor a, vektor b){
    
    if(a.size()!=b.size()) return -1;           //Ako nisu iste duzine dva vektora, automatski nisu permutirani

    if(a.size()==0 && b.size()==0) return 0;    //Ako su oba vektora prazna

    for(int i=0;i<a.size();i++){                //Provjera jesu li dva vektora ista
        if(a.at(i)!=b.at(i)) break;
        else if(i==a.size()-1) return 0;
    }
    
    int k=-1;
    bool imaliga=false;                        //koristan bool koji ako ne nadje jedan broj iz prvog vektora u drugom automatski vraca -1
    for(int i=0;i<a.size();i++){
        for(int j=b.size()-1;j>-1;j--){
            if(a.at(i)==b.at(j)){
                imaliga=true;
                k=b.size()-j;
                for(int x=i,y=j;x<a.size() && y<a.size();x++,y++){
                    if(a.at(x)!=b.at(y)) goto izlaz;
                    if(x==a.size()-1) x=-1;
                    if(y==b.size()-1) y=-1;
                    if(x==i-1) return k;
                }
                izlaz:;
            }
        }
        if(imaliga==false) return -1;

        imaliga=false;
        k=-1;
    }
    return k;
}

int main ()
{
    std::cout<<"Prva sekvenca: ";
    std::string prvi;
    std::getline(std::cin,prvi);
    int minus=1;
    int desetica=1;
    int broj=0;  
    vektor vprvi(0);
    for(int i=0;i<prvi.length();i++){
        if(prvi.at(i)!=' ' && prvi.at(i)!='-' && (prvi.at(i)<'0' || prvi.at(i)>'9')) break;
        else{
            if(prvi.at(i)=='-' && i+1!=prvi.length()) minus=-1;
            else if(i!=0 && prvi.at(i)==' ' && prvi.at(i-1)!=' ' ){
                izrod:
                broj*=minus;   
                vprvi.push_back(broj);
                minus=1; broj=0; desetica=1;
            }
            else if(prvi.at(i)>='0' && prvi.at(i)<='9'){
                char cifra=prvi.at(i);
                broj*=desetica;
                broj+=cifra-48;
                if(desetica==1) desetica*=10;
                if(prvi.at(i+1)!=' ' && (prvi.at(i+1)<'0' || prvi.at(i+1)>'9')) goto izrod;
            }
        }
    }

    std::cout<<"Druga sekvenca: ";
    std::string drugi;
    std::getline(std::cin,drugi); 
    vektor vdrugi(0);
    for(int i=0;i<drugi.length();i++){
        if(drugi.at(i)!=' ' && drugi.at(i)!='-' && (drugi.at(i)<'0' || drugi.at(i)>'9')) break;
        else{
            if(drugi.at(i)=='-' && i+1!=drugi.length()) minus=-1;
            else if(i!=0 && drugi.at(i)==' ' && drugi.at(i-1)!=' ' ){
                drugiizrod:
                broj*=minus;   
                vdrugi.push_back(broj);
                minus=1; broj=0; desetica=1;
            }
            else if(drugi.at(i)>='0' && drugi.at(i)<='9'){
                char cifra=drugi.at(i);
                broj*=desetica;
                broj+=cifra-48;
                if(desetica==1) desetica*=10;
                if(drugi.at(i+1)!=' ' && (drugi.at(i+1)<'0' || drugi.at(i+1)>'9')) goto drugiizrod;
            }
        }
    }

    int k=CiklickaPermutacija(vprvi, vdrugi);

    if(k==-1){
        std::cout<<"Druga sekvenca nije ciklicka permutacija prve.";
    } 
    else{
        std::cout<<"Druga sekvenca je ciklicka permutacija prve s pomakom "<<k<<".";
    }

	return 0;
}