"""
Gera os datasets usados nos experimentos (Seção 5 do relatório).

Estrutura de saída (dentro de experimentos/datasets/):
    int/random_<n>.txt        -- inteiros distintos em ordem aleatória
    int/sorted_asc_<n>.txt    -- inteiros em ordem crescente (pior caso p/ BST)
    int/sorted_desc_<n>.txt   -- inteiros em ordem decrescente (pior caso p/ BST)

    string/random_<n>.txt          -- palavras aleatórias, prefixos pouco compartilhados
    string/alta_densidade_<n>.txt  -- palavras com prefixos MUITO compartilhados
    string/baixa_densidade_<n>.txt -- palavras com prefixos pouco compartilhados (variação deliberada)

    coord/random_<n>.txt    -- pontos (x, y) uniformemente distribuídos
    coord/cluster_<n>.txt   -- pontos concentrados em poucos agrupamentos (densidade não uniforme)
    coord/sorted_x_<n>.txt  -- pontos ordenados por x (pior caso p/ KD-Tree sem balanceamento)

IMPORTANTE: a lista TAMANHOS abaixo precisa ser IDÊNTICA à lista TAMANHOS
declarada em experimentos/run_experimentos.cpp -- se mudar uma, muda a outra.
"""

import random
import string
import os

random.seed(42)  # reprodutibilidade: rodar de novo gera os mesmos datasets

TAMANHOS = [10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000]

BASE_DIR = os.path.join(os.path.dirname(__file__), "datasets")


def escrever_inteiros(caminho, valores):
    with open(caminho, "w") as f:
        f.write("\n".join(str(v) for v in valores))
        f.write("\n")


def escrever_strings(caminho, valores):
    with open(caminho, "w") as f:
        f.write("\n".join(valores))
        f.write("\n")


def escrever_pontos(caminho, pontos):
    with open(caminho, "w") as f:
        f.write("\n".join(f"{x} {y}" for x, y in pontos))
        f.write("\n")


# ---------------------------------------------------------------------------
# inteiros (BST, AVL, Treap, Splay)
# ---------------------------------------------------------------------------

def gerar_inteiros(n):
    # valores distintos, espaço bem maior que n pra evitar colisões
    return random.sample(range(0, n * 10 + 10), n)


def gerar_datasets_int():
    pasta = os.path.join(BASE_DIR, "int")
    os.makedirs(pasta, exist_ok=True)

    for n in TAMANHOS:
        valores = gerar_inteiros(n)
        escrever_inteiros(os.path.join(pasta, f"random_{n}.txt"), valores)

        ordenado = sorted(valores)
        escrever_inteiros(os.path.join(pasta, f"sorted_asc_{n}.txt"), ordenado)
        escrever_inteiros(os.path.join(pasta, f"sorted_desc_{n}.txt"), list(reversed(ordenado)))


# ---------------------------------------------------------------------------
# strings (Trie, Patricia)
# ---------------------------------------------------------------------------

LETRAS = string.ascii_lowercase


def gerar_string_aleatoria(tam_min=4, tam_max=8):
    tamanho = random.randint(tam_min, tam_max)
    return "".join(random.choice(LETRAS) for _ in range(tamanho))


def gerar_strings_random(n):
    vistas = set()
    resultado = []
    while len(resultado) < n:
        palavra = gerar_string_aleatoria()
        if palavra not in vistas:
            vistas.add(palavra)
            resultado.append(palavra)
    return resultado


# pool pequeno de prefixos -> muitas palavras vão compartilhar os primeiros
# caracteres, forçando bastante compressão/ramificação em Trie e Patricia
PREFIXOS_COMUNS = [
    "trabalh", "program", "comput", "desenvolv",
    "algorit", "estrutur", "implement", "recurs",
]


def gerar_strings_alta_densidade(n):
    vistas = set()
    resultado = []
    while len(resultado) < n:
        prefixo = random.choice(PREFIXOS_COMUNS)
        sufixo = "".join(random.choice(LETRAS) for _ in range(random.randint(3, 6)))
        palavra = prefixo + sufixo
        if palavra not in vistas:
            vistas.add(palavra)
            resultado.append(palavra)
    return resultado


def gerar_strings_baixa_densidade(n):
    # varia os 2 primeiros caracteres de forma cíclica ANTES de qualquer
    # aleatoriedade, maximizando a dispersão de prefixos compartilhados
    # (em n grande, ainda vai haver alguma repetição -- é "baixa densidade
    # relativa" a alta_densidade, não ausência total de prefixo comum)
    vistas = set()
    resultado = []
    i = 0
    while len(resultado) < n:
        c1 = LETRAS[i % 26]
        c2 = LETRAS[(i // 26) % 26]
        sufixo = "".join(random.choice(LETRAS) for _ in range(random.randint(3, 6)))
        palavra = c1 + c2 + sufixo
        if palavra not in vistas:
            vistas.add(palavra)
            resultado.append(palavra)
        i += 1
    return resultado


def gerar_datasets_string():
    pasta = os.path.join(BASE_DIR, "string")
    os.makedirs(pasta, exist_ok=True)

    for n in TAMANHOS:
        escrever_strings(os.path.join(pasta, f"random_{n}.txt"), gerar_strings_random(n))
        escrever_strings(os.path.join(pasta, f"alta_densidade_{n}.txt"), gerar_strings_alta_densidade(n))
        escrever_strings(os.path.join(pasta, f"baixa_densidade_{n}.txt"), gerar_strings_baixa_densidade(n))


# ---------------------------------------------------------------------------
# coordenadas (KD-Tree)
# ---------------------------------------------------------------------------

LIMITE_COORD = 1_000_000


def gerar_pontos_random(n):
    vistos = set()
    resultado = []
    while len(resultado) < n:
        p = (random.randint(0, LIMITE_COORD), random.randint(0, LIMITE_COORD))
        if p not in vistos:
            vistos.add(p)
            resultado.append(p)
    return resultado


def gerar_pontos_cluster(n, num_clusters=8, espalhamento=2000):
    centros = [
        (random.randint(0, LIMITE_COORD), random.randint(0, LIMITE_COORD))
        for _ in range(num_clusters)
    ]
    vistos = set()
    resultado = []
    while len(resultado) < n:
        cx, cy = random.choice(centros)
        x = max(0, min(LIMITE_COORD, int(random.gauss(cx, espalhamento))))
        y = max(0, min(LIMITE_COORD, int(random.gauss(cy, espalhamento))))
        p = (x, y)
        if p not in vistos:
            vistos.add(p)
            resultado.append(p)
    return resultado


def gerar_datasets_coord():
    pasta = os.path.join(BASE_DIR, "coord")
    os.makedirs(pasta, exist_ok=True)

    for n in TAMANHOS:
        pontos = gerar_pontos_random(n)
        escrever_pontos(os.path.join(pasta, f"random_{n}.txt"), pontos)

        cluster = gerar_pontos_cluster(n)
        escrever_pontos(os.path.join(pasta, f"cluster_{n}.txt"), cluster)

        ordenado_x = sorted(pontos, key=lambda p: p[0])
        escrever_pontos(os.path.join(pasta, f"sorted_x_{n}.txt"), ordenado_x)


if __name__ == "__main__":
    print("Gerando datasets de inteiros (BST, AVL, Treap, Splay)...")
    gerar_datasets_int()
    print("Gerando datasets de strings (Trie, Patricia)...")
    gerar_datasets_string()
    print("Gerando datasets de coordenadas (KD-Tree)...")
    gerar_datasets_coord()
    print(f"Concluido. Datasets salvos em: {BASE_DIR}")
