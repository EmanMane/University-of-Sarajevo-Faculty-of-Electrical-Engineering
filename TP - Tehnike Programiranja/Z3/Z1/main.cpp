//TP 2021/2022: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <utility>
#include <functional>
#include <string>
#include <algorithm>
#include <iomanip>

/*2 5
4 4
5 2
7 1*/



std::function<double(double)> BaricentricnaInterpolacija(std::vector<std::pair<double,double>> v, int d){
    int n=v.size();
    if(d<0 || d>n || v.size()==0) throw std::domain_error("Nedozvoljen red");
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(v[i].first==v[j].first) throw std::domain_error("Neispravni cvorovi");
        }
    }
    std::vector<double> w(n);
    for(int i=0;i<n;i++){
        std::vector<int> max={0,i-d},min={i,n-d-1};
        int d_gr=*max_element(max.begin(),max.end()),g_gr=*min_element(min.begin(),min.end());
        //std::cout<<"GGR="<<g_gr<<" DGR="<<d_gr<<std::endl;
        double S=0;
        for(int k=d_gr;k<=g_gr;k++){
            double jedinica_iz_sredine=std::pow(-1,k-1);
            double P=1;
            for(int j=k;j<=k+d;j++){
                if(j!=i){
                    P*=std::pow(v[i].first-v[j].first,-1);
                    //std::cout<<"P="<<P;
                }
            }
            S+=jedinica_iz_sredine*P;
        }
        w.at(i)=S;
        //std::cout<<"w.at("<<i<<")="<<w.at(i)<<std::endl;
    }
    std::function<double(double)> f=[w,d,v,n](double x)->double{
        double rezultat=0,brojnik=0,nazivnik=0;
        for(int i=0;i<n;i++){
            if(x==v[i].first) return v[i].second;
            brojnik+=(w.at(i)*v[i].second)/(x-v[i].first);
            nazivnik+=w.at(i)/(x-v[i].first);
            //std::cout<<"w.at(i)="<<w.at(i)<<std::endl;
        }
        //std::cout<<"brojnik="<<brojnik<<" nazivnik="<<nazivnik<<std::endl;
        rezultat=brojnik/nazivnik;
        return rezultat;
    };
    return f;
}

template<typename Tip>
std::function<double(double)> BaricentricnaInterpolacija(Tip funkcija, double x_min, double x_max, double delta_x, int d){
    if(x_min>x_max || delta_x<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double,double>> vektor_parova;
    while(x_min<=x_max){
        vektor_parova.push_back({x_min,funkcija(x_min)});
        x_min+=delta_x;
    }
    try{
        auto f = BaricentricnaInterpolacija(vektor_parova,d);
        return f;
    }
    catch(...){
        throw;
    }
}

int main ()
{
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    int x;
    std::cin>>x;
    if(x==1){
        std::cout<<"Unesite broj cvorova: ";
        int br_cvorova;
        std::cin>>br_cvorova;
        std::cout<<"Unesite cvorove kao parove x y: ";
        std::vector<std::pair<double,double>> vektor_parova;
        for(int i=0;i<br_cvorova;i++){
            std::pair<double,double> uneseni_par;
            std::cin>>uneseni_par.first;
            std::cin>>uneseni_par.second;
            vektor_parova.push_back(uneseni_par);
        }
        std::cout<<"Unesite red interpolacije: "; int d; std::cin>>d;
        try{
            auto f = BaricentricnaInterpolacija(vektor_parova,d);
            std::cin.ignore(10000,'\n');
            for(;;){
                std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                std::string unos;
                std::getline(std::cin,unos);
                try {
                    double argument=std::stod(unos);
                    try{
                        std::cout<<"f("<<argument<<") = "<<f(argument)<<std::endl;
                    }
                    catch(...){

                    }
                }
                catch(...){
                    return 0;
                }
            }
        }
        catch(std::domain_error error){
            std::cout<<error.what();
        }
    }
    else if(x==2){
        double x_min,x_max,delta_x;
        std::cout<<"Unesite krajeve intervala i korak: ";
        std::cin>>x_min;
        std::cin>>x_max;
        std::cin>>delta_x;
        std::cout<<"Unesite red interpolacije: "; int d; std::cin>>d;
        std::cin.ignore(10000,'\n');
        auto funkcija = [](double x){return x*x+std::sin(x);};
        try{
            auto f = BaricentricnaInterpolacija(funkcija,x_min,x_max,delta_x,d);
            for(;;){
                std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                std::string unos;
                std::getline(std::cin,unos);
                try {
                    double argument=std::stod(unos);
                    try{
                        std::cout<<"f("<<argument<<") = "<<funkcija(argument)<<" fapprox("<<argument<<") = "<<f(argument)<<std::endl;
                    }
                    catch(...){

                    }
                }
                catch(...){
                    return 0;
                }
            }
        }
        catch(std::domain_error error){
            std::cout<<error.what();
        }
    }
	return 0;
}