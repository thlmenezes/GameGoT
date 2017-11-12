#include "../headers/character.h"
#include <stdlib.h>
#include <string.h>



//TOD
//WARNING: Força estava escrito errado na declaração da função
//--------------------------------------------------------------
Character* character_create(char* _name, char* _house, int _agility,
int _strength, int _intelligence, int _health)
{

    Character* personagem = (Character*) malloc(sizeof(Character));
    personagem->name      = (char*) malloc(strlen(_name)*sizeof(char));
    personagem->house     = (char*) malloc(strlen(_house)*sizeof(char));
    strcpy(personagem->name, _name);
    strcpy(personagem->house, _house);
    personagem->agility = _agility;
    personagem->strength = _strength;
    personagem->intelligence = _intelligence;
    personagem->health = _health;
    return personagem;
}//End character_create()
