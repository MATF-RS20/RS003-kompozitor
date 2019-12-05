# RS003-kompozitor

## Članovi tima
* Aleksandar Stefanović &emsp;mi17479@alas.matf.bg.ac.rs
* Kristina Pantelić&emsp;&emsp;&emsp;&emsp;mi16091@alas.matf.bg.ac.rs
* Anđelka Milovanović&emsp;&emsp;mi15145@alas.matf.bg.ac.rs

## Kratak opis projekta
Kompozitor ima cilj da korisniku omogući kreativnu manipulaciju zvukom.<br>
Kombinovanjem raznih instrumenata, tonova i ulaznih zvukova, aplikacija kreira željeni izlaz.

### Korišćene biblioteke
* Qt5
* SFML

### Pokretanje u CLion okruženju
Da bi se projekat pokrenuo u CLion okruženju, potrebno je otići na: `Settings > Build, Execution, Deployment > CMake` i postaviti **CMake options** na:
```
-DCMAKE_PREFIX_PATH=/PATH/TO/YOUR/Qt/5.12.6/gcc_64/lib/cmake/
```
Uobičajena putanja za Unix sisteme je:
```
-DCMAKE_PREFIX_PATH=~/Qt/5.12.6/gcc_64/lib/cmake/
``` 
