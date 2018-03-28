/* Dictionary.c
 * Edward Lee
 * Implementation of the Dictionary associative array using a hash function
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

//tableSize: globally defines the number of chaining lists to be used
const int tableSize = 101;

//hash: prototype for the hash function
int hash(char* key);

//Constructors and definitions for the Node object
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;
typedef NodeObj* Node;
Node newNode(char* k, char* v){
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k,
   N->value = v;
   N->next = NULL;
   return N;
}
//freeNode: frees the memory attached to a Node
void freeNode(Node* N){
   if(N!=NULL && *N!=NULL){
      free(*N);
      *N = NULL;
   }
}
//deleteAll: prototype for the deleteAll function
void deleteAll(Node N);

//Constructors and definitions for the Line object
typedef struct LineObj{
   Node front;
} LineObj;
typedef LineObj* Line;
Line newLine(void){
   Line L = malloc(sizeof(LineObj));
   assert(L!=NULL);
   L->front = NULL;
   return L;
}
//depopulate: prototype for the "empty line" function
void depopulate(Line L);
//freeLine: Frees the memory attached to a Line
void freeLine(Line* L){
   if(L!=NULL && *L!=NULL){
      depopulate(*L);
      free(*L);
      *L = NULL;
   }
}

//Constructors and definitions for the Dictionary object
typedef struct DictionaryObj{
   int numEntries;
   Line *table;
} DictionaryObj;
Dictionary newDictionary(void){
   int i = 0;
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->table = calloc(tableSize,sizeof(LineObj));
   for(i=0; i<tableSize; i++){
      D->table[i] = newLine();
   }
   D->numEntries = 0;
   return D;
}
typedef struct DictionaryObj* Dictionary;
//freeDictionary: frees the memory attached to a Dictionary
void freeDictionary(Dictionary* pD){
   int i = 0;
   Line L;
   if(pD!=NULL){
      for(i=0; i<tableSize; i++){
         L = (*pD)->table[i];
         freeLine(&L);
      }
      free((*pD)->table);
      free(*pD);
      *pD = NULL;
   }
}
//isEmpty: returns 1 (true) if the Dictionary is empty, 0 if it isn't
int isEmpty(Dictionary D){
   if(D==NULL){
      fprintf(stderr, "dictionary is null\n");
      exit(EXIT_FAILURE);
   }
   return(D->numEntries==0);
}
//size: returns the int of the dictionary's size
int size(Dictionary D){
   if(D==NULL){
      fprintf(stderr, "cannot return size of a null dictionary\n");
      exit(EXIT_FAILURE);
   }
   return(D->numEntries);
}
//findKey: returns a reference to a node with the specified key
Node findKey(Node N, char* k){
   if(N==NULL || strcmp(N->key, k)==0){
      return N;
   }else{
      return findKey(N->next, k);
   }
   return NULL;
}
//lookup: returns the Value of the specified key, if it exists
char* lookup(Dictionary D, char* k){
   Line L = D->table[hash(k)];
   Node N = L->front;
   if(D==NULL){
      fprintf(stderr, "dictionary is null, ya donk\n");
      exit(EXIT_FAILURE);
   }
   N = findKey(N, k);
   return(N==NULL?NULL : N->value);
}
//insert: puts in a specified key/value pair
void insert(Dictionary D, char* k, char* v){
   Line L = D->table[hash(k)];
   Node N = findKey(L->front, k);
   Node B;
   if(D==NULL){
      fprintf(stderr, "can't insert into null dictionary, ya donk\n");
      exit(EXIT_FAILURE);
   }
   if(N!=NULL){
      fprintf(stderr, "can't insert existing key, ya donk\n");
      exit(EXIT_FAILURE);
   }
   if(D->numEntries==0){
      L->front = newNode(k, v);
   }else{
      B = newNode(k, v);
      B->next = L->front;
      L->front = B;
   }
   D->numEntries++;
}
//find: returns a reference to the node of the specified index in the line
Node find(int i, Line L){
   Node N = L->front;
   int j = 0;
   for(j=1; j<i; j++){
      N = N->next;
   }
   return N;
}
//delete: deletes the value with the specified key
void delete(Dictionary D, char* k){
   Node B, C, E;
   Line L = D->table[hash(k)];
   int index = 2;
   if(D==NULL){
      fprintf(stderr, "cannot delete null dictionary\n");
      exit(EXIT_FAILURE);
   }
   B = L->front;
   while(B!=NULL){
      if(strcmp(B->key, k)==0){
         break;
      }
      B = B->next;
      index++;
   }
   if(B==NULL){
      fprintf(stderr, "%s doesn't exist, ya donk\n", k);
      exit(EXIT_FAILURE);
   }
   if(index==1){
      C = L->front;
      L->front = L->front->next;
      freeNode(&C);
   }else{
      C = find(index-1, L);
      E = C->next;
      C->next = E->next;
      freeNode(&E);
   }
   D->numEntries--;
}
//depopulate: defines the depopulate function, used to empty a Line
void depopulate(Line N){
   deleteAll(N->front);
   N->front = NULL;
}
//deleteAll: helper function used to free said line
void deleteAll(Node N){
   if(N!=NULL){
      deleteAll(N->next);
      freeNode(&N);
   }
   freeNode(&N);
}
//makeEmpty: depopulates a specified Dictionary
void makeEmpty(Dictionary D){
   int i = 0;
   for(i=0; i<tableSize; i++){
      depopulate(D->table[i]);
   }
   D->numEntries=0;
}
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
   unsigned int result = 0xBAE86554;
   while (*input) {
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}
//printDictionary: prints out the Dictionary in the specified output stream
void printDictionary(FILE* out, Dictionary D){
   int i = 0;
   if(D==NULL){
      fprintf(out, "dictionary's null, ya donk\n");
      exit(EXIT_FAILURE);
   }
   for(i=0; i<tableSize; i++){
      Line L = D->table[i];
      Node N = L->front;
      while(N!=NULL){
         fprintf(out, "%s %s\n", N->key, N->value);
         N = N->next;
      }
   }
}
