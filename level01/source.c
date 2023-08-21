#include <stdio.h>

void run(void)

{
  fwrite("Good... Wait what?\n",1,0x13,stdout);
  system("/bin/sh");
  return;
}



int main(void)
{
    // Declare a character array to store user input, with space for 76 characters
    char input[2];
    // Read user input and store it in the 'input' array
    gets(input);  // WARNING: Using gets is unsafe and should be avoided in practice

    return 0;
}

