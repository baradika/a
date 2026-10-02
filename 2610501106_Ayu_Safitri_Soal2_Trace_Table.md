# Soal 2. Penelusuran Memori Mandiri / Execution Trace Table
**Nama: Ayu Safitri**
**NIM: 2610501106**

## Parameter NIM Anda
- NIM = `2610501106`
- X = digit ke-3 dari belakang = `1`
- Y = digit ke-2 dari belakang = `0`
- Z = digit terakhir = `6`
- MAX_Q = (6 % 3) + 4 = **4**
- MAX_S = **4**
- Rumus pengganti ganjil (Y + Z) = 0 + 6 = **6**

## Aturan yang Dipakai
1. **Enqueue Spesifik:** prioritas GENAP dimasukkan normal, prioritas GANJIL diganti menjadi (Y+Z) = 6.
2. **Dequeue ke Stack:** data yang keluar dari Queue otomatis di-PUSH ke Stack Pembatalan.
3. Queue linear array FIFO, Stack LIFO. Awal: `front = -1, rear = -1, top = -1`.

## Perhitungan Prioritas Mentah -> Final
1. `Enqueue("Mhs_A", X+1)` = 1+1 = 2, GENAP -> **tetap 2**
2. `Enqueue("Mhs_B", Y+2)` = 0+2 = 2, GENAP -> **tetap 2**
3. `Enqueue("Mhs_C", Z+3)` = 6+3 = 9, GANJIL -> **menjadi 6**
4. `Dequeue()` -> Mhs_A keluar, PUSH ke Stack
5. `Enqueue("Mhs_D", X+Y)` = 1+0 = 1, GANJIL -> **menjadi 6**
6. `Pop_Stack()` -> ambil Mhs_A dari Stack

## Tabel Penelusuran Status Memori

| Langkah | Operasi | front | rear | Queue[0] | Queue[1] | Queue[2] | Queue[3] | top | Stack[0] | Stack[1..3] | Keterangan |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 0 | Initial State | -1 | -1 | kosong | kosong | kosong | kosong | -1 | kosong | kosong | Queue & Stack kosong |
| 1 | Enqueue(Mhs_A, 2) | 0 | 0 | Mhs_A,2 | kosong | kosong | kosong | -1 | kosong | kosong | 2 genap, masuk normal |
| 2 | Enqueue(Mhs_B, 2) | 0 | 1 | Mhs_A,2 | Mhs_B,2 | kosong | kosong | -1 | kosong | kosong | 2 genap, masuk normal |
| 3 | Enqueue(Mhs_C, 9->6) | 0 | 2 | Mhs_A,2 | Mhs_B,2 | Mhs_C,6 | kosong | -1 | kosong | kosong | 9 ganjil, diganti 6 |
| 4 | Dequeue() -> Push | 1 | 2 | - (keluar) | Mhs_B,2 | Mhs_C,6 | kosong | 0 | Mhs_A,2 | kosong | Mhs_A FIFO keluar, push ke Stack |
| 5 | Enqueue(Mhs_D, 1->6) | 1 | 3 | - (keluar) | Mhs_B,2 | Mhs_C,6 | Mhs_D,6 | 0 | Mhs_A,2 | kosong | 1 ganjil, diganti 6, rear=3 penuh |
| 6 | Pop_Stack() | 1 | 3 | - (keluar) | Mhs_B,2 | Mhs_C,6 | Mhs_D,6 | -1 | - (diambil) | kosong | Mhs_A di-pop, Stack kosong lagi |

## Status Akhir
- Queue: `front=1, rear=3` berisi [Mhs_B p=2] [Mhs_C p=6] [Mhs_D p=6], indeks 0 sudah kosong karena ter-dequeue.
- Stack: `top=-1` kosong (Mhs_A sudah di-pop/dibatalkan).
- Hasil ini terverifikasi dengan program `2610501106_Ayu_Safitri_SiAntri_Dynamic.c` yang dijalankan di folder ini.
