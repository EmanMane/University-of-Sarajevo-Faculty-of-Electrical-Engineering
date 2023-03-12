//TP 2021/2022: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <limits>
#include <sstream>

long long int m=std::numeric_limits<long long int>::min();
long long int M=std::numeric_limits<long long int>::max();
long double E=1e-10;

class Razlomak{
    long long int brojnik,nazivnik;
    static long long int NZD(long long int p, long long int q){
        while(q!=0){
            long long int mod=p%q;
            p=q; q=mod;
        }
        return p;
    }
    static bool ProvjeriMnozenje(long long int x, long long int y){
        if(y>0){
            if(x<m/y || x>M/y) return true;
        }
        if(y==-1){ if(x==m) return true;}
        else if(y<0){
            if(x==m || -x>M/(-y) || -x<m/(-y)) return true;
        }
        return false;
    }
    static bool ProvjeriSabiranje(long long int x, long long y){
        if(y>0){
            if(x>M-y) return true;
        }
        if(y<0){
            if(x<m-y) return true;
        }
        return false;
    }
    static bool ProvjeriOduzimanje(long long int x, long long y){
        if(y>0){
            if(x>M-y) return true;
        }
        if(y<0){
            if(x<m-y) return true;
        }
        return false;
    }
    public:
    Razlomak(long long int brojnik,long long int nazivnik);
    Razlomak(long long int brojnik):brojnik(brojnik),nazivnik(1){}
    Razlomak():brojnik(0),nazivnik(1){}
    long long int DajBrojnik() const{
        return brojnik;
    }
    long long int DajNazivnik() const{
        return nazivnik;
    }
    long double DajDecimalni() const{
        long double decimala=brojnik;
        decimala/=nazivnik;
        return decimala;
    }
    friend std::ostream &operator <<(std::ostream &tok, const Razlomak &x);
    friend std::istream &operator >>(std::istream &tok, Razlomak &x);
    friend Razlomak operator+(const Razlomak &x,const Razlomak &y);
    friend Razlomak operator-(const Razlomak &x,const Razlomak &y);
    friend Razlomak operator*(const Razlomak &x,const Razlomak &y);
    friend Razlomak operator/(const Razlomak &x,const Razlomak &y);
    friend Razlomak operator-(const Razlomak &x){
        if(ProvjeriMnozenje(x.brojnik,-1)) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
        return {-x.brojnik,x.nazivnik};
    }
    friend Razlomak operator+(const Razlomak &x){
        return x;
    }
    friend Razlomak &operator+=(Razlomak &x,const Razlomak &y){
        x=x+y;
        return x;
    }
    friend Razlomak &operator-=(Razlomak &x,const Razlomak &y){
        x=x-y;
        return x;
    }
    friend Razlomak &operator*=(Razlomak &x,const Razlomak &y){
        x=x*y;
        return x;
    }
    friend Razlomak &operator/=(Razlomak &x,const Razlomak &y){
        x=x/y;
        return x;
    }
    friend Razlomak &operator++(Razlomak &x){
        Razlomak jedan(1,1);
        x=x+jedan;
        return x;
    }
    friend Razlomak &operator--(Razlomak &x){
        Razlomak jedan(1,1);
        x=x-jedan;
        return x;
    }
    friend Razlomak operator++(Razlomak &x,int){
        auto pom(x);
        Razlomak jedan(1,1);
        x=x+jedan;
        return pom;
    }
    friend Razlomak operator--(Razlomak &x,int){
        auto pom(x);
        Razlomak jedan(1,1);
        x=x-jedan;
        return pom;
    }
    friend bool operator<(const Razlomak &x,const Razlomak &y){
        long double decimalni1=x.DajDecimalni(),decimalni2=y.DajDecimalni();
        if(decimalni1<decimalni2) return true;
        return false;
    }
    friend bool operator>(const Razlomak &x,const Razlomak &y){
        long double decimalni1=x.DajDecimalni(),decimalni2=y.DajDecimalni();
        if(decimalni1>decimalni2) return true;
        return false;
    }
    friend bool operator==(const Razlomak &x,const Razlomak &y){
        long double decimalni1=x.DajDecimalni(),decimalni2=y.DajDecimalni();
        if(std::fabs(decimalni1-decimalni2)<E) return true;
        return false;
    }
    friend bool operator<=(const Razlomak &x,const Razlomak &y){
        if(x<y || x==y) return true;
        return false;
    }
    friend bool operator>=(const Razlomak &x,const Razlomak &y){
        if(x>y || x==y) return true;
        return false;
    }
    friend bool operator!=(const Razlomak &x,const Razlomak &y){
        if(x==y) return false;
        return true;
    }
    operator long double() const{
        long double b=brojnik,n=nazivnik;
        long double x=b/n;
        return x;
    }
};

Razlomak::Razlomak(long long int brojnik,long long int nazivnik){
    if(nazivnik==0) throw std::logic_error("Nekorektan razlomak");
    long long int nzd=NZD(brojnik,nazivnik);
    brojnik/=nzd;
    nazivnik/=nzd;
    if(nazivnik<0){ 
        brojnik*=-1;
        nazivnik*=-1;
    }
    Razlomak::brojnik=brojnik;
    Razlomak::nazivnik=nazivnik;
}
std::ostream &operator <<(std::ostream &tok, const Razlomak &x){
    if(x.nazivnik!=1) tok<<x.brojnik<<"/"<<x.nazivnik;
    else tok<<x.brojnik;
    return tok;
}
std::istream &operator >>(std::istream &tok, Razlomak &x){
    char znak{};
    long long int brojnik{},nazivnik=1;
    tok>>std::ws;
    if(isdigit(tok.peek())==false && tok.peek()!='-') tok.setstate(std::ios::failbit);
    else{
        tok>>brojnik;
        if(tok.peek()!='/'){ 
            if(tok.peek()==' ' || 
            tok.peek()=='\n' ||
            tok.peek()=='\r' ||
            tok.peek()=='\f' ||
            tok.peek()=='\v' ||
            tok.peek()=='\t' ||
            tok.peek()==EOF) nazivnik=1;
            else tok.setstate(std::ios::failbit);
        }
        else{
            tok>>znak>>nazivnik;
            if(znak!='/' || (tok.peek()!=' ' && 
            tok.peek()!='\n' &&
            tok.peek()!='\r' &&
            tok.peek()!='\f' &&
            tok.peek()!='\v' &&
            tok.peek()!='\t' &&
            tok.peek()!=EOF)) tok.setstate(std::ios::failbit);
            //std::cout<<"tok.peek je "<<tok.peek()<<"\n";
        }
    }
    //if(!tok.fail()){//on ovdje ipak radi sa nekim vrijednostima, UPITNO!
        long long int nzd=Razlomak::NZD(brojnik,nazivnik);
        x.brojnik=brojnik/nzd; x.nazivnik=nazivnik/nzd;
    //}
    return tok;
}
Razlomak operator+(const Razlomak &x,const Razlomak &y){
    long long int r=Razlomak::NZD(x.nazivnik,y.nazivnik),brojnik,nazivnik;
    if(Razlomak::ProvjeriMnozenje(x.brojnik,y.nazivnik/r) || Razlomak::ProvjeriMnozenje(y.brojnik,x.nazivnik/r)
    || Razlomak::ProvjeriSabiranje(x.brojnik*(y.nazivnik/r),y.brojnik*(x.nazivnik/r))
    || Razlomak::ProvjeriMnozenje(x.nazivnik,y.nazivnik/r)) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    brojnik=x.brojnik*(y.nazivnik/r)+y.brojnik*(x.nazivnik/r);
    nazivnik=x.nazivnik*(y.nazivnik/r);
    Razlomak z(brojnik,nazivnik);
    return z;
}
Razlomak operator-(const Razlomak &x,const Razlomak &y){
    long long int r=Razlomak::NZD(x.nazivnik,y.nazivnik),brojnik,nazivnik;
    if(Razlomak::ProvjeriMnozenje(x.brojnik,y.nazivnik/r) || Razlomak::ProvjeriMnozenje(y.brojnik,x.nazivnik/r)
    || Razlomak::ProvjeriOduzimanje(x.brojnik*(y.nazivnik/r),y.brojnik*(x.nazivnik/r))
    || Razlomak::ProvjeriMnozenje(x.nazivnik,y.nazivnik/r)) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    brojnik=x.brojnik*(y.nazivnik/r)-y.brojnik*(x.nazivnik/r);
    nazivnik=x.nazivnik*(y.nazivnik/r);
    Razlomak z(brojnik,nazivnik);
    return z;
}
Razlomak operator*(const Razlomak &x,const Razlomak &y){
    long long int s=Razlomak::NZD(x.brojnik,y.nazivnik),t=Razlomak::NZD(y.brojnik,x.nazivnik),brojnik,nazivnik;
    if(Razlomak::ProvjeriMnozenje(x.brojnik/s,y.brojnik/t) || Razlomak::ProvjeriMnozenje(x.nazivnik/t,y.nazivnik/s)) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    brojnik=(x.brojnik/s)*(y.brojnik/t);
    nazivnik=(x.nazivnik/t)*(y.nazivnik/s);
    Razlomak z(brojnik,nazivnik);
    return z;
}
Razlomak operator/(const Razlomak &x,const Razlomak &y){
    long long int r=Razlomak::NZD(x.nazivnik,y.nazivnik),u=Razlomak::NZD(x.brojnik,y.brojnik),brojnik,nazivnik;
    if(Razlomak::ProvjeriMnozenje(x.brojnik/u,y.nazivnik/r) || Razlomak::ProvjeriMnozenje(x.nazivnik/r,y.brojnik/u)) throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    brojnik=(x.brojnik/u)*(y.nazivnik/r);
    nazivnik=(x.nazivnik/r)*(y.brojnik/u);
    Razlomak z(brojnik,nazivnik);
    return z;
}

int main ()
{
    Razlomak r1(1,2); Razlomak r2(2,3);  Razlomak r3;
    Razlomak r5(5);
    std::cout<<"Prvi: "<<r1.DajBrojnik()<<"/"<<r1.DajNazivnik()<<"="<<r1.DajDecimalni()<<std::endl;
    std::cout<<"Drugi: "<<r2.DajBrojnik()<<"/"<<r2.DajNazivnik()<<"="<<r2.DajDecimalni()<<std::endl;
    std::cout<<"prvi>drugi--->";if(r1>r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"prvi<drugi--->";if(r1<r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"prvi==drugi--->";if(r1==r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"prvi!=drugi--->";if(r1!=r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"prvi+drugi--->"; r3=r1+r2; std::cout<<r3<<std::endl;
    std::cout<<"prvi-=drugi--->"; r1-=r2; std::cout<<r1<<std::endl;
    std::cout<<"(prvi++)--->"; r1++; std::cout<<r1<<std::endl;
    std::cout<<"prvi*=drugi--->"; r1*=r2; std::cout<<r1<<std::endl;
    r1++; ++r1; long double decimalno=static_cast<long double>(r1);
	return 0;
}
