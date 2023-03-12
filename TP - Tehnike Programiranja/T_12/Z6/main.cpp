/* 
    TP 16/17 (LV 12, Zadatak 6)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>

template <typename TipEl>
class Matrica {
    char ime_matrice;
    int br_redova, br_kolona;
    TipEl **elementi;
    static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
    static void DealocirajMemoriju(TipEl **elementi, int br_redova);
    void KopirajElemente(TipEl **elementi);
public:
    Matrica(int br_redova, int br_kolona, char ime = 0);
    Matrica(const Matrica &m);
    Matrica(Matrica &&m);
    ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
    Matrica &operator =(const Matrica &m);
    Matrica &operator =(Matrica &&m);
//////////////////////////////////////////////////////////////
    TipEl* &operator [](int i){return elementi[i];}
    TipEl* operator [](int i) const {return elementi[i];}
    TipEl &operator ()(int i,int j) {
        if(i<=0 || i>br_redova || j<=0 || j>br_kolona) throw std::range_error("Neispravan indeks");
        return elementi[i-1][j-1];
    }
    TipEl operator ()(int i,int j) const {
        if(i<=0 || i>br_redova || j<=0 || j>br_kolona) throw std::range_error("Neispravan indeks");
        return elementi[i-1][j-1];
    }
    template<typename Tip>
    friend Matrica<Tip> operator +(const Matrica<Tip> &m1,const Matrica<Tip> &m2);
    template<typename Tip>
    friend Matrica<Tip> operator -(const Matrica<Tip> &m1,const Matrica<Tip> &m2);
    template <typename Tip>
    friend std::istream &operator >>(std::istream &tok,Matrica<Tip> &m);
    template <typename Tip>
    friend std::ostream &operator <<(std::ostream &tok,Matrica<Tip> &m);
    template<typename Tip>
    friend Matrica<Tip> operator *(int x,const Matrica<Tip> &m1);
    template<typename Tip>
    friend Matrica<Tip> operator *(const Matrica<Tip> &m1,int x);
    template<typename Tip>
    friend Matrica<Tip> operator *(const Matrica<Tip> &m1,const Matrica<Tip> &m2);
    template<typename Tip>
    friend Matrica<Tip> operator +=(Matrica<Tip> &m1,const Matrica<Tip> &m2);
    template<typename Tip>
    friend Matrica<Tip> operator -=(Matrica<Tip> &m1,const Matrica<Tip> &m2);
    template<typename Tip>
    friend Matrica<Tip> operator *=(Matrica<Tip> &m1,const Matrica<Tip> &m2);
    template<typename Tip>
    friend Matrica<Tip> operator *=(Matrica<Tip> &m1,int x);
    operator std::string() const;
//////////////////////////////////////////////////////////////
    void Unesi();
    void Ispisi(int sirina_ispisa) const;
    template <typename Tip2>
    friend Matrica<Tip2> ZbirMatrica(const Matrica<Tip2> &m1,
    const Matrica<Tip2> &m2);
    };
/************************************************************/
    template <typename TipEl>
    std::ostream &operator <<(std::ostream &tok,Matrica<TipEl> &m){
        int wid(tok.width());
        for(int i = 0; i < m.br_redova; i++){
            for(int j = 0; j < m.br_kolona; j++) {
                tok << std::setw(wid) << m.elementi[i][j];
            }
            tok<<std::endl;
        }
        return tok;
    }
    
    template <typename TipEl>
    std::istream &operator >>(std::istream &tok,Matrica<TipEl> &m){
        for(int i = 0; i < m.br_redova; i++)
                for(int j = 0; j < m.br_kolona; j++) {
                    std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
                    tok >> m.elementi[i][j];
                }
        return tok;
    }

    template<typename TipEl>
        Matrica<TipEl> operator *(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2){
            if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
            Matrica<TipEl> nova(m1.br_redova,m2.br_kolona);
            for(int i=0;i<m1.br_redova;i++){
                for(int j=0;j<m2.br_kolona;j++){
                    nova.elementi[i][j]=0;
                    for(int k=0;k<m1.br_redova;k++){
                        nova.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
                    }
                }
            }
            return nova;
        }

    template<typename TipEl>
    Matrica<TipEl> operator +(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2){
        if(m1.br_kolona!=m2.br_kolona && m1.br_redova!=m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> nova(m1.br_redova,m2.br_kolona);
        for(int i=0;i<m1.br_redova;i++){
            for(int j=0;j<m2.br_kolona;j++){
                nova.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
            }
        }
        return nova;
    }

    template<typename TipEl>
    Matrica<TipEl> operator -(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2){
        if(m1.br_kolona!=m2.br_kolona && m1.br_redova!=m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        Matrica<TipEl> nova(m1.br_redova,m2.br_kolona);
        for(int i=0;i<m1.br_redova;i++){
            for(int j=0;j<m2.br_kolona;j++){
                nova.elementi[i][j]=m1.elementi[i][j]-m2.elementi[i][j];
            }
        }
        return nova;
    }

    template<typename TipEl>
    Matrica<TipEl> operator +=(Matrica<TipEl> &m1,const Matrica<TipEl> &m2){
        if(m1.br_kolona!=m2.br_kolona && m1.br_redova!=m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        return m1=m1+m2;;
    }

    template<typename Tip>
    Matrica<Tip> operator -=(Matrica<Tip> &m1,const Matrica<Tip> &m2){
        if(m1.br_kolona!=m2.br_kolona && m1.br_redova!=m2.br_redova) throw std::domain_error("Matrice nemaju jednake dimenzije!");
        return m1=m1-m2;;
    }

    template<typename Tip>
    Matrica<Tip> operator *=(Matrica<Tip> &m1,const Matrica<Tip> &m2){
        if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        return m1=m1*m2;
    }

    template<typename TipEl>
    Matrica<TipEl> operator *(int x,const Matrica<TipEl> &m1){
        Matrica<TipEl> nova(m1.br_redova,m1.br_kolona);
        for(int i=0;i<m1.br_redova;i++){
            for(int j=0;j<m1.br_kolona;j++){
                nova.elementi[i][j]=m1.elementi[i][j]*x;
            }
        }
        return nova;
    }

    template<typename TipEl>
    Matrica<TipEl> operator *(const Matrica<TipEl> &m1,int x){
        Matrica<TipEl> nova(m1.br_redova,m1.br_kolona);
        for(int i=0;i<m1.br_redova;i++){
            for(int j=0;j<m1.br_kolona;j++){
                nova.elementi[i][j]=m1.elementi[i][j]*x;
            }
        }
        return nova;
    }

    template<typename TipEl>
    Matrica<TipEl> operator *=(Matrica<TipEl> &m1,int x){
        return m1=m1*x;
    }

    template<typename TipEl>
    Matrica<TipEl>::operator std::string() const{
        std::string s("{");
        for(int i=0;i<br_redova;i++){
            s+="{";
            for(int j=0;j<br_redova;j++){
                s+=std::to_string(int(elementi[i][j]));
                if(j!=br_kolona-1) s+=",";
            }
            if(i!=br_redova-1) s+="},";
            else s+="}";
        }
        s+="}";
        return s;
    }
//////////////////////////////////////////////////////////////
template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
    TipEl **elementi = new TipEl*[br_redova]{}; 
    try {
        for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
    }
    catch(...) {
        DealocirajMemoriju(elementi, br_redova); throw;
    }
    return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
 for(int i = 0; i < br_redova; i++) delete[] elementi[i];
 delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) : 
br_redova(br_redova), br_kolona(br_kolona), 
ime_matrice(ime),elementi(AlocirajMemoriju(br_redova, br_kolona)) {}

template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
    for(int i = 0; i < br_redova; i++)
    for(int j = 0; j < br_kolona; j++)
    Matrica::elementi[i][j] = elementi[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
    br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
    elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
    KopirajElemente(m.elementi);
}

template <typename TipEl>
 Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova), 
 br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice) {
 m.br_redova = 0; m.elementi = nullptr;
 }

template <typename TipEl>
 Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) {
 if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
 TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
 DealocirajMemoriju(elementi, br_redova);
 elementi = novi_prostor;
 }
 else if(br_redova > m.br_redova)
 for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
 br_redova = m.br_redova; br_kolona = m.br_kolona;
 ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);
 return *this;
 }

template <typename TipEl>
 Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) {
 std::swap(br_redova, m.br_redova); std::swap(br_kolona, m.br_kolona);
 std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);
 return *this;
 }

template <typename TipEl>
 void Matrica<TipEl>::Unesi() {
 for(int i = 0; i < br_redova; i++)
 for(int j = 0; j < br_kolona; j++) {
 std::cout << ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
 std::cin >> elementi[i][j];
 }
 }

template <typename TipEl>
 void Matrica<TipEl>::Ispisi(int sirina_ispisa) const {
 for(int i = 0; i < br_redova; i++) {
 for(int j = 0; j < br_kolona; j++)
 std::cout << std::setw(sirina_ispisa) << elementi[i][j];
 std::cout << std::endl;
 }
 }
template <typename TipEl>
 Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1, 
 const Matrica<TipEl> &m2) {
 if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
 throw std::domain_error("Matrice nemaju jednake dimenzije!");
 Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
 for(int i = 0; i < m1.br_redova; i++)
 for(int j = 0; j < m1.br_kolona; j++)
 m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
 return m3;
 }
 
int main() {
//AT12 testiranje implicitne konverzije (const) matrice u string
  try {
Matrica<double> a(2, 2, 'a');
a[0][0] = 10; a[0][1] = 2; 
a[1][0] = 4; a[1][1] = 5; 
std::string s; 
s = a; 
std::cout << s << std::endl;
const Matrica<double> b(a);
s=a;
std::cout << a << std::endl;
  }
  catch(std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }
    catch(std::domain_error e) {
    std::cout << e.what();
  }
    catch(std::range_error e) {
    std::cout << e.what();
  }
 return 0;
}