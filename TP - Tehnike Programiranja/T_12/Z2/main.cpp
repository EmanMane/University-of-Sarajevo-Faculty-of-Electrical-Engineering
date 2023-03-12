/* 
    TP 16/17 (LV 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <set>

template<typename Tip>
std::set<Tip> operator +(std::set<Tip> set1,std::set<Tip> set2){
        std::set<Tip> novi;
        auto p=set1.begin();
        auto q=set2.begin();
        while(p!=set1.end() || q!=set2.end()){
            if(p!=set1.end()) novi.insert(*p);
            if(q!=set2.end()) novi.insert(*q);
            if(p!=set1.end()) p++; 
            if(q!=set2.end()) q++;
        }
        return novi;
}

template<typename Tip>
std::set<Tip> operator *(std::set<Tip> set1,std::set<Tip> set2){
    std::set<Tip> novi;
    auto p=set1.begin();
    auto q=set2.begin();
    while(p!=set1.end() && q!=set2.end()){
        if(*p==*q) novi.insert(*p);
        if(*p<*q) p++; 
        else if(*q<*p) q++;
        else{p++; q++;}
    }
    return novi;
}

template<typename Tip>
std::set<Tip> &operator +=(std::set<Tip> &set1,const std::set<Tip> &set2){
    set1=set1+set2;
    return set1;
}

template<typename Tip>
std::set<Tip> &operator *=(std::set<Tip> &set1,const std::set<Tip> &set2){
    set1=set1*set2;
    return set1;
}

template<typename Tip1,typename Tip2>
std::ostream &operator <<(std::ostream &tok,const std::pair<Tip1,Tip2> &par){
    return tok<<"("<<par.first<<","<<par.second<<")";
}

template<typename Tip>
std::ostream &operator <<(std::ostream &tok,const std::set<Tip> &s){
    tok<<"{";
    if(s.begin()!=s.end()){
        auto p=s.begin(), q=s.end();
        q--;
        while(p!=q){
            tok<<*p<<",";
            p++;
        }
        tok<<*q;
    }
    tok<<"}";
    return tok;
}

template<typename Tip1,typename Tip2>
std::set<std::pair<Tip1,Tip2>> operator %(std::set<Tip1> set1,std::set<Tip2> set2){
    auto p=set1.begin();
    auto q=set2.begin(),rstq=q;
    std::set<std::pair<Tip1,Tip2>> novi;
    while(p!=set1.end()){
        while(q!=set2.end()){
            std::pair<Tip1,Tip2> par={*p,*q};
            novi.insert(par);
            q++;
        }
        q=rstq;
        p++;
    }
    return novi;
}

int main ()
{
    std::set<int> s1{3, 5, 1, 2, 8}, s2{7, 2, 8, 4};
    std::cout << s1 + s2 << std::endl; // Ispis "{1,2,3,4,5,7,8}"
    std::cout << s1 * s2 << std::endl; // Ispis "{2,8}"
    std::set<char> s3{'A', 'B'};
    std::set<int> s4{1, 2, 3};
    std::cout << s3 % s4 << std::endl; // Ispis "{(A,1),(A,2),(A,3),(B,1),(B,2),(B,3)}"	return 0;
}