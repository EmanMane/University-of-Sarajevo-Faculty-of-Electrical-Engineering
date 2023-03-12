#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

template <typename TipOznake> class Grana;
template <typename TipOznake> class Cvor;
template <typename TipOznake> class GranaIterator;

template <typename TipOznake> class UsmjereniGraf {
public:
  UsmjereniGraf() {}
  UsmjereniGraf(int broj_cvorova) {}
  virtual ~UsmjereniGraf() {}
  virtual int dajBrojCvorova() const = 0;
  virtual void postaviBrojCvorova(int broj_cvorova) = 0;
  virtual void dodajGranu(int c1, int c2, double tezina) = 0;
  virtual void obrisiGranu(int c1, int c2) = 0;
  virtual void postaviTezinuGrane(int c1, int c2, double tezina) = 0;
  virtual double dajTezinuGrane(int c1, int c2) const = 0;
  virtual bool postojiGrana(int c1, int c2) = 0;
  virtual void postaviOznakuCvora(int broj_cvora, TipOznake oznaka) = 0;
  virtual TipOznake dajOznakuCvora(int broj_cvora) const = 0;
  virtual void postaviOznakuGrane(int c1, int c2, TipOznake oznaka) = 0;
  virtual TipOznake dajOznakuGrane(int c1, int c2) const = 0;
  virtual Cvor<TipOznake> dajCvor(int c) = 0;
  virtual Grana<TipOznake> dajGranu(int c1, int c2) = 0;
  virtual GranaIterator<TipOznake> dajGranePocetak() = 0;
  virtual GranaIterator<TipOznake> dajGraneKraj() = 0;
};

template <typename TipOznake> class Cvor {
  UsmjereniGraf<TipOznake> *pok;
  int broj;
  TipOznake oznaka;

public:
  Cvor(UsmjereniGraf<TipOznake> *p, int broj_cvora)
      : pok(p), broj(broj_cvora) {}
  Cvor(UsmjereniGraf<TipOznake> *p, int broj_cvora, TipOznake oznaka)
      : pok(p), broj(broj_cvora), oznaka(oznaka) {}

  TipOznake dajOznaku() const { return oznaka; }
  void postaviOznaku(TipOznake oznaka) {
    pok->postaviOznakuCvora(broj, oznaka);
  }
  void postaviOznaku1(TipOznake o) { oznaka = o; }
  int dajRedniBroj() const { return broj; }
  friend class Grana<TipOznake>;
};

template <typename TipOznake> class Grana {
  double tezina;
  TipOznake oznaka;
  Cvor<TipOznake> *poc;
  Cvor<TipOznake> *slj;

public:
  Grana() : oznaka(TipOznake{}), poc(nullptr), slj(nullptr), tezina(0) {}

  Grana(double tezina, TipOznake oznaka, Cvor<TipOznake> *p, Cvor<TipOznake> *s)
      : tezina(tezina), oznaka(oznaka), poc(p), slj(s) {}

  double dajTezinu() const { return tezina; }

  void postaviTezinu(double tezina) {
    poc->pok->postaviTezinuGrane(poc->dajRedniBroj(), slj->dajRedniBroj(),
                                 tezina);
  }
  void postaviTezinu1(double t) { tezina = t; }

  TipOznake dajOznaku() const { return oznaka; }

  void postaviOznaku(TipOznake oznaka) {
    poc->pok->postaviOznakuGrane(poc->dajRedniBroj(), slj->dajRedniBroj(),
                                 oznaka);
  }
  void postaviOznaku1(TipOznake o) { oznaka = o; }

  Cvor<TipOznake> dajPolazniCvor() const { return *poc; }

  Cvor<TipOznake> dajDolazniCvor() const { return *slj; }

  bool isti(int x, int y) {
    return (x == poc->dajRedniBroj() && y == slj->dajRedniBroj());
  }
};

template <typename TipKljuca, typename TipVrijednosti> class Mapa {
public:
  Mapa<TipKljuca, TipVrijednosti>(){};
  virtual ~Mapa(){};
  virtual TipVrijednosti &operator[](TipKljuca kljuc) = 0;
  virtual TipVrijednosti operator[](const TipKljuca kljuc) const = 0;
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const TipKljuca &kljuc) = 0;
};
/*-----------------------------------------------------------------*/
template <typename TipKljuca, typename TipVrijednosti>
class HashMapaLan : public Mapa<TipKljuca, TipVrijednosti> {
  int vel;
  std::vector<std::list<std::pair<TipKljuca, TipVrijednosti>> *> hash_mapa;
  unsigned int (*funkcija)(TipKljuca, unsigned int);

public:
  HashMapaLan<TipKljuca, TipVrijednosti>()
      : hash_mapa(100), vel(0), funkcija(nullptr) {}

  HashMapaLan(const HashMapaLan<TipKljuca, TipVrijednosti> &mapa)
      : hash_mapa(mapa.hash_mapa.size()), vel(mapa.vel),
        funkcija(mapa.funkcija) {
    for (int i = 0; i < hash_mapa.size(); i++) {
      if (mapa.hash_mapa[i])
        hash_mapa[i] = new std::list<std::pair<TipKljuca, TipVrijednosti>>(
            *mapa.hash_mapa[i]);
    }
  }

  ~HashMapaLan() {
    for (int i = 0; i < hash_mapa.size(); i++)
      delete hash_mapa[i];
  }

  TipVrijednosti &operator[](TipKljuca kljuc) {
    if (funkcija) {
      unsigned int hash = funkcija(kljuc, hash_mapa.size());
      if (hash_mapa[hash]) {
        auto iter = hash_mapa[hash]->begin();
        for (auto iterator = hash_mapa[hash]->begin();
             iterator != hash_mapa[hash]->end(); iterator++)
          if (iterator->first == kljuc)
            return iterator->second;
        while (iter != hash_mapa[hash]->end() && iter->first < kljuc)
          iter++;
        vel++;
        return (hash_mapa[hash]->insert(iter,
                                        std::pair<TipKljuca, TipVrijednosti>(
                                            kljuc, TipVrijednosti{})))
            ->second;
      } else {
        hash_mapa[hash] = new std::list<std::pair<TipKljuca, TipVrijednosti>>{
            std::pair<TipKljuca, TipVrijednosti>(kljuc, TipVrijednosti{})};
        vel++;
        auto iterator = hash_mapa[hash]->begin();
        return iterator->second;
      }
    } else
      throw("Nije definisana hash funkcija");
  }

  TipVrijednosti operator[](const TipKljuca kljuc) const {
    if (funkcija) {
      unsigned int hash = funkcija(kljuc, hash_mapa.size());
      if (hash_mapa[hash]) {
        for (auto iterator = hash_mapa[hash]->begin();
             iterator != hash_mapa[hash]->end(); iterator++)
          if (iterator->first == kljuc)
            return iterator->second;
      }
      return TipVrijednosti{};
    } else
      throw("Nije definisana hash funkcija");
  }

  int brojElemenata() const { return vel; }

  void obrisi() {
    typename std::vector<
        std::list<std::pair<TipKljuca, TipVrijednosti>> *>::iterator it;
    for (it = hash_mapa.begin(); it != hash_mapa.end(); it++)
      if (*it != nullptr)
        delete (*it);
    hash_mapa.clear();
    vel = 0;
    hash_mapa.resize(100);
  }

  void obrisi(const TipKljuca &kljuc) {
    if (funkcija) {
      unsigned int hash = funkcija(kljuc, hash_mapa.size());
      if (hash_mapa[hash] != nullptr) {
        for (auto iterator = hash_mapa[hash]->begin();iterator != hash_mapa[hash]->end(); ) {
          if (iterator->first == kljuc) {
            hash_mapa[hash]->erase(iterator);
            vel--;
            return;
          }
          else{
              iterator++;
          }
        }
        if (hash_mapa[hash]->empty()){
            delete hash_mapa[hash];
            hash_mapa[hash]=nullptr;
        }

      }
    } else
      throw("Nije definisana hash funkcija");
  }

  void definisiHashFunkciju(unsigned int (*h_funkcija)(TipKljuca ulaz,
                                                       unsigned int raspon)) {
    funkcija = h_funkcija;
  }

  HashMapaLan &operator=(const HashMapaLan<TipKljuca, TipVrijednosti> &mapa) {
    if (&mapa == this)
      return *this;
    obrisi();
    hash_mapa.resize(mapa.hash_mapa.size(), nullptr);
    funkcija = mapa.funkcija;
    vel = mapa.vel;
    for (int i = 0; i < hash_mapa.size(); i++) {
      if (mapa.hash_mapa[i])
        hash_mapa[i] = new std::list<std::pair<TipKljuca, TipVrijednosti>>(
            *mapa.hash_mapa[i]);
    }
    return *this;
  }
};
/*-----------------------------------------------------------------*/
template <typename TipOznake>
class ListaGraf : public UsmjereniGraf<TipOznake> {
protected:
  std::vector<Cvor<TipOznake> *> c;
  std::vector<std::vector<Grana<TipOznake> *>> list;
  int avg = 0;

public:
  ListaGraf() {}

  ListaGraf(int broj_cvorova) {
    if (broj_cvorova < 0)
      throw "Error";
    list.resize(broj_cvorova);
    c.resize(broj_cvorova);
    for (int i = 0; i < broj_cvorova; i++)
      c[i] = new Cvor<TipOznake>(this, i, TipOznake{});
  }

  ~ListaGraf() {
    for (int i = 0; i < list.size(); i++) {
      for (int j = 0; j < list[i].size(); j++)
        delete list[i][j];
    }
    for (int i = 0; i < c.size(); i++)
      delete c[i];
  }

  int dajBrojCvorova() const { return list.size(); }

  void postaviBrojCvorova(int broj_cvorova) {
    if (c.size() < broj_cvorova) {
      c.resize(broj_cvorova);
      for (int i = 0; i < list.size(); i++)
        c[i] = new Cvor<TipOznake>(this, i, TipOznake{});
      list.resize(broj_cvorova);
    } else
      throw "Error";
  }

  void dodajGranu(int c1, int c2, double tezina) {
    list[c1].push_back(new Grana<TipOznake>(tezina, TipOznake{}, c[c1], c[c2]));
  }

  void obrisiGranu(int c1, int c2) {
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        delete list[c1][i];
        list[c1].erase(list[c1].begin() + i);
        return;
      }
    }
  }

  void postaviTezinuGrane(int c1, int c2, double tezina) {
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        list[c1][i]->postaviTezinu1(tezina);
        return;
      }
    }
  }

  double dajTezinuGrane(int c1, int c2) const {
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        return list[c1][i]->dajTezinu();
      }
    }
  }

  bool postojiGrana(int c1, int c2) {
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        return true;
      }
    }
  }

  void postaviOznakuCvora(int broj_cvora, TipOznake oznaka) {
    c[broj_cvora]->postaviOznaku1(oznaka);
  }

  TipOznake dajOznakuCvora(int broj_cvora) const {
    return c[broj_cvora]->dajOznaku();
  }

  void postaviOznakuGrane(int c1, int c2, TipOznake oznaka) {
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        list[c1][i]->postaviOznaku1(oznaka);
        return;
      }
    }
  }

  TipOznake dajOznakuGrane(int c1, int c2) const {
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        return list[c1][i]->dajOznaku();
      }
    }
  }

  Cvor<TipOznake> dajCvor(int i) { return *c[i]; }

  Grana<TipOznake> dajGranu(int c1, int c2) {
    if (c1 > c.size() || c2 > c.size())
      throw("ERROR");
    for (int i = 0; i < list[c1].size(); i++) {
      if (list[c1][i]->isti(c1, c2)) {
        return *list[c1][i];
      }
    }
  }

  virtual GranaIterator<TipOznake> dajGranePocetak() {
    for (int i = 0; i < list.size(); i++) {
      for (int j = 0; j < list[i].size(); j++) {
        if (list[i][j] != nullptr)
          return GranaIterator<TipOznake>(this, i, j);
      }
    }
    return GranaIterator<TipOznake>(this, 0, 0);
  }

  virtual GranaIterator<TipOznake> dajGraneKraj() {
    for (int i = list.size() - 1; i > 0; i--) {
      for (int j = list[i].size() - 1; j > 0; j--) {
        if (list[i][j] != nullptr) {
          if (j < list[i].size() - 1)
            return GranaIterator<TipOznake>(this, i, j + 1);
          return GranaIterator<TipOznake>(this, i + 1, 0);
        }
      }
    }
    return GranaIterator<TipOznake>(this, list.size() - 1,
                                    list[list.size() - 1].size() - 1);
  }

  friend class GranaIterator<TipOznake>;
  template <typename TipOznakeX>
  friend void bfs(UsmjereniGraf<TipOznakeX> *graf, vector<Cvor<bool>> &bfso,
                  Cvor<TipOznakeX> c, int next);
  template <typename TipOznakeX>
  friend void dfs(UsmjereniGraf<TipOznakeX> *graf, vector<Cvor<bool>> &dfso,
                  Cvor<TipOznakeX> c);
};
template <typename TipOznakeX>
void bfs(UsmjereniGraf<TipOznakeX> *graf, vector<Cvor<bool>> &bfso,
         Cvor<TipOznakeX> c, int next = 0) {
  ListaGraf<TipOznakeX> *pom = dynamic_cast<ListaGraf<TipOznakeX> *>(graf);
  if (pom->avg == pom->dajBrojCvorova()) {
    pom->avg = 0;
    return;
  }
  auto poz = TipOznakeX(1);
  if (pom->c[c.dajRedniBroj()]->dajOznaku() != poz) {
    pom->c[c.dajRedniBroj()]->postaviOznaku(poz);
    bfso.push_back(c);
    pom->avg++;
  }
  for (int i = 0; i < pom->list[c.dajRedniBroj()].size(); i++) {
    if (pom->list[c.dajRedniBroj()][i]->dajDolazniCvor().dajOznaku() != poz) {
      bfso.push_back(pom->list[c.dajRedniBroj()][i]->dajDolazniCvor());
      pom->list[c.dajRedniBroj()][i]->dajDolazniCvor().postaviOznaku(poz);
      pom->avg++;
    }
  }
  bfs(graf, bfso, bfso[++next], next);
}
template <typename TipOznakeX>
void dfs(UsmjereniGraf<TipOznakeX> *graf, vector<Cvor<bool>> &dfso,
         Cvor<TipOznakeX> c) {
  ListaGraf<TipOznakeX> *pom = dynamic_cast<ListaGraf<TipOznakeX> *>(graf);
  auto poz = TipOznakeX(1);
  pom->c[c.dajRedniBroj()]->postaviOznaku(poz);
  dfso.push_back(c);
  pom->avg;

  for (int i = 0; i < pom->list[c.dajRedniBroj()].size(); i++) {
    if (pom->list[c.dajRedniBroj()][i]->dajDolazniCvor().dajOznaku() != poz) {
      dfs(graf, dfso, pom->list[c.dajRedniBroj()][i]->dajDolazniCvor());
    }
  }

  if (pom->avg < pom->dajBrojCvorova()) {
    for (int i = 0; i < pom->list.size(); i++) {
      for (int j = 0; j < pom->list[i].size(); j++) {
        if (pom->list[i][j] != nullptr &&
            pom->list[i][j]->dajDolazniCvor().dajOznaku() != poz) {
          if (pom->c[i]->dajOznaku() != poz) {
            pom->c[i]->postaviOznaku(poz);
            dfso.push_back(*pom->c[i]);
          }
          dfs(graf, dfso, pom->list[i][j]->dajDolazniCvor());
        }
      }
    }
  }

  if (pom->avg == pom->dajBrojCvorova())
    pom->avg = 0;
}

template <typename TipOznake> class GranaIterator {
  ListaGraf<TipOznake> *pok;
  int koordinata1, koordinata2;

public:
  GranaIterator<TipOznake>(ListaGraf<TipOznake> *p, int koordinata1,
                           int koordinata2)
      : pok(p), koordinata1(koordinata1), koordinata2(koordinata2) {}

  Grana<TipOznake> operator*() { return *pok->list[koordinata1][koordinata2]; }

  bool operator==(const GranaIterator<TipOznake> &it) const {
    if (it.pok == pok && it.koordinata1 == koordinata1 &&
        it.koordinata2 == koordinata2)
      return 1;
    return 0;
  }

  bool operator!=(const GranaIterator<TipOznake> &it) const {
    if (*this == it)
      return 0;
    return 1;
  }

  GranaIterator &operator++() {
    if (koordinata1 == pok->list.size() - 1 &&
        koordinata2 == pok->list[pok->list.size() - 1].size() - 1)
      koordinata2++;
    if (koordinata2 != pok->list[koordinata1].size() - 1)
      koordinata2++;
    else {
      koordinata2 = 0;
      koordinata1++;
    }
    return *this;
  }

  GranaIterator operator++(int) {
    GranaIterator<TipOznake> pom = (*this);
    ++(*this);
    return pom;
  }
};

int main() {

  return 0;
}