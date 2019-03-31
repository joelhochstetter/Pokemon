/* Joel Hochstetter - z5115275
Tuesday 2pm Tute - William Archninal
20/10/2016
Contains required Pkmn.c files including extra helper functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pkmn.h"

const char * const TYPES[] = {
   "Bug",
   "Dark",
   "Dragon",
   "Electric",
   "Fairy",
   "Fighting",
   "Fire",
   "Flying",
   "Ghost",
   "Grass",
   "Ground",
   "Ice",
   "Normal",
   "Poison",
   "Psychic",
   "Rock",
   "Steel",
   "Water"};

#define TRUE 1
#define FALSE 0

struct _list {
   Pkmn head;
   Pkmn tail;
   Pkmn curPkmn;
   int size;
   int numFound;
};

struct _pkmn {
   int id;
   char name[PKMN_NAME_LENGTH + 1];
   double height;
   double weight;
   int type1;
   int type2;
   int found;
   Pkmn next;
   Pkmn prev;
   int evolvesToId;
};

static void printAsterisks(int length);
static void printName(Pkmn cur);
static Pkmn getPkmnByID(PkmnList list, int searchid);
static int isAlreadyInList(PkmnList list, Pkmn pkmn);
static int containsSubstring(char *string, char *substring);
static Pkmn duplicateOf(Pkmn p);
static void addCopyIdOrder(PkmnList sublist, Pkmn cur);
static void appendPkmnBetweenElements(PkmnList sublist, Pkmn toInsert, Pkmn prev, Pkmn next);

//helper functions
static void printAsterisks(int length) { 
//prints instead of name for not found pokemon
   int i;
   for (i = 0; i < length; i++) {
      printf("*");
   }
}

static void printName(Pkmn cur) {
   if (cur->found == TRUE) {
      printf("%s", cur->name);
   } else {
      printAsterisks(strlen(cur->name)); 
   }
}

static Pkmn getPkmnByID(PkmnList list, int searchid) {
//For a given id. Returns pointer to pokemon it exists and else NULL 
   Pkmn cur = list->head;
   Pkmn pkmn = NULL;
   while (cur != NULL && pkmn == NULL) {
      if (cur->id == searchid) {
         pkmn = cur;
      } 
      cur = cur->next; 
   }
   return pkmn;
}

static int isAlreadyInList(PkmnList list, Pkmn pkmn) {
   int result = FALSE;
   if (getPkmnByID(list, pkmn->id) != NULL) {
      result = TRUE;
   }
   return result;
}

static int containsSubstring(char *string, char *substring) {
//Non-case sensitive test if substring is in string
   int result = FALSE;
   int substringPos = 0; //stores letter from substring its up to
   int i = 0; //stores letter from string that loop is up too
   while (string[i] != '\0' && result == FALSE) {
      if (tolower(string[i]) == tolower(substring[substringPos])) {
         substringPos++;
         if (substring[substringPos] == '\0') {
            result = TRUE;
         }
      } else {
         substringPos = 0; //resets to start of word
      }
      i++;
   }
   return result;
}

static Pkmn duplicateOf(Pkmn p) {
//creates exact duplicate except for pointers to next and previous
   Pkmn dup = createPkmn(p->id, p->name, p->height, p->weight, 
   p->type1, p->type2);
   if (p->found == TRUE) {
      dup->found = TRUE;
   }
   dup->evolvesToId = p->evolvesToId;
   return dup;  
}

static void addCopyIdOrder(PkmnList sublist, Pkmn cur) {
   Pkmn curCopy = duplicateOf(cur); //so we add copy not original Pkmn
   Pkmn subCur = sublist->head;
   Pkmn subPrev = NULL;
   int foundPos = FALSE;
   if (sublist->head == NULL) {
      sublist->head = curCopy;
   } else {
      while(foundPos == FALSE && subCur != NULL) {
         if (subCur->id > curCopy->id) {
            foundPos = TRUE;
         } else {
            subPrev = subCur;
            subCur = subCur->next;
         }   
      }
   }
   appendPkmnBetweenElements(sublist, curCopy, subPrev, subCur);
   sublist->size ++;
}

static void appendPkmnBetweenElements(PkmnList sublist, Pkmn toInsert, Pkmn prev, Pkmn next) {
   if (next != NULL) { //if it is not to be added at end of list
      toInsert->next = next;
      next->prev = toInsert;
   } else { //if at end of list
      sublist->tail = toInsert;
      toInsert->next = NULL;
   }
   if (prev != NULL) { //if it is not to be added at start of list
      prev->next = toInsert;
      toInsert->prev = prev;
   } else { //if at start of list
      sublist->head = toInsert;
      toInsert->prev = NULL;
   }
}

//part 1
const char * getTypeString(int i) {
   return TYPES[i];
}

Pkmn createPkmn(int id, char * name, double height, double weight, 
int type1, int type2) { //split to adhere to 72 char limit
   Pkmn pkmn = malloc(sizeof(struct _pkmn));
   if (pkmn == NULL) {
      printf("Out of memory\n");
      exit(EXIT_FAILURE);
   }
   pkmn->found = FALSE;
   pkmn->id = id;
   strcpy(pkmn->name, name);
   pkmn->height = height;
   pkmn->weight = weight;
   if (type1 > type2) { //places types in alphabetical order
      int temp;
      temp = type1;
      type1 = type2;
      type2 = temp;
   }
   if (type1 == -1) { //swaps type order if first entered is no type
      int temp1;
      temp1 = type1;
      type1 = type2;
      type2 = temp1;      
   }
   pkmn->type1 = type1;
   pkmn->type2 = type2;
   pkmn->evolvesToId = -1; //by default it does not 
   pkmn->next = NULL;
   pkmn->prev = NULL;
   return pkmn;
}

void printCurrentPkmn(PkmnList list) {
   Pkmn cur = list->curPkmn;
   if (cur != NULL) { //if exists prints in format required
      printf("Id: %03d\nName: " , cur->id);
      if (cur->found == FALSE) {
         printAsterisks(strlen(cur->name));
         printf("\nHeight: --\nWeight: --\nType: --\n");
      } else {
         printf("%s\nHeight: %.2lfm\nWeight: %.2lfkg\nType: %s", 
         cur->name, cur->height, cur->weight, 
         getTypeString(cur->type1)); //all on one line (72 char limit)
         if (cur->type2 >= 0) { //if has 2nd type
            printf("/%s", getTypeString(cur->type2));
         }
         printf("\n");
      }
   } else {//if removed Pkmn is at start
      printf("No Pokemon in list.\n");
   }
}

PkmnList createPkmnList() { //creates PkmnList and initialises values
   PkmnList list = malloc(sizeof(struct _list));
   if (list == NULL) {
      printf("Out of memory\n");
      exit(EXIT_FAILURE);
   }
   list->size = 0;
   list->numFound = 0;
   list->head = NULL; 
   list->tail = NULL;
   list->curPkmn = NULL;
   return list;
}

void freePkmnList(PkmnList list) {
   Pkmn cur = list->head;
   Pkmn prev = NULL;
   while (cur != NULL) {
      prev = cur;
      cur = cur->next;
      free(prev);
   }
   free(list);
}

void addPkmnToList(PkmnList list, Pkmn pkmn) {
//adds Pokemon to list if pokemon with the same id is not already in it
   if (isAlreadyInList(list, pkmn) == FALSE) { 
      if (list->size == 0) {
         list->head = pkmn;
         list->curPkmn = pkmn;
      } else {
         (list->tail)->next = pkmn;
         pkmn->prev = list->tail;
      }
      if (pkmn->found == TRUE) {
         list->numFound ++;
      }
      list->tail = pkmn;
      list->size ++;
   } else {
      free(pkmn); //frees if it it a copy of a pokemon already in list
   }
}

void printPkmnList(PkmnList list) {
   if (list->size > 0) {
      Pkmn cur = list->head;
      while (cur != NULL) {
         if (cur == list->curPkmn) {
            printf("--> ");   
         } else {
            printf("    ");
         }
         printf("#%03d: ", cur->id);
         printName(cur);
         printf("\n");
         cur = cur->next;
      } 
   } else {
      printf("No Pokemon in list.\n");
   }
}

//part 2
void nextPkmn(PkmnList list) {
   if (list->curPkmn != NULL) {
      if ((list->curPkmn)->next != NULL) {
         list->curPkmn = (list->curPkmn)->next;
      }
   }
}

void prevPkmn(PkmnList list) {
   if (list->curPkmn != NULL) {
      if ((list->curPkmn)->prev != NULL) {
         list->curPkmn = (list->curPkmn)->prev;
      }
   }
}

void jumpToPkmn(PkmnList list, int id) {
   Pkmn newCur = getPkmnByID(list, id);
   if (newCur != NULL) {
      list->curPkmn = newCur;
   }
}

void removePkmn(PkmnList list) {
   if (list->curPkmn != NULL) {
      if ((list->curPkmn)->found == TRUE) {
         list->numFound--;
      }
      Pkmn afterCur = (list->curPkmn)->next;
      Pkmn beforeCur = (list->curPkmn)->prev; 
      free(list->curPkmn);
      list->size --;
      if (beforeCur == NULL && afterCur == NULL) { //only pkmn in list
         list->curPkmn = NULL;
         list->head = NULL;
         list->tail = NULL;      
      } else if (beforeCur == NULL) { //if removed Pkmn is not at start
         list->head = afterCur;
         afterCur->prev = NULL;
         list->curPkmn = list->head;
      } else if (afterCur != NULL) { //if removed Pkmn is not at start
         afterCur->prev = beforeCur;
         beforeCur->next = afterCur;
         list->curPkmn = afterCur;
      } else if (beforeCur != NULL) { //if cur was last element
           beforeCur->next = NULL;
           list->tail = beforeCur;
           list->curPkmn = beforeCur;
      } 
   }
}

// Stage 3 Functions
void findPkmn(int seed, int factor, int numberOfNewPkmn, 
PkmnList list) { //split into 2 lines to adhere to character limit 
   if (list->size != 0) {
      int randnum;
      int i = 0;
      Pkmn pkmn;
      srand(seed);
      while (i < numberOfNewPkmn) { 
         randnum = rand() % factor; //randnum is between 0 and factor - 1
         pkmn = getPkmnByID(list, randnum);
         if (pkmn != NULL) { 
            if (pkmn->found == FALSE) {
               pkmn->found = TRUE;
               list->numFound++;
            } 
            i++; //only increments when it encounters a pokemon
         }  
      }
   }
}

int totalFound(PkmnList list) {  
   return list->numFound;
}

// Stage 4 Functions
void addEvolution(PkmnList list, int pkmnId, int evolutionId) {
   if (evolutionId != pkmnId && pkmnId >= 0 && evolutionId >= 0) {
      Pkmn basePkmn = getPkmnByID(list, pkmnId);
      if (basePkmn != NULL) {//if first entered exists 
         if (basePkmn->evolvesToId == -1) { //no evolution already set
            basePkmn->evolvesToId = evolutionId;
         }
      }  
   }
}

void showEvolutions(PkmnList list) {
   Pkmn cur = list->curPkmn;
   Pkmn evolPkmn = NULL;
   if (cur != NULL) {
      printf("#%03d ", cur->id); 
      printName(cur);
      while (cur != NULL && cur->evolvesToId != -1) {
         printf(" --> ");
         printf("#%03d ", cur->evolvesToId);
         evolPkmn = getPkmnByID(list, cur->evolvesToId);
         cur = evolPkmn;
         if (cur != NULL) {
            printName(cur);
         } else { //if pokemon doesn't exist yet
            printf("?????");
         }
      }
      printf("\n");
   }
}


// Stage 5 Functions
PkmnList getPkmnOfType(PkmnList list, int type) {
   PkmnList typeList = createPkmnList();
   typeList->size = 0;
   typeList->numFound = 0;
   Pkmn cur = list->head;
   while (cur != NULL) {
      if (cur->type1 == type || cur->type2 == type) {
      //^if one of types is same
         addPkmnToList(typeList, duplicateOf(cur)); 
      }
      cur = cur->next;
   }
   return typeList;  
}

PkmnList getFoundPkmn(PkmnList list) {
   int foundCount = 0;
   PkmnList foundList = createPkmnList();
   Pkmn cur = list->head;
   while (cur != NULL && foundCount < list->numFound) {
      if (cur->found == TRUE) {
         addCopyIdOrder(foundList, cur);
         foundCount++;
      }
      cur = cur->next;
   }
   foundList->curPkmn = foundList->head;
   return foundList;
}


PkmnList searchByName(PkmnList list, char text[]) {
   PkmnList nameList = createPkmnList();
   Pkmn cur = list->head; 
   while (cur != NULL) {
      if (containsSubstring(cur->name, text) == TRUE) {
         addPkmnToList(nameList, duplicateOf(cur));   
      }
      cur = cur->next;
   }
   return nameList;
}
