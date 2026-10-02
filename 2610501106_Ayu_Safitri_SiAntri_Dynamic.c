#include <stdio.h>
#include <string.h>

#define MAX_Q 4 // (6 % 3) + 4 = 4, NIM 2610501106: X=1 Y=0 Z=6
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

void initQueue(Queue *q) { q->front = -1; q->rear = -1; }
void initStack(StackPembatalan *s) { s->top = -1; }
int isQueueFull(Queue *q) { return q->rear == MAX_Q - 1; }
int isQueueEmpty(Queue *q) { return q->front == -1 || q->front > q->rear; }
int isStackFull(StackPembatalan *s) { return s->top == MAX_S - 1; }
int isStackEmpty(StackPembatalan *s) { return s->top == -1; }

// Aturan Enqueue Spesifik: genap normal, ganjil -> (Y+Z). Y=0 Z=6 jadi 6
int aturanPrioritas(int p_mentah, int Y, int Z) {
    if (p_mentah % 2 == 0) return p_mentah;
    return Y + Z;
}

void enqueueBenar(Queue *q, Mahasiswa m) {
    if (q->rear == MAX_Q - 1) {
        printf("Queue Penuh\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->data[q->rear] = m;
}

Mahasiswa dequeueKeStack(Queue *q, StackPembatalan *s) {
    Mahasiswa dummy; strcpy(dummy.nim, "-"); strcpy(dummy.nama, "-"); dummy.prioritas = -1;
    if (isQueueEmpty(q)) { printf("Queue Kosong\n"); return dummy; }
    Mahasiswa keluar = q->data[q->front];
    q->front++;
    // Otomatis PUSH ke Stack Pembatalan
    if (!isStackFull(s)) { s->top++; s->data[s->top] = keluar; }
    else printf("Stack Penuh, data %s hilang dari stack\n", keluar.nama);
    return keluar;
}

Mahasiswa popStack(StackPembatalan *s) {
    Mahasiswa dummy; strcpy(dummy.nim, "-"); strcpy(dummy.nama, "-"); dummy.prioritas = -1;
    if (isStackEmpty(s)) { printf("Stack Kosong\n"); return dummy; }
    Mahasiswa m = s->data[s->top];
    s->top--;
    return m;
}

void cetakStatus(Queue *q, StackPembatalan *s, const char *label) {
    printf("\n[%s] front=%d rear=%d | top=%d\n", label, q->front, q->rear, s->top);
    printf(" Queue: ");
    for (int i = 0; i < MAX_Q; i++) {
        if (q->front != -1 && i >= q->front && i <= q->rear)
            printf("[%d:%s p=%d] ", i, q->data[i].nama, q->data[i].prioritas);
        else
            printf("[%d:kosong] ", i);
    }
    printf("\n Stack: ");
    for (int i = 0; i < MAX_S; i++) {
        if (i <= s->top && s->top != -1)
            printf("[%d:%s p=%d] ", i, s->data[i].nama, s->data[i].prioritas);
        else
            printf("[%d:kosong] ", i);
    }
    printf("\n");
}

int main() {
    int X = 1, Y = 0, Z = 6;
    printf("NIM 2610501106 Ayu Safitri -> X=%d Y=%d Z=%d MAX_Q=%d MAX_S=%d Y+Z=%d\n",
           X, Y, Z, MAX_Q, MAX_S, Y + Z);

    Queue q; StackPembatalan s;
    initQueue(&q); initStack(&s);

    // Soal 1: demo pointer ->
    Mahasiswa mhsPertama;
    strcpy(mhsPertama.nim, "106"); strcpy(mhsPertama.nama, "Ayu"); mhsPertama.prioritas = 2;
    Mahasiswa *ptrMHS = &mhsPertama;
    ptrMHS->prioritas = 10;
    printf("Demo pointer: %s %s prioritas=%d\n", ptrMHS->nim, ptrMHS->nama, ptrMHS->prioritas);

    cetakStatus(&q, &s, "Initial");

    Mahasiswa m;
    // 1. Enqueue Mhs_A X+1
    strcpy(m.nim, "A1"); strcpy(m.nama, "A"); m.prioritas = aturanPrioritas(X + 1, Y, Z);
    enqueueBenar(&q, m); cetakStatus(&q, &s, "1. Enqueue Mhs_A p=X+1");
    // 2. Enqueue Mhs_B Y+2
    strcpy(m.nim, "B1"); strcpy(m.nama, "B"); m.prioritas = aturanPrioritas(Y + 2, Y, Z);
    enqueueBenar(&q, m); cetakStatus(&q, &s, "2. Enqueue Mhs_B p=Y+2");
    // 3. Enqueue Mhs_C Z+3
    strcpy(m.nim, "C1"); strcpy(m.nama, "C"); m.prioritas = aturanPrioritas(Z + 3, Y, Z);
    enqueueBenar(&q, m); cetakStatus(&q, &s, "3. Enqueue Mhs_C p=Z+3 -> ganjil jadi 6");
    // 4. Dequeue -> push stack
    Mahasiswa k = dequeueKeStack(&q, &s); cetakStatus(&q, &s, "4. Dequeue -> Push Stack");
    printf("   yang keluar: %s p=%d\n", k.nama, k.prioritas);
    // 5. Enqueue Mhs_D X+Y
    strcpy(m.nim, "D1"); strcpy(m.nama, "D"); m.prioritas = aturanPrioritas(X + Y, Y, Z);
    enqueueBenar(&q, m); cetakStatus(&q, &s, "5. Enqueue Mhs_D p=X+Y -> ganjil jadi 6");
    // 6. Pop stack
    Mahasiswa p = popStack(&s); cetakStatus(&q, &s, "6. Pop_Stack");
    printf("   yang di-pop: %s p=%d\n", p.nama, p.prioritas);

    return 0;
}
