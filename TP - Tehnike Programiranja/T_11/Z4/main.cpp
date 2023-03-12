/* 
    TP 16/17 (LV 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <iomanip>

class Tim{
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
    public:
    Tim(const char ime[]){
        if(std::strlen(ime)>20) throw std::range_error("Predugacko ime tima");
        std::strcpy(ime_tima,ime);
        broj_odigranih=0;
        broj_pobjeda=0;
        broj_nerijesenih=0;
        broj_poraza=0;
        broj_datih=0;
        broj_primljenih=0;
        broj_poena=0;
    }
    void ObradiUtakmicu(int broj_datih, int broj_primljenih){
        if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
        Tim::broj_datih+=broj_datih; Tim::broj_primljenih+=broj_primljenih;
        broj_odigranih++;
        int skor=broj_datih-broj_primljenih;
        if(skor<0) broj_poraza++;
        if(skor==0){
            broj_nerijesenih++; broj_poena++;
        }
        if(skor>0){
            broj_pobjeda++; broj_poena+=3;
        }
    }
    const char *DajImeTima() const{
        return ime_tima;
    }
    int DajBrojPoena() const{
        return broj_poena;
    }
    int DajGolRazliku() const{
        return broj_datih-broj_primljenih;
    }
    void IspisiPodatke() const{
        std::cout<<std::setw(20)<<std::left<<ime_tima
        <<std::setw(4)<<std::right<<broj_odigranih
        <<std::setw(4)<<std::right<<broj_pobjeda
        <<std::setw(4)<<std::right<<broj_nerijesenih
        <<std::setw(4)<<std::right<<broj_poraza
        <<std::setw(4)<<std::right<<broj_datih
        <<std::setw(4)<<std::right<<broj_primljenih
        <<std::setw(4)<<std::right<<broj_poena<<std::endl;
    }
};

class Liga{
    int broj_timova;
    const int max_br_timova;
    Tim **timovi;

    //sljedeca funkcija koristi se za poređenje pri sortiranju (std::sort) i
    //tipa je static bool jer bez static kompajler izbacuje error...
    static bool UslovSortiranja(Tim *p,Tim *q){
        if(p->DajBrojPoena()>q->DajBrojPoena()) return true;
        else if(p->DajBrojPoena()==q->DajBrojPoena() && p->DajGolRazliku()>q->DajGolRazliku()) return true;
        else if(p->DajBrojPoena()==q->DajBrojPoena() && p->DajGolRazliku()<q->DajGolRazliku()) return false;
        else if(p->DajBrojPoena()==q->DajBrojPoena() && p->DajGolRazliku()==q->DajGolRazliku() && std::strcmp(p->DajImeTima(),q->DajImeTima())<0) return true;
        return false;
    }
    public:
    explicit Liga(int velicina_lige) : max_br_timova(velicina_lige){
        broj_timova=0;
        timovi=nullptr;
        timovi=new Tim*[max_br_timova]{};
    }
    explicit Liga(std::initializer_list<Tim> lista_timova) : max_br_timova(lista_timova.size()){
        broj_timova=lista_timova.size();
        timovi=nullptr;
        timovi=new Tim*[max_br_timova]{};
        try{
            int i=0;
            for(auto iter=lista_timova.begin();iter!=lista_timova.end();iter++){
                timovi[i]=new Tim(*iter);
                i++;
            }
        }
        catch(...){
            for(int i=0;i<broj_timova;i++) delete timovi[i];
            delete[] timovi;
        }
    }
    ~Liga(){
        for(int i=0;i<broj_timova;i++) delete timovi[i];
        delete[] timovi;
        timovi=nullptr;
    }

    
    Liga(const Liga &l) : max_br_timova(l.max_br_timova){
        broj_timova=l.broj_timova;
        timovi=new Tim*[l.broj_timova];
        try{
            for(int i=0;i<broj_timova;i++) timovi[i]=new Tim(*l.timovi[i]);
        }
        catch(...){
            for(int i=0;i<broj_timova;i++) delete timovi[i];
            delete[] timovi;
            timovi=nullptr;
        }
    }

    
    Liga(Liga &&l) : max_br_timova(l.max_br_timova){
        broj_timova=l.broj_timova;
        timovi=l.timovi;
        l.timovi=nullptr;
    }

    //Kopirajuća verzija
    Liga &operator =(const Liga &l){
        if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
        if(broj_timova<l.broj_timova){
            try{
                for(int i=broj_timova;i<l.broj_timova;i++) timovi[i]=new Tim(*l.timovi[i]);
            }
            catch(...){
                for(int i=broj_timova;i<l.broj_timova;i++){
                    delete timovi[i];
                    timovi[i]=nullptr;
                }
                throw;
            }
        }
        else if(broj_timova>l.broj_timova) for(int i=l.broj_timova;i<broj_timova;i++) timovi[i]=nullptr;
        broj_timova=l.broj_timova;
        for(int i=0;i<broj_timova;i++) *timovi[i]=*l.timovi[i];
        return *this;
    }

    //Pomjerajuća verzija
    Liga &operator =(Liga &&l){
        if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
        broj_timova=l.broj_timova;
        timovi=l.timovi;
        l.timovi=nullptr;
        return *this;
    }
    void DodajNoviTim(const char ime_tima[]){
        if(broj_timova==max_br_timova) throw std::range_error("Liga popunjena");
        for(int i=0;i<broj_timova;i++) if(strcmp(timovi[i]->DajImeTima(),ime_tima)==0) throw std::logic_error("Tim vec postoji");
        timovi[broj_timova++]=new Tim(ime_tima);
    }
    void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2){
        Tim *pomocni1=nullptr,*pomocni2=nullptr;
        for(int i=0;i<broj_timova;i++){
            if(std::strcmp(timovi[i]->DajImeTima(),tim1)==0){
                pomocni1=timovi[i];
                break;
            }
        }
        for(int i=0;i<broj_timova;i++){
            if(std::strcmp(timovi[i]->DajImeTima(),tim2)==0){
                pomocni2=timovi[i];
                break;
            }
        }
        if(pomocni1==nullptr || pomocni2==nullptr) throw std::logic_error("Tim nije nadjen");
        if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
        pomocni1->ObradiUtakmicu(rezultat_1,rezultat_2);
        pomocni2->ObradiUtakmicu(rezultat_2,rezultat_1);
    }
    void IspisiTabelu(){
        std::sort(timovi,timovi+broj_timova,UslovSortiranja);
        for(int i=0;i<broj_timova;i++) timovi[i]->IspisiPodatke();
    }
};
int main ()
{
    Liga Premier_Liga_BiH{"Celik","Borac","Jedinstvo","Zeljeznicar","Zrinjski","Sarajevo"};
    for(;;){
        Premier_Liga_BiH.IspisiTabelu();
        std::cout<<std::endl;
        std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
        std::string tim1,tim2;
        std::getline(std::cin,tim1);
        if(tim1.size()==0) break;
        std::cout<<"Unesite ime drugog tima: ";
        std::getline(std::cin,tim2);
        std::cout<<"Unesite broj postigutih golova za oba tima: ";
        int skor1,skor2;
        std::cin>>skor1; std::cin>>skor2;
        std::cin.ignore(10000,'\n');
        std::cout<<std::endl;
        const char *ctim1=tim1.c_str(),*ctim2=tim2.c_str();
        try{
            Premier_Liga_BiH.RegistrirajUtakmicu(ctim1,ctim2,skor1,skor2);
        }
        catch(std::logic_error error){
            std::cout<<error.what()<<std::endl;;
        }
    }
	return 0;
}