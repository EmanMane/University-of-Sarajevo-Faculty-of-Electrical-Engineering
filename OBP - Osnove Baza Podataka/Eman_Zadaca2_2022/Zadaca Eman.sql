SELECT * FROM KONTINENT;
SELECT * FROM DRZAVA;
SELECT * FROM GRAD;
SELECT * FROM LOKACIJA;
SELECT * FROM FIZICKO_LICE;
SELECT * FROM PRAVNO_LICE;
SELECT * FROM PROIZVODJAC;
SELECT * FROM KURIRSKA_SLUZBA;
SELECT * FROM UGOVOR_ZA_PRAVNO_LICE;
SELECT * FROM KUPAC;
SELECT * FROM UPOSLENIK;
SELECT * FROM ODJEL;
SELECT * FROM UGOVOR_ZA_UPOSLENIKA;
SELECT * FROM SKLADISTE;
SELECT * FROM KATEGORIJA;
SELECT * FROM POPUST;
SELECT * FROM PROIZVOD;
SELECT * FROM KOLICINA;
SELECT * FROM GARANCIJA;
SELECT * FROM ISPORUKA;
SELECT * FROM NARUDZBA_PROIZVODA;
SELECT * FROM FAKTURA;


--Zadatak1.

ALTER SESSION SET CURRENT_SCHEMA = erd;

--1.
SELECT DISTINCT prl.naziv AS ResNaziv
FROM pravno_lice prl, fizicko_lice fzl, lokacija l
WHERE prl.lokacija_id=l.lokacija_id AND fzl.lokacija_id=l.lokacija_id AND
EXISTS (SELECT lokacija.lokacija_id
        FROM lokacija, fizicko_lice, pravno_lice
        WHERE lokacija.lokacija_id=fizicko_lice.lokacija_id AND pravno_lice.lokacija_id=lokacija.lokacija_id AND fizicko_lice.lokacija_id=pravno_lice.lokacija_id);

--1. PROVJERA Rezultat: 207
SELECT Sum(Length(ResNaziv)*3) FROM
(SELECT DISTINCT prl.naziv AS ResNaziv
FROM pravno_lice prl, fizicko_lice fzl, lokacija l
WHERE prl.lokacija_id=l.lokacija_id AND fzl.lokacija_id=l.lokacija_id AND
EXISTS (SELECT lokacija.lokacija_id
        FROM lokacija, fizicko_lice, pravno_lice
        WHERE lokacija.lokacija_id=fizicko_lice.lokacija_id AND pravno_lice.lokacija_id=lokacija.lokacija_id AND fizicko_lice.lokacija_id=pravno_lice.lokacija_id));

--1. SLANJE Rezultat: 483
SELECT Sum(Length(ResNaziv)*7) FROM
(SELECT DISTINCT prl.naziv AS ResNaziv
FROM pravno_lice prl, fizicko_lice fzl, lokacija l
WHERE prl.lokacija_id=l.lokacija_id AND fzl.lokacija_id=l.lokacija_id AND
EXISTS (SELECT lokacija.lokacija_id
        FROM lokacija, fizicko_lice, pravno_lice
        WHERE lokacija.lokacija_id=fizicko_lice.lokacija_id AND pravno_lice.lokacija_id=lokacija.lokacija_id AND fizicko_lice.lokacija_id=pravno_lice.lokacija_id));

--2.
SELECT DISTINCT To_Char(ugpl.datum_potpisivanja,'dd.MM.yyyy') AS "Datum Potpisivanja", pl.naziv AS ResNaziv
FROM ugovor_za_pravno_lice ugpl, pravno_lice pl
WHERE ugpl.pravno_lice_id=pl.pravno_lice_id AND ugpl.datum_potpisivanja>(SELECT Min(fkt.datum_kupoprodaje)
                                                                         FROM faktura fkt, proizvod pr, narudzba_proizvoda nrp
                                                                         WHERE nrp.faktura_id=fkt.faktura_id AND pr.proizvod_id=nrp.proizvod_id AND pr.broj_mjeseci_garancije IS NOT NULL);

--2. PROVJERA Rezultat: 402
SELECT Sum(Length(ResNaziv)*3 + Length("Datum Potpisivanja")*3) FROM
(SELECT DISTINCT To_Char(ugpl.datum_potpisivanja,'dd.MM.yyyy') AS "Datum Potpisivanja", pl.naziv AS ResNaziv
FROM ugovor_za_pravno_lice ugpl, pravno_lice pl
WHERE ugpl.pravno_lice_id=pl.pravno_lice_id AND ugpl.datum_potpisivanja>(SELECT Min(fkt.datum_kupoprodaje)
                                                                         FROM faktura fkt, proizvod pr, narudzba_proizvoda nrp
                                                                         WHERE nrp.faktura_id=fkt.faktura_id AND pr.proizvod_id=nrp.proizvod_id AND pr.broj_mjeseci_garancije IS NOT NULL
                                                                        ));

--2. SLANJE Rezultat: 938
SELECT Sum(Length(ResNaziv)*7 + Length("Datum Potpisivanja")*7) FROM
(SELECT DISTINCT To_Char(ugpl.datum_potpisivanja,'dd.MM.yyyy') AS "Datum Potpisivanja", pl.naziv AS ResNaziv
FROM ugovor_za_pravno_lice ugpl, pravno_lice pl
WHERE ugpl.pravno_lice_id=pl.pravno_lice_id AND ugpl.datum_potpisivanja>(SELECT Min(fkt.datum_kupoprodaje)
                                                                         FROM faktura fkt, proizvod pr, narudzba_proizvoda nrp
                                                                         WHERE nrp.faktura_id=fkt.faktura_id AND pr.proizvod_id=nrp.proizvod_id AND pr.broj_mjeseci_garancije IS NOT NULL
                                                                        ));

--3.
SELECT naziv
FROM proizvod
WHERE kategorija_id = ANY (SELECT prz.kategorija_id
                           FROM proizvod prz, kolicina kol
                           WHERE prz.proizvod_id=kol.proizvod_id AND (SELECT Max(k.kolicina_proizvoda)
                                 FROM kolicina k, proizvod p
                                 WHERE p.proizvod_id=k.proizvod_id) = kol.kolicina_proizvoda);

--3. PROVJERA Rezultat: 51
SELECT Sum(Length(naziv)*3) FROM
(SELECT naziv
FROM proizvod
WHERE kategorija_id = ANY (SELECT prz.kategorija_id
                           FROM proizvod prz, kolicina kol
                           WHERE prz.proizvod_id=kol.proizvod_id AND (SELECT Max(k.kolicina_proizvoda)
                                 FROM kolicina k, proizvod p
                                 WHERE p.proizvod_id=k.proizvod_id) = kol.kolicina_proizvoda));

--3. SLANJE Rezultat: 119
SELECT Sum(Length(naziv)*7) FROM
(SELECT naziv
FROM proizvod
WHERE kategorija_id = ANY (SELECT prz.kategorija_id
                           FROM proizvod prz, kolicina kol
                           WHERE prz.proizvod_id=kol.proizvod_id AND (SELECT Max(k.kolicina_proizvoda)
                                 FROM kolicina k, proizvod p
                                 WHERE p.proizvod_id=k.proizvod_id) = kol.kolicina_proizvoda));

--4.
SELECT prz.naziv AS "Proizvod", prl.naziv AS "Proizvodjac"
FROM proizvod prz, proizvodjac przv, pravno_lice prl
WHERE przv.proizvodjac_id=prz.proizvodjac_id AND prl.pravno_lice_id=przv.proizvodjac_id
      AND przv.proizvodjac_id IN(SELECT proizvodjac.proizvodjac_id
                                    FROM proizvodjac
                                    WHERE EXISTS(SELECT * FROM proizvod pro WHERE pro.cijena>(SELECT Avg(cijena) FROM proizvod) AND proizvodjac.proizvodjac_id=pro.proizvodjac_id));

--4. PROVJERA Rezultat: 504
SELECT Sum(Length("Proizvod")*3 + Length("Proizvodjac")*3) FROM
(SELECT prz.naziv AS "Proizvod", prl.naziv AS "Proizvodjac"
FROM proizvod prz, proizvodjac przv, pravno_lice prl
WHERE przv.proizvodjac_id=prz.proizvodjac_id AND prl.pravno_lice_id=przv.proizvodjac_id
      AND przv.proizvodjac_id IN(SELECT proizvodjac.proizvodjac_id
                                    FROM proizvodjac
                                    WHERE EXISTS(SELECT * FROM proizvod pro WHERE pro.cijena>(SELECT Avg(cijena) FROM proizvod) AND proizvodjac.proizvodjac_id=pro.proizvodjac_id)));

--4. SLANJE Rezultat: 1176
SELECT Sum(Length("Proizvod")*7 + Length("Proizvodjac")*7) FROM
(SELECT prz.naziv AS "Proizvod", prl.naziv AS "Proizvodjac"
FROM proizvod prz, proizvodjac przv, pravno_lice prl
WHERE przv.proizvodjac_id=prz.proizvodjac_id AND prl.pravno_lice_id=przv.proizvodjac_id
      AND przv.proizvodjac_id IN(SELECT proizvodjac.proizvodjac_id
                                    FROM proizvodjac
                                    WHERE EXISTS(SELECT * FROM proizvod pro WHERE pro.cijena>(SELECT Avg(cijena) FROM proizvod) AND proizvodjac.proizvodjac_id=pro.proizvodjac_id)));

--5.
SELECT fzl.ime || ' ' || fzl.prezime AS "Ime i prezime", Sum(fkt.iznos) AS "iznos"
FROM fizicko_lice fzl, kupac kpc, uposlenik ups, faktura fkt
WHERE fzl.fizicko_lice_id=ups.uposlenik_id AND kpc.kupac_id=fzl.fizicko_lice_id AND fzl.fizicko_lice_id=fkt.kupac_id
HAVING Sum(fkt.iznos)> (SELECT Round(Avg(Sum(faktura.iznos)),2)
                        FROM faktura, fizicko_lice, kupac
                        WHERE fizicko_lice.fizicko_lice_id=faktura.kupac_id AND kupac.kupac_id=faktura.kupac_id
                        GROUP BY fizicko_lice.ime,fizicko_lice.prezime)
GROUP BY fzl.ime,fzl.prezime;

--5. PROVJERA Rezultat: 6897
SELECT Sum(Length("Ime i prezime")*3 + "iznos"*3) FROM
(SELECT fzl.ime || ' ' || fzl.prezime AS "Ime i prezime", Sum(fkt.iznos) AS "iznos"
FROM fizicko_lice fzl, kupac kpc, uposlenik ups, faktura fkt
WHERE fzl.fizicko_lice_id=ups.uposlenik_id AND kpc.kupac_id=fzl.fizicko_lice_id AND fzl.fizicko_lice_id=fkt.kupac_id
HAVING Sum(fkt.iznos)> (SELECT Round(Avg(Sum(faktura.iznos)),2)
                        FROM faktura, fizicko_lice, kupac
                        WHERE fizicko_lice.fizicko_lice_id=faktura.kupac_id AND kupac.kupac_id=faktura.kupac_id
                        GROUP BY fizicko_lice.ime,fizicko_lice.prezime)
GROUP BY fzl.ime,fzl.prezime);

--5. SLANJE Rezultat: 16093
SELECT Sum(Length("Ime i prezime")*7 + "iznos"*7) FROM
(SELECT fzl.ime || ' ' || fzl.prezime AS "Ime i prezime", Sum(fkt.iznos) AS "iznos"
FROM fizicko_lice fzl, kupac kpc, uposlenik ups, faktura fkt
WHERE fzl.fizicko_lice_id=ups.uposlenik_id AND kpc.kupac_id=fzl.fizicko_lice_id AND fzl.fizicko_lice_id=fkt.kupac_id
HAVING Sum(fkt.iznos)> (SELECT Round(Avg(Sum(faktura.iznos)),2)
                        FROM faktura, fizicko_lice, kupac
                        WHERE fizicko_lice.fizicko_lice_id=faktura.kupac_id AND kupac.kupac_id=faktura.kupac_id
                        GROUP BY fizicko_lice.ime,fizicko_lice.prezime)
GROUP BY fzl.ime,fzl.prezime);

--6
SELECT prl.naziv AS "naziv"
FROM kurirska_sluzba krs, pravno_lice prl
WHERE prl.pravno_lice_id=krs.kurirska_sluzba_id
     AND (SELECT Sum(kolicina.kolicina_proizvoda)
          FROM faktura, isporuka, proizvod, narudzba_proizvoda, popust, kolicina
          WHERE kolicina.proizvod_id=proizvod.proizvod_id AND faktura.isporuka_id=isporuka.isporuka_id AND faktura.faktura_id=narudzba_proizvoda.faktura_id AND narudzba_proizvoda.popust_id=popust.popust_id
                AND narudzba_proizvoda.proizvod_id=proizvod.proizvod_id AND isporuka.kurirska_sluzba_id=krs.kurirska_sluzba_id
                AND narudzba_proizvoda.popust_id IS NOT NULL)
          =(SELECT Max(Sum(kolicina.kolicina_proizvoda))
          FROM faktura, isporuka, proizvod, narudzba_proizvoda, popust, kolicina
          WHERE kolicina.proizvod_id=proizvod.proizvod_id AND faktura.faktura_id=narudzba_proizvoda.faktura_id AND faktura.isporuka_id=isporuka.isporuka_id
                AND narudzba_proizvoda.popust_id=popust.popust_id
                AND narudzba_proizvoda.proizvod_id=proizvod.proizvod_id AND narudzba_proizvoda.popust_id IS NOT NULL
          GROUP BY krs.kurirska_sluzba_id);

--6. Rezultat: 18
SELECT Sum(Length("naziv")*3) FROM
(SELECT prl.naziv AS "naziv"
FROM kurirska_sluzba krs, pravno_lice prl
WHERE prl.pravno_lice_id=krs.kurirska_sluzba_id
     AND (SELECT Sum(kolicina.kolicina_proizvoda)
          FROM faktura, isporuka, proizvod, narudzba_proizvoda, popust, kolicina
          WHERE kolicina.proizvod_id=proizvod.proizvod_id AND faktura.isporuka_id=isporuka.isporuka_id AND faktura.faktura_id=narudzba_proizvoda.faktura_id AND narudzba_proizvoda.popust_id=popust.popust_id
                AND narudzba_proizvoda.proizvod_id=proizvod.proizvod_id AND isporuka.kurirska_sluzba_id=krs.kurirska_sluzba_id
                AND narudzba_proizvoda.popust_id IS NOT NULL)
          =(SELECT Max(Sum(kolicina.kolicina_proizvoda))
          FROM faktura, isporuka, proizvod, narudzba_proizvoda, popust, kolicina
          WHERE kolicina.proizvod_id=proizvod.proizvod_id AND faktura.faktura_id=narudzba_proizvoda.faktura_id AND faktura.isporuka_id=isporuka.isporuka_id
                AND narudzba_proizvoda.popust_id=popust.popust_id
                AND narudzba_proizvoda.proizvod_id=proizvod.proizvod_id AND narudzba_proizvoda.popust_id IS NOT NULL
          GROUP BY krs.kurirska_sluzba_id));

--6. Rezultat: 42
SELECT Sum(Length("naziv")*7) FROM
(SELECT prl.naziv AS "naziv"
FROM kurirska_sluzba krs, pravno_lice prl
WHERE prl.pravno_lice_id=krs.kurirska_sluzba_id
     AND (SELECT Sum(kolicina.kolicina_proizvoda)
          FROM faktura, isporuka, proizvod, narudzba_proizvoda, popust, kolicina
          WHERE kolicina.proizvod_id=proizvod.proizvod_id AND faktura.isporuka_id=isporuka.isporuka_id AND faktura.faktura_id=narudzba_proizvoda.faktura_id AND narudzba_proizvoda.popust_id=popust.popust_id
                AND narudzba_proizvoda.proizvod_id=proizvod.proizvod_id AND isporuka.kurirska_sluzba_id=krs.kurirska_sluzba_id
                AND narudzba_proizvoda.popust_id IS NOT NULL)
          =(SELECT Max(Sum(kolicina.kolicina_proizvoda))
          FROM faktura, isporuka, proizvod, narudzba_proizvoda, popust, kolicina
          WHERE kolicina.proizvod_id=proizvod.proizvod_id AND faktura.faktura_id=narudzba_proizvoda.faktura_id AND faktura.isporuka_id=isporuka.isporuka_id
                AND narudzba_proizvoda.popust_id=popust.popust_id
                AND narudzba_proizvoda.proizvod_id=proizvod.proizvod_id AND narudzba_proizvoda.popust_id IS NOT NULL
          GROUP BY krs.kurirska_sluzba_id));

--7.
SELECT fl.ime || ' ' || fl.prezime AS "Kupac", Sum(n.kolicina_jednog_proizvoda*(pr.cijena*(pp.postotak)/100)) AS "Usteda"
FROM popust pp, proizvod pr, narudzba_proizvoda n, faktura f, kupac k, fizicko_lice fl
WHERE pp.popust_id=n.popust_id AND n.proizvod_id=pr.proizvod_id AND f.kupac_id=k.kupac_id AND f.faktura_id=n.faktura_id AND k.kupac_id=fl.fizicko_lice_id
GROUP BY (ime,prezime);

--7. Rezultat: 17709
SELECT Sum(Length("Kupac")*3 + Round("Usteda")*3) FROM
(SELECT fl.ime || ' ' || fl.prezime AS "Kupac", Sum(n.kolicina_jednog_proizvoda*(pr.cijena*(pp.postotak)/100)) AS "Usteda"
FROM popust pp, proizvod pr, narudzba_proizvoda n, faktura f, kupac k, fizicko_lice fl
WHERE pp.popust_id=n.popust_id AND n.proizvod_id=pr.proizvod_id AND f.kupac_id=k.kupac_id AND f.faktura_id=n.faktura_id AND k.kupac_id=fl.fizicko_lice_id
GROUP BY (ime,prezime));

--7. Rezultat: 41321
SELECT Sum(Length("Kupac")*7 + Round("Usteda")*7) FROM
(SELECT fl.ime || ' ' || fl.prezime AS "Kupac", Sum(n.kolicina_jednog_proizvoda*(pr.cijena*(pp.postotak)/100)) AS "Usteda"
FROM popust pp, proizvod pr, narudzba_proizvoda n, faktura f, kupac k, fizicko_lice fl
WHERE pp.popust_id=n.popust_id AND n.proizvod_id=pr.proizvod_id AND f.kupac_id=k.kupac_id AND f.faktura_id=n.faktura_id AND k.kupac_id=fl.fizicko_lice_id
GROUP BY (ime,prezime));


--8.
SELECT DISTINCT i.isporuka_id AS idisporuke, k.kurirska_sluzba_id AS idkurirske
FROM isporuka i, faktura f, proizvod p, narudzba_proizvoda n, popust pp, kurirska_sluzba k
WHERE f.isporuka_id=i.isporuka_id AND p.proizvod_id=n.proizvod_id AND pp.popust_id=n.popust_id AND f.faktura_id=n.faktura_id AND k.kurirska_sluzba_id=i.kurirska_sluzba_id
      AND pp.postotak IS NOT NULL AND p.broj_mjeseci_garancije IS NOT NULL;


--8. Rezultat: 243
 SELECT Sum(idisporuke*3 + idkurirske*3) FROM
(SELECT DISTINCT i.isporuka_id AS idisporuke, k.kurirska_sluzba_id AS idkurirske
FROM isporuka i, faktura f, proizvod p, narudzba_proizvoda n, popust pp, kurirska_sluzba k
WHERE f.isporuka_id=i.isporuka_id AND p.proizvod_id=n.proizvod_id AND pp.popust_id=n.popust_id AND f.faktura_id=n.faktura_id AND k.kurirska_sluzba_id=i.kurirska_sluzba_id
      AND pp.postotak IS NOT NULL AND p.broj_mjeseci_garancije IS NOT NULL);

--8. Rezultat: 567
 SELECT Sum(idisporuke*7 + idkurirske*7) FROM
(SELECT DISTINCT i.isporuka_id AS idisporuke, k.kurirska_sluzba_id AS idkurirske
FROM isporuka i, faktura f, proizvod p, narudzba_proizvoda n, popust pp, kurirska_sluzba k
WHERE f.isporuka_id=i.isporuka_id AND p.proizvod_id=n.proizvod_id AND pp.popust_id=n.popust_id AND f.faktura_id=n.faktura_id AND k.kurirska_sluzba_id=i.kurirska_sluzba_id
      AND pp.postotak IS NOT NULL AND p.broj_mjeseci_garancije IS NOT NULL);

--9.
SELECT naziv, cijena
FROM proizvod
WHERE cijena>(SELECT Round(Avg(Max(cijena)),2)
              FROM proizvod
              GROUP BY kategorija_id);

--9. Rezultat: 9210
 SELECT Sum(Length(naziv)*3 + cijena*3) FROM
(SELECT naziv, cijena
FROM proizvod
WHERE cijena>(SELECT Round(Avg(Max(cijena)),2)
              FROM proizvod
              GROUP BY kategorija_id));

--9. Rezultat: 21490
SELECT Sum(Length(naziv)*7 + cijena*7) FROM
(SELECT naziv, cijena
FROM proizvod
WHERE cijena>(SELECT Round(Avg(Max(cijena)),2)
              FROM proizvod
              GROUP BY kategorija_id));

--10.
SELECT p.naziv, p.cijena
FROM proizvod p, kategorija k
WHERE p.kategorija_id = k.kategorija_id AND p.cijena < ALL(SELECT Avg(proizvod.cijena)
                                                           FROM proizvod, kategorija nadk, kategorija
                                                           WHERE nadk.kategorija_id!=p.kategorija_id AND nadk.kategorija_id=kategorija.nadkategorija_id
                                                           GROUP BY proizvod.kategorija_id);

--10. Rezultat: 2448
SELECT Sum(Length(naziv)*3 + Round(cijena)*3) FROM
(SELECT p.naziv, p.cijena
FROM proizvod p, kategorija k
WHERE p.kategorija_id = k.kategorija_id AND p.cijena < ALL(SELECT Avg(proizvod.cijena)
                                                           FROM proizvod, kategorija nadk, kategorija
                                                           WHERE nadk.kategorija_id!=p.kategorija_id AND nadk.kategorija_id=kategorija.nadkategorija_id
                                                           GROUP BY proizvod.kategorija_id));

--10. Rezultat: 5712
SELECT Sum(Length(naziv)*7 + Round(cijena)*7) FROM
(SELECT p.naziv, p.cijena
FROM proizvod p, kategorija k
WHERE p.kategorija_id = k.kategorija_id AND p.cijena < ALL(SELECT Avg(proizvod.cijena)
                                                           FROM proizvod, kategorija nadk, kategorija
                                                           WHERE nadk.kategorija_id!=p.kategorija_id AND nadk.kategorija_id=kategorija.nadkategorija_id
                                                           GROUP BY proizvod.kategorija_id));

--Zadatak2.

--Kreiranje tabela
CREATE TABLE TabelaA(id NUMBER(20),
                     naziv VARCHAR(50),
                     datum DATE,
                     cijelibroj NUMBER(20),
                     realnibroj NUMBER(20,2),
                     CONSTRAINT con_pr_a PRIMARY KEY(id),
                     CONSTRAINT con_cijeli_a CHECK(cijelibroj NOT BETWEEN 5 AND 15),
                     CONSTRAINT con_realni_a CHECK(realnibroj>5));

CREATE TABLE TabelaB(id NUMBER(20),
                     naziv VARCHAR(50),
                     datum DATE,
                     cijelibroj NUMBER(20),
                     realnibroj NUMBER(20,2),
                     fktabelaa NUMBER(20) NOT NULL,
                     CONSTRAINT con_pr_b PRIMARY KEY(id),
                     CONSTRAINT con_cijeli_b UNIQUE(cijelibroj),
                     CONSTRAINT con_a_fk FOREIGN KEY (fktabelaa) REFERENCES tabelaa(id)
                     );

CREATE TABLE TabelaC(id NUMBER(20),
                     naziv VARCHAR(50) not null,
                     datum DATE,
                     cijelibroj NUMBER(20) not null,
                     realnibroj NUMBER(20,2),
                     fktabelab NUMBER(20),
                     CONSTRAINT con_pr_bc PRIMARY KEY(id),
                     CONSTRAINT FkCnst FOREIGN KEY (fktabelab) REFERENCES tabelab(id)
                     );

INSERT INTO tabelaA VALUES (1,'tekst',NULL,NULL,6.2);
INSERT INTO tabelaA VALUES (2,NULL,NULL,3,5.26);
INSERT INTO tabelaA VALUES (3,'tekst',NULL,1,NULL);
INSERT INTO tabelaA VALUES (4,NULL,NULL,NULL,NULL);
INSERT INTO tabelaA VALUES (5,'tekst',NULL,16,6.78);

INSERT INTO tabelaB VALUES (1,null,NULL,1,null,1);
INSERT INTO tabelaB VALUES (2,NULL,NULL,3,null,1);
INSERT INTO tabelaB VALUES (3,NULL,NULL,6,NULL,2);
INSERT INTO tabelaB VALUES (4,NULL,NULL,11,NULL,2);
INSERT INTO tabelaB VALUES (5,NULL,NULL,22,null,3);

INSERT INTO tabelaC VALUES (1,'YES',NULL,33,null,4);
INSERT INTO tabelaC VALUES (2,'NO',NULL,33,null,2);
INSERT INTO tabelaC VALUES (3,'NO',NULL,55,NULL,1);

--Testiranje komandi:

INSERT INTO TabelaA (id,naziv,datum,cijeliBroj,realniBroj) VALUES (6,'tekst',null,null,6.20);
--OK

INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (6,null,null,1,null,1);
--notOK - ne mo�emo unijeti red jer tabela ima ogranicenje da cijeli broj (4. kolona) mora biti unique, a vec postoji red u tabli sa vrjednoscu 1 u navedenoj koloni.

INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (7,null,null,123,null,6);
--OK

INSERT INTO TabelaC (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaB) VALUES (4,'NO',null,55,null,null);
--OK

Update TabelaA set naziv = 'tekst' Where naziv is null and cijeliBroj is not null;
--OK

Drop table tabelaB;
--notOK - ne mo�emo uraditi Drop jer se strani kljuc koji je povezan sa primarnim kljucem tabele nalazi u tabeli C.

Delete from TabelaA where realniBroj is null;
--notOK - ako bismo brisali iz tabele A, ne bi vise postojao strani kljuc koji se nalazi u tabeli B

Delete from TabelaA where id = 5;
--OK

Update TabelaB set fktabelaA = 4 where fktabelaA = 2;
--OK

Alter Table tabelaA add Constraint cst Check (naziv like 'tekst');
--OK

--Rezultati za provjeru su:
Select Sum(id) From TabelaA;
--Rezultat 16

Select Sum(id) FROM TabelaB;
--Rezultat 22

Select Sum(id) From TabelaC;
--Rezultat 10

--Zadatak3.
DROP TABLE TabelaC;

DROP TABLE TabelaB;

DROP TABLE TabelaA;

DROP TABLE TabelaABekap;

DROP TABLE TabelaBCheck;

DROP PROCEDURE p;

DROP SEQUENCE seq1;

DROP SEQUENCE seq2;

DROP TRIGGER triger1;

DROP TRIGGER triger2;

SELECT * FROM tabelaC;

SELECT * FROM tabelaB;

SELECT * FROM tabelaA;

CREATE TABLE TabelaA(id NUMBER(20),
                     naziv VARCHAR(50),
                     datum DATE,
                     cijelibroj NUMBER(20),
                     realnibroj NUMBER(20,2),
                     CONSTRAINT con_pr_a PRIMARY KEY(id),
                     CONSTRAINT con_cijeli_a CHECK(cijelibroj NOT BETWEEN 5 AND 15),
                     CONSTRAINT con_realni_a CHECK(realnibroj>5));

CREATE TABLE TabelaB(id NUMBER(20),
                     naziv VARCHAR(50),
                     datum DATE,
                     cijelibroj NUMBER(20),
                     realnibroj NUMBER(20,2),
                     fktabelaa NUMBER(20) NOT NULL,
                     CONSTRAINT con_pr_b PRIMARY KEY(id),
                     CONSTRAINT con_cijeli_b UNIQUE(cijelibroj),
                     CONSTRAINT con_a_fk FOREIGN KEY (fktabelaa) REFERENCES tabelaa(id));

CREATE TABLE TabelaC(id NUMBER(20),
                     naziv VARCHAR(50) not null,
                     datum DATE,
                     cijelibroj NUMBER(20) not null,
                     realnibroj NUMBER(20,2),
                     fktabelab NUMBER(20),
                     CONSTRAINT con_pr_bc PRIMARY KEY(id),
                     CONSTRAINT FkCnst FOREIGN KEY (fktabelab) REFERENCES tabelab(id));

INSERT INTO tabelaA VALUES (1,'tekst',NULL,NULL,6.2);
INSERT INTO tabelaA VALUES (2,NULL,NULL,3,5.26);
INSERT INTO tabelaA VALUES (3,'tekst',NULL,1,NULL);
INSERT INTO tabelaA VALUES (4,NULL,NULL,NULL,NULL);
INSERT INTO tabelaA VALUES (5,'tekst',NULL,16,6.78);

INSERT INTO tabelaB VALUES (1,null,NULL,1,null,1);
INSERT INTO tabelaB VALUES (2,NULL,NULL,3,null,1);
INSERT INTO tabelaB VALUES (3,NULL,NULL,6,NULL,2);
INSERT INTO tabelaB VALUES (4,NULL,NULL,11,NULL,2);
INSERT INTO tabelaB VALUES (5,NULL,NULL,22,null,3);

INSERT INTO tabelaC VALUES (1,'YES',NULL,33,null,4);
INSERT INTO tabelaC VALUES (2,'NO',NULL,33,null,2);
INSERT INTO tabelaC VALUES (3,'NO',NULL,55,NULL,1);

CREATE SEQUENCE seq1
INCREMENT BY 1
START WITH 1
NOMAXVALUE
NOCACHE
NOCYCLE;

CREATE SEQUENCE seq2
INCREMENT BY 1
START WITH 1
NOMAXVALUE
NOCACHE
NOCYCLE;

CREATE TABLE TabelaABekap(id NUMBER(20),
                     naziv VARCHAR(50),
                     datum DATE,
                     cijelibroj NUMBER(20),
                     realnibroj NUMBER(20,2),
                     cijeliBrojB integer,
                     sekvenca integer,
                     CONSTRAINT con_pr_bek PRIMARY KEY(id),
                     CONSTRAINT con_cijeli_bek CHECK(cijelibroj NOT BETWEEN 5 AND 15),
                     CONSTRAINT con_realni_bek CHECK(realnibroj>5));

CREATE TABLE TabelaBCheck(sekvenca INTEGER PRIMARY KEY);

CREATE OR REPLACE TRIGGER ztrig1
AFTER INSERT
ON tabelab
FOR EACH ROW
DECLARE
  a_id NUMBER;
  a_naziv VARCHAR2(20);
  a_datum DATE;
  a_cijelibroj NUMBER;
  a_realnibroj NUMBER;
  a_brojac NUMBER :=0;

BEGIN
  SELECT a.id, a.naziv, a.datum, a.cijelibroj, a.realnibroj
  INTO a_id, a_naziv, a_datum, a_cijelibroj, a_realnibroj
  FROM tabelaa a
  WHERE :new.fktabelaa = a.id;

  SELECT Count(*)
  INTO a_brojac
  FROM tabelaabekap ab
  WHERE ab.id = a_id;

  IF a_brojac = 1
    THEN
      UPDATE tabelaabekap
      SET cijelibrojb = cijelibrojb + :new.cijelibroj
      WHERE id = a_id;
  ELSE
    INSERT INTO tabelaabekap
    VALUES (a_id, a_naziv, a_datum, a_cijelibroj, a_realnibroj, :new.cijelibroj, seq1.NEXTVAL);
  END IF;
END;
/

CREATE OR REPLACE TRIGGER ztrig2
AFTER DELETE
ON tabelab
BEGIN
INSERT INTO tabelabcheck VALUES(seq2.NEXTVAL-1);
END;
/

CREATE OR REPLACE PROCEDURE mojaprocedura (parametar NUMBER)
  IS
   ponavljanja NUMBER :=0;
   prvi_id NUMBER :=0;
  BEGIN
   SELECT Sum(cijelibroj)
   INTO ponavljanja
   FROM tabelaa;

   SELECT Max(id)
   INTO prvi_id
   FROM tabelac;

   FOR i IN 1..ponavljanja LOOP
      INSERT INTO tabelac VALUES(prvi_id+i, 'x', NULL, parametar, NULL, NULL);
   END LOOP;
   END;
/

--UNOS KOMANDI:
INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (6,null,null,2,null,1);
INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (7,null,null,4,null,2);
INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (8,null,null,8,null,1);
INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (9,null,null,5,null,3);
INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (10,null,null,7,null,3);
INSERT INTO TabelaB (id,naziv,datum,cijeliBroj,realniBroj,FkTabelaA) VALUES (11,null,null,9,null,5);
Delete From TabelaB where id not in (select FkTabelaB from TabelaC);
Alter TABLE tabelaC drop constraint FkCnst;
Delete from TabelaB where 1=1;
--izvrsenje procedure na kraju sa call NazivProcedure(1);
call mojaprocedura(1);
--Rezultati poziva su:
Select SUM(id*3 + cijeliBrojB*3) from TabelaABekap;
--138
Select Sum(id*3 + cijeliBroj*3) from TabelaC;
--1251
Select Sum(MOD(sekvenca,10)*3) from TabelaBCheck;
--9
--Potrebno je utvditi rezultate poziva:
Select SUM(id*7 + cijeliBrojB*7) from TabelaABekap;
--322
Select Sum(id*7 + cijeliBroj*7) from TabelaC;
--2919
Select Sum(MOD(sekvenca,10)*7) from TabelaBCheck;
--21
