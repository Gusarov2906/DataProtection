#pragma once
#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"

int main()
{
    setlocale(0, "RUS");
    srand(time(NULL));
    task1_run("doc.doc");
    task2_run("doc.doc");
    task3_run();
    system("pause");
    return 0;
}