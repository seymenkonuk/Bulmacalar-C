#include <stdio.h>
#include "apartmanlar.h"

main() {
    int ust[4] = {4, 1, 0, 0};
    int sag[4] = {0, 2, 0, 0};
    int alt[4] = {0, 0, 0, 0};
    int sol[4] = {0, 0, 0, 0};
    cozApartmanlarBulmacasi(4,ust, sag, alt, sol, true);
    while (1);
}
