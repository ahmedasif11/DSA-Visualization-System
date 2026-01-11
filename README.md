# DSA Visualization System

A professional desktop application for visualizing Data Structures and Algorithms, built with C++ and SFML 3.0. This application provides interactive visualizations of sorting algorithms with step-by-step execution control.

![C++](https://img.shields.io/badge/C++-17+-00599C?style=flat&logo=c%2B%2B)
![SFML](https://img.shields.io/badge/SFML-3.0-8CC445?style=flat)
![License](https://img.shields.io/badge/License-MIT-blue?style=flat)

## Features

- **Interactive Algorithm Visualization**: Watch sorting algorithms execute step-by-step with visual feedback
- **Multiple Sorting Algorithms**: 
  - Bubble Sort
  - Insertion Sort
  - Selection Sort
- **Real-time Controls**: Play, pause, reset, and navigate through algorithm steps
- **Professional UI**: Clean, modern interface with hover effects and keyboard navigation
- **Custom Implementation**: Core data structures and algorithms implemented from scratch (no STL dependencies)

## Requirements

- **Compiler**: GCC 7+ or MSVC 2017+ (C++17 support required)
- **SFML**: Version 3.0 or higher
- **Build System**: Make or CMake
- **Platform**: Windows (tested with MSYS2 UCRT64), Linux, macOS

## Installation

### Windows (MSYS2 UCRT64)

1. Install MSYS2 from [msys2.org](https://www.msys2.org/)
2. Open MSYS2 UCRT64 terminal
3. Install dependencies:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   pacman -S mingw-w64-ucrt-x86_64-make
   pacman -S mingw-w64-ucrt-x86_64-sfml
   ```
4. Clone the repository:
   ```bash
   git clone <repository-url>
   cd DSA-Visulizer
   ```
5. Build the project:
   ```bash
   make clean
   make
   ```
6. Run the application:
   ```bash
   ./bin/DSA-Visulizer.exe
   ```

### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential libsfml-dev

# Build
make clean
make

# Run
./bin/DSA-Visulizer
```

### macOS

```bash
# Install dependencies via Homebrew
brew install sfml

# Build
make clean
make

# Run
./bin/DSA-Visulizer
```

## Usage

1. **Start the Application**: Launch the executable from the `bin/` directory
2. **Main Menu**: Use mouse or arrow keys to navigate
3. **Select Algorithm**: 
   - Click "Algorithms" → "Sorting Algorithms"
   - Choose a sorting algorithm (Bubble Sort, Insertion Sort, or Selection Sort)
4. **Visualize**: 
   - Click "Play" to start the visualization
   - Use "Pause" to pause execution
   - Use "Reset" to restart from the beginning
   - Press ESC to open the pause menu

## Project Structure

```
DSA-Visulizer/
├── src/
│   ├── App/              # Application entry point and configuration
│   ├── Core/             # Core systems (State, Events, Resources)
│   ├── DSA/              # Data structures and algorithms
│   ├── States/           # Application states (menus, visualizer)
│   ├── UI/               # UI components (buttons, labels, themes)
│   └── Visual/           # Visualization components
├── build/                # Build output directory
├── bin/                  # Executable output directory
├── Makefile              # Build configuration
└── README.md             # This file
```

## Architecture

The application follows a clean architecture with clear separation of concerns:

- **State Management**: Game State Pattern for managing application screens
- **Event System**: Publisher-subscriber pattern for decoupled communication
- **Resource Management**: Centralized loading and caching of fonts and textures
- **Algorithm Execution**: Step-by-step execution with timing control
- **Visualization**: Modular rendering system for array visualization

## Building from Source

### Using Make

```bash
make clean    # Clean build artifacts
make          # Build the project
make run      # Build and run (if available)
```

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
./DSA-Visulizer
```

## Keyboard Shortcuts

- **Arrow Keys**: Navigate menus
- **Enter/Space**: Select/Activate
- **ESC**: Pause menu / Go back

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Maintain code style consistency
2. Add appropriate comments for complex logic
3. Test changes thoroughly
4. Update documentation as needed

## License

This project is open source and available under the MIT License.

## Acknowledgments

- Built with [SFML](https://www.sfml-dev.org/) graphics library
- Inspired by the need for better algorithm visualization tools

---

**Note**: Fonts are automatically loaded from system fonts if custom fonts are not available. The application will use Windows system fonts (Arial, Tahoma, etc.) as fallback.
