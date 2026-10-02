# Jawaban Praktikum Struktur Data — Modul "Si-Antri Dynamic"
**Nama: Ayu Safitri**
**NIM: 2610501106**

## 1. Penentuan Parameter X, Y, Z, MAX_Q, MAX_S

NIM = `2610501106`

3 digit terakhir NIM = `106`:
- X = digit ke-3 dari belakang = `1`
- Y = digit ke-2 dari belakang = `0`
- Z = digit ke-1 dari belakang (terakhir) = `6`

Perhitungan:
- **X = 1, Y = 0, Z = 6**
- **MAX_Q = (Z % 3) + 4 = (6 % 3) + 4 = 0 + 4 = 4**
- **MAX_S = 4**
- Nilai pengganti prioritas ganjil **(Y + Z) = 0 + 6 = 6**

---

## Soal 1. Perancangan Structure & Pointer

### a. Deklarasi struct Mahasiswa dan struct Queue dalam Bahasa C

```c
#include <stdio.h>
#include <string.h>

#define MAX_Q 4   // (Z % 3) + 4 = (6 % 3) + 4 = 4
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
```

### b. Alokasi pointer Mahasiswa *ptrMHS dengan operator ->

```c
int main() {
    Mahasiswa mhsPertama;

    strcpy(mhsPertama.nim, "106");
    strcpy(mhsPertama.nama, "Ayu");
    mhsPertama.prioritas = 2;

    // Alokasi pointer: arahkan ke alamat mhsPertama
    Mahasiswa *ptrMHS = &mhsPertama;

    // Ubah prioritas via operator ->
    ptrMHS->prioritas = 10;

    printf("NIM: %s, Nama: %s, Prioritas: %d\n",
           ptrMHS->nim, ptrMHS->nama, ptrMHS->prioritas);
    return 0;
}
```

**Penjelasan:** `Mahasiswa *ptrMHS = &mhsPertama;` membuat pointer menunjuk ke `mhsPertama`.
Operator `->` dipakai untuk mengakses/mengubah field lewat pointer, misal `ptrMHS->prioritas = 10;`.

---

## Soal 2. Execution Trace Table (6 Operasi)

Aturan Enqueue Spesifik:
- Prioritas GENAP -> dimasukkan normal.
- Prioritas GANJIL -> diganti menjadi (Y + Z) = 6.

Perhitungan prioritas mentah:
1. `Enqueue("Mhs_A", X+1)` = 1+1 = **2 (GENAP) -> tetap 2**
2. `Enqueue("Mhs_B", Y+2)` = 0+2 = **2 (GENAP) -> tetap 2**
3. `Enqueue("Mhs_C", Z+3)` = 6+3 = **9 (GANJIL) -> menjadi 6**
4. `Dequeue()` -> Mhs_A keluar Queue, otomatis PUSH ke Stack
5. `Enqueue("Mhs_D", X+Y)` = 1+0 = **1 (GANJIL) -> menjadi 6**
6. `Pop_Stack()` -> ambil Mhs_A dari Stack

Kondisi awal: `front = -1, rear = -1, top = -1` (Queue & Stack kosong).

### Tabel Penelusuran Status Memori

| Langkah | Operasi | front | rear | Queue[0] | Queue[1] | Queue[2] | Queue[3] | top | Stack[0] | Stack[1..3] |
|---|---|---|---|---|---|---|---|---|---|---|
| 0 | Initial State | -1 | -1 | kosong | kosong | kosong | kosong | -1 | kosong | kosong |
| 1 | Enqueue(Mhs_A, p=2) | 0 | 0 | Mhs_A,2 | kosong | kosong | kosong | -1 | kosong | kosong |
| 2 | Enqueue(Mhs_B, p=2) | 0 | 1 | Mhs_A,2 | Mhs_B,2 | kosong | kosong | -1 | kosong | kosong |
| 3 | Enqueue(Mhs_C, 9->6) | 0 | 2 | Mhs_A,2 | Mhs_B,2 | Mhs_C,6 | kosong | -1 | kosong | kosong |
| 4 | Dequeue() -> Push Stack | 1 | 2 | - (keluar) | Mhs_B,2 | Mhs_C,6 | kosong | 0 | Mhs_A,2 | kosong |
| 5 | Enqueue(Mhs_D, 1->6) | 1 | 3 | - (keluar) | Mhs_B,2 | Mhs_C,6 | Mhs_D,6 | 0 | Mhs_A,2 | kosong |
| 6 | Pop_Stack() | 1 | 3 | - (keluar) | Mhs_B,2 | Mhs_C,6 | Mhs_D,6 | -1 | - (diambil) | kosong |

Keterangan tiap langkah:
- Langkah 1: prioritas 2 genap, front 0 rear 0.
- Langkah 2: prioritas 2 genap, rear jadi 1.
- Langkah 3: prioritas 9 ganjil -> diganti 6, rear jadi 2.
- Langkah 4: Dequeue ambil indeks front=0 (Mhs_A), front jadi 1, Mhs_A di-push ke Stack top=0.
- Langkah 5: prioritas 1 ganjil -> diganti 6, rear jadi 3 (Queue penuh: rear = MAX_Q-1).
- Langkah 6: Pop ambil Mhs_A dari Stack, top kembali -1 (Stack kosong). Queue tidak berubah.

Status akhir: Queue berisi Mhs_B, Mhs_C, Mhs_D (front=1, rear=3). Stack kosong (top=-1).

---

## Soal 3. Debugging / Refactoring Kode Queue

Kode bermasalah:

```c
void enqueueBermasalah(Queue q, Mahasiswa m) {
    if (q.rear == MAX_Q) {
        printf("Penuh\n");
    } else {
        q.rear++;
        q.data[q.rear] = m;
    }
}
```

### Analisis 2 Kesalahan Fatal

**Kesalahan 1: Pass by value, bukan pass by reference / pointer.**
Parameter `Queue q` disalin (pass by value). Perubahan `q.rear++` dan `q.data[...] = m` hanya terjadi pada salinan lokal di dalam fungsi, tidak mengubah Queue asli milik pemanggil. Akibatnya enqueue seolah-olah tidak pernah terjadi.

Solusi: gunakan pointer `Queue *q` dan akses dengan `q->rear`, `q->data[...]`.

**Kesalahan 2: Penanganan batas array basis-0 salah (off-by-one, buffer overflow).**
Array C `data[MAX_Q]` indeks validnya `0 .. MAX_Q-1`. Cek `q.rear == MAX_Q` baru menolak saat rear sudah di luar array. Jika rear = MAX_Q-1 (penuh), cek lolos, lalu `rear++` menjadi MAX_Q dan `data[MAX_Q] = m` menulis di luar batas array (buffer overflow / undefined behavior). Belum ada penanganan `front` saat enqueue pertama.

Solusi: cek penuh dengan `q->rear == MAX_Q - 1` SEBELUM increment, dan inisialisasi `front = 0` saat queue kosong.

### Fungsi Perbaikan yang Benar

```c
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
```
