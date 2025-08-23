#ifndef HASHSET_H
#define HASHSET_H

typedef struct
{
    const char **keys;
    int capacity;
    int length;
} hashset_t;

hashset_t *create_hashset();
const char **get_keys(hashset_t *set);
void add_key(const char *key, hashset_t *set);
int set_contains(const char *key, hashset_t *set);
void free_hashset(hashset_t *set);
void print_set(hashset_t *set);

#endif // HASHSET_H
