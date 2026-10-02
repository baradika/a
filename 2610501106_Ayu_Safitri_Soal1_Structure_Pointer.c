#include <stdio.h>
#include <string.h>

// NIM 2610501106 Ayu Safitri
// X=1 (digit ke-3 dari belakang), Y=0, Z=6
// MAX_Q = (Z % 3) + 4 = (6 % 3) + 4 = 4
// MAX_S = 4
#define MAX_Q 4
#define MAX_S 4

typedef struct {
    char nim[4];
    char nama[5];
    int prioritas;
} Mahasiswa;

typedef struct {
    int front;
    int rear;
    Mahasiswa data[MAX_Q];
} Queue;

typedef struct {
    int top;
    Mahasiswa data[MAX_S];
} StackPembatalan;

int main() {
    Mahasiswa mhsPertama;
    strcpy(mhsPertama.nim, "106");
    strcpy(mhsPertama.nama, "Ayu");
    mhsPertama.prioritas = 2; // X+1 = 2 (genap)

    printf("Sebelum: %s %s prioritas=%d\n",
           mhsPertama.nim, mhsPertama.nama, mhsPertama.prioritas);

    // Alokasi pointer ke mahasiswa pertama
    Mahasiswa *ptrMHS = &mhsPertama;

    // Ubah prioritas via operator ->
    ptrMHS->prioritas = 10;

    printf("Sesudah via ptrMHS->prioritas: %s %s prioritas=%d\n",
           ptrMHS->nim, ptrMHS->nama, ptrMHS->prioritas);

    return 0;
}
