#include <iostream>

#include "findSynonyms.hpp"

int main()
{
    FindSynonyms find("f1.txt", "f2.txt", "f3.txt");

    find.Print("f4.txt");

    return 0;
}