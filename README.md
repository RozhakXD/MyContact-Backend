# 🚀 MyContact-Backend API: RESTful Powerhouse Built with C++ 🌟

![MyContact - Logo](https://github.com/user-attachments/assets/448a5786-41cb-4d00-a68f-b83467e8470a)

## 📋 Deskripsi Proyek

**MyContact-Backend** adalah sebuah RESTful API untuk manajemen kontak yang dibangun sepenuhnya menggunakan C++. Proyek ini merupakan evolusi dari [aplikasi CLI sederhana](https://raw.githubusercontent.com/RozhakXD/MyContact-Backend/refs/heads/main/Main.cpp) yang sebelumnya dibuat sebagai tugas mata kuliah Struktur Data.

Tujuan dari pengembangan ini adalah untuk mentransformasi aplikasi konsol menjadi layanan backend yang kokoh, menerapkan arsitektur perangkat lunak modern (seperti _Repository Pattern_), dan memanfaatkan _toolchain_ C++ profesional (CMake) untuk membangun aplikasi yang scalable dan mudah dikelola.

## ✨ Fitur Utama

API ini menyediakan fungsionalitas CRUD (Create, Read, Update, Delete) penuh untuk data kontak, memungkinkan klien eksternal untuk:

a. **Menambahkan** kontak baru.  
b. **Membaca** seluruh daftar kontak.  
c. **Mencari** kontak berdasarkan ID, nama, atau kategori.  
d. **Memperbarui** informasi kontak yang sudah ada.  
e. **Menghapus** kontak dari database.  

## 🏗️ Arsitektur dan Teknologi

Proyek ini dibangun dengan fokus pada kode yang bersih dan terstruktur menggunakan prinsip-prinsip Object-Oriented Programming (OOP).

- **Bahasa: C++17**
- **Web Framework:** **Crow (v1.2.1)** - Sebuah framework micro-web C++ yang ringan dan cepat untuk membangun API.
- **Database:** **SQLite3** - Sistem database relasional yang disimpan dalam satu file, ideal untuk aplikasi skala kecil hingga menengah.
- **Database Wrapper:** `sqlite_modern_cpp` - Untuk interaksi yang aman dan modern dengan SQLite.
- **Build System:** **CMake** - Standar industri untuk mengelola proses build dan dependensi proyek C++.
- **Arsitektur:**
  - **Model-View-Controller (MVC) like:** Logika dipisahkan dengan jelas.
  - **Repository Pattern:** Abstraksi lapisan data yang memisahkan logika bisnis dari interaksi database. `ContactRepository` menjadi satu-satunya gerbang untuk mengakses data.

## 🚀 API Documentation

Berikut adalah dokumentasi lengkap untuk semua _endpoint_ yang tersedia.
| Method | Endpoint                           | Deskripsi                          | Contoh Body (Request)                                          | Respon Sukses (2xx)                                   | Respon Gagal (4xx/5xx)                     |
|--------|------------------------------------|------------------------------------|----------------------------------------------------------------|--------------------------------------------------------|--------------------------------------------|
| POST   | `/contacts`                        | Menambahkan kontak baru            | `{"name":"Nama", "phone":"+62...", "category":"#Kategori"}`     | 201 Created – `{"message":"Contact added"}`           | 400 Bad Request – 500 Internal Server Error |
| GET    | `/contacts`                        | Mengambil semua kontak             | -                                                              | 200 OK – `{"status":"success", "data":[...]}`         | -                                          |
| GET    | `/contacts/{id}`                   | Mengambil kontak berdasarkan ID    | -                                                              | 200 OK – `{"status":"success", "data":{...}}`         | 404 Not Found                             |
| GET    | `/contacts/search?name=...`        | Mencari kontak berdasarkan nama    | -                                                              | 200 OK – `{"status":"success", "data":[...]}`         | 400 Bad Request                           |
| GET    | `/contacts/search?category=...`    | Mencari kontak berdasarkan kategori| -                                                              | 200 OK – `{"status":"success", "data":[...]}`         | 400 Bad Request                           |
| PUT    | `/contacts/{id}`                   | Memperbarui kontak berdasarkan ID  | `{"name":"Nama Baru", "phone":"+62...", "category":"#KategoriBaru"}` | 200 OK – `{"message":"Contact updated"}`             | 400 Bad Request – 404 Not Found           |
| DELETE | `/contacts/{id}`                   | Menghapus kontak berdasarkan ID    | -                                                              | 200 OK – `{"message":"Contact deleted"}`              | 404 Not Found                             |

## 🛠️ Cara Menjalankan Proyek

Proyek ini dikembangkan dan diuji pada **WSL (Kali Linux)**.

**1. Prasyarat:**  
Pastikan Anda memiliki `g++`, `cmake`, dan library yang dibutuhkan.

```bash
sudo apt update
sudo apt install build-essential cmake libboost-all-dev libsqlite3-dev
```

**2. Clone Repository:**  

```bash
git clone https://github.com/RozhakXD/MyContact-Backend.git
cd MyContact-Backend
```

**3. Unduh Dependensi Pihak Ketiga:**  
Proyek ini memerlukan **Crow** dan **sqlite_modern_cpp**. Skrip akan mengunduhnya untuk Anda.

```bash
cd third_party
curl -L https://github.com/CrowCpp/Crow/raw/master/include/crow_all.h -o crow_all.h
curl -L https://github.com/SqliteModernCpp/sqlite_modern_cpp/raw/master/hdr/sqlite_modern_cpp.h -o sqlite_modern_cpp.h
cd ..
```

**4. Build Proyek:**  
Gunakan CMake untuk meng-generate file build dan kompilasi.

```bash
mkdir build
cd build
cmake ..
make
```

**5. Jalankan Server:**  
Setelah kompilasi berhasil, jalankan executable-nya.

```bash
./MyContact
```

Server akan berjalan di `http://localhost:18080`. Gunakan API Client seperti **Postman** atau **Insomnia** untuk berinteraksi dengan API.

## 📜 Lisensi

Proyek ini dilisensikan di bawah [MIT License](LICENSE).
