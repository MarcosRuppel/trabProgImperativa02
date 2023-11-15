//
// Created by Marcos P Ruppel on 14/11/2023.
//

#ifndef TRABPROGIMPERATIVA02_LISTA_H
#define TRABPROGIMPERATIVA02_LISTA_H

#define MAX_STRING_LENGTH 50

typedef struct {
    int chave;
    char titulo[MAX_STRING_LENGTH];
    char artista[MAX_STRING_LENGTH];
    char album[MAX_STRING_LENGTH];
    int ano;
} Musica;

typedef struct Nodo {
    Musica musica;
    struct Nodo* prox;
} Nodo;

Nodo* lerArquivoTexto(const char* nomeArquivo);
Nodo* lerArquivoBinario(const char* nomeArquivo);
void realizarOperacoes(Nodo** lista);
void armazenarDadosHeap(Nodo** lista, Musica musica);
void gravarArquivoBinario(const char* nomeArquivo, Nodo* lista);
void exportarArquivoTexto(const char* nomeArquivoBinario, const char* nomeArquivoTexto);

#endif //TRABPROGIMPERATIVA02_LISTA_H
