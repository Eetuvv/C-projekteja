Algoritmi, joka laskee tekstitiedostossa esiintyvien sanojen määrän ja lajittelee ne esiintyvyyden mukaan suurimmasta pienimpään. 
Lopuksi ohjelma tulostaa 100 suurinta sanaa laskevaan järjestykseen.
Ohjelmassa luetaan tekstitiedosto ja siinä esiintyvät sanat, ja niiden esiintyvyydet tallennetaan hajautustauluun, joka on luotu ohjelmassa. 
Törmäykset on hoidettu käyttämällä luotainmenetelmää. Tämän jälkeen kaikki sanat kopioidaan toiseen taulukkoon, ja niiden arvot järjestetään laskevaan järjestykseen 
quicksort-algoritmia käyttäen. Lopuksi taulukon järjestetyt sanat ja niitä vastaavat arvot tulostetaan.

Ohjelman suoritus on hyvin nopea, sillä se hyödyntää itse toteutettua hajautustaulua sanojen esiintyvyyden tallentamiseen, ja quicksort-algoritmia lajitteluun.
Esimerkkitiedoston "WarPath.txt" suorittamiseen menee noin 0.6 sekuntia tiedoston sisältäessä noin 570 000 sanaa.
