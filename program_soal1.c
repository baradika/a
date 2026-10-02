#include <stdio.h>
#include <string.h>

#define MAX_Q 4  // (Z%3)+4 = (6%3)+4 = 4
#define MAX_S 4

typedef struct {
    char nim[4];
    char nama[5];
    int prioritas;   // Diisi angka bulat
} Mahasiswa;

typedef struct {
    Mahasiswa data[MAX_Q];
    int front;
    int rear;
} Queue;

typedef struct {
    Mahasiswa data[MAX_S];
    int top;
} Stack;

int main() {
    Queue q;
    q.front = -1;
    q.rear = -1;

    // Contoh isi awal mahasiswa pertama (Mhs_A, prioritas 2)
    q.front = 0;
    q.rear = 0;
    strcpy(q.data[0].nim, "A1");
    strcpy(q.data[0].nama, "A");
    q.data[0].prioritas = 2;

    // Pointer untuk mengubah mahasiswa pertama via ->
    Mahasiswa *ptrMHS = &q.data[0];  // arahkan ke indeks front
    printf("Sebelum: %d\n", q.data[0].prioritas);

    ptrMHS->prioritas = 6;  // ubah via operator panah

    printf("Sesudah: %d\n", q.data[0].prioritas);
    printf("Via pointer: %s | %d\n", ptrMHS->nama, ptrMHS->prioritas);
    return 0;
}
