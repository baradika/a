#include <stdio.h>
#include <string.h>

// NIM 2610501106 Ayu Safitri : MAX_Q=4
#define MAX_Q 4

typedef struct {
    char nim[4];
    char nama[5];
    int prioritas;
} Mahasiswa;

typedef struct {
    Mahasiswa data[MAX_Q];
    int front;
    int rear;
} Queue;

// Draf bermasalah (dokumentasi saja):
// void enqueueBermasalah(Queue q, Mahasiswa m) {
//     if (q.rear == MAX_Q) { printf("Penuh\n"); }
//     else { q.rear++; q.data[q.rear] = m; }
// }

void enqueueBenar(Queue *q, Mahasiswa m) {
    if (q->rear == MAX_Q - 1) {
        printf("Queue Penuh\n");
        return;
    }
    if (q->front == -1) {   // queue kosong pertama kali
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear++;
    }
    q->data[q->rear] = m;
}

void cetakQ(Queue *q) {
    printf("front=%d rear=%d | Queue:", q->front, q->rear);
    for (int i = q->front; i <= q->rear; i++)
        printf(" [%s|%d]", q->data[i].nama, q->data[i].prioritas);
    printf("\n");
}

int main() {
    printf("=== SOAL 3 : Debugging / Refactoring ===\n");
    Queue antri; antri.front = -1; antri.rear = -1;
    Mahasiswa m;

    // A|2 (X+1 genap), B|2 (Y+2 genap), C|6 (Z+3 ganjil->Y+Z), D|6 (X+Y ganjil->Y+Z)
    strcpy(m.nim, "A1"); strcpy(m.nama, "A"); m.prioritas = 2;
    enqueueBenar(&antri, m); cetakQ(&antri);

    strcpy(m.nim, "B1"); strcpy(m.nama, "B"); m.prioritas = 2;
    enqueueBenar(&antri, m); cetakQ(&antri);

    strcpy(m.nim, "C1"); strcpy(m.nama, "C"); m.prioritas = 6;
    enqueueBenar(&antri, m); cetakQ(&antri);

    strcpy(m.nim, "D1"); strcpy(m.nama, "D"); m.prioritas = 6;
    enqueueBenar(&antri, m); cetakQ(&antri);

    printf("Uji batas: coba enqueue ke-5 (harus ditolak penuh)\n");
    strcpy(m.nim, "E1"); strcpy(m.nama, "E"); m.prioritas = 2;
    enqueueBenar(&antri, m);

    return 0;
}
