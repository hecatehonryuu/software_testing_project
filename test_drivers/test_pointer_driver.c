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
   cell* list;
   int x;
   FILE* fp; 

   if (argc < 2) {
      printf("Supply the input file\n");
      exit(-1);
   }   

   fp = fopen(argv[1], "r");

   if(!fp) 
      exit(-1);

   /* allocate a cell */
   list = (cell *)malloc(sizeof(cell)); 
   fscanf(fp, "%d%x%d", &(list->v), &(list->next), &x);

   fclose(fp);

   printf("inputs are list->v = %d, list->next = 0x%x, x = %d\n", list->v, list->next, x); 
   
   test_unit(list, x); 
}
