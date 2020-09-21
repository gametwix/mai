#include <stdio.h>

int main()
{
  int a;
  FILE *file;
  char fname[50];
  scanf("%s",fname);
  file=fopen(fname,"rb");
  //while(feof(file))
  //{
    fread(&a,sizeof(int),1,file);
    printf("%d\n",a);
    printf("---------------------\n");
//  }
  return 0;
}
