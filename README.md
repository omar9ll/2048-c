# 🎮 2048 in C

A terminal version of the classic **2048** puzzle game, written in C.

Slide tiles with **W / A / S / D**; matching tiles merge and double. Reach **2048** to win, and the game ends when no moves are left.

## ✨ Features
- 4×4 board stored as a 2D array, with new 2 or 4 tiles spawned in random empty cells
- Shift-and-merge logic for all four directions (reused by transforming rows/columns)
- Win detection (2048 tile) and game-over detection (no empty cells or merges left)
- Raw keyboard input on Unix using `termios`, so moves happen without pressing Enter
- Modular structure (`game2048.c` + `utility.c/.h`) built with a Makefile (`-Wall -Wextra -std=c99`)

## ▶️ Build & play
```bash
make
./game2048
```
Controls: `w` up · `a` left · `s` down · `d` right · `q` quit

> Uses `termios`, so it runs on Linux/macOS terminals.

## 🛠️ Tech
C (C99) · gcc · Make · Unix terminal I/O
