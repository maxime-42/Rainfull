#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void)
{
    void *unaff_retaddr;
    char local_50[76];

    fflush(stdout);
    gets(local_50);

    // Check if the high nibble of unaff_retaddr is 0xb
    if (((uintptr_t)unaff_retaddr & 0xF0000000) == 0xB0000000)
    {
        printf("(%p)\n", unaff_retaddr);
        // Exit the program with a non-zero status
        _exit(1);
    }

    // Print the input string
    puts(local_50);

    // Duplicate and ignore the duplicated result
    strdup(local_50);

    return;
}

