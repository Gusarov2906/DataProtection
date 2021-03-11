#define _CRT_SECURE_NO_WARNINGS
#include "task3.h"
#include "task1.h"
#pragma once


void encode()
{
    char tmp;
    char keys[256];
    FILE* inputFile;
    FILE* keysFile;
    FILE* outputFile;

    int size = get_file_size("doc.doc");
    if (!(inputFile = fopen("doc.doc", "rb"))) {
        std::cout << "file does not exist.....";
        return;
    }
    if (!(keysFile = fopen("key.txt", "rb"))) {
        std::cout << "file does not exist.....";
        return;
    }
    if (!(outputFile = fopen("doc1.doc", "wb"))) {
        std::cout << "file does not exist.....";
        return;
    }
    for (int i = 0; i < 256; i++)
    {
        keys[i] = fgetc(keysFile);
        std::cout << keys[i];
    }
    for (int i = 0; i < size; i++)
    {
        tmp = fgetc(inputFile);
        std::cout << keys[tmp];
        fputc(keys[(unsigned char)tmp], outputFile);
    }
    std::cout << std::endl;
    fclose(inputFile);
    fclose(keysFile);
    fclose(outputFile);
}

int get_index(char keys[256], char val)
{
    for (int i = 0; i < 256; i++)
    {
        if (keys[i] == val)
            return i;
    }
}
void decode()
{
    char tmp;
    char keys[256];
    int index;
    FILE* inputFile;
    FILE* keysFile;
    FILE* outputFile;

    int size = get_file_size("doc1.doc");

    if (!(inputFile = fopen("doc1.doc", "rb"))) {
        std::cout << "file does not exist.....";
        return;
    }
    if (!(keysFile = fopen("key.txt", "rb"))) {
        std::cout << "file does not exist.....";
        return;
    }
    if (!(outputFile = fopen("doc2.doc", "wb"))) {
        std::cout << "file does not exist.....";
        return;
    }

    for (int i = 0; i < 256; i++)
    {
        keys[i] = fgetc(keysFile);
        //std::cout << keys[i];
    }

    for (int i = 0; i < size; i++)
    {
        tmp = fgetc(inputFile);
        index = get_index(keys, tmp);
        //td::cout << tmp << " " << index << " _ ";
        fputc(index, outputFile);
    }

    fclose(inputFile);
    fclose(keysFile);
    fclose(outputFile);
}

void generate_key()
{
    FILE* output;
    if (!(output = fopen("key.txt", "wb"))) {
        std::cout << "file does not exist.....";
        return;
    }
    char keys[256];
    char tmp;
    int m, n;
    uint8_t val = 0;
    for (int i = 0; i < 256; i++)
    {
        keys[i] = val;
        val++;
    }
    for (int i = 0; i < 256; i++)
    {
        m = rand() % 255;
        n = rand() % 255;
        tmp = keys[n];
        keys[n] = keys[m];
        keys[m] = tmp;
    }
    for (int i = 0; i < 256; i++)
    {
        fputc(keys[i], output);
    }
    fclose(output);
}

void task3_run()
{
    generate_key();
    encode();
    decode();
}