#include "task2.h"
#include "task1.h"
#pragma once


void task2_run(std::string file_name)
{
    int size = get_file_size(file_name);
    int frequency[256];

    std::cout << "\nTASK2: " << std::endl;

    for (int i = 0; i < 256; i++)
        frequency[i] = 0;
    char tmp;

    std::ifstream file(file_name, std::ios::binary);
    while (!file.eof())
    {
        file.read(&tmp, 1);
        frequency[uint8_t(tmp)]++;
    }
    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] != 0)
        {
            std::cout << std::hex << char(i) << ": " << (double)frequency[i] / size << std::endl;
        }
    }
}