# Text Editor Laba-Laba Sunda

Text Editor Laba-Laba Sunda adalah sebuah proyek aplikasi text editor berbasis terminal yang dikembangkan untuk menyediakan fitur pengelolaan teks yang interaktif. Aplikasi ini mendukung operasi dasar seperti menambahkan, menghapus, mengedit teks, serta fitur undo/redo yang lengkap.

## Fitur Utama
- **Manajemen Blok Teks**: Tambah, hapus, dan modifikasi blok teks.
- **Fitur Undo dan Redo**: Memungkinkan pengguna membatalkan atau mengulangi perubahan dengan mudah.
- **Fitur Copy dan Paste**: Memungkinkan pengguna untuk mengcopy teks dan mempastenya
- **Navigasi Fleksibel**: Gerakkan kursor ke atas, bawah, kiri, atau kanan dengan kontrol keyboard.
- **Blok Operasi Teks**: Dukungan untuk operasi copy-paste dan blok operasi teks.
- **Antarmuka Berbasis Terminal**: Dirancang untuk berjalan di lingkungan CLI dengan interaksi yang sederhana.

## Prasyarat
Pastikan Anda telah menginstal:
- **C++ Compiler**: Disarankan menggunakan GCC atau kompatibel.
- **Git**: Untuk cloning repository.

## Instalasi
1. Clone repository ini ke komputer Anda:
    ```bash
    git clone https://github.com/Fauzan-A25/Text_Editor_Laba_Laba_Sunda.git
    ```
2. Masuk ke direktori proyek:
    ```bash
    cd Text_Editor_Laba_Laba_Sunda
    ```
3. Kompilasi kode menggunakan g++:
    ```bash
    g++ -o text_editor source.cpp
    ```
4. Jalankan program:
    ```bash
    ./text_editor
    ```

## Cara Penggunaan
- Gunakan tombol navigasi untuk memindahkan kursor.
- Gunakan pilihan menu untuk mengelola teks.
- Tekan `ESC` untuk keluar dari aplikasi.

## Struktur Proyek
- **source.cpp**: Berisi implementasi utama dari aplikasi text editor.
- **header.h**: File header untuk mendeklarasikan fungsi dan struktur yang digunakan.
- **EditText.cpp**: File untuk menyimpan implementasi fungsi untuk edit text notepadd.

## Kontribusi
Kami menerima kontribusi untuk meningkatkan fitur dan stabilitas aplikasi ini. Jika Anda ingin berkontribusi:
1. Fork repository ini.
2. Buat branch baru:
    ```bash
    git checkout -b fitur-baru
    ```
3. Commit perubahan Anda:
    ```bash
    git commit -m "Menambahkan fitur baru"
    ```
4. Push branch Anda:
    ```bash
    git push origin fitur-baru
    ```
5. Buat pull request di GitHub.
