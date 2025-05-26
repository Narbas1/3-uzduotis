
## Programos paleidimo instrukcija ir reikalavimai:

1. Reikia turėti cmake ir c++ compiler.
2. Yra 3 programos kurios skiriasi naudojamais duomenų konteineriais (vector, deque ir list).
3. Atidarykite norimą aplanką ir paleiskite .bat failą.

---

## v0.1

## Pagrindines programos funkcijos:

    -Saugoti studentu duomenis (varda, pavarde, namu darbu pazymius ir egzamino rezultata) vektoriuje.
    -Duomenis ivesti paciam, sugeneruoti arba nuskaityti is failo.
    -Ivesti tam tikra namu darbu pazymiu skaiciu.
    -Skaiciuoti galutini pazymi naudojant namu darbu pazymiu vidurki arba mediana.
    -Isvesti studento rezultatus (pavarde, varda ir galutini pazymi) terminale arba faile.
    -Rikiuoti studentus pagal ju pavarde arba galutini pazymi.

---

## v0.2

##  Testavimo atvejai su skirtingais kiekiais studentu:

    Testavimas buvo daromas su chrono biblioteka. Buvo matuojamas laikas per kuri yra suskaiciuojami studentu galutiniai pazymiai, surikiuojami pagal naudotojo pasirinkima ir isspausdinami i terminala arba atskira faila.

    -10 000 studentu(15 pazymiu) - ~0,4 sekundes.
    -100 000 studentu(20 pazymiu) - ~5 sekundes.
    -1 000 000 studentu(7 pazymiai) - ~20 sekundziu.

---

# v0.3

Pridėtas išimčių valdymas, ko pasekoje mažesnis šansas programai nustoti veikti, kai naudotojas įveda netinkamą reikšmę.
Taipogi kodas išskirstytas į 2 .cpp ir 2 .h failus.


---

# v0.4 

Failu generavimas:

<img width="193" alt="gen4" src="https://github.com/user-attachments/assets/c795a15d-1552-4139-862b-b081a02310f2" />
<img width="190" alt="gen3" src="https://github.com/user-attachments/assets/2d563dea-9b3a-41ea-85c5-38640b672fdb" />
<img width="188" alt="gen2" src="https://github.com/user-attachments/assets/62e4a9e7-2616-4ccd-a8ea-2f66b960a0f2" />
<img width="197" alt="gen1" src="https://github.com/user-attachments/assets/f940fe21-2b9c-4499-b402-0b3c096c7a8e" />
<img width="197" alt="gen5" src="https://github.com/user-attachments/assets/3b83c6f5-fed3-403b-ae85-1bd4843575d7" />

Vidurkiai:
1000 stud. - 0.0177s
10000 stud. - 0.0602s
100000 stud. - 0.3074s
1000000 stud. - 3.2566s
10000000 stud. - 27.9020s

Programa suskirsto nepažangius ir pažangius studentus į du konteinerius ir išveda į failą. Taipogi buvo atlikti spartos testavimai:
(Į visos programos laiką yra iskaičiuoti duomenų struktūrų clearinimai.)

| Duomenu struktura | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| VECTOR            | 1000              | 0.0226      | 0.0003     | 0.0001           | 0.0000            | 0.0345                 |
| VECTOR            | 10000             | 0.1410      | 0.0011     | 0.0005           | 0.0004            | 0.1738                 |
| VECTOR            | 100000            | 1.1356      | 0.0100     | 0.0061           | 0.0045            | 1.4282                 |
| VECTOR            | 1000000           | 10.9439     | 0.0998     | 0.0712           | 0.0508            | 13.7958                |
| VECTOR            | 10000000          | 106.5451    | 0.9422     | 0.8096           | 0.5705            | 137.4656               |

---

# v1.0

Buvo atlikti testai su skirtingomis studentu skirstymo kategorijomis ir skirtingais duomenu konteineriais:

    1. Pirma strategija: kuriami 2 nauji konteineriai nepazangiems ir pazangiems studentams.
    2. Antra strategija: kuriamas tik vienas naujas konteineris nepazangiems studentams, o pazangus yra paliekami bendrame studentu konteineryje
    3. Trecia strategija: panaudojama efektyvus STL algoritmai studentu skirstymui, naudojami du nauji konteineriai kaip ir pirmoje strategijoje.


Su std::list ir std::vector, programos laikas buvo panasus su visomis trijomis strategijomis, std::deque antroje strategijoje veike greiciausiai.
Taciau su std::vector programa veikia greiciausiai visomis strategijomis.
Greiciausias studentu skirstymas i konteinerius buvo su std::vector antroje kategorijoje. 

(Visi tikslūs duomenys yra pateikti "testavimas" aplanke).


PIRMOS STRATEGIJOS VIDURKIAI:

| Duomenu struktura | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| VECTOR            | 1000              | 0.0226      | 0.0003     | 0.0001           | 0.0000            | 0.0345                 |
| VECTOR            | 10000             | 0.1410      | 0.0011     | 0.0005           | 0.0004            | 0.1738                 |
| VECTOR            | 100000            | 1.1356      | 0.0100     | 0.0061           | 0.0045            | 1.4282                 |
| VECTOR            | 1000000           | 10.9439     | 0.0998     | 0.0712           | 0.0508            | 13.7958                |
| VECTOR            | 10000000          | 106.5451    | 0.9422     | 0.8096           | 0.5705            | 137.4656               |

| Duomenu struktura | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| DEQUE             | 1000              | 0.0255      | 0.0009     | 0.0002           | 0.0001            | 0.0325                 |
| DEQUE             | 10000             | 0.1247      | 0.0031     | 0.0018           | 0.0019            | 0.1601                 |
| DEQUE             | 100000            | 1.2193      | 0.0335     | 0.0317           | 0.0218            | 1.5587                 |
| DEQUE             | 1000000           | 11.8474     | 0.4473     | 0.3554           | 0.2591            | 15.4173                |
| DEQUE             | 10000000          | 115.3710    | 17.9229    | 5.8130           | 3.2740            | 171.1180               |

| Duomenu struktura | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| LIST              | 1000              | 0.0259      | 0.0004     | 0.0001           | 0.0001            | 0.0315                 |
| LIST              | 10000             | 0.1312      | 0.0026     | 0.0007           | 0.0006            | 0.1661                 |
| LIST              | 100000            | 1.1583      | 0.0321     | 0.0157           | 0.0111            | 1.4773                 |
| LIST              | 1000000           | 11.2576     | 0.2440     | 0.2751           | 0.1769            | 14.5437                |
| LIST              | 10000000          | 112.2425    | 2.3491     | 4.3532           | 3.5194            | 151.1853               |

ANTROS STRATEGIJOS VIDURKIAI:

| Duomenu struktura | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| VECTOR            | 1000              | 0.0221      | 0.0001     | 0.0001           | 0.0001            | 0.0335                 |
| VECTOR            | 10000             | 0.1290      | 0.0004     | 0.0004           | 0.0004            | 0.1593                 |
| VECTOR            | 100000            | 1.0768      | 0.0044     | 0.0060           | 0.0055            | 1.3177                 |
| VECTOR            | 1000000           | 10.5127     | 0.0535     | 0.0682           | 0.0488            | 13.3517                |
| VECTOR            | 10000000          | 106.7535    | 0.5635     | 0.9038           | 0.6211            | 136.2877               |

| Duomenu struktūra | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| DEQUE             | 1000              | 0.0250      | 0.0002     | 0.0003           | 0.0002            | 0.0330                 |
| DEQUE             | 10000             | 0.1229      | 0.0010     | 0.0017           | 0.0013            | 0.1566                 |
| DEQUE             | 100000            | 1.2055      | 0.0122     | 0.0343           | 0.0225            | 1.5570                 |
| DEQUE             | 1000000           | 11.4982     | 0.1353     | 0.3383           | 0.2688            | 14.8661                |
| DEQUE             | 10000000          | 115.1534    | 1.5433     | 4.0853           | 3.0224            | 153.4777               |

| Duomenu struktūra | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| LIST              | 1000              | 0.0279      | 0.0002     | 0.0001           | 0.0000            | 0.0341                 |
| LIST              | 10000             | 0.1248      | 0.0010     | 0.0005           | 0.0004            | 0.1560                 |
| LIST              | 100000            | 1.1132      | 0.0093     | 0.0168           | 0.0099            | 1.4028                 |
| LIST              | 1000000           | 11.2146     | 0.1203     | 0.2905           | 0.1859            | 14.4400                |
| LIST              | 10000000          | 111.7623    | 1.0372     | 4.2729           | 3.4909            | 149.6851               |

TRECIOS STRATEGIJOS VIDURKIAI:

| Duomenu struktūra | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| VECTOR            | 1000              | 0.0248      | 0.0001     | 0.0001           | 0.0001            | 0.0394                 |
| VECTOR            | 10000             | 0.1192      | 0.0005     | 0.0004           | 0.0003            | 0.1473                 |
| VECTOR            | 100000            | 1.0871      | 0.0056     | 0.0056           | 0.0055            | 1.3554                 |
| VECTOR            | 1000000           | 10.9489     | 0.0608     | 0.0711           | 0.0546            | 13.5909                |
| VECTOR            | 10000000          | 106.8128    | 0.6380     | 0.8444           | 0.6203            | 136.6014               |

| Duomenu struktūra | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| DEQUE             | 1000              | 0.0318      | 0.0016     | 0.0002           | 0.0002            | 0.0410                 |
| DEQUE             | 10000             | 0.1236      | 0.0029     | 0.0021           | 0.0016            | 0.1622                 |
| DEQUE             | 100000            | 1.2469      | 0.0362     | 0.0415           | 0.0252            | 1.6059                 |
| DEQUE             | 1000000           | 11.3295     | 0.4554     | 0.3311           | 0.2381            | 14.9033                |
| DEQUE             | 10000000          | 113.1615    | 18.6010    | 6.3074           | 3.0935            | 170.6782               |

| Duomenu struktūra | Studentų skaičius | Nuskaitymas | Skirstymas | Norm. rusiavimas | Nepaž. rusiavimas | Visos programos laikas |
|-------------------|-------------------|-------------|------------|------------------|-------------------|------------------------|
| vector            | 1000              | 0.0261      | 0.0005     | 0.0001           | 0.0000            | 0.0362                 |
| vector            | 10000             | 0.1348      | 0.0020     | 0.0004           | 0.0003            | 0.1659                 |
| vector            | 100000            | 1.1388      | 0.0254     | 0.0127           | 0.0076            | 1.4495                 |
| vector            | 1000000           | 11.1509     | 0.3374     | 0.2212           | 0.1218            | 14.3329                |
| vector            | 10000000          | 111.1183    | 3.6333     | 3.6922           | 2.7921            | 151.1029               |





---

Testai buvo atlikti su šiais sistemos parametrais:
- 16GB RAM
- Intel i7-14650HX 2.20GHz CPU
- 833GB SSD

---

v1.0 versijos funkcijos:

    -Įvesti studentus ranka, generuoti arba nuskaityti iš failo.
    -Apskaičiuoti studentu galutinį pažymį naudojant arba vidurki arba medianą (namų darbų pažymių).
    -Testuojant, programa išveda pažangius ir nepažangius studentus į atskirus failus.
    -Galimybė generuoti failus programos spartos testavimui.

---

# v1.1

Struct'as pakeistas i klase. Buvo atlikti programos spartos testai su struct'u, klase ir papildomais optimizacijos flag'ais

no flags:

| Studentų kiekis | Nuskaitymas | Skirstymas | Pažangių rūšiavimas | Nepažangių rūšiavimas | Pažangių spausdinimas | Nepažangių spausdinimas | Visas laikas |
|-----------------|-------------|------------|---------------------|----------------------|----------------------|------------------------|--------------|
| 100000          | 1.7269      | 0.0137     | 0.0333              | 0.0220               | 0.2251               | 0.1300                 | 2.1510       |
| 1000000         | 11.2078     | 0.0783     | 0.2235              | 0.1904               | 1.4316               | 1.0712                 | 14.2028      |

O1:

| Studentų kiekis | Nuskaitymas | Skirstymas | Pažangių rūšiavimas | Nepažangių rūšiavimas | Pažangių spausdinimas | Nepažangių spausdinimas | Visas laikas |
|-----------------|-------------|------------|---------------------|----------------------|----------------------|------------------------|--------------|
| 100000          | 1.4228      | 0.0078     | 0.0204              | 0.0156               | 0.1415               | 0.1023                 | 1.7105       |
| 1000000         | 11.2172     | 0.0780     | 0.2627              | 0.1771               | 1.3789               | 0.9775                 | 14.0917      |

O2:

| Studentų kiekis | Nuskaitymas | Skirstymas | Pažangių rūšiavimas | Nepažangių rūšiavimas | Pažangių spausdinimas | Nepažangių spausdinimas | Visas laikas |
|-----------------|-------------|------------|---------------------|----------------------|----------------------|------------------------|--------------|
| 100000          | 1.6637      | 0.0084     | 0.0275              | 0.0182               | 0.1599               | 0.1188                 | 1.9965       |
| 1000000         | 11.0741     | 0.0757     | 0.2526              | 0.1711               | 1.4431               | 1.1465                 | 14.1631      |

O3:

| Studentų kiekis | Nuskaitymas | Skirstymas | Pažangių rūšiavimas | Nepažangių rūšiavimas | Pažangių spausdinimas | Nepažangių spausdinimas | Visas laikas |
|-----------------|-------------|------------|---------------------|----------------------|----------------------|------------------------|--------------|
| 100000          | 1.5169      | 0.0073     | 0.0203              | 0.0170               | 0.1494               | 0.1135                 | 1.8244       |
| 1000000         | 11.2250     | 0.0732     | 0.2207              | 0.1593               | 1.5693               | 1.0375                 | 14.2851      |

stuct:

| Studentų kiekis | Nuskaitymas | Skirstymas | Pažangių rūšiavimas | Nepažangių rūšiavimas | Pažangių spausdinimas | Nepažangių spausdinimas | Visas laikas |
|-----------------|-------------|------------|---------------------|----------------------|----------------------|------------------------|--------------|
| 100000          | 1.0871      | 0.0056     | 0.0056              | 0.0055               | 0.1467               | 0.1050                 | 1.3554       |
| 1000000         | 10.9489     | 0.0608     | 0.0711              | 0.0546               | 1.4081               | 1.0473                 | 13.5909      |


.exe failo dydis - 190KB


---

# v1.2

Prideta ivesties ir isvesties operatoriu perdengimas, rule of 5 metodai.
Jie visi veikia ir juos patikrinti galima meniu 7-tame pasirinkime.

Isvesties perdengimas: naudodami "cout <<" galime isvesti studento duomenis(vardas, pavarde, visi pazymiai, galutinis).
Ivesties perdengimas: naudodami "cin >>" galime ranka ivesti studento duomenis.

Programos sparta nezymiai pagreitejo:

| Studentų kiekis | Nuskaitymas | Skirstymas | Pažangių rūšiavimas | Nepažangių rūšiavimas | Pažangių spausdinimas | Nepažangių spausdinimas | Visas laikas |
|-----------------|-------------|------------|---------------------|----------------------|----------------------|------------------------|--------------|
| 100000          | 1.0746      | 0.0034     | 0.0058              | 0.0064               | 0.1309               | 0.1026                 | 1.3237       |
| 1000000         | 10.6076     | 0.0540     | 0.0714              | 0.0577               | 1.3181               | 1.0284                 | 13.0711      |




---


# v1.5

Sioje versijoje yra padaryta abstrakti base klase Human ir is jos derived klase Student. Base klase turi 2 members - vardas, pavarde. Turi pure virtual funkcija skaiciuotiGalutini(), setterius, getterius ir virtualu default destruktoriu.
Buvo atlikti spartos testai kurie nesiskiria nuo praeitos programos versijos:

| Studentų kiekis | Failo nuskaitymas| Studentų skirstymas | Normalių studentų rūšiavimas| Nepažangių studentų rūšiavimas| Nepažangių studentų spausdinimas| Normalių studentų spausdinimas | Visas testavimo laikas |
|-----------------|----------------------|---------------------------------------|---------------------------------------|----------------------------------------|---------------------------------------------|------------------------------------------|----------------------------|
| 1,000           | 0.0251               | 0.0000                                | 0.0001                                | 0.0000                                 | 0.0019                                      | 0.0024                                   | 0.0295                     |
| 10,000          | 0.1374               | 0.0002                                | 0.0007                                | 0.0005                                 | 0.0182                                      | 0.0239                                   | 0.1809                     |
| 100,000         | 1.2881               | 0.0029                                | 0.0068                                | 0.0050                                 | 0.1164                                      | 0.1649                                   | 1.5841                     |
| 1,000,000       | 10.3480              | 0.0361                                | 0.0915                                | 0.0642                                 | 1.2394                                      | 1.5768                                   | 13.3560                    |
| 10,000,000      | 102.2241             | 0.3216                                | 1.0488                                | 0.7445                                 | 11.9840                                     | 15.9589                                  | 132.2816                   |


---


# v2.0

Buvo sukurta dokumentacija su Doxygen, sukompiliuotas .pdf failas (refman.pdf).
Buvo realizuoti unit testai su doctest - rule of 5 metodai, vidurkio ir medianos skaiciavimai, galutinio skaiciavimai, output overloadas.
Visi metodai praejo testavima:

<img width="349" alt="Screenshot 2025-05-12 003035" src="https://github.com/user-attachments/assets/0d644af3-7e1b-4cd3-bf8e-103d56ed3e9c" />

# v3.0

Buvo sukurta nuosava Vector klase, kuri turi pagrindinius std::vector metodus.
Atminties perskirstymas std::vector ir Vector buvo 28 kartai.

Testu su int vidurkiai:

| int | std::vector | my vector |
|----------|-------------------|---------------------|
| 10,000 | 0.0000s | 0.0000s |
| 100,000 | 0.0000s | 0.0000s |
| 1,000,000 | 0.0003s | 0.0003s |
| 10,000,000 | 0.0077s | 0.0093s |
| 100,000,000 | 0.0897s | 0.0810s |

Testu su studentais vidurkiai:

| Students | std::vector | my vector |
|----------|-------------------|-----------------|
| 10,000 | 0.0000s | 0.0000s |
| 100,000 | 0.0050s | 0.0050s |
| 1,000,000 | 0.1060s | 0.0840s |
| 10,000,000 | 0.8475s | 0.7795s |
| 100,000,000 | 35.0965s | 24.3160s |

Buvo atlikti unit testai ivairiems metodams, visi jie praejo:

![image](https://github.com/user-attachments/assets/cf5d1302-a419-412e-be75-cf661f3907a5)


Programos spartos testavimas su nuosava Vector klase:
Rezultatai panasus lyginant su praeitu versiju testais, kai buvo naudojamas std::vector.

| Studentų skaičius | Failo nuskaitymas (s) | Studentų skirstymas (s) | Normalių rūšiavimas (s) | Nepažangių rūšiavimas (s) | Bendras laikas (s) |
|:-----------------:|:--------------------:|:----------------------:|:----------------------:|:------------------------:|:-----------------:|
| 1,000 | 0.0186 | 0.0003 | 0.0001 | 0.0000 | 0.0271 |
| 10,000 | 0.1741 | 0.0025 | 0.0008 | 0.0006 | 0.2311 |
| 100,000 | 1.5045 | 0.0176 | 0.0067 | 0.0052 | 1.7696 |
| 1,000,000 | 10.8061 | 0.1344 | 0.0908 | 0.0685 | 13.7586 |
| 10,000,000 | 107.6847 | 1.4313 | 1.1022 | 0.7620 | 135.1421 |

