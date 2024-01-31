# HPC
projekt
podajemy argumenty :
N - ilość symulacji
proc - część jaką zjmuje kolor zielony
ag1 - agresywność zielonego
ag2 - agresywność czerwonego
rozm1 - współczynnik rozmnażania zielonego
rozm2 -współczynik rozmnażania czerwonego
kroki - ilość kroków symulacji.


W każdym kroku w każdej symulacji kolory mogą  ze sobą walczyć - losowana jest liczba, i porówynawana jest z współcyznnikami agresji przemnożonymi przez cześć jaką zajmuje dany kolor.
- to kto wygra zależy od wyniku porównania. Od ich agresji zależy też ilu wrogów zabiją.
 agresja= agresywność(1) * (x1)/(x1+x2)
Następnie sie rozmnażają x+=x*rozm.

potem liczona jest średnia ilość każdego  kolorów, oraz odchylenie od średniej
program zwraca średnie i oddchylenia dla każdego z kroków, wraz z parametrami początkowymi i czasem wykonywania symulacji.


![obraz](https://github.com/JadwigaS/HPC/assets/80515572/5faba772-0616-4531-a9a8-3cbe3f5dcf9d)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/5021b5b6-2328-4cbf-a84a-34b0ec6e4b30)
Skalowanie:
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/547952af-f09a-4f1d-876e-bff10551382f)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/7bbfa13d-4d67-4d4b-8312-ecc1efc12edb)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/4e3d401c-1c75-45b8-947c-3b03c9c66d03)
![obraz](https://github.com/JadwigaS/HPC/assets/80515572/bc6919cb-e5e2-485e-a83c-4472172a0230)

