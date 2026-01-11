# DSA Visualizer

A simple C++ app I made to visualize sorting algorithms. It uses SFML 3.0 and shows how different sorting algorithms work step by step.

## What it does

You can watch sorting algorithms in action with visual feedback. Currently supports:
- Bubble Sort
- Insertion Sort  
- Selection Sort

There's a play/pause button, reset, and you can control the speed with a slider. The bars show numbers and there's a legend to understand what the colors mean. Pretty straightforward.

## Building it

I'm using Windows with MSYS2, but it should work on Linux/Mac too if you have SFML 3.0 installed.

### Windows (MSYS2)

If you're using MSYS2 like me:

```bash
# Install SFML and stuff
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-make
pacman -S mingw-w64-ucrt-x86_64-sfml

# Then build
cd DSA-Visulizer
make clean
make
```

Run it from `bin/DSA-Visulizer.exe`

### Linux

```bash
sudo apt-get install build-essential libsfml-dev
make clean && make
./bin/DSA-Visulizer
```

### macOS

```bash
brew install sfml
make clean && make
./bin/DSA-Visulizer
```

## How to use

1. Run the exe
2. Click through menus (Algorithms → Sorting Algorithms)
3. Pick a sorting algorithm
4. Hit Play and watch it work
5. Adjust speed with the slider on the bottom
6. ESC opens pause menu, Space toggles play/pause

That's pretty much it. The UI is self-explanatory.

## Project structure

```
src/
  App/          - main app stuff
  Core/         - state management, events
  DSA/          - algorithms and array implementation
  States/       - different screens (menus, visualizer)
  UI/           - buttons, labels, slider, themes
  Visual/       - rendering components for bars/annotations
```

I tried to keep things organized but I'm sure it could be better. The code is comment-free now (as requested).

## Notes

- Built with SFML 3.0 (had to update a lot of stuff from 2.x)
- Everything is implemented from scratch, no STL containers for the core DSA stuff
- Fonts fall back to system fonts if custom ones aren't found
- The speed slider works in real-time, no stuttering

## Building

Just use `make`. Or CMake if you prefer:

```bash
mkdir build && cd build
cmake ..
make
```

That's it. Let me know if something breaks or if you want more algorithms added.
