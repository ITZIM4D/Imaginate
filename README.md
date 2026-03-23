# Imaginate
This project is a basic game engine that I want to create my own games on and build off of. Currently written only for Mac but going to be create windows implementation in the future.

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
- Compatible with multiple object files