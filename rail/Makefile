MODULES = modules/vacancy-detection modules/test # $(wildcard modules/*)

rm    = rm -rf
mkdir = mkdir -p
make  = make

include .env

all: build

init:
	@$(mkdir) $(RAIL_BIN_DIR)
	@$(mkdir) $(RAIL_OBJECT_DIR)
	@$(mkdir) $(RAIL_LIB_DIR)

clean:
	@$(rm) $(RAIL_TARGET_DIR)

$(MODULES): clean init
	@$(make) -C $@

build: $(MODULES)
