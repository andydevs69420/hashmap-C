/*
 | HashMap implementation in C programming language.
 | author: andydevs69420
 | description: HashMap with key and value type of char * | char[]
 | Copyright (C) andydevs69420 2022 All rights reserved.
 */


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef HASHMAP__H
#define HASHMAP__H

typedef struct MAPENTRY MapEntry;
typedef struct MAPENTRY {
    char *key;
    char *val;
    MapEntry *tail;

    // methods
    void (*update_or_insert)(MapEntry*, MapEntry*);
    char *(*match_until)(MapEntry*, char*);
} MapEntry;

MapEntry *new_MapEntry(char*, char *);
void update_or_insert(MapEntry*, MapEntry*);
char *match_until(MapEntry*, char*);

typedef struct HASHMAP HashMap;
typedef struct HASHMAP {
    MapEntry **bucket;
    int element_size;
    int default_size;

    // methods
    void (*put)(HashMap*, char*, char*);
    char *(*get)(HashMap*, char*);
    void (*rehash)(HashMap*);
    int  (*hashKey)(char*);
} HashMap;

HashMap *new_HashMap();
void put(HashMap*, char*, char*);
char *get(HashMap*, char*);
void rehash(HashMap*);
int hashKey(char*);

#endif


#ifdef __cplusplus
}
#endif
