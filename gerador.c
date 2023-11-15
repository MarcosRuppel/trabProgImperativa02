#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Nodo* lerArquivoTexto(const char* nomeArquivo) {
    // Implementação da leitura do arquivo texto e construção da lista
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }

    Nodo* lista = NULL;
    Musica musica;

    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d\n",
                  &musica.chave, musica.titulo, musica.artista, musica.album, &musica.ano) == 5) {
        armazenarDadosHeap(&lista, musica);
    }

    fclose(arquivo);
    return lista;
}

void armazenarDadosHeap(Nodo** lista, Musica musica) {
    // Implementação da inserção ordenada na lista encadeada
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        perror("Erro ao alocar memória!");
        exit(EXIT_FAILURE);
    }

    novoNodo->musica = musica;
    novoNodo->prox = NULL;

    if(*lista == NULL || musica.chave < (*lista)->musica.chave) {
        // Inserção no início da lista ou em lista vazia
        novoNodo->prox = *lista;
        *lista = novoNodo;
    } else {
        // Inserção no meio ou no final da lista
        Nodo* atual = *lista;
        while (atual->prox != NULL && atual->prox->musica.chave < musica.chave) {
            atual = atual->prox;
        }
        novoNodo->prox = atual->prox;
        atual->prox = novoNodo;
    }
    // Mensagem de debug
    printf("Inserido chave: %d\n", musica.chave);
}

void gravarArquivoBinario(const char* nomeArquivo, Nodo* lista) {
    // Abre o arquivo binário para escrita
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita!");
        exit(EXIT_FAILURE);
    }

    // Percorre a lista e escreve cada elemento no arquivo
    Nodo* atual = lista;
    while (atual != NULL) {
        fwrite(&(atual->musica), sizeof(Musica), 1, arquivo);
        atual = atual->prox;
    }

    // Fecha o arquivo
    fclose(arquivo);
    printf("Arquivo %s gerado com sucesso.", nomeArquivo);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo_texto>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Leitura do arquivo de texto e construção da lista
    Nodo* lista = lerArquivoTexto(argv[1]);
    gravarArquivoBinario("saida.bin", lista);

    // Liberação de memória da lista, se necessário
    free(lista);

    return EXIT_SUCCESS;
}