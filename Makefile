# Compiler và flags
CXX := g++
CXXFLAGS := -I"include" -I"include/SDL2" -I"include/SDL2_image" -Wall -g
LDFLAGS := -L"lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Thư mục
SRC_DIR := src
BUILD_DIR := build

# Tìm tất cả file .cpp trong thư mục con của src
SRC_DIRS := src/Core_System src/Graphics_Rendering src/Entities src/Map src/Combat_Mechanics src/Sound_Effects
SRC_FILES := $(wildcard $(patsubst %, %/*.cpp, $(SRC_DIRS)))
OBJ_FILES := $(patsubst src/%.cpp, build/%.o, $(SRC_FILES))

# File thực thi
TARGET := $(BUILD_DIR)/main.exe

# Rule chính
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compile từng file .cpp thành .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	cmd /c rmdir /s /q $(BUILD_DIR) || echo "No build folder to delete."
