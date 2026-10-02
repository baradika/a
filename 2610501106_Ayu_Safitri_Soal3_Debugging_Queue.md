# Soal 3. Debugging / Refactoring Kode Queue
**Nama: Ayu Safitri**
**NIM: 2610501106 (X=1, Y=0, Z=6, MAX_Q=4, MAX_S=4)**

## Kode Bermasalah dari Asisten Lab

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

## Analisis 2 Kesalahan Fatal

### Kesalahan 1: Pass by value, bukan pass by reference / pointer
- Parameter `Queue q` diteruskan secara **pass by value** (seluruh struct di-copy ke parameter lokal).
- Perubahan `q.rear++` dan `q.data[q.rear] = m` hanya berlaku pada salinan lokal di dalam fungsi.
- Setelah fungsi selesai, Queue asli di pemanggil **tidak berubah** — enqueue gagal secara fungsional.
- **Perbaikan:** gunakan pointer `Queue *q` agar fungsi mengubah objek asli, dengan akses `q->rear` dan `q->data[...]`.

### Kesalahan 2: Penanganan batas array basis-0 salah (off-by-one)
- Array C `data[MAX_Q]` indeks validnya `0 .. MAX_Q-1` (untuk MAX_Q=4 berarti 0..3).
- Cek `if (q.rear == MAX_Q)` baru menolak saat `rear == 4`, yaitu **sudah di luar array**.
- Jika `rear == 3` (penuh), cek lolos, lalu `rear++` menjadi 4 dan `data[4] = m` menulis **di luar batas array** (buffer overflow / undefined behavior).
- Kode juga tidak menginisialisasi `front` saat enqueue pertama (front tetap -1).
- **Perbaikan:** cek penuh dengan `q->rear == MAX_Q - 1` SEBELUM increment, dan set `front = 0` jika `front == -1`.

## Fungsi Perbaikan yang Benar dalam Bahasa C

```c
void enqueueBenar(Queue *q, Mahasiswa m) {
    // 1. Cek penuh sesuai basis-0: rear == MAX_Q-1
    if (q->rear == MAX_Q - 1) {
        printf("Queue Penuh\n");
        return;
    }
    // 2. Inisialisasi front pada enqueue pertama
    if (q->front == -1) {
        q->front = 0;
    }
    // 3. Geser rear lalu isi (pass by reference via pointer)
    q->rear++;
    q->data[q->rear] = m;
}
```

**Ringkasan perbaikan:**
1. `Queue q` -> `Queue *q` + operator `->` supaya perubahan tersimpan.
2. `q.rear == MAX_Q` -> `q->rear == MAX_Q - 1` dicek sebelum `rear++` supaya tidak buffer overflow, plus penanganan `front == -1`.
