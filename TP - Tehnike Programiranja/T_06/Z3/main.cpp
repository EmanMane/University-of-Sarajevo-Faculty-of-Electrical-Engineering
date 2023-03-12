/* 
    TP 2018/2019: LV 6, Zadatak 3
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <vector>

int **KreirajTrougao(int n){
    if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
    try{
        int **matrica(new int *[n]);
        for(int i=0;i<n;i++) matrica[i]=nullptr;
        try{
            for(int i=0;i<n;i++) matrica[i]=new int [2*i+1];
        }catch(...){
            for(int i=0;i<n;i++) delete[] matrica[i];
            delete[] matrica;
            throw;
        }
        for(int i=0;i<n;i++){
            int k=i+1;
            int brreda=2*i+1;
            for(int j=0;j<brreda;j++){
                if(i==j) matrica[i][j]=1;
                else if(j<brreda/2){
                    matrica[i][j]=k;
                    k--;
                }
                else{
                    k++;
                    matrica[i][j]=k;
                }
            }
        }
        return matrica;
    }catch(...){
        throw;
        }
}

int main ()
{
    std::cout<<"Koliko zelite redova: ";
    int n;
    std::cin>>n;
    int **G_mat=nullptr;
    try{
        G_mat=KreirajTrougao(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<2*i+1;j++){
                std::cout<<G_mat[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        for(int i=0;i<n;i++) delete[] G_mat[i];
        delete[] G_mat;
    }
    catch(std::domain_error){
        std::cout<<"Izuzetak: Broj redova mora biti pozitivan";
    }
    catch(std::bad_alloc){
        std::cout<<"Izuzetak: Nedovoljno memorije!";
    }
	return 0;
}