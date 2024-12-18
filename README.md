# Cub3D - 42 Project

## Table of Contents
- [Introduction](#introduction)
- [Mandatory Part](#mandatory-part)
  - [Overview](#overview)
  - [Gameplay](#gameplay)
  - [Compilation and Execution](#compilation-and-execution)
- [Bonus Part](#bonus-part)
  - [Overview](#bonus-overview)
  - [Features](#bonus-features)
- [Resources](#resources)
- [Authors](#authors)

## Introduction
**Cub3D** is a 42 project inspired by classic FPS games like Wolfenstein 3D. The goal is to build a 3D rendering engine using raycasting, implementing core gameplay mechanics, and creating an immersive maze exploration experience. This project tests your understanding of graphical programming, 3D mathematics, and efficient memory management.

## Mandatory Part

### Overview
The mandatory part of the project requires you to:
- Render a 3D view of a maze using raycasting.
- Handle player movements and collisions.
- Parse a `.cub` map file containing the maze's configuration.

### Gameplay
- The player can move in four directions (forward, backward, left, right) and rotate their view.
- Walls, floors, and ceilings are rendered based on the map file.
- The game ends when the player reaches a designated exit.

### Compilation and Execution
To compile the project, use the following command:

```bash
make
```

To run the game, execute:

```bash
./cub3D map.cub
```

Here, `map.cub` is a valid map file adhering to the project specifications.

## Bonus Part

### Bonus Overview
The bonus part introduces advanced features and enhancements to the basic game engine, adding more depth and interaction to the game.

### Features
- **Doors and Keys:** Add doors that can be opened with keys or triggers.
- **Enemies and AI:** Implement enemies with basic AI for chasing or attacking the player.
- **Multiple Levels:** Allow progression through different maps or levels.
- **Minimap:** Display a minimap showing the player’s position and surroundings.
- **Improved Graphics:** Add textures to walls, floors, and ceilings, and implement sprite rendering for objects.

### Compilation and Execution
To compile the bonus version, use:

```bash
make bonus
```

Run the game with:

```bash
./cub3D_bonus map.cub
```

## Resources
- [Cub3D - 42 Project Subject](https://projects.intra.42.fr/projects/cub3d)
- [Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX Documentation](https://harm-smith.github.io/42-graphics/)
- [Wolfenstein 3D - Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D)

## Authors
**hel-omra** and **tbesbess**
[42 Intra Profiles]

- [hel-omra](https://profile.intra.42.fr/users/hel-omra)
- [tbesbess](https://profile.intra.42.fr/users/tbesbess)
