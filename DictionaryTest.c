//DictionaryTest.c
//Edward Lee
//Tests the Dictionary.c file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

void BugFound(){
   printf("Bug found. Exiting now.\n");
}
void success(){
   printf("Test successfully passes.\n");
   printf("------------------------------------------------------\n");
}

int main(){
   Dictionary A = newDictionary();
   Dictionary B = newDictionary();
   printf("Beginning the Dictionary Test.\n");
   printf("******************************************************\n");
   printf("Testing isEmpty and size on an empty Dictionary.\n");
   printf("%i\n",isEmpty(A));
   printf("%i\n",size(A));
   if(!(isEmpty(A)==1)||(size(A)>0)){
      BugFound();
      exit(EXIT_FAILURE);
   }
   success();
   printf("Testing isEmpty and size on a populated Dictionary.\n");
   insert(A, "Alpha:", "Anna.");
   insert(A, "Bravo:", "Boris.");
   insert(A, "Charlie:", "Center.");
   printf("%i\n",isEmpty(A));
   printf("%i\n",size(A));
   if(!(isEmpty(A)==0)||(!(size(A)==3))){
      BugFound();
      exit(EXIT_FAILURE);
   }
   success();
   printf("Testing lookup.\n");
   printf("%s\n",lookup(A, "Bravo:"));
   //printf("%s\n",lookup(A, "Delta"));
   if((!(strcmp(lookup(A, "Bravo:"), "Boris.")==0))||(lookup(A, "Delta")!=NULL)){
      BugFound();
      exit(EXIT_FAILURE);
   }
   success();
   printf("Testing lookup on a null Dictionary.\n");
   //printf("%s\n",lookup(B, "Echo"));
   if(lookup(B,"Echo")!=NULL){
      BugFound();
      exit(EXIT_FAILURE);
   }
   success();
   printf("Testing insert, delete, and makeEmpty.\n");
   insert(A, "Foxtrot:", "Fyodor.");
   insert(A, "Hotel:", "Chariton.");
   delete(A, "Charlie:");
   printDictionary(stdout, A);
   makeEmpty(A);
   printDictionary(stdout, A);
   printf("%i\n",size(A));
   if(!(size(A)==0)){
      BugFound();
      exit(EXIT_FAILURE);
   }
   freeDictionary(&A);
   freeDictionary(&B);
   printf("******************************************************\n");
   printf("All tests passed. Have a nice day.\n");
}
