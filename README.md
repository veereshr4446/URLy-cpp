# 🔗 URLy — C++ URL Shortener

A lightweight, high-performance URL shortener built from scratch in C++ using Windows Sockets. This project demonstrates core system design and networking concepts.

## ✨ Features

- **REST API** (`GET /ping`, `GET /shorten?url=...`)
- **Random 6-character short codes** (collision-free)
- **File-based persistence** (URLs saved to `urls.txt`)
- **100% C++** (No external libraries)

## 🛠️ Tech Stack

- **Language:** C++
- **Networking:** Windows Sockets (`winsock2.h`)
- **Storage:** File-based (`urls.txt`)

## 🚀 How to Run

```bash
g++ minimal_api.cpp -o urly.exe -lws2_32
.\urly.exe
