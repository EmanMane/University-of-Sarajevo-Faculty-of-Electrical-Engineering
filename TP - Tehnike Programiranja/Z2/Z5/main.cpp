//TP 2021/2022: Zadaća 2, Zadatak 5
#include <iostream>
#include <vector>
#include <deque>
#include <functional>


auto funkcija(double x, double y)->decltype(x+y){
    return x+2*y;
}

template<typename Tip1,typename Tip2,typename FunTip> 
auto GeneraliziraniSpoljasnjiProizvod(Tip1 poc1, Tip1 kraj1, Tip2 poc2, Tip2 kraj2,FunTip fun)->decltype(fun(*poc1,*poc2))**{
    decltype(fun(*poc1,*poc2)) **m=nullptr;
    int brredova=0,brkolona=0;
    Tip1 rstpoc1=poc1;
    Tip2 rstpoc2=poc2;
    while(poc1!=kraj1){
        poc1++; brredova++;
    }poc1=rstpoc1;
    while(poc2!=kraj2){
        poc2++; brkolona++;
    }poc2=rstpoc2;
    try{
        m=new decltype(fun(*poc1,*poc2)) *[brredova];
        for(int i=0;i<brredova;i++) m[i]=nullptr;
        try{
            for(int i=0;i<brredova;i++) m[i]=new decltype(fun(*poc1,*poc2)) [brkolona];
        }
        catch(...){
            for(int i=0;i<brredova;i++) delete[] m[i];
            delete[] m;
            throw;
        }
        for(int i=0;i<brredova;i++){
            poc2=rstpoc2;
            for(int j=0;j<brkolona;j++){
                m[i][j]=fun(*poc1,*poc2);
                poc2++;
            }
            poc1++;
        }
    }
    catch(...){throw std::range_error("Nema dovoljno memorije!");}
    return m;
}

int main ()
{
    try{
        std::cout<<"Duzina prve sekvence: "; int n1; std::cin>>n1;
        std::cout<<"Elementi prve sekvence: "; std::vector<double> v(n1); for(int i=0;i<n1;i++){double clan; std::cin>>clan; v.at(i)=clan;}
        std::cout<<"Duzina druge sekvence: "; int n2; std::cin>>n2;
        std::cout<<"Elementi druge sekvence: "; std::deque<double> d(n2); for(int i=0;i<n2;i++){double clan; std::cin>>clan; d.at(i)=clan;}
        double **Matrica=GeneraliziraniSpoljasnjiProizvod(std::begin(v),std::end(v),std::begin(d),std::end(d),funkcija);
        std::cout<<"Generalizirani spoljasnji proizvod uz f(x,y)=x+2y:"<<std::endl;
        for(int i=0;i<n1;i++){
            for(int j=0;j<n2;j++){
                std::cout<<Matrica[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        for(int i=0;i<n1;i++) delete[] Matrica[i];
        delete[] Matrica;
    }
    catch(std::range_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}
