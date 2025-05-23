CC=nvcc
OUT_DIR=out
EXECUTABLES = add-naive add-one-block add-multiple-blocks
TARGETS = $(addprefix $(OUT_DIR)/, $(EXECUTABLES))

all: $(TARGETS)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%: %.cu | $(OUT_DIR)
	$(CC) -o $@ $<

clean:
	rm -rf $(OUT_DIR)

.PHONY: all clean profile

profile: $(TARGETS)
	@for exe in $(EXECUTABLES); do \
		echo "---- Profiling $$exe... -----"; \
		./nsys_easy ./$(OUT_DIR)/$$exe; \
	done
