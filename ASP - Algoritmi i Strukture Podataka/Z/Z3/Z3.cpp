#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void radixSort(vector<int> &a){
    vector<vector<int>> cifre;
    int max_broj=0,cifre_max_broja=0,k=1;

    if(a.size()!=0){
        for(int i=0;i<a.size();i++){
            if(i==0){ 
                max_broj=a.at(i);
                cifre_max_broja=log10(max_broj)+1;
            }
            else if(a.at(i)>max_broj){
                max_broj=a.at(i);
                cifre_max_broja=log10(max_broj)+1;
            }
        }
    }

    for(int i=0;i<cifre_max_broja;i++){
        if(i==0) cifre.resize(10);
        for(int j=0;j<cifre.size();j++) cifre.at(j).resize(0);
        for(int j=0;j<a.size();j++) cifre.at((a.at(j)/k)%10).push_back(a.at(j));
        a.resize(0);
        int br=0;
        for(int i=0;i<cifre.size();i++){
            a.resize(a.size()+cifre.at(i).size());
            for(int j=0;j<cifre.at(i).size();j++){
                a.at(br)=cifre.at(i).at(j); br++;
            }
        }
        k*=10;
    }
}

void popravi(vector<int> &a, int i, int v){
    int lijevo,desno;
    while(!(i<v && i>=(v/2))){
        lijevo=2*i+1;
        desno=2*i+2;
        if(desno<v && a.at(desno)>a.at(lijevo)) lijevo=desno;
        if(a.at(i)>a.at(lijevo)) break;
        int pom=i; i=lijevo;
        int pomocni_clan=a.at(pom);
        a.at(pom)=a.at(i);
        a.at(i)=pomocni_clan;
    }
}

void stvoriGomilu(vector<int> &a){
    for(int i=a.size()/2;i>=0;i--){
        popravi(a,i,a.size());
    }
}

void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
    if(velicina<=a.size()){
        a.push_back(umetnuti);
        int pom_vel=velicina;
        velicina++;
        while((pom_vel)!=0 && a.at((pom_vel-1)/2)<a.at(pom_vel)){
            int pomocni_clan=a.at(pom_vel);
            a.at(pom_vel)=a.at((pom_vel-1)/2);
            a.at((pom_vel-1)/2)=pomocni_clan;
            pom_vel=(pom_vel-1)/2;
        }
    }
}


int izbaciPrvi(vector<int> &a, int &velicina){
    if(a.size()!=0){
        velicina--;
        int pomocni_clan=a.at(0);
        a.at(0)=a.at(velicina);
        a.at(velicina)=pomocni_clan;
        if(velicina!=0) popravi(a,0,velicina);
    }
    return 0;
}

void gomilaSort(vector<int> &a){
    stvoriGomilu(a);
    int v,x;
    for(int i=0;i<a.size();i++){
        if(i==0) v=a.size();
        if(a.size()!=0){
            x=izbaciPrvi(a,v);
        }
    }
}

int main(){
    return 0;
}