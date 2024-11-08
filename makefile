# directories
SRC = src
BIN = bin
INCLUDE = include
LIB = lib
LIB_SRC = $(SRC)/$(LIB)
STATIC_DIR = $(LIB)/static
SHARED_DIR = $(LIB)/shared

# compiler arguments and flags
CXX = g++
CXXFLAGS = -Wall -I$(INCLUDE) -I$(LIB_SRC)
LDFLAGS =
AR = ar
ARFLAGS = rcs

# source files and object files
SRC_FILES = $(wildcard $(SRC)/*.cpp $(SRC)/*.c)
OBJ_FILES = $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(patsubst $(SRC)/%.c,$(BIN)/%.o,$(SRC_FILES)))

# library source files
HXX_FILES = $(wildcard $(INCLUDE)/*.hxx)
TPP_FILES = $(wildcard $(LIB_SRC)/*.tpp)
LIB_CPP_FILES = $(patsubst $(INCLUDE)/%.hxx,$(BIN)/%.cpp,$(HXX_FILES))
LIB_OBJ_FILES = $(patsubst $(INCLUDE)/%.hxx,$(BIN)/%.o,$(HXX_FILES))

# library names
LIB_NAME = library
STATIC_LIB = $(STATIC_DIR)/$(LIB_NAME).a
SHARED_LIB = $(SHARED_DIR)/$(LIB_NAME)$(SHARED)

# executable target
TARGET = executable

# os detection
ifdef ComSpec
	RM = del /q /f
	RM_DIR = rmdir /q /s
	MKDIR_BIN = if not exist "$(BIN)" mkdir "$(BIN)"
	MKDIR_STATIC = if not exist "$(STATIC_DIR)" mkdir "$(STATIC_DIR)"
	MKDIR_SHARED = if not exist "$(SHARED_DIR)" mkdir "$(SHARED_DIR)"
	EXE = .exe
	CLEAR = cls
	RUN =
	SHARED = .dll
else
	RM = rm -f
	RM_DIR = rm -rf
	MKDIR_BIN = mkdir -p $(BIN)
	MKDIR_STATIC = mkdir -p $(STATIC_DIR)
	MKDIR_SHARED = mkdir -p $(SHARED_DIR)
	CXXFLAGS += -fpic
	EXE =
	CLEAR = clear
	RUN = ./
	SHARED = .so
endif

# default target
all: $(TARGET)

# create necessary directories
directories:
	@$(MKDIR_BIN)
	@$(MKDIR_STATIC)
	@$(MKDIR_SHARED)

# library targets
lib: directories $(STATIC_LIB) $(SHARED_LIB)
	
# generate intermediate cpp files for template compilation
ifdef ComSpec
$(BIN)/%.cpp: $(INCLUDE)/%.hxx
	@echo #include ^<$*.hxx^> > "$@"
else
$(BIN)/%.cpp: $(INCLUDE)/%.hxx
	@echo '#include <$*.hxx>' > $@
endif

# compile library object files
$(BIN)/%.o: $(BIN)/%.cpp $(INCLUDE)/%.hxx $(LIB_SRC)/%.tpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# create static library
$(STATIC_LIB): $(LIB_OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

# create shared library
$(SHARED_LIB): $(LIB_OBJ_FILES)
	$(CXX) -shared -o $@ $^

# link to executable
$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@$(EXE) $^ $(LDFLAGS)

# compile object files from source files
$(BIN)/%.o: $(SRC)/%.cpp
	@$(MKDIR_BIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/%.c
	@$(MKDIR_BIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# debug target to show detected files
debug:
	@echo "Header files found: $(HXX_FILES)"
	@echo "Template files found: $(TPP_FILES)"
	@echo "Generated cpp files: $(LIB_CPP_FILES)"
	@echo "Object files to create: $(LIB_OBJ_FILES)"

# clean
clean:
ifdef ComSpec
	@if exist $(BIN) $(RM_DIR) $(BIN)
	@if exist $(LIB) $(RM_DIR) $(LIB)
	@if exist $(TARGET)$(EXE) $(RM) $(TARGET)$(EXE)
else
	$(RM_DIR) $(BIN)
	$(RM_DIR) $(LIB)
	$(RM) $(TARGET)$(EXE)
endif

# run
run: $(TARGET)
	@$(CLEAR) 
	@$(RUN)$(TARGET)$(EXE)

.phony: all clean run lib directories debug