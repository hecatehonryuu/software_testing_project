#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int double_x(int x) { return 2*x; }

void good() {

}

void test_unit(int x, int y) {
   int z = double_x(x);
   /* z = 4, y = 4 */
   if (z == y) {
     if (x != y+10) {
       good();
     }   
     else {
       assert(0 && "fatal");
     }   
  }
}

int main(int argc, char* argv[]) {

 int x, y;
 
 /* test driver start */
 FILE* fp = NULL;

 if (argc < 2) {
   printf("%d\n", argc);
   exit(-1);
 }

 fp = fopen(argv[1], "r");
 
 if (!fp) {
    exit(-1);
 }
 
 fscanf(fp, "%d%d", &x, &y);
 fclose(fp);
 
 printf("x = %d, y = %d\n", x, y); 

 /* test driver end */

 test_unit(x, y);
	}
