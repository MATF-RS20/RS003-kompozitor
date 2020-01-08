# RS003-kompozitor

## Članovi tima
* Aleksandar Stefanović &emsp;mi17479@alas.matf.bg.ac.rs
* Kristina Pantelić&emsp;&emsp;&emsp;&emsp;mi16091@alas.matf.bg.ac.rs
* Anđelka Milovanović&emsp;&emsp;mi15145@alas.matf.bg.ac.rs

## Izgled aplikacije
![current_state](https://github.com/MATF-RS20/RS003-kompozitor/blob/master/wiki/week5_state.png)

## Kratak opis projekta
Kompozitor ima cilj da korisniku omogući kreativnu manipulaciju zvukom.<br>
Kombinovanjem sintetički generisanih tonova sa klavijature i ulaznih zvukova, aplikacija kreira željeni izlaz.<br>
Korisnik ima opcije da istovremeno čuva i reprodukuje snimljene melodije, kroz interaktivno korišćenje tastature ili mikrofona.

### Korišćene biblioteke
* Qt5
* SFML

#### Pokretanje projekta u CLion okruženju
Da bi se projekat pokrenuo u CLion okruženju, potrebno je otići na: `Settings > Build, Execution, Deployment > CMake` i postaviti **CMake options** na:
```
-DCMAKE_PREFIX_PATH=/PATH/TO/YOUR/Qt/5.12.6/gcc_64/lib/cmake/
```
Uobičajena putanja za Unix sisteme je:
```
-DCMAKE_PREFIX_PATH=~/Qt/5.12.6/gcc_64/lib/cmake/
``` 

#### Pokretanje projekta iz terminala
1. Potrebno je instalirati i **`cmake`**
2. Zatim, uraditi **`git clone https://github.com/MATF-RS20/RS003-kompozitor.git`**
3. Pozicionirati se u _**RS003-kompozitor**_ direktorijum
4. Napraviti **_build_** direktorijum sa: **`mkdir build`**
5. Pozicionirati se u _**build**_ direktorijum i u njemu izvršiti komandu: <br>
**`cmake .. -DCMAKE_PREFIX_PATH=~/Qt/5.13.2/clang_64/lib/cmake`**, odnosno prilagoditi putanju do odgovarajućeg direktorijuma
6. Uraditi **`make`** 
7. Pokrenuti izvršivu datoteku sa: **`./Kompozitor`**
