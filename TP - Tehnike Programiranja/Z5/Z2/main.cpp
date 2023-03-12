//TP 2021/2022: Zadaća 5, Zadatak 2
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <iterator>

class Berza{
    std::vector<int> cijene_dionica;
    int min_cijena,max_cijena;
    public:
    Berza(int min,int max){
        if(max<0 || min<0) throw std::range_error("Ilegalne granicne cijene");
        min_cijena=min; max_cijena=max;
    }
    Berza(int max){
        if(max<0) throw std::range_error("Ilegalne granicne cijene");
        min_cijena=0; max_cijena=max;
    }
    void RegistrirajCijenu(int cijena){
        if(cijena<min_cijena || cijena>max_cijena) throw std::range_error("Ilegalna cijena");
        cijene_dionica.push_back(cijena);
    }
    int DajBrojRegistriranihCijena() const{
        return cijene_dionica.size();
    }
    void BrisiSve(){
        cijene_dionica.clear();
    }
    int DajMinimalnuCijenu() const{
        if(cijene_dionica.size()==0) throw std::range_error("Nema registriranih cijena");
        return *std::min_element(cijene_dionica.begin(),cijene_dionica.end(),[](int x,int y){
            return x<y;
        });
    }
    int DajMaksimalnuCijenu() const{
        if(cijene_dionica.size()==0) throw std::range_error("Nema registriranih cijena");
        return *std::max_element(cijene_dionica.begin(),cijene_dionica.end(),[](int x,int y){
            return x<y;
        });
    }
    friend bool operator !(const Berza &x){
        if(x.cijene_dionica.size()==0) return true;
        return false;
    }
    int DajBrojCijenaVecihOd(int granica) const{
        if(cijene_dionica.size()==0) throw std::range_error("Nema registriranih cijena");
        return count_if(cijene_dionica.begin(),cijene_dionica.end(),std::bind(std::greater<int>(),std::placeholders::_1,granica)); //+1 jer bi onda ne broji granicnu vrijednost
    }
    void Ispisi() const;
    int operator[](int x) const;
    //prefiksna
    friend Berza &operator ++(Berza &x);
    //postfiksna
    friend Berza operator ++(Berza &x,int);
    //prefiksna
    friend Berza &operator --(Berza &x);
    //postfiksna
    friend Berza operator --(Berza &x,int);
    //prefiksna
    friend Berza &operator -(Berza &x);
    ///////////UPITNO STA SE POSTAVI ZA MAX I MIN CIJENU??? *****NAREDNA 4***
    friend Berza operator +(Berza &x,int y);
    friend Berza operator +(int y,Berza &x);
    friend Berza operator -(Berza &x,int y);
    friend Berza operator -(int y,Berza &x);
    friend Berza operator -(Berza &x,Berza &y);
    friend Berza operator +(Berza &x,Berza &y);
    friend Berza operator +=(Berza &x,Berza &y);
    friend Berza operator -=(Berza &x,Berza &y);
    friend bool operator ==(const Berza &x,const Berza &y);
    friend bool operator !=(const Berza &x,const Berza &y);
};

void Berza::Ispisi() const{
        std::vector<int> pom=cijene_dionica;
        std::sort(pom.begin(),pom.end(),std::greater<int>());
        std::transform(pom.begin(),pom.end(),
            std::ostream_iterator<double>(std::cout<<std::fixed<<std::setprecision(2),"\n"),
            std::bind(std::multiplies<double>(),std::placeholders::_1,0.01));
        //for(int i=0;i<pom.size();i++){
        //    double uKM=pom.at(i)*0.01;
        //    std::cout<<std::fixed<<std::setprecision(2)<<uKM<<std::endl;
        //}
    }
    int Berza::operator[](int x) const{
        if(x<1 || x>=cijene_dionica.size()) throw std::range_error("Neispravan indeks");
        int cijena=0;
        for(int i=0;i<cijene_dionica.size();i++)
            if(i+1==x){
                cijena=cijene_dionica.at(i);
            }
        return cijena;
    }
    //prefiksna
    Berza &operator ++(Berza &x){
        int vel=x.cijene_dionica.size();
        std::vector<int> pom=x.cijene_dionica,jedinicni(vel,100);
        std::transform(pom.begin(),pom.end(),jedinicni.begin(),pom.begin(),std::plus<int>());
        int error=0;
        error+=count_if(pom.begin(),pom.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(pom.begin(),pom.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::range_error("Prekoracen dozvoljeni opseg cijena");}
        x.cijene_dionica=pom;
        return x;
    }
    //postfiksna
    Berza operator ++(Berza &x,int){
        auto pom(x);
        ++x;
        return pom;
    }
    //prefiksna
    Berza &operator --(Berza &x){
        int vel=x.cijene_dionica.size();
        std::vector<int> pom=x.cijene_dionica,jedinicni(vel,100);
        std::transform(pom.begin(),pom.end(),jedinicni.begin(),pom.begin(),std::minus<int>());
        int error=0;
        error+=count_if(pom.begin(),pom.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(pom.begin(),pom.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::range_error("Prekoracen dozvoljeni opseg cijena");}
        x.cijene_dionica=pom;
        return x;
    }
    //postfiksna
    Berza operator --(Berza &x,int){
        auto pom(x);
        --x;
        return pom;
    }
    //prefiksna
    Berza &operator -(Berza &x){
        int vel=x.cijene_dionica.size(),zbir=x.max_cijena-x.min_cijena;
        std::vector<int> pom=x.cijene_dionica,novi(vel,zbir);
        std::transform(novi.begin(),novi.end(),pom.begin(),novi.begin(),std::minus<int>());
        x.cijene_dionica=novi;
        return x;
    }
    ///////////UPITNO STA SE POSTAVI ZA MAX I MIN CIJENU??? *****NAREDNA 4***
    Berza operator +(Berza &x,int y){
        Berza novi=x;
        int vel=x.cijene_dionica.size();
        std::vector<int> pom=x.cijene_dionica,jedinicni(vel,y);
        std::transform(pom.begin(),pom.end(),jedinicni.begin(),pom.begin(),std::plus<int>());
        int error=0;
        error+=count_if(pom.begin(),pom.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(pom.begin(),pom.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::domain_error("Prekoracen dozvoljeni opseg cijena");}
        novi.cijene_dionica=pom;
        return novi;
    }
    Berza operator +(int y,Berza &x){
        Berza novi=x;
        int vel=x.cijene_dionica.size();
        std::vector<int> pom=x.cijene_dionica,jedinicni(vel,y);
        std::transform(pom.begin(),pom.end(),jedinicni.begin(),pom.begin(),std::plus<int>());
        int error=0;
        error+=count_if(pom.begin(),pom.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(pom.begin(),pom.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::domain_error("Prekoracen dozvoljeni opseg cijena");}
        novi.cijene_dionica=pom;
        return novi;
    }
    Berza operator -(Berza &x,int y){
        Berza novi=x;
        int vel=x.cijene_dionica.size();
        std::vector<int> pom=x.cijene_dionica,jedinicni(vel,y);
        std::transform(pom.begin(),pom.end(),jedinicni.begin(),pom.begin(),std::minus<int>());
        int error=0;
        error+=count_if(pom.begin(),pom.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(pom.begin(),pom.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::domain_error("Prekoracen dozvoljeni opseg cijena");}
        novi.cijene_dionica=pom;
        return novi;
    }
    Berza operator -(int y,Berza &x){
        Berza novi=x;
        int vel=x.cijene_dionica.size();
        std::vector<int> pom=x.cijene_dionica,jedinicni(vel,y);
        std::transform(jedinicni.begin(),jedinicni.end(),pom.begin(),pom.begin(),std::minus<int>());
        int error=0;
        error+=count_if(pom.begin(),pom.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(pom.begin(),pom.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::domain_error("Prekoracen dozvoljeni opseg cijena");}
        novi.cijene_dionica=pom;
        return novi;
    }
    Berza operator -(Berza &x,Berza &y){
        if(x.cijene_dionica.size()!=y.cijene_dionica.size() || x.min_cijena!=y.min_cijena || x.max_cijena!=y.max_cijena) throw std::domain_error("Nesaglasni operandi");
        Berza novi=x;
        std::vector<int> pom1=x.cijene_dionica,pom2=y.cijene_dionica;
        std::transform(pom1.begin(),pom1.end(),pom2.begin(),novi.cijene_dionica.begin(),std::minus<int>());
        int error=0;
        error+=count_if(novi.cijene_dionica.begin(),novi.cijene_dionica.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(novi.cijene_dionica.begin(),novi.cijene_dionica.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::domain_error("Prekoracen dozvoljeni opseg cijena");}
        return novi;
    }
    Berza operator +(Berza &x,Berza &y){
        if(x.cijene_dionica.size()!=y.cijene_dionica.size() || x.min_cijena!=y.min_cijena || x.max_cijena!=y.max_cijena) throw std::domain_error("Nesaglasni operandi");
        Berza novi=x;
        std::vector<int> pom1=x.cijene_dionica,pom2=y.cijene_dionica;
        std::transform(pom1.begin(),pom1.end(),pom2.begin(),novi.cijene_dionica.begin(),std::plus<int>());
        int error=0;
        error+=count_if(novi.cijene_dionica.begin(),novi.cijene_dionica.end(),std::bind(std::less<int>(),std::placeholders::_1,x.min_cijena));
        error+=count_if(novi.cijene_dionica.begin(),novi.cijene_dionica.end(),std::bind(std::greater<int>(),std::placeholders::_1,x.max_cijena));
        if(error>0){throw std::domain_error("Prekoracen dozvoljeni opseg cijena");}
        return novi;
    }
    Berza operator +=(Berza &x,Berza &y){
        x=x+y;
        return x;
    }
    Berza operator +=(Berza &x,int y){
        x=x+y;
        return x;
    }
    Berza operator -=(Berza &x,Berza &y){
        x=x-y;
        return x;
    }
    Berza operator -=(Berza &x,int y){
        x=x-y;
        return x;
    }
    bool operator ==(const Berza &x,const Berza &y){
        if(x.cijene_dionica!=y.cijene_dionica) return false;
        return true;
    }
    bool operator !=(const Berza &x,const Berza &y){
        if(x==y) return false;
        return true;
    }

int main ()
{
    Berza b(100,1000);
    Berza b2(100,1000);
    b.RegistrirajCijenu(100);
    b.RegistrirajCijenu(200);
    b.RegistrirajCijenu(300);
    b.RegistrirajCijenu(400);
    b.RegistrirajCijenu(500);
    b++;
    b.Ispisi();
    std::cout<<"-------------\n";
    b--;
    b.Ispisi();
    std::cout<<"-------------\n";
    -b;
    b.Ispisi();
    std::cout<<"-------------\n";
    b-=5;
    b.Ispisi();
    std::cout<<"-------------\n";
    b+=9;
    b.Ispisi();
    std::cout<<"-------------\n";
    if(b==b2) std::cout<<"Iste\n";//Ne ispisuje nista, OK
    std::cout<<"-------------\n";
    b.BrisiSve();
    if(!b)  std::cout<<"Loše\n";
    std::cout<<"-------------\n";
	return 0;
}
