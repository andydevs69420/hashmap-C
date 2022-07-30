/*
 | HashMap implementation in C programming language.
 | author: andydevs69420
 | description: HashMap with key type and value of char * | char[]
 | Copyright (C) andydevs69420 2022 All rights reserved.
 */

#include "hashmap.h"


#ifndef MAPENTRY__IMPLEMENT
#define MAPENTRY__IMPLEMENT

MapEntry *new_MapEntry(char *_key, char *_val) {
    MapEntry *mapentry = (MapEntry*) malloc(sizeof(MapEntry));
        mapentry->key  = _key;
        mapentry->val  = _val;
        mapentry->tail = NULL;

        // init method(s)
        mapentry->update_or_insert = update_or_insert;
    return mapentry;
}

void update_or_insert(MapEntry *self, MapEntry *new_entry) {

}

#endif



#ifndef HASHMAP__IMPLEMENT
#define HASHMAP__IMPLEMENT

// @HashMap constructor
HashMap *new_HashMap() {
    HashMap *hashmap = (HashMap*) malloc(sizeof(HashMap));
        hashmap->default_size = 16; // 16 by default
        hashmap->element_size =  0;

        hashmap->bucket = malloc(sizeof(MapEntry) * hashmap->default_size);

        // init methods
        hashmap->put = put;
        hashmap->get = get;
        hashmap->rehash  = rehash;
        hashmap->hashKey = hashKey; 
    return hashmap;
}

void put(HashMap *self, char *_key, char *_val) {

    int bucketidx, hashcode = self->hashKey(_key);
        bucketidx = hashcode % self->default_size;

    if (self->bucket[bucketidx] != NULL)
    {
        // collision
        return;
    }

    // insert
    self->bucket[bucketidx] = 

    printf("%s %s\n", _key, _val);
}

char *get(HashMap *self, char *_key) {

}

void rehash(HashMap *self) {

}

int hashKey(char *_key) {
    int hash = 0;
    if (strlen(_key) <= 0) return hash;

    int idx;
    for(idx = 0; idx < strlen(_key); idx++) {
        hash  = ((hash << 5) - hash) + (int) _key[idx];
        hash |= 0;
    }
    return hash;
}

#endif