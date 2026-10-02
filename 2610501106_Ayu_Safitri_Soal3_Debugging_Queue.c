#include <stdio.h>
#include <string.h>

// NIM 2610501106 Ayu Safitri : X=1 Y=0 Z=6 MAX_Q=4
#define MAX_Q 4

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

// --- Kode bermasalah (JANGAN dipakai, hanya dokumentasi) ---
// Kesalahan 1: Queue q pass-by-value -> perubahan hilang
// Kesalahan 2: cek q.rear == MAX_Q salah, harus MAX_Q-1 (basis 0)
// void enqueueBermasalah(Queue q, Mahasiswa m) {
//     if (q.rear == MAX_Q) { printf("Penuh\n"); }
//     else { q.rear++; q.data[q.rear] = m; }
// }

// --- Fungsi perbaikan yang benar ---
void enqueueBenar(Queue *q, Mahasiswa m) {
    if (q->rear == MAX_Q - 1) {
        printf("Queue Penuh\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = m;
}

int main() {
    Queue q = {-1, -1, {0}};
    Mahasiswa m;

    strcpy(m.nim, "106"); strcpy(m.nama, "Ayu"); m.prioritas = 2;
    enqueueBenar(&q, m);
    strcpy(m.nim, "B1"); strcpy(m.nama, "B"); m.prioritas = 2;
    enqueueBenar(&q, m);

    printf("front=%d rear=%d\n", q.front, q.rear);
    for (int i = q.front; i <= q.rear; i++)
        printf("[%d] %s p=%d\n", i, q.data[i].nama, q.data[i].prioritas);

    return 0;
}
