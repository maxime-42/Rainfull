#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[68];



void	m(void)
{
	printf("%s - %d\n", c, (int)time(0));
}
int main(int argc, char *argv[]) {
  // Allocate and initialize memory for two integer pointers
  int *ptr1 = (int *)malloc(2 * sizeof(int));
  ptr1[0] = 1;
  ptr1[1] = 2;

  // Allocate memory for two character arrays and copy strings from arguments
  char *str1 = (char *)malloc(strlen(argv[1]) + 1);
  char *str2 = (char *)malloc(strlen(argv[2]) + 1);
  strcpy(str1, argv[1]);
  strcpy(str2, argv[2]);

  // Open a file for reading
  FILE *file = fopen("/home/user/level8/.pass", "r");

  if (file != NULL) {

    // Read a line from the file
    fgets(buffer, sizeof(buffer), file);

    // Print a separator
    puts("~~");

    // Clean up and free allocated memory
    fclose(file);
  }

  return 0;
}

