#include <stdio.h>

int main()
{
    const char martini[5] = {0xF0, 0x9F, 0x8D, 0xB8, '\0'};
    printf("Let's go drink some %s\n\n", martini);

    char *question = "\xE2\x9D\x93";
    char* bee = "\U0001F41D";
    printf("To %s or not to %s, that is the %s", bee, bee, question);
    return 0;
}
