# Compiler và flags
CXX := g++
INCLUDE_FLAGS := -Iinclude -Iinclude/SDL2 -Iinclude/SDL2_image -Iinclude/Core_System -Iinclude/SDL2_ttf
CXXFLAGS := $(INCLUDE_FLAGS) -Wall -g -Dmain=SDL_main
LDFLAGS := -L"lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Thư mục
SRC_DIR := src
BUILD_DIR := build

# Tìm tất cả file .cpp trong src/
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# File thực thi
TARGET := $(BUILD_DIR)/main.exe

# Rule chính
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile từng file .cpp thành .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Clean nhưng giữ thư mục build
clean:
	@del /S /Q $(BUILD_DIR)\*.o $(BUILD_DIR)\*.exe 2>nul || echo "Nothing to clean."
