#include <stdio.h>
#include <string.h>

// NIM 2610501106 Ayu Safitri : X=1 Y=0 Z=6 MAX_Q=4 MAX_S=4 Y+Z=6
#define MAX_Q 4
#define MAX_S 4
int X = 1, Y = 0, Z = 6;

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

typedef struct {
    Mahasiswa data[MAX_S];
    int top;
} Stack;

Queue q;
Stack s;

void cetak(const char *label) {
    printf("\n[%s] front=%d rear=%d top=%d\n", label, q.front, q.rear, s.top);
    printf(" Queue: ");
    for (int i = 0; i < MAX_Q; i++) {
        if (q.front != -1 && i >= q.front && i <= q.rear)
            printf("[%d:%s|%d] ", i, q.data[i].nama, q.data[i].prioritas);
        else printf("[%d:-] ", i);
    }
    printf("\n Stack: ");
    for (int i = 0; i < MAX_S; i++) {
        if (s.top != -1 && i <= s.top)
            printf("[%d:%s|%d] ", i, s.data[i].nama, s.data[i].prioritas);
        else printf("[%d:-] ", i);
    }
    printf("\n");
}

void enqueue(const char *nama, int p_input) {
    int p_final = p_input;
    if (p_input % 2 != 0) p_final = Y + Z;
    if (q.rear == MAX_Q - 1) { printf("Queue PENUH!\n"); return; }
    if (q.front == -1) { q.front = 0; q.rear = 0; }
    else { q.rear++; }
    strcpy(q.data[q.rear].nama, nama);
    q.data[q.rear].prioritas = p_final;
}

void enqueueBenar(Queue *qq, Mahasiswa m) {
    if (qq->rear == MAX_Q - 1) { printf("Queue Penuh\n"); return; }
    if (qq->front == -1) { qq->front = 0; qq->rear = 0; }
    else { qq->rear++; }
    qq->data[qq->rear] = m;
}

int main() {
    printf("=== BAGIAN 1 : Structure & Pointer (Soal 1) ===\n");
    Queue q1; q1.front = -1; q1.rear = -1;
    q1.front = 0; q1.rear = 0;
    strcpy(q1.data[0].nim, "A1");
    strcpy(q1.data[0].nama, "A");
    q1.data[0].prioritas = 2;
    Mahasiswa *ptrMHS = &q1.data[0];
    printf("Sebelum: %d\n", q1.data[0].prioritas);
    ptrMHS->prioritas = 6;
    printf("Sesudah: %d\n", q1.data[0].prioritas);
    printf("Via pointer: %s | %d\n", ptrMHS->nama, ptrMHS->prioritas);

    printf("\n=== BAGIAN 2 : Trace 6 operasi (Soal 2) ===\n");
    q.front = -1; q.rear = -1; s.top = -1;
    cetak("0. Awal");
    enqueue("A", X + 1); cetak("1. Enqueue Mhs_A X+1=2");
    enqueue("B", Y + 2); cetak("2. Enqueue Mhs_B Y+2=2");
    enqueue("C", Z + 3); cetak("3. Enqueue Mhs_C Z+3=9 -> 6");
    // Dequeue -> push stack
    Mahasiswa keluar = q.data[q.front]; q.front++;
    s.top++; s.data[s.top] = keluar;
    printf("Dequeue: %s|%d -> PUSH ke Stack\n", keluar.nama, keluar.prioritas);
    cetak("4. Dequeue -> Push Stack");
    enqueue("D", X + Y); cetak("5. Enqueue Mhs_D X+Y=1 -> 6");
    Mahasiswa pm = s.data[s.top--];
    printf("Pop_Stack: %s|%d\n", pm.nama, pm.prioritas);
    cetak("6. Pop_Stack");
    printf("\nAkhir: Queue front=%d rear=%d (B|2 C|6 D|6), Stack top=%d (kosong)\n", q.front, q.rear, s.top);

    printf("\n=== BAGIAN 3 : Debugging (Soal 3) ===\n");
    Queue antri; antri.front = -1; antri.rear = -1;
    Mahasiswa m;
    strcpy(m.nim, "A1"); strcpy(m.nama, "A"); m.prioritas = 2;
    enqueueBenar(&antri, m);
    printf("front=%d rear=%d | Queue: [A|2]\n", antri.front, antri.rear);
    strcpy(m.nim, "B1"); strcpy(m.nama, "B"); m.prioritas = 2;
    enqueueBenar(&antri, m);
    printf("front=%d rear=%d | Queue: [A|2] [B|2]\n", antri.front, antri.rear);
    strcpy(m.nim, "C1"); strcpy(m.nama, "C"); m.prioritas = 6;
    enqueueBenar(&antri, m);
    printf("front=%d rear=%d | Queue: [A|2] [B|2] [C|6]\n", antri.front, antri.rear);
    strcpy(m.nim, "D1"); strcpy(m.nama, "D"); m.prioritas = 6;
    enqueueBenar(&antri, m);
    printf("front=%d rear=%d | Queue: [A|2] [B|2] [C|6] [D|6]\n", antri.front, antri.rear);
    printf("Uji batas: coba enqueue ke-5 (harus ditolak penuh)\n");
    strcpy(m.nim, "E1"); strcpy(m.nama, "E"); m.prioritas = 2;
    enqueueBenar(&antri, m);

    return 0;
}
