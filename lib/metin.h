/*
Bazý Metinsel Ýþlevleri Barýndýrýr
*/

#ifndef METIN_H
#define METIN_H
#include <stdbool.h>

int uzunluk(const char metin[]);                                                                // metin'in uzunluðunu döndürür.
void esitle(char kopya[], const char asil[]);                                                   // "kopya" isimli diziye "asil" isimli dizideki deðerleri yazar.
const char* kucult(const char metin[]);                                                         // "metin" dizisindeki tüm harfleri küçültür ve geriye döndürür. 
                                                                                                // döndürülen deðer; esitle(metin, kucult("metin")) þeklinde kullanýlabilir.
const char* buyut(const char metin[]);                                                          // "metin" dizisindeki tüm harfleri büyütür ve geriye döndürür.
const char* dondur(const char metin[]);                                                         // "metin" dizisindeki tüm küçük harfleri büyük, büyük harfleri küçüðe çevirir ve geriye döndürür.
const char* ters(const char metin[]);                                                           // "metin" dizisini tersten yazýlmýþýný geriye döndürür. seymen -> nemyes
const char* birlestir(const char m1[], const char m2[]);                                        // iki metni birleþtirerek geriye sonucu döndürür.
const char* ayir(const char metin[], int bas, int bit);                                         // "metin" dizisinin "bas" indexinden baþlayarak ve bit indexini ayýrýr.
bool ara(const char metin[], const char aranan[]);                                              // "metin" dizisinde "aranan" metnini arar. Varsa true yoksa false döndürür.
int bul(const char metin[], const char aranan[]);                                               // "metin" dizisinde "aranan" metnini arar. Varsa indexini, yoksa -1 döndürür.
int kacKez(const char metin[], const char aranan[]);                                            // "metin" dizisinde "aranan" metninin kaç kez olduðunu döndürür.
bool ozdesMi(const char m1[], const char m2[]);                                                 // "m1" ile "m2" metinlerinin ayný olup olmadýðýný döndürür.
const char* degistir(const char metin[], const char aranan[], const char yeni[], bool hepsiMi); // "metin" dizisindeki "aranan" metinlerini "yeni" metni ile deðiþtirir.
const char* tumunuDegistir(const char metin[], const char aranan[], const char yeni[]);         // "metin" dizisindeki "aranan" metinlerini "yeni" metni ile deðiþtirir.
bool tamSayiMi(const char metin[]);                                                             // "metin" dizisinin tam sayýya dönüþüp dönüþemeyeceðini döndürür.
bool sayiMi(const char metin[]);                                                                // "metin" dizisinin (ondalýklý) sayýya dönüþüp dönüþemeyeceðini döndürür.
int tamSayiyaDonustur(const char metin[]);                                                      // "metin" dizisi tam sayýya dönüþmüyorsa -1, dönüþüyorsa sonucu geriye döndürür. 
float sayiyaDonustur(const char metin[]);                                                       // "metin" dizisi sayýya dönüþmüyorsa -1, dönüþüyorsa sonucu geriye döndürür. 
bool anagramMi(const char m1[], const char m2[]);                                               // iki metinde ayný karakterler ayný sayýda bulunuyorsa true döndürür.
const char* formatliMetin(const char tsm[]);                                                    // "tsm" metnindeki sayýyý baþýndaki sýfýrlar olmadan ve ilk indexi iþaret olacak þekilde formatlar ve döndürür.

int uzunluk(const char metin[]) {
    int i;
    for (i=0; metin[i] != '\0'; i++);
    return i;
}

void esitle(char kopya[], const char asil[]) {
    int i;
    for (i=0; asil[i] != '\0'; i++) kopya[i] = asil[i];
    kopya[i] = '\0';
}

const char* kucult(const char metin[]) {
    char sonuc[uzunluk(metin)+1];
    int i;
    for (i=0; metin[i]!='\0'; i++) {
        if (metin[i] >= 'A' && metin[i] <= 'Z')
            sonuc[i] = metin[i] - ('A' - 'a');
        else
            sonuc[i] = metin[i];
    }
    sonuc[i] = '\0';
    const char* deger = sonuc;
    return deger;
}

const char* buyut(const char metin[]) {
    char sonuc[uzunluk(metin)+1];
    int i;
    for (i=0; metin[i]!='\0'; i++) {
        if (metin[i] >= 'a' && metin[i] <= 'z')
            sonuc[i] = metin[i] - ('a' - 'A');
        else
            sonuc[i] = metin[i];
    }
    sonuc[i] = '\0';
    const char* deger = sonuc;
    return deger;
}

const char* dondur(const char metin[]) {
    char sonuc[uzunluk(metin)+1];
    int i;
    for (i=0; metin[i]!='\0'; i++) {
        if (metin[i] >= 'A' && metin[i] <= 'Z')
            sonuc[i] = metin[i] - ('A' - 'a');
        else if (metin[i] >= 'a' && metin[i] <= 'z')
            sonuc[i] = metin[i] - ('a' - 'A');
        else
            sonuc[i] = metin[i];
    }
    sonuc[i] = '\0';
    const char* deger = sonuc;
    return deger;
}

const char* ters(const char metin[]) {
    int son = uzunluk(metin) - 1;
    char sonuc[son+2];
    int i;
    for (i=0; metin[i] != '\0'; i++) sonuc[i] = metin[son - i];
    sonuc[i] = '\0';
    const char* deger = sonuc;
    return deger;
}

const char* birlestir(const char m1[], const char m2[]) {
    char sonuc[uzunluk(m1)+uzunluk(m2)+1];
    int i, j;
    for (i=0; m1[i] != '\0'; i++) sonuc[i] = m1[i];
    for (j=0; m2[j] != '\0'; j++) sonuc[i+j] = m2[j];
    sonuc[i+j] = '\0';
    const char* deger = sonuc;
    return deger;
}

const char* ayir(const char metin[], int bas, int bit) {
    char sonuc[bit-bas+1+1];
    int i;
    for (i=bas; i<=bit; i++) {
        sonuc[i-bas] = metin[i];
        if (metin[i] == '\0') break;
    }
    sonuc[i-bas] = '\0';
    const char* deger = sonuc;
    return deger;
}

bool ara(const char metin[], const char aranan[]) {
    if (bul(metin, aranan) == -1) return false;
    return true;
}

int bul(const char metin[], const char aranan[]) {
    int i, j;
    for (i=0; metin[i] != '\0'; i++) {
        for (j=0; aranan[j] != '\0'; j++) {
            if (aranan[j] != metin[i+j])
                break;
        }
        if (aranan[j] == '\0') return i;
    }
    return -1;
}

int kacKez(const char metin[], const char aranan[]) {
    int sonuc = 0;
    int index;
    int aUzunluk = uzunluk(aranan);
    char depo[uzunluk(metin)+1]; esitle(depo, metin);
    while (1) {
        index = bul(depo, aranan);
        if (index == -1) return sonuc;
        sonuc++;
        esitle(depo, ayir(depo, index + aUzunluk, uzunluk(depo)-1));
    }
}

bool ozdesMi(const char m1[], const char m2[]) {
    int i;
    for (i=0; m1[i] != '\0'; i++)
        if (m1[i] != m2[i])
            return false;
    return m2[i] == '\0';
}

const char* degistir(const char metin[], const char aranan[], const char yeni[], bool hepsiMi) {
    if (hepsiMi) return tumunuDegistir(metin, aranan, yeni);
    int index = bul(metin, aranan);
    if (index == -1) return metin;
    int sUzunluk = uzunluk(metin) - uzunluk(aranan) + uzunluk(yeni);
    char x[sUzunluk+1];
    char sonuc[sUzunluk+1];
    esitle(x, birlestir(ayir(metin, 0, index-1), yeni));
    esitle(sonuc, ayir(metin, index+uzunluk(aranan), uzunluk(metin)-1));
    return birlestir(x, sonuc);
}

const char* tumunuDegistir(const char metin[], const char aranan[], const char yeni[]) {
    int adet = kacKez(metin, aranan);
    if (adet == 0) return metin;
    int sUzunluk = (uzunluk(yeni)-uzunluk(aranan))*adet + uzunluk(metin);
    char sonuc[sUzunluk + 1];
    sonuc[0] = '\0';
    char depo[uzunluk(metin)+1]; esitle(depo, metin);
    while (1) {
        int index = bul(depo, aranan);
        if (index == -1) return birlestir(sonuc, depo);
        esitle(
            sonuc, 
            birlestir(
                birlestir(sonuc, ayir(depo, 0, index-1)), 
                yeni
            )
        );
        esitle(depo, ayir(depo, index+uzunluk(aranan), uzunluk(depo)-1));
    }
    
}

bool tamSayiMi(const char metin[]) {
    int i = 0;
    if (metin[i] == '+' || metin[i] == '-') i++;
    for (; metin[i] != '\0'; i++)
        if (!(metin[i] >= '0' && metin[i] <= '9'))
            return false;
    return true;
}

bool sayiMi(const char metin[]) {
    int i = 0, nokta = 0;
    if (metin[i] == '+' || metin[i] == '-') i++;
    if (metin[i] < '0' || metin[i] > '9') return false;
    for (; metin[i] != '\0'; i++) {
        if (!((metin[i] >= '0' && metin[i] <= '9') || (metin[i] == '.' && nokta == 0)))
            return false;
        if (metin[i] == '.') nokta++;
    }
    return true;
}

int tamSayiyaDonustur(const char metin[]) {
    if (!tamSayiMi(metin)) return -1;
    int i = 0, isaret = 1, sonuc = 0;
    if (metin[i] == '+' || metin[i] == '-') i++;
    if (metin[i] == '-') isaret = -1;
    for (; metin[i] != '\0'; i++) sonuc = sonuc*10 + (metin[i] - '0');
    return sonuc*isaret;
}

float sayiyaDonustur(const char metin[]) {
    if (!sayiMi(metin)) return -1;
    int index = bul(metin, ".");
    if (index == -1) return tamSayiyaDonustur(metin);
    int i, ondalikUzunluk = uzunluk(metin) - index + 1;
    float tamKisim = tamSayiyaDonustur(ayir(metin, 0, index-1));
    float ondalikliKisim = tamSayiyaDonustur(ayir(metin, index+1, uzunluk(metin)-1));
    for (i=0; i < ondalikUzunluk-1; i++) ondalikliKisim /= 10;
    return ondalikliKisim + tamKisim; // float iþlemlerinden dolayý yanlýþ veriyor
}

bool anagramMi(const char m1[], const char m2[]) {
    int adet1[256] = {0};
    int i, sayi = 0;
    for (i=0; m1[i]!='\0'; i++) { 
        adet1[m1[i]]++;
        if (adet1[m1[i]] == 1) sayi++;
    }
    for (i=0; m2[i]!='\0'; i++) {
        adet1[m2[i]]--;
        if (adet1[m2[i]] == 0) sayi--;
        else if (adet1[m2[i]] < 0) return false;
    }
    return (sayi == 0);
}

const char* formatliMetin(const char tsm[]) {
    if (!sayiMi(tsm)) return "+0";
    int i=0, index = 1; bool kontrol = false;
    if (tsm[0] != '+' && tsm[0] != '-') i=1;
    char sonuc[uzunluk(tsm)+1+i];
    if (tsm[0] != '+' && tsm[0] != '-') sonuc[0] = '+';
    else sonuc[0] = tsm[0];
    
    for (i=1-i; tsm[i] != '\0'; i++) {
        if (tsm[i] == '0' && !kontrol) continue;
        if (tsm[i] == '.' && !kontrol) {
            sonuc[index] = '0';
            index++;
            sonuc[index] = '.';
            index++;
        } else {
            sonuc[index] = tsm[i];
            index++;
        }
        kontrol = true;
    }
    sonuc[index] = '\0';
    
    const char* deger = sonuc;
    return deger;
}
#endif
