#include <cstdio>
#include <cstring>

void foo(char* str)
{
    char c[4];
    strcpy(c, str);
}

int main(int argc, char** argv)
{
    foo(argv[1]);
    printf("done…");

    return 0;
}
