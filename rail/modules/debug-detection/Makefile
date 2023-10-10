FINAL_NAME = debug-detection

SOURCES := $(wildcard $(RAIL_SRC_DIR)/*.c $(RAIL_SRC_DIR)/*/*.c)
OBJECTS := $(SOURCES:$(RAIL_SRC_DIR)/%.c=$(RAIL_OBJECT_DIR)/%.o)
rm       = rm -rf
mkdir    = mkdir -p

all: build

init:
	@$(mkdir) $(OBJ_DIR)
	@$(mkdir) $(BIN_DIR)
	@$(mkdir) $(SO_DIR)

clean:
	@$(rm) $(RAIL_TARGET_DIR)

$(OBJECTS): $(RAIL_OBJECT_DIR)/%.o : $(RAIL_SRC_DIR)/%.c
	@$(RAIL_CC) $(RAIL_CC_FLAGS)  -c $< -o $@

build: $(OBJECTS)
	@$(RAIL_CC) -o $(RAIL_BIN_DIR)/$(FINAL_NAME) $(RAIL_OBJECT_DIR)/*.o
