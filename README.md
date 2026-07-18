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
2. Run
bash
.\urly.exe
3. Test in Browser
Open your browser and visit: http://localhost:8080/ping

You should see:

json
{"status":"alive","message":"Viresh's URL Shortener is running!"}
📂 API Endpoints
Endpoint	Method	Description
/ping	GET	Health check — returns {"status":"alive"}
/shorten?url=X	GET	Shorten a URL — returns {"short_code":"abc123","long_url":"X"}
Example:

text
GET http://localhost:8080/shorten?url=google.com
Response:

json
{"short_code":"a7k9m2","long_url":"=google.com"}
📅 What I Learned
Concept	How URLy Taught Me
HTTP Protocol	Building a raw socket server
REST API	Designing endpoints
Persistence	Saving to urls.txt
Collision Handling	do-while loop with map
System Design	Thinking about scale and trade-offs
🏆 Why This Project Matters
This project demonstrates:

Low-level networking (sockets)

C++ proficiency (pointers, memory management)

System design fundamentals (REST, persistence, routing)

Built by Viresh Ranjanagi
