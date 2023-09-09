#include <stdio.h>
#include <stdlib.h>

void n(void)
{
    char local_buffer[520];

    printf("Enter input: ");
    fgets(local_buffer, sizeof(local_buffer), stdin);
    p(local_buffer);

    if (m == 0x1025544)
    {
        system("/bin/cat /home/user/level5/.pass");
    }

    return;
}

