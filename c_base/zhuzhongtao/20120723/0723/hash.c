#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *link;
struct node { char *name; char *defn; link next; };
#define HASHSIZE 101
link hashtab[HASHSIZE];
link NODE(char *name, char *defn, link next)
{
    link t = malloc(sizeof *t);
    t->name = strdup(name);
    t->defn = strdup(defn);
    t->next = next;
    return t;
}
void init()
{
    int i;
    for (i=0; i<HASHSIZE; i++) hashtab[i] = NULL;
}
unsigned hash(char *name)
{
    unsigned i;
    for (i=0; *name; name++) i = *name + 31 * i;
    return i % HASHSIZE;
}
link lookup(char *name)
{
    link t;
    for (t=hashtab[hash(name)]; t; t=t->next)
        if (strcmp(name, t->name)==0) return t;
    return NULL;
}
link install(char *name, char *defn)
{
    link t; unsigned i;
    if (t=lookup(name)) { // found
        free(t->defn);
        t->defn = strdup(defn);
    } else {              // not found
        i = hash(name);
        t = hashtab[i] = NODE(name, defn, hashtab[i]);
    }
    return t;
}
int main()
{
    int i;
    struct { char *name; char *defn; }
    pair[] = {
        { "Brian Kernighan", "C rabbi" },
        { "Dennis Ritchie",  "C rabbi" },
        { "Mingzhe Ji",      "C master" },
        { "Zhongtao Zhu",    "C pupil" }
    };
    for (i=0; i<sizeof(pair)/sizeof(pair[0]); i++)
        install(pair[i].name, pair[i].defn);
    for (i=0; i<sizeof(pair)/sizeof(pair[0]); i++)
        printf("%4d %s\t%s\n",
                hash(pair[i].name),
                pair[i].name,
                lookup(pair[i].name)->defn);
    return 0;
}
