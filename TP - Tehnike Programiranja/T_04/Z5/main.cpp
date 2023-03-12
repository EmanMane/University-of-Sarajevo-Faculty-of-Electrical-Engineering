//TP 2021/2022: LV 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>

template <typename NekiTip>

NekiTip Presjek(NekiTip v1,NekiTip v2){
    NekiTip v3;
    for(int i=0;i<v1.size();i++){
        for(int j=0;j<v2.size();j++){
            if(v1.at(i)==v2.at(j)) v3.push_back(v2.at(j));
        }
    }
    for(int i=0;i<v3.size();i++){
        for(int j=i+1;j<v3.size();j++){
            if(v3.at(i)==v3.at(j)){ 
                v3.erase(v3.begin()+j);
                j--;
            }
        }
    }
    return v3;
}

int main ()
{
    std::cout<<"Test za realne brojeve..."<<std::endl;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite elemente prvog vektora: ";
    std::vector<double> v1;
    double a;
    for(int i=0;i<n;i++){
        std::cin>>a;
        v1.push_back(a);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>n;
    std::cout<<"Unesite elemente drugog vektora: ";
    std::vector<double> v2;
    for(int i=0;i<n;i++){
        std::cin>>a;
        v2.push_back(a);
    }
    std::vector<double> v3=Presjek(v1,v2);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0;i<v3.size();i++){
        std::cout<<v3.at(i)<<" ";
    }
    std::cout<<std::endl;
    std::vector<std::string> v4;
    std::cout<<"Test za stringove..."<<std::endl;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>n;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): "<<std::endl;
    for(int i=0;i<n+1;i++){
        std::string s;
        std::getline(std::cin,s);
        v4.push_back(s);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: "<<std::endl;
    std::cin>>n;
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    std::vector<std::string> v5;
    for(int i=0;i<n+1;i++){
        std::string s;
        std::getline(std::cin,s);
        v5.push_back(s);
    }
    std::vector<std::string> v6=Presjek(v4,v5);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0;i<v6.size();i++){
        std::cout<<v6.at(i)<<std::endl;
    }
	return 0;
}
