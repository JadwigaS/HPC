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
