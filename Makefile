TOP_NAME = top

TOP_SRC = $(wildcard csrc/*.cpp)
TOP_VSRC = $(wildcard vsrc/*.v)

BUILD_DIR = obj_dir

all: sim


sim:compile run 
	$(call git_commit, "sim RTL") 

compile:
	@echo "==========Compiling...=========="
	verilator --cc --trace-fst $(TOP_VSRC) --exe $(TOP_SRC) --build -j 24
run:
	@echo "==========Running...=========="
	./$(BUILD_DIR)/V$(TOP_NAME)

wave:
	@echo "==========Generating wave...=========="
	gtkwave waveform.fst


clean:
	@echo "==========Cleaning...=========="
	rm -rf $(BUILD_DIR) waveform.fst
