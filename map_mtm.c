//
// Created by user on 11/05/2018.
//
#include "map_mtm.h"
#include <stdlib.h>

typedef struct map_node* Node;
struct map_node {
    MapKeyElement key;
    MapDataElement data;
    Node next;
};
struct Map_t {
    Node first;
    int size;
    Node iterator;
    copyMapDataElements copyData;
    copyMapKeyElements copyKey;
    freeMapDataElements freeData;
    freeMapKeyElements freeKey;
    compareMapKeyElements comapareKey;
};

// comment
Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {
    if(!copyDataElement || !copyKeyElement || !freeDataElement || !freeKeyElement ||
            !compareKeyElements) {
        return NULL;
    }
    Map map = malloc(sizeof(*map));
    if(!map) {
        return NULL;
    }
    map->first = NULL;
    map->size = 0;
    map->iterator = NULL;
    map->copyData = copyDataElement;
    map->copyKey = copyKeyElement;
    map->freeData = freeDataElement;
    map->freeKey = freeKeyElement;
    map->comapareKey = compareKeyElements;
    return map;
}

void mapDestroy(Map map) {
    while(map->first) {
        Node toDelete = map->first; //holds pointer to the first node in the map
        map->first =  (map->first)->next; // save the pointer to the next node
        map->freeKey(toDelete->key);
        map->freeData(toDelete->data);
        free(toDelete);
    }
    free(map);
}

Map mapCopy(Map map) {
    if (!map) {
        return NULL;
    }
    Map newMap = mapCreate(map->copyData, map->copyKey, map->freeData, map->freeKey, map->comapareKey);
    Node old_current = map->first;
    Node new_current = NULL;
    Node last_new_current = NULL;
    while (old_current) {

        new_current = malloc(sizeof(*new_current));
        if (!new_current) {
            return NULL;
        }
        new_current->key = map->copyKey(old_current->key);
        new_current->data = map->copyData(old_current->data);
        new_current->next = NULL;
        if (last_new_current) {
            last_new_current->next = new_current;
        }
        if (!newMap->first) {
            newMap->first = new_current;
        }
        last_new_current = new_current;
        old_current = old_current->next; // holds the address of the next node
    }
    newMap->size = map->size;
    return newMap;
}

int mapGetSize(Map map) {
    if(!map) {
        return -1;
    }
    return map->size;
}



