#include <stdio.h>
#include "apartmanlar.h"

main() {
    int boyut = 6;
    int ust[boyut], sag[boyut], alt[boyut], sol[boyut];
    int tahta[boyut][boyut];
    girdiAlApartmanlarBulmacasi(boyut, ust, sag, alt, sol, tahta);
    cozApartmanlarBulmacasi(boyut, ust, sag, alt, sol, tahta, true);
    while (1);
}
