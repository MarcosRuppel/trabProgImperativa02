//
// Created by Marcos P Ruppel on 10/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void liberarMemoria(Nodo* lista) {
    while (lista != NULL) {
        Nodo* proximo = lista->prox;
        free(lista);
        lista = proximo;
    }
}

void exibirMensagem(const char* mensagem) {
    printf("%s\n", mensagem);
}

// Função para aguardar o usuário pressionar Enter
void aguardarEnter() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n') {
        // Limpar o buffer de entrada
    }
    getchar(); // Aguardar o Enter
}

// Função para inserir uma nova música na lista
void inserirDados(Nodo** lista, Musica novoDado) {
    // Verifica se a chave já existe na lista
    Nodo* atual = *lista;
    while (atual != NULL) {
        if (atual->musica.chave == novoDado.chave) {
            // A chave já existe, incrementar as chaves subsequentes
            while (atual != NULL) {
                atual->musica.chave++;
                atual = atual->prox;
            }
            break;
        }
        atual = atual->prox;
    }

    // Cria um novo nó
    Nodo* novoNodo = (Nodo*)calloc(1, sizeof(Nodo));
    if (novoNodo == NULL) {
        fprintf(stderr,"Erro ao alocar memoria para novo nodo!\n");
        exit(EXIT_FAILURE);
    }

    // Preenche o novo nó com os dados fornecidos
    novoNodo->musica = novoDado;
    novoNodo->prox = NULL;

    // Caso a lista esteja vazia ou a nova chave seja menor que a primeira, insere no início
    if (*lista == NULL || novoDado.chave < (*lista)->musica.chave) {
        novoNodo->prox = *lista;
        *lista = novoNodo;
        exibirMensagem("Dados carregados com sucesso.");
        return;
    }

    // Encontra o ponto de inserção na lista ordenada
    atual = *lista;
    while (atual->prox != NULL && novoDado.chave > atual->prox->musica.chave) {
        atual = atual->prox;
    }

    // Insere o novo nó na posição correta
    novoNodo->prox = atual->prox;
    atual->prox = novoNodo;

    exibirMensagem("Dados carregados com sucesso.");
}

// Função para remover uma música da lista com base na chave
void removerDados(Nodo** lista, int chaveRemover) {
    Nodo* temp = *lista;
    Nodo* anterior = NULL;

    // Verifica se o nó a ser removido é o primeiro
    if (temp != NULL && temp->musica.chave == chaveRemover) {
        *lista = temp->prox;
        free(temp);
        exibirMensagem("Dados removidos com sucesso.");
        return;
    }

    // Busca o nó a ser removido
    while (temp != NULL && temp->musica.chave != chaveRemover) {
        anterior = temp;
        temp = temp->prox;
    }

    // Se a chave não estiver presente na lista
    if (temp == NULL) {
        exibirMensagem("Chave nao encontrada. Nenhum dado removido.");
        return;
    }

    // Remove o nó encontrado
    anterior->prox = temp->prox;
    free(temp);
    exibirMensagem("Dados removidos com sucesso.");
}

// Função recursiva para exibir dados de um elemento com base na chave
void exibirDadosRecursivo(Nodo* nodo, int chaveBuscar) {
    // Caso base: chegou ao final da lista sem encontrar a chave
    if (nodo == NULL) {
        exibirMensagem("Chave nao encontrada. Nenhum dado exibido.");
        aguardarEnter();
        return;
    }

    // Caso a chave seja encontrada, exibe os dados
    if (nodo->musica.chave == chaveBuscar) {
        printf("Dados encontrados:\n");
        printf("Chave: %d\n", nodo->musica.chave);
        printf("Titulo: %s\n", nodo->musica.titulo);
        printf("Artista: %s\n", nodo->musica.artista);
        printf("Album: %s\n", nodo->musica.album);
        printf("Ano: %d\n", nodo->musica.ano);
        aguardarEnter();
        return;
    }

    // Chama recursivamente a função para o próximo nó na lista
    exibirDadosRecursivo(nodo->prox, chaveBuscar);
}

// Função para chamar a versão recursiva
void exibirDados(Nodo* lista, int chaveBuscar) {
    exibirDadosRecursivo(lista, chaveBuscar);
}

void gravarArquivoBinario(const char* nomeArquivo, Nodo* lista) {
    // Abre o arquivo binário para escrita
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        fprintf(stderr,"Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    // Percorre a lista e escreve cada elemento no arquivo
    Nodo* atual = lista;
    while (atual != NULL) {
        fwrite(&(atual->musica), sizeof(Musica), 1, arquivo);
        atual = atual->prox;
    }

    // Fecha o arquivo
    fclose(arquivo);
    printf("Arquivo %s gerado com sucesso.\n", nomeArquivo);
}

void realizarOperacoes(Nodo** lista) {
    // Implementação da interação contínua com o usuário e operações no Editor
    int opcao;
    do {
        printf("\nOpcoes:\n");
        printf("1. Inserir musica no catalogo\n");
        printf("2. Remover musica do catalogo\n");
        printf("3. Buscar musica no catalogo\n");
        printf("4. Salvar no arquivo binario\n");
        printf("0. Encerrar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Musica novoDado;
                printf("Digite a chave do novo dado: ");
                scanf("%d", &novoDado.chave);
                getchar();
                printf("Digite o titulo: ");
                fgets(novoDado.titulo, sizeof(novoDado.titulo), stdin);
                novoDado.titulo[strcspn(novoDado.titulo, "\n")] = '\0';  // Remove o caractere de nova linha
                printf("Digite o artista: ");
                fgets(novoDado.artista, sizeof(novoDado.artista), stdin);
                novoDado.artista[strcspn(novoDado.artista, "\n")] = '\0';  // Remove o caractere de nova linha
                printf("Digite o album: ");
                fgets(novoDado.album, sizeof(novoDado.album), stdin);
                novoDado.album[strcspn(novoDado.album, "\n")] = '\0';  // Remove o caractere de nova linha
                printf("Digite o ano: ");
                scanf("%d", &novoDado.ano);
                inserirDados(lista, novoDado);
                break;
            }
            case 2: {
                int chaveRemover;
                printf("\nDigite a chave do dado a ser removido: ");
                scanf("%d", &chaveRemover);
                removerDados(lista, chaveRemover);
                break;
            }
            case 3: {
                int chaveBuscar;
                printf("\nDigite a chave do dado a ser buscado: ");
                scanf("%d", &chaveBuscar);
                exibirDados(*lista, chaveBuscar);
                break;
            }
            case 4: {
                char nomeArquivoNovo[100];
                printf("\nDigite o nome do arquivo binario: ");
                scanf("%s", nomeArquivoNovo);
                gravarArquivoBinario(nomeArquivoNovo, *lista);
                break;
            }
            case 0:
                printf("\nEncerrando o programa.");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.");
        }
    } while (opcao != 0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_binario>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *nomeArquivo = argv[1];

    // Abre o arquivo binário para leitura
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo) {
        fprintf(stderr,"Erro ao abrir o arquivo binário para leitura!\n");
        return EXIT_FAILURE;
    }

    // Lê os dados do arquivo e os armazena na lista encadeada
    Nodo *lista = NULL;
    Musica tempMusica;

    while (fread(&tempMusica, sizeof(Musica), 1, arquivo) == 1) {
        inserirDados(&lista, tempMusica);
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    // Executa as operações no Editor
    realizarOperacoes(&lista);

    // Libera a memória alocada para a lista antes de encerrar o programa
    liberarMemoria(lista);

    return EXIT_SUCCESS;
}
