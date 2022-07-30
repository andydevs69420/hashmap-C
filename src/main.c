/*
 | HashMap implementation in C programming language.
 | author: andydevs69420
 | description: HashMap with key type and value of char * | char[]
 | Copyright (C) andydevs69420 2022 All rights reserved.
 */


#include "hashmap.h"

int main() {

    HashMap *colors = new_HashMap();
    colors->put(colors, "Hello", "World");

    return 0;
}