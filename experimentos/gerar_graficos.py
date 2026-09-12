import pandas as pd
import matplotlib.pyplot as plt
import os

# =============================================================================
# CONFIGURAÇÕES GLOBAIS
# =============================================================================
ARQUIVO_DADOS = 'resultados.csv'
PASTA_SAIDA = 'graficos'

ESTRUTURAS_INT = ['BST', 'AVL', 'TREAP', 'SPLAY']
ESTRUTURAS_STR = ['TRIE', 'PATRICIA']
OPERACOES = ['insercao', 'busca', 'remocao']

# Dicionário de cores para garantir consistência visual em todos os gráficos
CORES = {
    'BST': '#1f77b4',       # Azul
    'AVL': '#2ca02c',       # Verde
    'TREAP': '#d62728',     # Vermelho
    'SPLAY': '#9467bd',     # Roxo
    'TRIE': '#ff7f0e',      # Laranja
    'PATRICIA': '#8c564b',  # Marrom
    'KDTREE': '#e377c2'     # Rosa
}

# =============================================================================
# FUNÇÕES DE PLOTAGEM REUTILIZÁVEIS
# =============================================================================
def criar_pasta_saida():
    """Garante que a pasta de gráficos exista."""
    if not os.path.exists(PASTA_SAIDA):
        os.makedirs(PASTA_SAIDA)

def plot_comparativo_simples(df, coluna_agrupamento, titulo, nome_arquivo, usa_cores_globais=False):
    """Gera um gráfico comparativo único em escala log-log."""
    plt.figure(figsize=(10, 6))
    
    # Agrupa pelo identificador (ex: estrutura) e plota cada linha
    for chave, grupo in df.groupby(coluna_agrupamento):
        grupo = grupo.sort_values('tamanho').dropna(subset=['tamanho', 'tempo_ms'])
        if grupo.empty:
            continue
            
        cor = CORES.get(chave, None) if usa_cores_globais else None
        plt.plot(grupo['tamanho'], grupo['tempo_ms'], marker='o', 
                 label=chave, linewidth=2, color=cor)

    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Tamanho da entrada (log)')
    plt.ylabel('Tempo (ms, log)')
    plt.title(titulo)
    plt.legend(title=coluna_agrupamento.capitalize(), bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.grid(True, which="both", ls="--", alpha=0.4)
    plt.tight_layout()
    plt.savefig(os.path.join(PASTA_SAIDA, nome_arquivo), dpi=300)
    plt.close()

def plot_subplots_operacoes(df, coluna_agrupamento, titulo_principal, nome_arquivo):
    """Gera uma figura com 3 subplots (Inserção, Busca, Remoção) em escala log-log."""
    fig, axes = plt.subplots(1, 3, figsize=(18, 6))
    
    for idx, op in enumerate(OPERACOES):
        ax = axes[idx]
        df_op = df[df['operacao'] == op]
        
        for chave, grupo in df_op.groupby(coluna_agrupamento):
            grupo = grupo.sort_values('tamanho').dropna(subset=['tamanho', 'tempo_ms'])
            if grupo.empty:
                continue
            ax.plot(grupo['tamanho'], grupo['tempo_ms'], marker='o', label=chave, linewidth=2)
            
        ax.set_xscale('log')
        ax.set_yscale('log')
        ax.set_xlabel('Tamanho da entrada (log)')
        if idx == 0:
            ax.set_ylabel('Tempo (ms, log)')
            
        ax.set_title(f'Operação: {op.capitalize()}')
        ax.legend(title=coluna_agrupamento.capitalize())
        ax.grid(True, which="both", ls="--", alpha=0.4)
        
    fig.suptitle(titulo_principal, fontsize=16, y=1.05)
    plt.tight_layout()
    plt.savefig(os.path.join(PASTA_SAIDA, nome_arquivo), dpi=300, bbox_inches='tight')
    plt.close()

def gerar_tabela_resumo(df):
    """Gera uma imagem de tabela com o tempo médio das estruturas no pior/maior caso (variação random)."""
    # Filtra apenas o cenário neutro
    df_rand = df[df['variacao'] == 'random'].copy()
    
    # Encontra o maior tamanho testado para cada estrutura e operação
    indices_max = df_rand.groupby(['estrutura', 'operacao'])['tamanho'].idxmax()
    df_max = df_rand.loc[indices_max]
    
    # Cria uma tabela pivotada: linhas=estruturas, colunas=operacoes
    pivot = df_max.pivot(index='estrutura', columns='operacao', values='tempo_ms')
    
    # Formata a tabela para plotagem
    fig, ax = plt.subplots(figsize=(8, 4))
    ax.axis('off')
    ax.axis('tight')
    
    textos_celulas = [[f"{val:.4f}" if pd.notna(val) else "N/A" for val in row] for row in pivot.values]
    
    tabela = ax.table(cellText=textos_celulas, 
                      rowLabels=pivot.index, 
                      colLabels=pivot.columns, 
                      loc='center', 
                      cellLoc='center')
    tabela.scale(1, 1.8)
    tabela.set_fontsize(12)
    
    plt.title('Tabela Resumo: Tempo (ms) no Maior Tamanho Disponível (Variação: Random)', pad=20)
    plt.tight_layout()
    plt.savefig(os.path.join(PASTA_SAIDA, '07_tabela_resumo_maior_tamanho.png'), dpi=300)
    plt.close()

# =============================================================================
# FLUXO PRINCIPAL DE EXECUÇÃO
# =============================================================================
def main():
    criar_pasta_saida()
    
    try:
        df = pd.read_csv(ARQUIVO_DADOS)
    except FileNotFoundError:
        print(f"Erro: O arquivo '{ARQUIVO_DADOS}' não foi encontrado no diretório atual.")
        return
    
    # Limpa dados irrelevantes e garante tipagem numéricas
    df['tempo_ms'] = pd.to_numeric(df['tempo_ms'], errors='coerce')
    df = df.dropna(subset=['tempo_ms'])

    print("Iniciando geração dos gráficos...")

    # 1. Visão geral por operação (Inteiros)
    for op in OPERACOES:
        df_filtro = df[(df['operacao'] == op) & 
                       (df['variacao'] == 'random') & 
                       (df['estrutura'].isin(ESTRUTURAS_INT))]
        plot_comparativo_simples(
            df_filtro, 'estrutura', 
            f'1. Visão Geral (Chave Inteira) - {op.capitalize()}', 
            f'01_geral_inteiros_{op}.png', 
            usa_cores_globais=True
        )

    # 2. Efeito da ordem de inserção, por estrutura (Inteiros)
    for struct in ESTRUTURAS_INT:
        df_filtro = df[df['estrutura'] == struct]
        plot_subplots_operacoes(
            df_filtro, 'variacao', 
            f'2. Efeito da Ordem de Inserção - {struct}', 
            f'02_variacoes_{struct}.png'
        )

    # 3. Trie vs Patricia
    for op in OPERACOES:
        df_filtro = df[(df['operacao'] == op) & 
                       (df['variacao'] == 'random') & 
                       (df['estrutura'].isin(ESTRUTURAS_STR))]
        plot_comparativo_simples(
            df_filtro, 'estrutura', 
            f'3. TRIE vs PATRICIA - {op.capitalize()}', 
            f'03_trie_vs_patricia_{op}.png', 
            usa_cores_globais=True
        )

    # 4. Efeito da densidade de prefixo (Strings)
    for struct in ESTRUTURAS_STR:
        df_filtro = df[df['estrutura'] == struct]
        plot_subplots_operacoes(
            df_filtro, 'variacao', 
            f'4. Efeito da Densidade de Prefixo - {struct}', 
            f'04_variacoes_{struct}.png'
        )

    # 5. KD-Tree isolada
    df_kdtree = df[df['estrutura'] == 'KDTREE']
    if not df_kdtree.empty:
        plot_subplots_operacoes(
            df_kdtree, 'variacao', 
            '5. Variações Geométricas - KDTREE', 
            '05_variacoes_kdtree.png'
        )

    # 6. Visão geral entre TODAS as 7 estruturas
    for op in OPERACOES:
        df_filtro = df[(df['operacao'] == op) & (df['variacao'] == 'random')]
        plot_comparativo_simples(
            df_filtro, 'estrutura', 
            f'6. Comparação Global (Todas as Estruturas) - {op.capitalize()}', 
            f'06_global_todas_{op}.png', 
            usa_cores_globais=True
        )

    # 7. Tabela Resumo (Heatmap visual de texto)
    gerar_tabela_resumo(df)

    print(f"Sucesso! Todos os gráficos foram salvos na pasta '{PASTA_SAIDA}/'.")

if __name__ == "__main__":
    main()