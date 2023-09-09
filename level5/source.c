#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>




void o(void)
{
    // Run the system shell
    system("/bin/sh");
    
    // Exit the program with status code 1
    _exit(1);
}


void n(void)
{
    char input_buffer[520];

    printf("Enter input: ");
    fgets(input_buffer, sizeof(input_buffer), stdin);
    printf("%s", input_buffer);

    // Exit the program with status code 1
    exit(1);
}


int main(void)

{
  n();
  return 0;
}


