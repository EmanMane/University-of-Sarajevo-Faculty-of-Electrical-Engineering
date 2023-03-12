/*
ZADATAK4

Razviti klasu StampacServer koja obavlja funkciju servera za štampanje u jednoj kompaniji.
Klasa implementira funkciju void posaljiDokument(Prioritet p, string sadrzaj).
Prioritet je tip enum {Sef, Radnik, Pripravnik}. Ovaj enum se treba nalaziti u javnom
interfejsu klase. Sadržaj dokumenta za printanje je pojednostavljeno samo tekst - pa je tipa string.
Ova funkcija treba da prihvati dokument sa odgovarajućim prioritetom i pohrani ga za kasnije
štampanje.

Osim toga, ova klasa treba da implementira funkciju string dajDokument() koja od
dokumenata koji su poslati za štampanje vraća neodštampani dokument sa najvišim prioritetom, a
ako ima više dokumenata sa istim prioritetom, onda najstariji. Logično, najviši prioriet je Sef, a
zatim Radnik i najniži Pripravnik. Ako ne postoji niti jedan neodštampani dokument, treba
vratiti prazan string.

Klasa bi trebala biti korištena tako što će driver za štampače na računarima uposlenika pozivati
funkciju posaljiDokuement, a štampači čim završe sa prethodnim dokumentom, pozivati
funkciju dajDokument. Ovakvo ponašanje treba simulirati u main programu.
*/

#include<iostream>
#include<string>
#include<queue>

enum Prioritet {Sef=1, Radnik=2, Pripravnik=3};

struct Dokument{
    std::string sadrzaj;
    Prioritet p;
};

class StampacServer{
    std::queue<Dokument> red;
    int s=0,r=0,p=0;
    public:
    void posaljiDokument(Prioritet p, std::string sadrzaj){
        Dokument x; x.sadrzaj=sadrzaj; x.p=p;
        if(red.empty()) red.push(x);
        else{
            int n=red.size();
            if(x.p==1){
                bool ubacen=0;
                for(int i=0;i<n;i++){
                    Dokument pom=red.front();
                    if(pom.p==1){
                        red.push(pom); red.pop();
                    }
                    else{
                        if(!ubacen){
                            red.push(x);
                            ubacen=1;
                        }
                        red.push(pom); red.pop();
                    }
                }
                if(!ubacen){
                    red.push(x);
                }
            }
            else if(x.p==2){
                bool ubacen=0;
                for(int i=0;i<n;i++){
                    Dokument pom=red.front();
                    if(pom.p<=2){
                        red.push(pom); red.pop();
                    }
                    else{
                        if(!ubacen){
                            red.push(x);
                            ubacen=1;
                        }
                        red.push(pom); red.pop();
                    }
                }
                if(!ubacen){
                    red.push(x);
                    ubacen=1;
                }
            }
            else red.push(x);
        }
    }
    Dokument dajDokument(){
        if(red.empty()) throw("Nema dokumenata za printanje");
        Dokument x=red.front();
        red.pop();
        return x;
    }
    int dajBrojDokumenata(){
        return red.size();
    }
};

void pom1(StampacServer& M){
    int p; std::string sadrzaj;
    opet:;
    std::cout<<"Unesite prioritet (1 - Sef, 2 - Radnik, 3 - Pripravnik): "; std::cin>>p;
    if(p!=1 && p!=2 && p!=3){
        std::cout<<"Neispravna Komanda...\n";  
        goto opet;
    }
    Prioritet P;
    if(p==1) P=Sef;
    if(p==2) P=Radnik;
    if(p==3) P=Pripravnik;
    std::cout<<"Unesite string: "; getline(std::cin, sadrzaj); getline(std::cin, sadrzaj);
    M.posaljiDokument(P,sadrzaj);
    std::cout<<"->Uspjesna radnja<-\n";
}

void pom2(StampacServer& M){
    int n=M.dajBrojDokumenata();
    for(int i=0;i<n;i++){
        Dokument pom=M.dajDokument();
        if(pom.p==1) std::cout<<"Sef         "<<pom.sadrzaj<<"\n";
        if(pom.p==2) std::cout<<"Radnik      "<<pom.sadrzaj<<"\n";
        if(pom.p==3) std::cout<<"Pripravnik  "<<pom.sadrzaj<<"\n";
    }
}

void pom3(StampacServer& M){
    Dokument pom=M.dajDokument();
    if(pom.p==1) std::cout<<"Sef         "<<pom.sadrzaj<<"\n";
    if(pom.p==2) std::cout<<"Radnik      "<<pom.sadrzaj<<"\n";
    if(pom.p==3) std::cout<<"Pripravnik  "<<pom.sadrzaj<<"\n";
}


int main(){
    StampacServer M;
    std::cout<<"Izaberite opciju:\n1 - POSALJI DOCX\n2 - ISPRINTAJ SVE DOCX REDOM\n3 - DAJ DOCX\n4 - ZAVRSI\n----------------------\n";
    for(;;){
        std::cout<<"Komanda: ";
        int x; std::cin>>x;
        switch(x){
            case 1  : pom1(M);   break;
            case 2  : pom2(M);   break;
            case 3  : pom3(M);   break;
            case 4  : return 0;  break;
            default : std::cout<<"Neispravna Komanda...\n";  break;
        }
    }
    return 0;
}