#ifndef PKMN_H
#define PKMN_H

typedef struct _pkmn * Pkmn;
typedef struct _list * PkmnList;

#define NO_TYPE -1
#define BUG 0
#define DARK 1
#define DRAGON 2
#define ELECTRIC 3
#define FAIRY 4
#define FIGHTING 5
#define FIRE 6
#define FLYING 7
#define GHOST 8
#define GRASS 9
#define GROUND 10
#define ICE 11
#define NORMAL 12
#define POISON 13
#define PSYCHIC 14
#define ROCK 15
#define STEEL 16
#define WATER 17

#define NUM_TYPES 18

#define PKMN_NAME_LENGTH 50

const char * getTypeString(int i);

// Stage 1 Functions
Pkmn createPkmn(int id, char * name, double height, double weight, int type1, int type2);
void printCurrentPkmn(PkmnList list);
PkmnList createPkmnList();
void freePkmnList(PkmnList list);
void addPkmnToList(PkmnList list, Pkmn pkmn);
void printPkmnList(PkmnList list);

// Stage 2 Functions
void nextPkmn(PkmnList list);
void prevPkmn(PkmnList list);
void jumpToPkmn(PkmnList list, int id);
void removePkmn(PkmnList list);

// Stage 3 Functions
void findPkmn(int seed, int factor, int numberOfNewPkmn, PkmnList list);
int totalFound(PkmnList list);

// Stage 4 Functions
void addEvolution(PkmnList list, int pkmnId, int evolutionId);
void showEvolutions(PkmnList list);

// Stage 5 Functions
PkmnList getPkmnOfType(PkmnList list, int type);
PkmnList getFoundPkmn(PkmnList list);
PkmnList searchByName(PkmnList list, char text[]);
#endif
