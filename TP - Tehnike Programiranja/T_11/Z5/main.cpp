/* 
    TP 16/17 (LV 11, Zadatak 5)
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
#include <memory>
#include <vector>

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
    std::vector<std::shared_ptr<Tim>> timovi;
    static bool UslovSortiranja(std::shared_ptr<Tim> p,std::shared_ptr<Tim> q){
        if(p->DajBrojPoena()>q->DajBrojPoena()) return true;
        else if(p->DajBrojPoena()==q->DajBrojPoena() && p->DajGolRazliku()>q->DajGolRazliku()) return true;
        else if(p->DajBrojPoena()==q->DajBrojPoena() && p->DajGolRazliku()<q->DajGolRazliku()) return false;
        else if(p->DajBrojPoena()==q->DajBrojPoena() && p->DajGolRazliku()==q->DajGolRazliku() && std::strcmp(p->DajImeTima(),q->DajImeTima())<0) return true;
        return false;
    }
    public:
    explicit Liga()=default;
    explicit Liga(std::initializer_list<Tim> lista_timova){
        for(auto iter=lista_timova.begin();iter!=lista_timova.end();iter++){
            timovi.push_back(std::make_shared<Tim>(*iter));
        }
    }
    Liga(const Liga &l){
        timovi.resize(l.timovi.size());
        for(int i=0;i<timovi.size();i++) timovi[i]=std::make_shared<Tim>(*l.timovi[i]);
    }
    Liga(Liga &&l){
        timovi=std::move(l.timovi);
    }
    Liga &operator =(const Liga &l){
        timovi.resize(l.timovi.size());
        for(int i=0;i<timovi.size();i++) timovi[i]=std::make_shared<Tim>(*l.timovi[i]);
    }
    Liga &operator =(Liga &&l){
        timovi=std::move(l.timovi);
    }
    void DodajNoviTim(const char ime_tima[]){
        for(int i=0;i<timovi.size();i++) if(strcmp(timovi[i]->DajImeTima(),ime_tima)==0) throw std::logic_error("Tim vec postoji");
        timovi.push_back(std::make_shared<Tim>(ime_tima));
    }
    void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2){
        std::shared_ptr<Tim> pomocni1(nullptr), pomocni2(nullptr);
        for(int i=0;i<timovi.size();i++){
            if(std::strcmp(timovi[i]->DajImeTima(),tim1)==0){
                pomocni1=timovi[i];
                break;
            }
        }
        for(int i=0;i<timovi.size();i++){
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
        std::sort(timovi.begin(),timovi.end(),UslovSortiranja);
        for(int i=0;i<timovi.size();i++) timovi[i]->IspisiPodatke();
    }
};
int main ()
{   
    Liga Premier_League{"Celik","Borac","Jedinstvo","Zeljeznicar","Zrinjski","Sarajevo"};
    for(;;){
        Premier_League.IspisiTabelu();
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
            Premier_League.RegistrirajUtakmicu(ctim1,ctim2,skor1,skor2);
        }
        catch(std::logic_error error){
            std::cout<<error.what()<<std::endl;;
        }
    }
	return 0;
}