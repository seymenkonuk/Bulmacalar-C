#include <stdio.h>
#include "bloklariDiz.h"

main() {
    int adet = 10;
    int tahta[adet][3];
    rastgeleBlokOlustur(adet, tahta);
    bloklariDiz(adet, tahta, true);
    while (1);
}
