# Semafor_za_utakmicu
Mikroupravljači - projekt

Ovaj projekt se sastoji od 2 7-segmentna display-a, 3 LED (zelena, žuta, crvena), buzzer-a i tipkala (+ tipkalo integrirano na STM32 pločici (USER_BUTTON)).

Ovaj projekt simulira rad semafora koji se koristi na sportskim utakmicama.

Prilikom starta na display-ima se postavlja rezultat 0-0 popračen konstantnim treptanjem žute LED kao stanje izjednačenog rezultata.
Pritiskom tipkala integriranog na STM32 pločici simuliramo pogodat "domaćeg" tima i pokreće se naizmjenično treptanje "domaćeg" stanja semafora i svih LED, također ta radnja je popračena i zvučnom sirenom, sve to kao indikacija promjene rezultata.
Pritiskom (drugog) tipkala simuliramo pogodak "gostujućeg" tima i pokreće se kratko treptanje "gostujućeg" stanja semafora i crvene LED kao indikaciju promjene rezultata.

Općenito, konstantno tokom rada treptati će LED zavisno od stanja rezultata na semaforu.
Ako "domaći" tim vodi - treptati će zelena LED, ako je "gostujući" tim u vodstvu - treptati će crvena LED, u suportnom kada je rezultat izjednačen - treptati će žuta LED.
