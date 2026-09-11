CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Iinclude
BIN_DIR := bin

STRUCTS := BST AVL trie treap splay patricia kdtree

TEST_BINS := $(addprefix $(BIN_DIR)/test_, $(STRUCTS))

# Cada estrutura tem seu próprio executável de experimento (exp_<nome>),
# igual aos testes -- isso é necessário porque cada header declara sua
# própria "struct Node" no escopo global; incluir mais de um header de
# estrutura no MESMO arquivo .cpp causa erro de redefinição.
EXP_BINS := $(addprefix $(BIN_DIR)/exp_, $(STRUCTS))

.PHONY: all test clean datasets experimentos $(addprefix test-, $(STRUCTS))

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

# Gera os datasets (int/string/coord, várias variações e tamanhos de 10 a 100k)
datasets:
	python3 experimentos/gerar_datasets.py

# Compila cada executável de experimento: exp_BST.cpp + src/BST.cpp -> bin/exp_BST
$(BIN_DIR)/exp_%: experimentos/exp_%.cpp src/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Gera os datasets (se ainda não existirem), roda os 7 executáveis de
# experimento e concatena a saída de todos em experimentos/resultados.csv
experimentos: datasets $(EXP_BINS)
	@echo "estrutura,variacao,tamanho,operacao,tempo_ms" > experimentos/resultados.csv
	@for bin in $(EXP_BINS); do \
		echo "== Rodando $$bin =="; \
		./$$bin >> experimentos/resultados.csv; \
	done
	@echo ""
	@echo "Concluido! Resultados em experimentos/resultados.csv"