#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   char** arr;
   char* str;
   int num = 0;
   int i = 0,j = 0;

   printf("%s ", *argv);
   scanf("%d",&argc);	//receive name's number
   getchar();
   arr = (char**)malloc(sizeof(char*)*argc);	//2D dynamic allocation
   str = (char*)malloc(sizeof(char)*argc * 30);	//allocate str to store
   for (i = 0; i < argc; i++)
      arr[i] = (char*)malloc(sizeof(char) * 30);

   printf("enter %d names : \n", argc);
   gets(str);
   printf("the names you entered:\n");
   for (i = 0; i < argc;) {	//to store input str to arr
      if (str[j] == ' ') {
         strncpy(arr[i], str, j);	//copy by name's length
         arr[i][j] = '\0';
         printf("%s\n", arr[i]);
         i++;
         str = str + j + 1;
         j = 0;
      }
      else {
         j++;
      }
      if (i == argc - 1) {	//input last name
         strcpy(arr[i], str);
         printf("%s\n", arr[i]);
         break;
      }
   }

	for(i=0;i<argc;i++)
	free(arr[i]);
	free(arr); // releasd dynamic allocation
  
return 0;
}

