#include <iostream>

#include "list.h"

int main()
{
    auto ints = list<int>();

    for (int i = 0; i < 64; i++)
    {
        ints.add(i);
    }
    ints.reverse();

    for (int i = 0; i < ints.count; i++)
    {
        printf("%d\n", ints[i] );
    }
}
