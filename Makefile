#SRC specifies which files to compile as part of the project
SRC_DIR = Source
BUILD_DIR = Build

SRC =  $(wildcard Engine/Asset/*.cpp)
SRC += $(wildcard Engine/Management/*.cpp)
SRC += $(wildcard Engine/Primitive/*.cpp)
SRC += $(wildcard Engine/Rendering/*.cpp)
SRC += $(wildcard Source/*.cpp)
HDR = $(wildcard $(SRC_DIR)/*.h)

#CC specifies which compiler we're using
CC = g++

#Compiler Flags
# -w suppresses all warnings
CC_FLAGS = -w -std=c++11

#Linker Flags
LD_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lopenal -lalut
INCLUDES = -IInclude $(foreach file,$(wildcard Engine/*/include), -I$(file))

#TARGET specifies the name of our exectuable
TARGET_NAME = Egress
TARGET = ./$(TARGET_NAME)

OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))
.PHONY: clean distclean run

#This is the target that compiles our executable
all: dir $(TARGET)

dir:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo Linking $@
	@$(CC) -ggdb $^ -o $@ $(LD_FLAGS)

$(BUILD_DIR)/%.o : %.cpp
$(BUILD_DIR)/%.o : %.cpp $(BUILD_DIR)/%.d
	@echo Compiling $< to $@
	@$(CC) -ggdb $(CC_FLAGS) $(INCLUDES) -c $< -o $@ -MT $@ -MMD -MP -MF $(@:.o=.d)

clean:
	@echo Cleaning
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET)

distclean:
	@echo Removing Directory $(BUILD_DIR)
	@$(RM) -rf $(BUILD_DIR)

run: all
	@$(TARGET)

debug: all
	@ddd $(TARGET)

$(BUILD_DIR)/%.d:
	@mkdir -p $(dir $@)
.PRECIOUS: $(BUILD_DIR)/%.d

-include $(SRC:.cpp=.d)
