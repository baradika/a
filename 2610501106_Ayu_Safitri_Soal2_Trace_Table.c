#include <stdio.h>
#include <string.h>

// NIM 2610501106 Ayu Safitri : X=1 Y=0 Z=6 MAX_Q=4 MAX_S=4 Y+Z=6
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

int aturanPrioritas(int p_mentah, int Y, int Z) {
    if (p_mentah % 2 == 0) return p_mentah; // genap -> normal
    return Y + Z; // ganjil -> Y+Z
}

void enqueueBenar(Queue *q, Mahasiswa m) {
    if (q->rear == MAX_Q - 1) { printf("Queue Penuh\n"); return; }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->data[q->rear] = m;
}

Mahasiswa dequeueKeStack(Queue *q, StackPembatalan *s) {
    Mahasiswa d; strcpy(d.nim, "-"); strcpy(d.nama, "-"); d.prioritas = -1;
    if (q->front == -1 || q->front > q->rear) { printf("Queue Kosong\n"); return d; }
    Mahasiswa k = q->data[q->front];
    q->front++;
    s->top++; s->data[s->top] = k; // otomatis PUSH
    return k;
}

Mahasiswa popStack(StackPembatalan *s) {
    Mahasiswa d; strcpy(d.nim, "-"); strcpy(d.nama, "-"); d.prioritas = -1;
    if (s->top == -1) { printf("Stack Kosong\n"); return d; }
    return s->data[s->top--];
}

void cetak(Queue *q, StackPembatalan *s, const char *label) {
    printf("\n[%s] front=%d rear=%d top=%d\n", label, q->front, q->rear, s->top);
    printf(" Queue: ");
    for (int i = 0; i < MAX_Q; i++) {
        if (q->front != -1 && i >= q->front && i <= q->rear)
            printf("[%d:%s p=%d] ", i, q->data[i].nama, q->data[i].prioritas);
        else printf("[%d:kosong] ", i);
    }
    printf("\n Stack: ");
    for (int i = 0; i < MAX_S; i++) {
        if (i <= s->top && s->top != -1)
            printf("[%d:%s p=%d] ", i, s->data[i].nama, s->data[i].prioritas);
        else printf("[%d:kosong] ", i);
    }
    printf("\n");
}

int main() {
    int X = 1, Y = 0, Z = 6;
    Queue q = {-1, -1, {0}};
    StackPembatalan s = {-1, {0}};
    Mahasiswa m;

    cetak(&q, &s, "0. Initial");

    strcpy(m.nim, "A1"); strcpy(m.nama, "A"); m.prioritas = aturanPrioritas(X + 1, Y, Z);
    enqueueBenar(&q, m); cetak(&q, &s, "1. Enqueue Mhs_A X+1=2 genap->2");

    strcpy(m.nim, "B1"); strcpy(m.nama, "B"); m.prioritas = aturanPrioritas(Y + 2, Y, Z);
    enqueueBenar(&q, m); cetak(&q, &s, "2. Enqueue Mhs_B Y+2=2 genap->2");

    strcpy(m.nim, "C1"); strcpy(m.nama, "C"); m.prioritas = aturanPrioritas(Z + 3, Y, Z);
    enqueueBenar(&q, m); cetak(&q, &s, "3. Enqueue Mhs_C Z+3=9 ganjil->6");

    Mahasiswa k = dequeueKeStack(&q, &s);
    cetak(&q, &s, "4. Dequeue -> Push Stack");
    printf("   keluar: %s p=%d\n", k.nama, k.prioritas);

    strcpy(m.nim, "D1"); strcpy(m.nama, "D"); m.prioritas = aturanPrioritas(X + Y, Y, Z);
    enqueueBenar(&q, m); cetak(&q, &s, "5. Enqueue Mhs_D X+Y=1 ganjil->6");

    Mahasiswa p = popStack(&s);
    cetak(&q, &s, "6. Pop_Stack");
    printf("   di-pop: %s p=%d\n", p.nama, p.prioritas);

    return 0;
}
