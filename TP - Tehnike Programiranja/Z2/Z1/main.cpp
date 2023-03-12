//TP 2021/2022: Zadaća 2, Zadatak 1
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>
#include <stdexcept>
bool aktivan=true;
enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class Smjer {Nalijevo, Nadesno};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};
void AktivirajRobota(){/////////////////////////////////////////////////////////////////////////////////////////////////////
    aktivan=true;
}
void DeaktivirajRobota(){///////////////////////////////////////////////////////////////////////////////////////////////////
    aktivan=false;
}
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu){///////////////////////////////////////////////////////////////////
    if(na_koju_stranu==Smjer::Nalijevo && aktivan){
        if(orijentacija==Pravci::Sjever) orijentacija=Pravci::Sjeverozapad;
        else if(orijentacija==Pravci::Sjeveroistok) orijentacija=Pravci::Sjever;
        else if(orijentacija==Pravci::Istok) orijentacija=Pravci::Sjeveroistok;
        else if(orijentacija==Pravci::Jugoistok) orijentacija=Pravci::Istok;
        else if(orijentacija==Pravci::Jug) orijentacija=Pravci::Jugoistok;
        else if(orijentacija==Pravci::Jugozapad) orijentacija=Pravci::Jug;
        else if(orijentacija==Pravci::Zapad) orijentacija=Pravci::Jugozapad;
        else if(orijentacija==Pravci::Sjeverozapad) orijentacija=Pravci::Zapad;
    }
    else if(aktivan){
        if(orijentacija==Pravci::Sjever) orijentacija=Pravci::Sjeveroistok;
        else if(orijentacija==Pravci::Sjeveroistok) orijentacija=Pravci::Istok;
        else if(orijentacija==Pravci::Istok) orijentacija=Pravci::Jugoistok;
        else if(orijentacija==Pravci::Jugoistok) orijentacija=Pravci::Jug;
        else if(orijentacija==Pravci::Jug) orijentacija=Pravci::Jugozapad;
        else if(orijentacija==Pravci::Jugozapad) orijentacija=Pravci::Zapad;
        else if(orijentacija==Pravci::Zapad) orijentacija=Pravci::Sjeverozapad;
        else if(orijentacija==Pravci::Sjeverozapad) orijentacija=Pravci::Sjever;
    }
}
void Idi(int &x, int &y, Pravci orijentacija, int korak){///////////////////////////////////////////////////////////////////
    bool maxy=false,maxx=false,minx=false,miny=false;
    long long int pomocna=0;
    if(aktivan){
        pomocna=korak; pomocna+=y;
        if(pomocna>=std::numeric_limits<int>::max()) {maxy=true;}
        if(pomocna<=std::numeric_limits<int>::min()) miny=true;
        pomocna=korak; pomocna+=x;
        if(pomocna<=std::numeric_limits<int>::min()) minx=true;
        if(pomocna>=std::numeric_limits<int>::max()) {maxx=true;}
        if(orijentacija==Pravci::Sjever){
            if(miny==false && maxy==false) y+=korak; 
            else if(miny==true) y=std::numeric_limits<int>::min(); 
            else y=std::numeric_limits<int>::max();
        }
        else if(orijentacija==Pravci::Sjeveroistok){
            if(miny==false && maxy==false && minx==false && maxx==false){
                x+=korak; y+=korak; 
            } 
            if(miny==true) y=std::numeric_limits<int>::min(); 
            if(maxy==true) y=std::numeric_limits<int>::max(); 
            if(minx==true) x=std::numeric_limits<int>::min(); 
            if(maxx==true) x=std::numeric_limits<int>::max(); 
        }
        else if(orijentacija==Pravci::Istok){
            if(minx==false && maxx==false) x+=korak; 
            else if(minx==true) x=std::numeric_limits<int>::min(); 
            else x=std::numeric_limits<int>::max();
        }
        else if(orijentacija==Pravci::Jugoistok){
            if(miny==false && maxy==false && minx==false && maxx==false){
                x+=korak; y-=korak; 
            } 
            if(miny==true) y=std::numeric_limits<int>::min(); 
            if(maxy==true) y=std::numeric_limits<int>::max(); 
            if(minx==true) x=std::numeric_limits<int>::min(); 
            if(maxx==true) x=std::numeric_limits<int>::max(); 
        }
        else if(orijentacija==Pravci::Jug){
            if(miny==false && maxy==false) y-=korak; 
            else if(miny==true) y=std::numeric_limits<int>::min(); 
            else y=std::numeric_limits<int>::max();
        }
        else if(orijentacija==Pravci::Jugozapad){
            if(miny==false && maxy==false && minx==false && maxx==false){
                x-=korak; y-=korak; 
            } 
            if(miny==true) y=std::numeric_limits<int>::min(); 
            if(maxy==true) y=std::numeric_limits<int>::max(); 
            if(minx==true) x=std::numeric_limits<int>::min(); 
            if(maxx==true) x=std::numeric_limits<int>::max(); 
        }
        else if(orijentacija==Pravci::Zapad){
            if(miny==false && maxy==false) x-=korak; 
            else if(miny==true) y=std::numeric_limits<int>::min(); 
            else y=std::numeric_limits<int>::max();
        }
        else if(orijentacija==Pravci::Sjeverozapad){
            if(miny==false && maxy==false && minx==false && maxx==false){
                x-=korak; y+=korak; 
            } 
            if(miny==true) y=std::numeric_limits<int>::min(); 
            if(maxy==true) y=std::numeric_limits<int>::max(); 
            if(minx==true) x=std::numeric_limits<int>::min(); 
            if(maxx==true) x=std::numeric_limits<int>::max(); 
        }
    }
}
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske){//////////////////////////////////////////////
    bool L=false,D=false,I=false,K=false;
    int i=1, minus=1, broj=0;;
    char c;
    do{
        c=getchar();
        if(I==true && c=='\n'){kod_greske=KodoviGresaka::NedostajeParametar; return false;}
        if(c=='\n'){
            break;
        } 
        if(c==' '){}
        else if(i==1){
            if(c=='\n') break;
            if(c!='A' && c!='L' && c!='D' && c!='I' && c!='K'){
                kod_greske=KodoviGresaka::PogresnaKomanda;
                std::cin.ignore(10000,'\n');
                std::cin.clear();
                return false;
            }
            if(c=='L') L=true;
            if(c=='D') D=true; 
            if(c=='K') K=true;
            if(c=='A'){
                do{
                    c=getchar();
                    if(c=='\n'){
                        kod_greske=KodoviGresaka::NeispravanParametar;
                        return false;
                    }
                    if(c!='+' && c!='-'){
                        kod_greske=KodoviGresaka::NeispravanParametar;
                        std::cin.ignore(10000,'\n');
                        std::cin.clear();
                        return false;
                    }
                }while(c==' ');
                if(c=='+'){komanda=Komande::Aktiviraj;}
                if(c=='-'){komanda=Komande::Deaktiviraj;}
            }
            if(c=='I') I=true;
            i++;
        }
        else{
            if(I!=true) { //za dodatni parametar
                kod_greske=KodoviGresaka::SuvisanParametar; 
                std::cin.ignore(10000,'\n');
                std::cin.clear();
                return false;
            }
            if(c!='-' && (c>'9' || c<'0') && (I=true)){ //za neispravan parametar
                kod_greske=KodoviGresaka::NeispravanParametar;
                std::cin.ignore(10000,'\n');
                std::cin.clear();
                return false;
                }
            
            if(c=='-'){minus=-1;}
            else broj=c-48;
            do{ //unos broja, cifra po cifra
                c=getchar();
                if(c=='\n') break;
                if(c>'9' || c<'0'){ //Greska
                    kod_greske=KodoviGresaka::NeispravanParametar;
                    std::cin.ignore(10000,'\n');
                    std::cin.clear();
                    return false;
                }
                if(minus==-1 && broj!=0){ //Minus
                    minus=1; broj*=minus;
                }
                long long int kopija=broj; kopija*=10;
                if(kopija>std::numeric_limits<int>::max()){broj=std::numeric_limits<int>::max(); std::cin.ignore(10000,'\n'); std::cin.clear(); goto dalje;}
                if(kopija<std::numeric_limits<int>::min()){broj=std::numeric_limits<int>::min(); std::cin.ignore(10000,'\n'); std::cin.clear(); goto dalje;} 
                broj*=10;
                kopija+=c-48;
                if(kopija>std::numeric_limits<int>::max()){broj=std::numeric_limits<int>::max(); std::cin.ignore(10000,'\n'); std::cin.clear(); goto dalje;} 
                if(kopija<std::numeric_limits<int>::min()){broj=std::numeric_limits<int>::min(); std::cin.ignore(10000,'\n'); std::cin.clear(); goto dalje;} 
                if(broj>0) broj+=c-48;
                else broj-=c-48;
            }while(c!='\n');
        }
    }while(c!='\n');
    dalje:;
    if(L==true) komanda=Komande::Nalijevo;
    if(D==true) komanda=Komande::Nadesno;
    if(K==true) komanda=Komande::Kraj;
    if(I==true) {komanda=Komande::Idi; parametar=broj;}    
    return true;
}
void IspisiPoziciju(int x, int y, Pravci orijentacija){/////////////////////////////////////////////////////////////////////
    if(aktivan==true){
        if(orijentacija==Pravci::Sjever) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever."<<std::endl;
        if(orijentacija==Pravci::Sjeveroistok) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjeveroistok."<<std::endl;
        if(orijentacija==Pravci::Istok) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na istok."<<std::endl;
        if(orijentacija==Pravci::Jugoistok) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jugoistok."<<std::endl;
        if(orijentacija==Pravci::Jug) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jug."<<std::endl;
        if(orijentacija==Pravci::Jugozapad) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jugozapad."<<std::endl;
        if(orijentacija==Pravci::Zapad) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na zapad."<<std::endl;
        if(orijentacija==Pravci::Sjeverozapad) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjeverozapad."<<std::endl;
    }
    else{
        if(orijentacija==Pravci::Sjever) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever."<<std::endl;
        if(orijentacija==Pravci::Sjeveroistok) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjeveroistok."<<std::endl;
        if(orijentacija==Pravci::Istok) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na istok."<<std::endl;
        if(orijentacija==Pravci::Jugoistok) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jugoistok."<<std::endl;
        if(orijentacija==Pravci::Jug) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jug."<<std::endl;
        if(orijentacija==Pravci::Jugozapad) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jugozapad."<<std::endl;
        if(orijentacija==Pravci::Zapad) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na zapad."<<std::endl;
        if(orijentacija==Pravci::Sjeverozapad) std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjeverozapad."<<std::endl;
    }
}
void PrijaviGresku(KodoviGresaka kod_greske){///////////////////////////////////////////////////////////////////////////////
    if(kod_greske==KodoviGresaka::PogresnaKomanda) std::cout<<"Nerazumljiva komanda!"<<std::endl;
    if(kod_greske==KodoviGresaka::NedostajeParametar) std::cout<<"Komanda trazi parametar koji nije naveden!"<<std::endl;
    if(kod_greske==KodoviGresaka::SuvisanParametar) std::cout<<"Zadan je suvisan parametar nakon komande!"<<std::endl;
    if(kod_greske==KodoviGresaka::NeispravanParametar) std::cout<<"Parametar komande nije ispravan!"<<std::endl;
}
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija){///////////////////////////////////
    if(komanda==Komande::Kraj) goto ende;
    if(komanda==Komande::Aktiviraj) AktivirajRobota();
    if(komanda==Komande::Deaktiviraj) DeaktivirajRobota();
    if(komanda==Komande::Nalijevo) Rotiraj(orijentacija,Smjer::Nalijevo);
    if(komanda==Komande::Nadesno) Rotiraj(orijentacija,Smjer::Nadesno);
    if(komanda==Komande::Idi) Idi(x,y,orijentacija,parametar); 
    ende:;
}

int main (){
    int x=0,y=0,parametar;
    Pravci orijentacija=Pravci::Sjever; 
    Komande komanda=Komande::Aktiviraj; 
    KodoviGresaka kod_greske;
    bool Unos;
    for(;;){
        IspisiPoziciju(x,y,orijentacija);
        ponoviunos:
        std::cout<<"Unesi komandu: "<<std::endl;
        Unos=UnosKomande(komanda,parametar,kod_greske);
        if(Unos==true) IzvrsiKomandu(komanda, parametar,x,y,orijentacija);
        else {
            PrijaviGresku(kod_greske);
            goto ponoviunos;
        }
        if(komanda==Komande::Kraj) break;
    }
    std::cout<<"Dovidjenja!";
    return 0;
}