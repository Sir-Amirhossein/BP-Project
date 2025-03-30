# Food Reservation System

This is a **Food Reservation System** written in C, designed for managing food orders and reservations for both **students** and **admins**. It uses **SQLite** as the underlying database engine and provides a simple menu-driven interface via the command line.

## Features

- 👨‍🎓 **Student Panel**:
  - View available food items
  - Reserve meals
  - Cancel reservations
  - View personal reservation history

- 🧑‍💼 **Admin Panel**:
  - Manage food menus
  - Add or remove food options
  - View all reservations
  - Analyze order statistics

## Technologies

- Programming Language: **C**
- Database: **SQLite** (embedded, no setup required)
- Build System: **CMake**

## Getting Started

### 🔧 Build Instructions

Make sure you have `cmake` and a C compiler like `gcc` installed.

```bash
mkdir build
cd build
cmake ..
make
./Project
