CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Iinclude
BIN_DIR := bin

STRUCTS := BST AVL trie treap splay patricia kdtree

TEST_BINS := $(addprefix $(BIN_DIR)/test_, $(STRUCTS))

.PHONY: all test clean $(addprefix test-, $(STRUCTS))

all: $(TEST_BINS)

test: $(TEST_BINS)
	@for bin in $(TEST_BINS); do \
		echo "== Rodando $$bin =="; \
		./$$bin || exit 1; \
		echo ""; \
	done

$(BIN_DIR)/test_%: src/%.cpp test/test_%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

define TEST_RULE
test-$(1): $(BIN_DIR)/test_$(1)
	./$(BIN_DIR)/test_$(1)
endef

$(foreach s,$(STRUCTS),$(eval $(call TEST_RULE,$(s))))

clean:
	rm -rf $(BIN_DIR)