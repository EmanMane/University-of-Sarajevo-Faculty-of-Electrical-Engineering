//TP 2021/2022: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <array>
#include <iomanip>

#define eps 0.0000000001

typedef std::vector<double> vektor;
typedef std::vector<vektor> matrica;

matrica MnozenjeMatrica(matrica a,matrica b){

    int br_kol_a=0;
    int br_kol_b=0;
    int br_red_a=a.size();
    int br_red_b=b.size();
    
    for(int i=0;i<br_red_a;i++){
        if(i==0) br_kol_a=a.at(i).size();
        else if(br_kol_a!=a.at(i).size()) throw std::domain_error("Neispravna matrica!");
    }

    for(int i=0;i<br_red_b;i++){
        if(i==0) br_kol_b=b.at(i).size();
        else if(br_kol_b!=b.at(i).size()) throw std::domain_error("Neispravna matrica!");
    }
    
    if(br_kol_a!=br_red_b) throw std::domain_error("Matrice nisu saglasne za mnozenje!");

    matrica c;
    c.resize(br_red_a);
    for(int i=0;i<br_red_a;i++){
        c.at(i).resize(br_kol_b);
    }

    for(int i=0;i<br_red_a;i++){
        for(int j=0;j<br_kol_b;j++){
            double suma=0;
            for(int k=0;k<br_red_b;k++) suma+=a.at(i).at(k)*b.at(k).at(j);
            c.at(i).at(j)=suma;
        }
    }

    return c;
}


std::array<matrica,2> DoolittleLU(matrica H){
    std::array<matrica,2> LU;

    int br_kol_H;
    for(int i=0;i<H.size();i++){
        if(i==0) br_kol_H=H.at(i).size();
        else if(br_kol_H!=H.at(i).size()) throw std::domain_error("Neispravna matrica!");
    }

    for(int i=0;i<H.size();i++){
        if(H.size()!=H.at(i).size()) throw std::domain_error("Matrica mora biti kvadratna!");
    }
        
    LU.at(0).resize(H.size()); LU.at(1).resize(H.size());
    for(int i=0;i<H.size();i++){
        LU.at(0).at(i).resize(H.size()); LU.at(1).at(i).resize(H.size());
    }

    for(int i=0;i<H.size();i++){

        for(int j=i;j<H.size();j++){
            double S=0;
            for(int m=0;m<i;m++) S+=LU.at(0).at(i).at(m)*LU.at(1).at(m).at(j);
            LU.at(1).at(i).at(j)=H.at(i).at(j)-S;
            
        }
        
        for(int j=i;j<H.size();j++){
            if(i==j) LU.at(0).at(i).at(i)=1;
            else {
                double S=0;
                for(int m=0;m<i;m++){
                    S+=LU.at(0).at(j).at(m)*LU.at(1).at(m).at(i);
                }
                LU.at(0).at(j).at(i)=H.at(j).at(i)-S;
                LU.at(0).at(j).at(i)/=LU.at(1).at(i).at(i);
            }
        }

        if(fabs(LU.at(1).at(i).at(i))<eps) throw std::domain_error("Matrica je singularna!");
    }
    
    return LU;
}

bool ProvjeriFaktorizaciju(matrica H,std::array<matrica,2> LU){
    if(LU.at(0).size()==0 && LU.at(1).size()==0 && H.size()==0) return true;
    if(LU.at(0).at(0).size()!=LU.at(1).size() || H.size()!=LU.at(1).at(0).size() || H.at(0).size()!=LU.at(0).at(0).size()) return false;
    try{
        matrica x=MnozenjeMatrica(LU.at(0),LU.at(1));
    }
    catch(...){
        return false;
    }

    matrica x=MnozenjeMatrica(LU.at(0),LU.at(1));
    for(int i=0;i<x.size();i++){
        for(int j=0;j<x.size();j++){
            if(fabs(x.at(i).at(j)-H.at(i).at(j))>eps) return false;
        }
    }
    return true;
}

int main (){
    std::cout<<"Broj redova/kolona matrice: ";
    int n=0;
    std::cin>>n;
    matrica mat;
    mat.resize(n);
    for(int i=0;i<n;i++){
        mat.at(i).resize(n);
    }
    std::cout<<"Elementi matrice:"<<std::endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double clan;
            std::cin>>clan;
            mat.at(i).at(j)=clan;
        }
    }
    std::array<matrica,2> p;
    try{
        p=DoolittleLU(mat);
        std::cout<<std::endl;
        std::cout<<"Matrica L:"<<std::endl;
        for(int i=0;i<p.at(0).size();i++){
            for(int j=0;j<p.at(0).at(i).size();j++){
                std::cout<<p.at(0).at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"Matrica U:"<<std::endl;
        for(int i=0;i<p.at(1).size();i++){
            for(int j=0;j<p.at(1).at(i).size();j++){
                std::cout<<p.at(1).at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
    }
    catch(std::domain_error error){
        std::string singularitet=error.what();
        std::string provjera="Matrica je singularna!";
        if(singularitet==provjera){
            std::cout<<"LU faktorizacija ne postoji, jer je matrica singularna!";
            return 0;
        }
        std::cout<<error.what();
    }
	return 0;
}