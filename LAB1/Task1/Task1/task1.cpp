#include "task1.h"
#pragma once


int get_file_size(std::string file_name)
{
    std::ifstream file(file_name);
    int size = 0;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    return size;
}
void task1_run(std::string file_name)
{
    std::cout << "\nTASK1: " << std::endl;
    int size = get_file_size(file_name);
    std::cout << "Your file size: " << size << " byte" << std::endl;
}