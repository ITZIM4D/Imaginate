# Imaginate
This project is a basic game engine that I want to create my own games on and build off of. Currently written only for Mac but going to be create windows implementation in the future. To create a game you modify the Game.cpp file, this will 

## Table of Contents
-[Prerequisites](#prerequisites)
-[Installation and Running](#installation-and-running)
-[Features](#features)
-[Tech Stack](#tech-stack)

## Prerequisites
- [GLFW](https://www.glfw.org/download)

## Installation and Running

1. **Install GLFW**
    On mac using homebrew or package manager of choice do
    ```bash
    brew install glfw
    ```


2. **Clone the repository:**
   ```bash
   git clone https://github.com/ITZIM4D/MyGameEngine
   cd MyGameEngine/build
   ```

3. **Build and run the project**
    ```bash
    cmake --build .
    ./MyGameEngine
    ```

## Features
- Camera that moves around scene
- GameObjects
- Scripts that are in Lua
- Compatible with multiple object files
- Scene creations through JSON parsing

## Tech Stack
#### Core Language
- **C++** — Main application and engine logic

#### Graphics / Rendering
- **OpenGL** — Low-level graphics API for rendering

#### Scripting
- **Lua** — Embedded scripting language for game/app logic

#### Bindings / Integration
- **Sol2** — C++ ↔ Lua binding library

#### Data / Scene Format
- **JSON** — Used for scene definitions, configuration, and data serialization
