/* Joel Hochstetter - z5115275
Tuesday 2pm Tute - William Archninal
20/10/2016
Contains required main.c files including extra helper functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "Pkmn.h"

void printMenu();
Pkmn enterPkmn();
void findPkmnInput(PkmnList list);
void evolutionInput(PkmnList list);
PkmnList findPkmnOfTypeInput(PkmnList list);
PkmnList findPkmnByNameInput(PkmnList list);

int main(int argc, char * argv[]) {
   PkmnList list = createPkmnList();
   int id;
   printMenu();
   char selection;
   Pkmn pkmn;
   scanf(" %c", &selection);
   while(selection != 'q') {
      if(selection == 'a') {
         pkmn = enterPkmn();
         addPkmnToList(list, pkmn); 
      } else if (selection == 'p') {
         printPkmnList(list);
      } else if (selection == 'd') {
         printCurrentPkmn(list);
      } else if (selection == '>') {
         nextPkmn(list);
      } else if (selection == '<') {
         prevPkmn(list);
      } else if (selection == 'j') {
         printf("Id: ");
         scanf("%d", &id);
         jumpToPkmn(list, id);
      } else if (selection == 'r') {
         removePkmn(list);
      } else if (selection == 'f') {
         findPkmnInput(list);
      } else if (selection == 'c') {
         printf("%d Pokemon found.\n", totalFound(list));
      } else if (selection == 'e') {
         evolutionInput(list);
      } else if (selection == 's') {
         showEvolutions(list);
      } else if (selection == 't') { //I used these to test lists
         PkmnList typeList = findPkmnOfTypeInput(list);
         printPkmnList(typeList);
         freePkmnList(typeList);
      } else if (selection == 'l') {
         PkmnList foundList = getFoundPkmn(list);
         printPkmnList(foundList);
         freePkmnList(foundList);
      } else if (selection == 'n') {
         PkmnList nameList = findPkmnByNameInput(list);
         printPkmnList(nameList);
         freePkmnList(nameList);
      }
      printMenu();
      scanf(" %c", &selection);
   }
   freePkmnList(list);
   return EXIT_SUCCESS;
}

void printMenu() {
   printf("a - Add a Pokemon to the list\n");
   printf("p - Print list\n");
   printf("d - Display details of the current Pokemon\n");
   printf("> - Move to the next Pokemon\n");
   printf("< - Move to the previous Pokemon\n");
   printf("j - Jump to a specific Pokemon\n");
   printf("r - Remove the current Pokemon\n");
   printf("f - Find Pokemon\n");
   printf("c - Count the number of Pokemon which have been found\n");
   printf("e - Add an evolution to a Pokemon\n");
   printf("s - Show the evolutions of the current Pokemon\n");
   printf("q - Quit\n");
}

Pkmn enterPkmn() {
   int id = 0;
   char name[51];
   double height = 0.0;
   double weight = 0.0;
   int type1;
   int type2;
   printf("Id: ");
   scanf("%d", &id);
   printf("Name: ");
   scanf("%s", name);
   printf("Height: ");
   scanf("%lf", &height);
   printf("Weight: ");
   scanf("%lf", &weight);/* Joel Hochstetter - z5115275
Tuesday 2pm Tute - William Archninal
20/10/2016
Contains required Pkmn.c files including extra helper functions
*/

   printf("Type: ");
   scanf("%d", &type1);
   printf("Type: ");
   scanf("%d", &type2);
   Pkmn pkmn = createPkmn(id, name, height, weight, type1, type2);
   return pkmn;
}

void findPkmnInput(PkmnList list) {
   int seed;
   int factor;
   int numberOfNewPkmn;
   printf("Seed: ");
   scanf("%d", &seed);
   printf("Factor: ");
   scanf("%d", &factor);
   printf("Number to find: ");
   scanf("%d", &numberOfNewPkmn);
   findPkmn(seed, factor, numberOfNewPkmn, list);
}

void evolutionInput(PkmnList list) {
   int pkmnId;
   int evolutionId;
   printf("Id of original Pokemon: ");
   scanf("%d", &pkmnId);
   printf("Id of evolution: ");
   scanf("%d", &evolutionId);
   addEvolution(list, pkmnId, evolutionId);
}

PkmnList findPkmnOfTypeInput(PkmnList list) {
   int typeID;
   printf("Enter type ID: ");
   scanf("%d", &typeID);
   return getPkmnOfType(list, typeID); 
}

PkmnList findPkmnByNameInput(PkmnList list) {
   char name[51];
   printf("Enter name: ");
   scanf("%s", name);
   return searchByName(list, name);
}
