#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct cell {
   int v;
   struct cell* next;
}cell;

void good() {

}

void test_unit(cell* p, int x) {
   if (x > 0)
     if (p != NULL)
       if (2*x + 1 == p->v)
         if (p->next == p)
            assert(0 && "fatal");
   good();
}


int main(int argc, char* argv[]) {
   cell* list = NULL;
   int x;

   FILE* fp; 
   int length = 0;
   int i = 0;

   if (argc < 2) {
      printf("Supply the input file\n");
      exit(-1);
   }   
   

   fp = fopen(argv[1], "r");

   if(!fp) 
      exit(-1);

   //read the length of the list
   fscanf(fp, "%d\n", &length);
   printf("Length of the list is %d\n", length);
			   while (i < length) {
      /* allocate a cell */
      list = (cell *)malloc(sizeof(cell));
      fscanf(fp, "%d%x\n", &(list->v), &(list->next));
      printf("inputs are list->v = %d, list->next = 0x%x\n", list->v, list->next);
      i++;
   }
   fscanf(fp, "%d", &x);
   printf("Value of x is %d\n", x);

   fclose(fp);

   test_unit(list, x);
}
