# Compiler và flags
CXX := g++
INCLUDE_FLAGS := -Iinclude -Iinclude/SDL2 -Iinclude/lSDL2_mixer -Iinclude/lSDL2_ttf -Iinclude/SDL2_image -Iinclude/Core_System -Iinclude/Graphics_Rendering -Iinclude/Entities -Iinclude/Map
CXXFLAGS := $(INCLUDE_FLAGS) -Wall -g -Dmain=SDL_main
LDFLAGS := -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -mwindows

# Thư mục
SRC_DIR := src
BUILD_DIR := build

# Danh sách file
SRC_FILES := src/Graphics_Rendering/Graphic.cpp src/Graphics_Rendering/Animation.cpp src/Graphics_Rendering/Textengine.cpp src/Entities/Player.cpp src/Map/Map.cpp src/Core_System/Game.cpp src/main.cpp
OBJ_FILES := $(patsubst src/%.cpp, build/%.o, $(SRC_FILES))

# File thực thi
TARGET := $(BUILD_DIR)/main.exe

# Rule chính
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS) -mwindows

# Compile từng file .cpp thành .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Clean nhưng giữ thư mục build
clean:
	@echo "Cleaning up object files and executables..."
	@del /S /Q build\*.o build\*.exe 2>nul || echo "No object files to delete."
	@echo "Done!""