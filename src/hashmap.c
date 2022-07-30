/*
 | HashMap implementation in C programming language.
 | author: andydevs69420
 | description: HashMap with key and value type of char * | char[]
 | Copyright (C) andydevs69420 2022 All rights reserved.
 */

#include "hashmap.h"


#ifndef MAPENTRY__IMPLEMENT
#define MAPENTRY__IMPLEMENT

// @MapEntry constructor
/**
 * @brief Creates new MapEntry*(Object-like).
 * @param _key char[]
 * @param _val char[]
 * @return MapEntry* 
 **/
MapEntry *new_MapEntry(char *_key, char *_val)
{
    MapEntry *mapentry = (MapEntry*) malloc(sizeof(MapEntry));
        mapentry->key  = _key;
        mapentry->val  = _val;
        mapentry->tail = NULL;

        // init method(s)
        mapentry->update_or_insert = update_or_insert;
        mapentry->match_until = match_until;
    return mapentry;
}

/**
 * @brief Updates or append to linked list if collision happend.
 * @param self MapEntry*
 * @param new_entry MapEntry*
 **/
void update_or_insert(MapEntry *self, MapEntry *new_entry)
{
    // update if key is match to self
    if (strcmp(self->key, new_entry->key) == 0)
    {   self->val = new_entry->val;
        return; }
    
    MapEntry *head_or_tail = self;
    while (head_or_tail->tail != NULL)
        head_or_tail = head_or_tail->tail;
    head_or_tail->tail = new_entry;
}

/**
 * @brief Matches if linked list
 * @param self MapEntry*
 * @param _key char*
 * @return char* 
 */
char *match_until(MapEntry *self, char *_key)
{
    if (strcmp(self->key, _key) == 0) return self->val;

    MapEntry *tail = self->tail;
    while (tail->tail != NULL)
    {
        if (strcmp(tail->key, _key) == 0)
            return tail->val;
        tail = tail->tail;
    }
}

#endif


#ifndef HASHMAP__IMPLEMENT
#define HASHMAP__IMPLEMENT

// @HashMap constructor
/**
 * @brief Creates new HashMap*(Object-like).
 * @return HashMap* 
 **/
HashMap *new_HashMap()
{
    HashMap *hashmap = (HashMap*) malloc(sizeof(HashMap));
        hashmap->default_size = 16; // 16 by default
        hashmap->element_size =  0;

        // GENERATE BUCKET 
        hashmap->bucket = (MapEntry**) malloc(sizeof(MapEntry) * hashmap->default_size);

        // init methods
        hashmap->put = put;
        hashmap->get = get;
        hashmap->rehash  = rehash;
        hashmap->hashKey = hashKey; 
    return hashmap;
}

/**
 * @brief Puts new entry in bucket if key does not exist
 * otherwise, updates the existing entry with the sam key.
 * @param self HashMap*
 * @param _key char*
 * @param _val char*
 **/
void put(HashMap *self, char *_key, char *_val)
{
    int bucketidx, hashcode = self->hashKey(_key);
        bucketidx = hashcode % self->default_size;

    if (self->bucket[bucketidx] != NULL)
    {
        // collision
        self->bucket[bucketidx]->update_or_insert(
            self->bucket[bucketidx], 
            new_MapEntry(_key, _val)
        );
        return;
    }

    // insert
    self->bucket[bucketidx] = new_MapEntry(_key, _val);
    self->element_size++;

    /*
     | calculate load factor, 
     | if load factor is greater than 0.75
     | we need to rehash so that new entr(y | eis) will fit.
     */

    int load_factor = (double) self->element_size / self->default_size;

    if (load_factor > 0.75)
        self->rehash(self);
}

char *get(HashMap *self, char *_key)
{
    int bucketidx, hashcode = self->hashKey(_key);
        bucketidx = hashcode % self->default_size;
    
    // check if not allocated!
    if (self->bucket[bucketidx] == NULL)
        goto not_found;

    // _key is found?
    char *result = self->bucket[bucketidx]->match_until(
        self->bucket[bucketidx],
        _key
    );
    if (result)
        goto found;

    not_found:
    fprintf(stderr, "KeyError: key \"%s\" does not exist !!!\n", _key);
    exit(0x01);

    found:
    return result;
}

/**
 * @brief Doubles the bucket size and re calculate the entries (key).
 * @param self HashMap*
 **/
void rehash(HashMap *self)
{
    MapEntry **bucket_copy = self->bucket;
        int old = self->default_size;
        self->default_size *= 2;
        self->element_size  = 0;

    MapEntry **new_bucket = (MapEntry**) malloc(sizeof(MapEntry) * self->default_size);
    self->bucket = new_bucket;
    for(int idx = 0; idx < old; idx++)
    {
        MapEntry *head_to_tail = bucket_copy[idx];
        while (head_to_tail != NULL)
        {
            self->put(self, head_to_tail->key, head_to_tail->val);
            head_to_tail = head_to_tail->tail;
        }
    }
                
}

/**
 * @brief Hashes key string given.
 * @param _key char*
 * @return int 
 **/
int hashKey(char *_key)
{
    int hash = 0;
    if (strlen(_key) <= 0) return hash;

    int idx;
    for(idx = 0; idx < strlen(_key); idx++)
    {
        hash  = (hash * 31) + (int) _key[idx];
        //////// or ((hash << 5) - hash) + charcode key[idx]
        hash |= 0;
    }
    return hash;
}

#endif