#include <stdio.h>

int main()
{
  int base_node;
  FILE *file;
  char fname[50];
  scanf("%s",fname);
  file=fopen(fname,"wb+");
  while(1)
  {
    int breaker;
    printf("Add in base - 1\n");
    printf("Stop adding - 0\n");
    scanf("%d",&breaker);
    if(breaker == 0)
    {
      break;
    }
    else
    {
      printf("Enter data: ");
      scanf("%d",&base_node);
      fwrite(&base_node,sizeof(int),1,file);
    }
  }
  fclose(file);
  return 0;
}
