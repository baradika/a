# Soal 1. Perancangan Structure & Pointer
**Nama: Ayu Safitri**
**NIM: 2610501106**

## Penentuan Parameter NIM

NIM = `2610501106`

3 digit terakhir dari belakang:
- X = digit ke-3 dari belakang = `1`
- Y = digit ke-2 dari belakang = `0`
- Z = digit ke-1 dari belakang = `6`

Maka:
- **X = 1, Y = 0, Z = 6**
- **MAX_Q = (Z % 3) + 4 = (6 % 3) + 4 = 0 + 4 = 4**
- **MAX_S = 4**

## a. Deklarasi struct Mahasiswa dan struct Queue dalam Bahasa C

```c
#include <stdio.h>
#include <string.h>

#define MAX_Q 4   // (Z % 3) + 4 = 4, untuk NIM 2610501106
#define MAX_S 4

typedef struct {
    char nim[4];      // misal "106"
    char nama[5];     // misal "Ayu"
    int prioritas;    // angka bulat
} Mahasiswa;

typedef struct {
    int front;              // indeks depan Queue, -1 = kosong
    int rear;               // indeks belakang Queue, -1 = kosong
    Mahasiswa data[MAX_Q]; // Array of Structure
} Queue;

typedef struct {
    int top;                // puncak Stack, -1 = kosong
    Mahasiswa data[MAX_S];
} StackPembatalan;
```

## b. Alokasi pointer Mahasiswa *ptrMHS dengan operator ->

```c
int main() {
    Mahasiswa mhsPertama;

    strcpy(mhsPertama.nim, "106");
    strcpy(mhsPertama.nama, "Ayu");
    mhsPertama.prioritas = 2; // contoh: X+1 = 2 (genap)

    // Alokasi pointer: arahkan ke alamat mhsPertama
    Mahasiswa *ptrMHS = &mhsPertama;

    // Ubah nilai prioritas mahasiswa pertama via operator ->
    ptrMHS->prioritas = 10;

    printf("NIM: %s, Nama: %s, Prioritas: %d\n",
           ptrMHS->nim, ptrMHS->nama, ptrMHS->prioritas);
    return 0;
}
```

**Penjelasan:**
1. `Mahasiswa *ptrMHS` mendeklarasikan variabel pointer bertipe Mahasiswa.
2. `ptrMHS = &mhsPertama` mengisi pointer dengan alamat memori mahasiswa pertama.
3. `ptrMHS->prioritas = 10;` sama dengan `(*ptrMHS).prioritas = 10;` — mengubah field `prioritas` secara tidak langsung lewat pointer.
