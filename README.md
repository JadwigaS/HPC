# HPC -projekt zaliczeniowy
projekt symuluje walkę między dwoma kolorami - czerwonym i zielonym. Mogą one mieć różne poziomy agresywności i rozmnażania.
podajemy argumenty :
N - ilość symulacji 
proc - część jaką zajmuje kolor zielony (od zera do 1)
ag1 - agresywność zielonego (od zera do 1)
ag2 - agresywność czerwonego (od zera do 1)
rozm1 - współczynnik rozmnażania zielonego 
rozm2 - współczynnik rozmnażania czerwonego 
kroki - ilość kroków symulacji.
Polecenie kompilacji (na DWARFie ) i przykładowe uruchomienie
  module load openmpi-1.8-x86_64
  mpicc mainmpi.c -o main -lm -O3 -Wall

  mpirun -np 4 ./main 1000000 0.4 0.9 0.2 0.8 0.5 1000 >out1.txt

W każdym kroku w każdej symulacji kolory mogą  ze sobą walczyć - losowana jest liczba, i porównywana jest z współcyznnikami agresji przemnożonymi przez cześć jaką zajmuje dany kolor.
- to kto wygra zależy od wyniku porównania. Od ich agresji zależy też ilu wrogów zabiją.
 agresja= agresywność(1) * (x1)/(x1+x2)
Następnie sie rozmnażają x+=x*rozm.

Potem liczona jest średnia ilość każdego z kolorów, oraz odchylenie od średniej.
Program zwraca średnie i odchylenia dla każdego z kroków, wraz z parametrami początkowymi i czasem wykonywania symulacji.

Przykładowe wizualizacje wyników progamu:
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/5faba772-0616-4531-a9a8-3cbe3f5dcf9d)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/5021b5b6-2328-4cbf-a84a-34b0ec6e4b30)
Skalowanie:
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/547952af-f09a-4f1d-876e-bff10551382f)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/7bbfa13d-4d67-4d4b-8312-ecc1efc12edb)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/89134ac0-66d2-40f0-8a69-a12cb34c51d9)

![obraz](https://github.com/JadwigaS/HPC/assets/80515572/bc6919cb-e5e2-485e-a83c-4472172a0230)

