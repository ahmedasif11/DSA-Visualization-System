# Makefile for DSA Visualizer
# MSYS2 UCRT64 environment
# SFML 3.0

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Include directories
INCLUDES = -Isrc

# SFML libraries (SFML 3.0)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files (explicitly list all .cpp files)
SOURCES = \
	src/main.cpp \
	src/App/Application.cpp \
	src/Core/Events/EventBus.cpp \
	src/Core/Resources/ResourceManager.cpp \
	src/Core/State/State.cpp \
	src/Core/State/StateManager.cpp \
	src/States/EntryState.cpp \
	src/States/MainMenuState.cpp \
	src/States/TestState.cpp \
	src/States/AlgorithmMenuState.cpp \
	src/States/SortMenuState.cpp \
	src/States/VisualizerState.cpp \
	src/States/PauseMenuState.cpp \
	src/UI/Components/Button.cpp \
	src/UI/Components/Label.cpp \
	src/UI/Theme/Theme.cpp \
	src/UI/Theme/ThemeManager.cpp \
	src/DSA/Array/Array.cpp \
	src/DSA/Algorithms/Sorting/SorterBase.cpp \
	src/DSA/Algorithms/Sorting/BubbleSort.cpp \
	src/DSA/Algorithms/Sorting/InsertionSort.cpp \
	src/DSA/Algorithms/Sorting/SelectionSort.cpp \
	src/DSA/Algorithms/AlgorithmExecutor.cpp \
	src/Visual/Visualizer/BarVisualizer.cpp

# Object files
OBJECTS = $(SOURCES:src/%.cpp=$(BUILD_DIR)/%.o)

# Executable
TARGET = $(BIN_DIR)/DSA-Visulizer.exe

# Default target
all: $(TARGET)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/App
	mkdir -p $(BUILD_DIR)/Core/Events
	mkdir -p $(BUILD_DIR)/Core/Resources
	mkdir -p $(BUILD_DIR)/Core/State
	mkdir -p $(BUILD_DIR)/States
	mkdir -p $(BUILD_DIR)/UI/Components
	mkdir -p $(BUILD_DIR)/UI/Theme
	mkdir -p $(BUILD_DIR)/DSA/Array
	mkdir -p $(BUILD_DIR)/DSA/Algorithms/Sorting
	mkdir -p $(BUILD_DIR)/DSA/Algorithms
	mkdir -p $(BUILD_DIR)/Visual/Visualizer
	mkdir -p $(BIN_DIR)

# Build executable
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(SFML_LIBS)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the application
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rebuild everything
rebuild: clean all

.PHONY: all run clean rebuild
