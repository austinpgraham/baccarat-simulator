#include <stdio.h>
#include <stdlib.h>
#include "ds/hashset.h"

const int INITIAL_CAPACITY = 32;
const long HASH_P = 64;
const long HASH_M = 32416190071;
const int PERTURB_SHIFT = 5;
const float LOAD_FACTOR = 0.7;

hashset_t *create_hashset()
{
    hashset_t *new_set = malloc(sizeof(hashset_t));
    new_set->keys = malloc(INITIAL_CAPACITY * sizeof(char *));
    new_set->capacity = INITIAL_CAPACITY;
    new_set->length = 0;
    return new_set;
}

const char **get_keys(hashset_t *set)
{
    const char **keys = malloc(set->length * sizeof(char *));
    int array_index = 0;
    for (int i = 0; i < set->capacity; i++)
    {
        const char *key = set->keys[i];
        if (key != NULL)
        {
            keys[array_index++] = key;
        }
    }
    return keys;
}

/**
 * User a rolling-polynomial hash to has a string
 * into an integer we can use to determine where in
 * our hash set to put it.
 */
long long hash_key(const char *key)
{
    // Can't hash NULL can we?
    if (key == NULL)
    {
        return 0;
    }
    long long value = 0;
    long long p_pow = 1;
    int i = 0;
    do
    {
        int letter_value = key[i] - 'a' + 1;
        value = (value + letter_value * p_pow) % HASH_M;
        p_pow = (p_pow * HASH_P) % HASH_M;
    } while (key[++i] != '\0');
    return value;
}

int quadratic_probe(long long hash, hashset_t *set)
{
    int mask = set->capacity - 1;
    int index = hash & mask;
    long long perturb = hash;
    while (set->keys[index] != NULL)
    {
        if (hash_key(set->keys[index]) == hash)
        {
            return -index;
        }
        index = (index * PERTURB_SHIFT + perturb + 1) & mask;
        perturb >>= PERTURB_SHIFT;
    }
    return index;
}

void increase_capacity(hashset_t *set)
{
    set->capacity = set->capacity * 2;
    const char **keys = get_keys(set);

    free(set->keys);
    set->keys = malloc(set->capacity * sizeof(char *));

    for (int i = 0; i < set->length; i++)
    {
        long long key_hash = hash_key(keys[i]);
        int index = quadratic_probe(key_hash, set);
        set->keys[index] = keys[i];
    }

    free(keys);
}

void add_key(const char *key, hashset_t *set)
{
    long long key_hash = hash_key(key);
    int index = quadratic_probe(key_hash, set);
    if (index < 0)
    {
        // If we found the key, do nothing.
        return;
    }
    set->keys[index] = key;
    set->length += 1;

    // Increase capacity if we need
    if (set->length / (float)(set->capacity) > LOAD_FACTOR)
    {
        increase_capacity(set);
    }
}

int set_contains(const char *key, hashset_t *set)
{
    long long key_hash = hash_key(key);
    int expected_index = quadratic_probe(key_hash, set);
    return expected_index < 0;
}

void free_hashset(hashset_t *set)
{
    free(set->keys);
    free(set);
}

void print_set(hashset_t *set)
{
    int seen = 0;

    printf("{");
    const char **keys = get_keys(set);
    for (int i = 0; i < set->length; i++)
    {
        seen += 1;
        const char *key = keys[i];
        if (seen == set->length)
        {
            printf("%s", key);
        }
        else
        {
            printf("%s,", key);
        }
    }
    printf("}\n");

    free(keys);
}
