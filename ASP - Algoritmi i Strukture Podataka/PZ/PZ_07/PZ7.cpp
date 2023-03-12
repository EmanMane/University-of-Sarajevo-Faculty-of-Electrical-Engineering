#include<iostream>
#include<fstream>

using namespace std;

template<typename Tip>
void bubble_sort(Tip* niz, int vel){
    for(int i=0;i<vel-1;i++){
        for(int j=0;j<vel-1;j++){
            if(niz[j]>niz[j+1]){
                Tip pom=niz[j+1];
                niz[j+1]=niz[j];
                niz[j]=pom;
            }
        }
    }
}

template<typename Tip>
void selection_sort(Tip* niz, int vel){
    for(int i=0;i<vel-1;i++){
        int min=i;
        for(int j=i+1;j<vel;j++) if(niz[min]>niz[j]) min=j;
        Tip pom=niz[i];
        niz[i]=niz[min];
        niz[min]=pom;
    }
}

template<typename Tip>
int particija(int prvi, int zadnji,Tip* niz){
    int pivot=prvi;
    int i=pivot+1;
    while(i<=zadnji && niz[pivot]>niz[i]) i++;
    for(int j=i+1;j<=zadnji;j++){
        if(niz[j]<niz[pivot]){
            Tip pom=niz[i];
            niz[i]=niz[j];
            niz[j]=pom;
            i++;
        }
    }
    i--;
    Tip pom=niz[prvi];
    niz[prvi]=niz[i];
    niz[i]=pom;
    return i;
}

template<typename Tip>
void quick_sort(Tip* niz, int vel, int prvi=0,int prvi_put=true){
    if(prvi_put==true) vel--;
    if(prvi<vel){
        int i=particija(prvi,vel,niz);
        quick_sort(niz,i-1,prvi,false);
        quick_sort(niz,vel,i+1,false);
    }
}

template<typename Tip>
void merge(Tip* niz,int prvi, int vel,int p,int q){
    int vel2=vel-prvi+1,copy_prvi=prvi;
    Tip* pok=new Tip[vel2];
    for(int i=0;i<=vel-prvi;i++) pok[i]=niz[prvi+i];
    int x=0,y=q-prvi;
    while(x<=p-copy_prvi && y<=vel-copy_prvi){
        if(pok[y]<=pok[x]){
            niz[prvi]=pok[y]; y++;
        }
        else if(pok[y]>pok[x]){
            niz[prvi]=pok[x]; x++;
        }
        prvi++;
    }
    while(x<=p-copy_prvi){
        niz[prvi]=pok[x];
        x++; prvi++;
    }
    while(y<=vel-copy_prvi){
        niz[prvi]=pok[y];
        y++; prvi++;
    }
    delete[] pok;
}

template<typename Tip>
void merge_sort(Tip* niz, int vel,int prvi=0,int prvi_put=true){
    if(prvi_put==true) vel--;
    if(prvi<vel){
        int p,q;
        p=(vel+prvi)/2; q=p+1;
        merge_sort(niz,p,prvi,false);
        merge_sort(niz,vel,q,false);
        merge(niz,prvi,vel,p,q);
    }
}

void ucitaj(string filename, int*& niz, int &vel){
    vel=0;
    std::ifstream read,write;
    //Citanje da saznamo velicinu
    read.open(filename);
    for(;;){
        if(read.eof()) break;
        else{
            int broj;
            read>>broj;
            vel++;
        }
    }
    read.close();

    //Prepisivanje u niz
    write.open(filename);
    niz=new int[vel];
    for(int i=0;;i++){
        if(write.eof()) break;
        else write>>niz[i];
    }
    write.close();
}

void generisi(string filename, int vel){
    std::ofstream fajl;
    fajl.open(filename);
    for(int i=0;i<vel;i++) fajl<<rand()%100<<" ";
    fajl.close();
}

void funkcija(){

    int *niz,vel=0;
    std::cout<<"Unesite ime datoteke iz koje želite očitati niz: ";
    std::string fajl;
    std::cin>>fajl;
    ucitaj(fajl,niz,vel);

    clock_t t1,t2;
    std::cout<<"Izaberite algoritam:\n1 - Bubble Sort\n2 - Selection Sort\n3 - Quick Sort\n4 - Merge Sort\n";
    std::string unos;
    std::cin>>unos;
    if(unos=="1"){
        t1=clock();
        bubble_sort(niz,vel);
        t2=clock();
    }
    if(unos=="2"){
        t1=clock();
        selection_sort(niz,vel);
        t2=clock();
    }
    if(unos=="3"){
        t1=clock();
        quick_sort(niz,vel);
        t2=clock();
    }
    if(unos=="4"){
        t1=clock();
        merge_sort(niz,vel);
        t2=clock();
    }

    std::cout<<"Trajanje sortiranja: "<<(float)(t2-t1)/(CLOCKS_PER_SEC/1000);
    for(int i=0;i<vel-1;i++) if(niz[i]>niz[i+1]){
        std::cout<<"\nGreska u sortiranju\n";
        goto dalje;
    }
    std::cout<<"\nNiz je ispravno sortiran\n";
    dalje:
    std::cout<<"Unesite ime datoteke u koju se upisuje sortiran niz: ";
    std::cin>>unos;
    std::ofstream izlazni_fajl;
    izlazni_fajl.open(unos);
    for(int i=0;i<vel;i++){
        izlazni_fajl<<niz[i];
        izlazni_fajl<<" ";
    }
    izlazni_fajl.close();
}

int main(){
    generisi("nesortiran",12);
    generisi("sortiran",0);
    funkcija();
    return 0;
}