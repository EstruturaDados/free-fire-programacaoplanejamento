#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Enum para critérios de ordenação
typedef enum {
    NOME = 1,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 (baixa) a 5 (alta)
} Item;

// Variáveis globais
Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// Função para limpar a tela (simulada)
void limparTela() {
    for (int i = 0; i < 10; i++) printf("\n");
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n📦 Mochila de Fuga - Free Fire\n");
    printf("Itens cadastrados: %d\n", numItens);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "Sim" : "Não");
    printf("\n--- MENU ---\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Buscar item por nome (binária)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// Função para inserir um novo item
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("⚠️ Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("\n🔹 Cadastro de item:\n");
    printf("Nome: ");
    scanf("%s", novo.nome);
    printf("Tipo (arma, munição, cura, ferramenta): ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;
    printf("✅ Item adicionado!\n");
}

// Função para remover item pelo nome
void removerItem() {
    char nome[30];
    printf("\n❌ Remoção de item\nNome: ");
    scanf("%s", nome);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("✅ Item removido!\n");
            return;
        }
    }
    printf("⚠️ Item não encontrado.\n");
}

// Função para listar todos os itens
void listarItens() {
    printf("\n📋 Itens na mochila:\n");
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("| Nome       | Tipo        | Qtde | Prioridade |\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("| %-10s | %-10s | %-4d | %-10d |\n",
               mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("--------------------------------------------------\n");
}

// Função de ordenação por inserção
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            bool condicao = false;
            comparacoes++;

            if (criterio == NOME)
                condicao = strcmp(chave.nome, mochila[j].nome) < 0;
            else if (criterio == TIPO)
                condicao = strcmp(chave.tipo, mochila[j].tipo) < 0;
            else if (criterio == PRIORIDADE)
                condicao = chave.prioridade > mochila[j].prioridade;

            if (condicao) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }

    if (criterio == NOME) ordenadaPorNome = true;
    else ordenadaPorNome = false;

    printf("✅ Ordenação concluída com %d comparações.\n", comparacoes);
}

// Menu de ordenação
void menuDeOrdenacao() {
    int escolha;
    printf("\n📊 Escolha o critério de ordenação:\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha <= 3) {
        insertionSort((CriterioOrdenacao)escolha);
        listarItens();
    } else {
        printf("⚠️ Critério inválido.\n");
    }
}

// Busca binária por nome
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("⚠️ A mochila precisa estar ordenada por nome para busca binária.\n");
        return;
    }

    char nome[30];
    printf("\n🔍 Buscar item por nome: ");
    scanf("%s", nome);

    int inicio = 0, fim = numItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) {
            printf("✅ Item encontrado:\n");
            printf("- Nome: %s\n- Tipo: %s\n- Quantidade: %d\n- Prioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("❌ Item não encontrado.\n");
}

// Função principal
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("👋 Saindo da mochila...\n"); break;
            default: printf("⚠️ Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}