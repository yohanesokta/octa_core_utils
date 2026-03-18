# OCTA CORE Utils

**Octa Core Utils** adalah koleksi utilitas baris perintah (CLI) ringan yang dirancang khusus untuk lingkungan Windows. Proyek ini bertujuan untuk menyediakan fungsi-fungsi dasar sistem operasi yang cepat, portabel, dan mandiri (standalone), mirip dengan GNU Coreutils namun dioptimalkan untuk performa native Windows.

> **Octa Core Utils** is a collection of lightweight command-line utilities (CLI) specifically designed for the Windows environment. This project aims to provide fast, portable, and standalone operating system core functions, similar to GNU Coreutils but optimized for native Windows performance.



# Cara Install / How To Install

### Installers (x64)

[![Download for Windows](https://img.shields.io/badge/Download%20for-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://github.com/yohanesokta/octa_core_utils/releases/download/1.0/octacore-installer.exe)

### Windows PowerShell (x86-64)
```powershell
irm https://yohanesokta.github.io/octa_core_utils/install.ps1 | iex
```
> Instalasi akan di install di %APPDATA% dan otomatis menambahkan $PATH user di executable. Pastikan untuk restart terminal setelah instalasi
> 
## Fitur Utama / Key Features

- **Native Performance:** Ditulis sepenuhnya dalam C/C++ menggunakan Windows API langsung untuk kecepatan maksimal.
- **Zero Dependencies:** Setiap executable bersifat mandiri (standalone), tidak memerlukan DLL eksternal tambahan.
- **Lightweight:** Ukuran file sangat kecil karena dioptimalkan untuk efisiensi ruang penyimpanan.
- **Developer Friendly:** Dirancang untuk mudah diintegrasikan ke dalam workflow terminal atau skrip automasi.

---

# Cara Membangun dari Sumber / Build From Source
> Clone secara recursive untuk mengambil keseluruhan modul, karena beberapa terpisah dan mengambil dari repo lain.


```bash
git clone  --recurse-submodules https://github.com/yohanesokta/octa_core_utils.git
```

---
Proyek ini menggunakan **CMake** sebagai sistem build utamanya, yang mendukung berbagai compiler di Windows.

### 1. Menggunakan MinGW (GCC)

Pastikan kamu sudah menginstal MinGW-w64 dan sudah terdaftar di dalam `PATH`.

```bash
# Masuk ke direktori perintah
cd cmd

# Jalankan skrip build (jika menggunakan bash/git bash)
./build.sh

# ATAU secara manual dengan CMake
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release
```

### 2. Menggunakan Visual Studio (MSVC)

Gunakan **Developer Command Prompt for Visual Studio** atau **PowerShell**.

```powershell
# Buat direktori build
mkdir build
cd build

# Konfigurasi dan Build
cmake ..
cmake --build . --config Release
```

Setelah berhasil, file executable akan tersedia di folder `bin/`.

---

### OctaCore Independent Utility



| Command      | Fungsi                                             | progress |
| ------------ | -------------------------------------------------- | -------- |
| `notify`     | Send Message Display like (MSG)                    | ok       |
| `whoami`     | Display Hostname\Username                          | ok       |
| `sptest`     | Speaker Test Stereo                                | ok       |
| `xbrightnes` | Set External Monitor Brightnes                     | ok       |
| `htop`       | [Ntop For Windows](https://github.com/gsass1/NTop) | ok       |
| `wget`       | Downloading File over network                      | ok       |



### Tools filesystem dasar (paling penting)


| Command | Fungsi                      | progress |
| ------- | --------------------------- | -------- |
| `cp`    | copy file                   | ok       |
| `cat`   | tampilkan isi file          | ok       |
| `touch` | buat file kosong            | ok       |
| `mkdir` | buat directory              | ok       |
| `rmdir` | hapus directory kosong      | ok       |
| `pwd`   | tampilkan current directory | ok       |
| `stat`  | info file                   | ok       |
| `du`    | ukuran directory            | ok       |
| `df`    | disk usage                  | ok       |

---

| Command | Fungsi                     | progress |
| ------- | -------------------------- | -------- |
| `head`  | tampilkan N baris pertama  |
| `tail`  | tampilkan N baris terakhir |
| `wc`    | hitung line / word         |
| `sort`  | sort text                  |
| `uniq`  | hapus duplicate            |
| `grep`  | search text                | ok       |

---

| Command    | Fungsi                  | progress |
| ---------- | ----------------------- | -------- |
| `which`    | cari executable di PATH | ok       |
| `basename` | ambil nama file         |
| `dirname`  | ambil folder            |
| `realpath` | absolute path           |

---

### Tools developer

| Command   | Fungsi                         | progress |
| --------- | ------------------------------ | -------- |
| `hexdump` | lihat file binary              |
| `strings` | extract string dari binary     |
| `time`    | ukur runtime program           |
| `env`     | tampilkan environment variable | ok       |

---


| Command | Fungsi           | progress |
| ------- | ---------------- | -------- |
| `clear` | clear terminal   | ok       |
| `yes`   | print text terus | ok       |
| `sleep` | delay            |
| `echo`  | print text       | ok       |

---

| Tool    | Kegunaan                  | progress |
| ------- | ------------------------- | -------- |
| `tree`  | tampilkan struktur folder |
| `find`  | search file               |
| `xargs` | pipeline argument         |
| `watch` | run command berulang      |
| `diff`  | compare file              |

---

| Tool    | Fungsi                       | progress |
| ------- | ---------------------------- | -------- |
| `open`  | buka file dengan default app | ok       |
| `trash` | kirim file ke recycle bin    |
| `clip`  | copy ke clipboard            |
| `path`  | manage PATH                  |

---

| Tool      | Kenapa keren           | progress |
| --------- | ---------------------- | -------- |
| `grep`    | parsing text           |
| `find`    | recursive filesystem   |
| `tree`    | recursion algorithm    | ok       |
| `du`      | disk usage calculation |
| `hexdump` | binary processing      |

Ini menunjukkan:

* filesystem API
* parsing argument
* recursion
* binary data
