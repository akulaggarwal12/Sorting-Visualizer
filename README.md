# Army Sorting Visualizer

A real-time, interactive sorting algorithm visualizer built with **C++** and **Raylib**. This project simulates an "Army" of soldiers represented by bars, where their heights and HP correspond to their strength. The army must be sorted to defend against incoming fireballs.



## Features
* **Manual Step-by-Step Sorting**: Progress through algorithms frame-by-frame using the `SPACE` key.
* **Interactive Defense**: Fireballs launch based on the heights of the soldiers. If a fireball flies over a soldier's head due to a height mismatch, the game ends.
* **Dynamic Memory Management**: Utilizes C++ heap allocation (`new`/`delete[]`) for stability and to prevent stack overflow.
* **Multiple Algorithms**:
    * **1. Bubble Sort**: The classic adjacent-swap method.
    * **2. Cocktail Shaker Sort**: Bidirectional bubble sort for faster "turtle" movement.
    * **3. Selection Sort**: Finding the minimum element and placing it at the front of the unsorted section.
* **Visual Feedback**: Real-time color highlighting for active comparisons and "DEAD" status indicators.

## Tech Stack
* **Language**: C++
* **Graphics Library**: [Raylib](https://www.raylib.com/)
* **Memory Management**: Heap Allocation (Dynamic Arrays)
* **OS**: Linux (tested on Ubuntu/Mint)

## Installation & Compilation

### Prerequisites
Ensure you have `g++` and the `raylib` development libraries installed on your system.

### Compiling
To compile the project, use the following command:

```bash
g++ Game.cpp -o Game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
## Running

```bash
./Game
```

## Controls
* **Terminal Input**: Enter the size of the army (n) when prompted.
* **Algorithm Choice**: Select 1 (Bubble), 2 (Cocktail), or 3 (Selection) in the terminal.
* **SPACE Key**: Advance the sorting algorithm by one step during the simulation.

## Project Structure
* **SoldierStats**: Initializes random heights and HP for the army.
* **FireballStats**: Generates fireballs proportional to soldier heights.
* **BubbleSort/CocktailSort/SelectionSort**: Functions containing core graphics logic and frame-by-frame sorting.
* **swap**: A memory-safe reference-based swap for Soldier structs.

## Challenges Overcome
* **Memory Stability**: Resolved Segmentation Faults by moving from stack-based arrays to dynamic heap allocation.
* **Collision Synchronization**: Aligned fireball hitboxes with real-time changing bar heights during sorting passes.
* **State Management**: Used static variable tracking to allow the game loop to "remember" sorting progress across individual frames.
