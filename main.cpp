#include <iostream>

#include "list.h"

int main()
{
    auto ints = list<int>();

    for (int i = 0; i < 5; i++)
    {
        ints.add(i+10);
    }

    for (int i = 0; i < ints.count; i++)
    {
        printf("%d\n", ints[i] );
    }
}
