/*
 | HashMap implementation in C programming language.
 | author: andydevs69420
 | description: HashMap with key and value type of char * | char[]
 | Copyright (C) andydevs69420 2022 All rights reserved.
 */

#include "hashmap.h"

int main(int argc, char **args) 
{
    /*
     | Test
     | describe: test hashmap with hex colors.
     */

    HashMap *colors = new_HashMap();
    colors->put(colors, "Yellow", "#ffff00");
    colors->put(colors, "Blue"  , "#0000ff");
    colors->put(colors, "White" , "#ffffff");

    char *hexval = colors->get(colors, "Blue");
    printf("Blue: %s\n", hexval);

    hexval = colors->get(colors, "White");
    printf("White: %s\n", hexval);

    hexval = colors->get(colors, "Yellow");
    printf("Yellow: %s\n", hexval);

    /** OUTPUT: 
        $ ./compile-linux.sh 
        Blue: #0000ff
        White: #ffffff
        Yellow: #ffff00
    **/

    colors->get(colors, "Green");
    /** OUTPUT: 
        $ ./compile-linux.sh 
        Blue: #0000ff
        White: #ffffff
        Yellow: #ffff00
        KeyError: key "Green" does not exist !!!
    **/

    free(colors);
    return 0;
}