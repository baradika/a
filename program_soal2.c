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
        else
            printf("[%d:-] ", i);
    }
    printf("\n Stack: ");
    for (int i = 0; i < MAX_S; i++) {
        if (s.top != -1 && i <= s.top)
            printf("[%d:%s|%d] ", i, s.data[i].nama, s.data[i].prioritas);
        else
            printf("[%d:-] ", i);
    }
    printf("\n");
}

// Aturan Enqueue Spesifik: GENAP normal, GANJIL -> (Y+Z)
void enqueue(const char *nama, int p_input) {
    int p_final = p_input;
    if (p_input % 2 != 0) {
        p_final = Y + Z;  // 0+6 = 6
    }
    if (q.rear == MAX_Q - 1) { printf("Queue PENUH!\n"); return; }
    if (q.front == -1) { q.front = 0; q.rear = 0; }
    else { q.rear++; }
    strcpy(q.data[q.rear].nama, nama);
    q.data[q.rear].prioritas = p_final;
}

void dequeue_to_stack() {
    if (q.front == -1 || q.front > q.rear) { printf("Queue Kosong\n"); return; }
    Mahasiswa keluar = q.data[q.front];
    q.front++;
    s.top++;
    s.data[s.top] = keluar; // otomatis PUSH
    printf("Dequeue: %s|%d -> PUSH ke Stack\n", keluar.nama, keluar.prioritas);
}

void pop_stack() {
    if (s.top == -1) { printf("Stack Kosong\n"); return; }
    Mahasiswa m = s.data[s.top--];
    printf("Pop_Stack: %s|%d\n", m.nama, m.prioritas);
}

int main() {
    q.front = -1; q.rear = -1; s.top = -1;
    cetak("0. Awal front=-1 rear=-1 top=-1");

    enqueue("A", X + 1);      // 2 genap -> 2
    cetak("1. Enqueue Mhs_A X+1=2");

    enqueue("B", Y + 2);      // 2 genap -> 2
    cetak("2. Enqueue Mhs_B Y+2=2");

    enqueue("C", Z + 3);      // 9 ganjil -> 6
    cetak("3. Enqueue Mhs_C Z+3=9 -> 6");

    dequeue_to_stack();
    cetak("4. Dequeue -> Push Stack");

    enqueue("D", X + Y);      // 1 ganjil -> 6
    cetak("5. Enqueue Mhs_D X+Y=1 -> 6");

    pop_stack();
    cetak("6. Pop_Stack");

    printf("\nAkhir: Queue front=%d rear=%d (B|2 C|6 D|6), Stack top=%d (kosong)\n",
           q.front, q.rear, s.top);
    return 0;
}
