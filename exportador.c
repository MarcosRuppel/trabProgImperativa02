//
// Created by Marcos P Ruppel on 10/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void exportarArquivoTexto(const char* nomeArquivoBinario, const char* nomeArquivoTexto) {
    // Abre o arquivo binário para leitura
    FILE* arquivoBinario = fopen(nomeArquivoBinario, "rb");
    if (arquivoBinario == NULL) {
        perror("Erro ao abrir o arquivo binário");
        exit(EXIT_FAILURE);
    }

    // Cria o arquivo de texto para escrita
    FILE* arquivoTexto = fopen(nomeArquivoTexto, "w");
    if (arquivoTexto == NULL) {
        perror("Erro ao abrir o arquivo de texto para escrita!");
        fclose(arquivoBinario);
        exit(EXIT_FAILURE);
    }

    // Lê cada registro do arquivo binário e escreve no arquivo de texto
    Musica musica;
    while (fread(&musica, sizeof(Musica), 1, arquivoBinario) == 1) {
        fprintf(arquivoTexto, "%03d;%s;%s;%s;%d\n",
                musica.chave, musica.titulo, musica.artista, musica.album, musica.ano);
    }

    // Fecha os arquivos
    fclose(arquivoBinario);
    fclose(arquivoTexto);

    printf("Arquivo %s exportado para %s com sucesso.\n", nomeArquivoBinario, nomeArquivoTexto);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo_binario> <nome_do_arquivo_texto>\n", argv[0]);
        return EXIT_FAILURE;
    }

    exportarArquivoTexto(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
