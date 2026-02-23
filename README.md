# Game of Life

## <a name="introduction-en">📖 Introduction ##

The Game of Life is a cellular automaton by John Horton Conway. This project is a simple implementation in C of the game on a limited grid and limited iteration system. It's not made to be interactive. You create the starting pattern by 'painting' or by loading a map file.

[Conway's Game of Life on Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

## 📋 Table of Contents ##

* [📖 Introduction](#introduction-en)
* [⚙️ Requirements](#requirements-en)
* [🚀 How to start](#start-en)
* [🚀 How to play](#play-en)

## <a name="requirements-en">⚙️ Requirements ##

Use only the following functions :

* `atoi`, `read`, `putchar`, `malloc`, `calloc`, `realloc`, `free`, `putchar`

To load a map directly from a file, the `libft` is used, accordingly with `get_next_line` library.

### How does it work ###

Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step (iteration) in time, the following transitions occur:

- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## <a name="start-en">🚀 How to start ##

```sh
./life width height iterations
```

* `width` :  map width
* `height` :  map height
* `iterations` : number of simulation run/step

or

```sh
./life filename
```
First line of the map file :

* `width` :  map width
* `height` :  map height
* `iterations` : number of simulation run/step

Optionnal :

* `deadCell` :  character representing a deadCell
* `aliveCell` :  character representing an aliveCell

If a line is incomplete, it will be filled with deadeCells.
If a line is too long, it will be truncated to width from config

Example :

```sh
$> echo 'xdsawx' | ./life 2 2 10
$
00
00
$
```

or

```sh
$> ./life map2.txt
$
----------
----O-----
---OOO----
--O-O-O---
-OOO-OOO--
--O-O-O---
---OOO----
----O-----
----------
----------
$
```


## <a name="play-en">🚀 How to play ##

- `w`, `a`, `s`, `d` -> move the pen up, left, bottom, and right.
- `x` -> lower or lift the pen in order to start or stop drawing.

Any other character will be rejected. Press `Enter` when you finished your input and `Ctrl + D` to close stdin. 

### How to end the game ###

The printed game simulation is the result.

---
