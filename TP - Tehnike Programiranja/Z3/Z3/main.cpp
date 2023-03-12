//TP 2021/2022: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
struct Matrica {
    char ime_matrice; // Koristi se samo u funkciji "UnesiMatricu"
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!!!
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0) {
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova; mat.br_kolona = br_kolona; mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova]{};
    try {
        for(int i = 0; i < br_redova; i++) 
        mat.elementi[i] = new TipElemenata[br_kolona]; 
    }
    catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename TipElemenata>
void UnesiMatricu(char ime = '0', Matrica<TipElemenata> &mat={}) {
    for(int i = 0; i < mat.br_redova; i++)
    for(int j = 0; j < mat.br_kolona; j++) {
        std::cout << ime << "(" << i + 1 << "," << j + 1 << ") = ";
        std::cin >> mat.elementi[i][j];
    }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_obrisati=false) {
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)  std::cout << std::setprecision(preciznost) << std::setw(sirina_ispisa) << mat.elementi[i][j];
        std::cout << std::endl;
    }
    if(treba_obrisati){
        if(!mat.elementi) return;
        for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
        delete[] mat.elementi;
        //mat.elementi = nullptr;
    } 
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++) for(int j = 0; j < m1.br_kolona; j++) m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
} 

template <typename TipElemenata> 
Matrica<TipElemenata> ProduktMatrica(Matrica<TipElemenata> m1, Matrica<TipElemenata> m2){
    if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova,m2.br_kolona,'P');
    for(int i=0;i<m1.br_redova;i++){
        for(int j=0;j<m2.br_kolona;j++){
            int S=0;
            for(int k=0;k<m2.br_redova;k++) S+=m1.elementi[i][k]*m2.elementi[k][j];
            m3.elementi[i][j]=S;
        }
    }
    return m3;
}

template <typename TipElemenata> 
Matrica<TipElemenata> MatricniPolinom(Matrica<TipElemenata> A, std::vector<double> koeficijenti){
    if(A.br_kolona!=A.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
    if(koeficijenti.size()==0){
        auto m3=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
        for(int i=0;i<A.br_redova;i++) for(int j=0;j<A.br_kolona;j++) m3.elementi[i][j]=0;
        return m3;
    }
    auto m3=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona,'X');
    for(int i=0;i<A.br_redova;i++) for(int j=0;j<A.br_kolona;j++) m3.elementi[i][j]=0;
    auto pomocna=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona,'p');
    for(int i=0;i<koeficijenti.size();i++){
        if(i==0){
            for(int j=0;j<A.br_redova;j++) for(int k=0;k<A.br_kolona;k++){
                if(j==k) pomocna.elementi[j][k]=1;
                else pomocna.elementi[j][k]=0;
            }
            for(int j=0;j<A.br_redova;j++) for(int k=0;k<A.br_kolona;k++) m3.elementi[j][k]+=pomocna.elementi[j][k]*koeficijenti.at(i);
        }
        else{
            Matrica<TipElemenata> temp=ProduktMatrica(pomocna,A);
            for(int j=0;j<A.br_redova;j++) for(int k=0;k<A.br_kolona;k++) m3.elementi[j][k]+=temp.elementi[j][k]*koeficijenti.at(i);
            UnistiMatricu(pomocna);
            pomocna=temp;
        }
    }
    UnistiMatricu(pomocna);
    return m3;
}

int main() {
    Matrica<double> a, b; // AUTOMATSKA INICIJALIZACIJA!!!
    int n;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> n;
    //try {
        a = StvoriMatricu<double>(n, n, 'A'); 
        std::cout << "Unesite elemente matrice A: \n";
        UnesiMatricu<double>('A',a);
        std::cout << "Unesite red polinoma: ";
        int red; std::cin>>red;
        std::cout << "Unesite koeficijente polinoma: ";
        std::vector<double> polinom;
        for(int i=0;i<red+1;i++){
            double broj;
            std::cin>>broj;
            polinom.push_back(broj);
        }
        IspisiMatricu(b = MatricniPolinom(a, polinom), 10, 6, true);
        //IspisiMatricu(b = ProduktMatrica(a, a), 10, 6, true);
    //}
    //catch(std::bad_alloc) {
    //    std::cout << "Nema dovoljno memorije!\n";
    //}
    UnistiMatricu(a);
    return 0;
}