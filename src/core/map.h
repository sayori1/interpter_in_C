#ifndef MAP_H
#define MAP_H


#include "array.h"
typedef struct{
    void* key;
    void* value;
} Pair;

typedef struct{
    Array* pairs;
} Map;

Map* mapCreate(int capacity){
    Map* map = (Map*)malloc(sizeof(Map));
    map->pairs = arrayCreate(capacity, sizeof(Pair));
    return map;
}

void mapSet(Map* map, void* key, void* value){
    Pair* pair = (Pair*)malloc(sizeof(Pair));
    pair->key = key;
    pair->value = value;

    arrayPush(map->pairs, pair, sizeof(Pair));
}

void* mapGet(Map* map, void* key){
    for(int i = 0; i < map->pairs->size; i++){
        Pair* pair = (Pair*)arrayGet(map->pairs, i);
        if(pair->key == key){
            return pair->value;
        }
    }
    return NULL;
}

void mapRemove(Map* map, void* key){
    for(int i = 0; i < map->pairs->size; i++){
        Pair* pair = (Pair*)arrayGet(map->pairs, i);
        if(pair->key == key){
            arrayRemove(map->pairs, i);
            return;
        }
    }
}

void mapFree(Map* map){
    arrayFree(map->pairs);
    free(map);
}

int containsKey(Map* map, void* key){
    for(int i = 0; i < map->pairs->size; i++){
        Pair* pair = (Pair*)arrayGet(map->pairs, i);
        if(pair->key == key){
            return 1;
        }
    }
    return 0;
}

#endif // !MAP_H
