#include <stddef.h>
#include <stdlib.h>


struct String
{
    size_t len;
    size_t max;
    char *data;
};


void string_clear(struct String *string)
{
    if (!string) return;

    for (size_t i = 0; i < string->max; i++) string->data[i] = 0;
    string->len = 0;
}


void string_destroy(struct String *string)
{
    if (!string) return;

    free(string->data);
    free(string);
}


void string_realloc(struct String *string, size_t new)
{
    if (!string) return;

    char *tmp = realloc(string->data, new + 1);
    if (!tmp) return;

    string->data = tmp;
    string->data[new] = 0;
}


struct String *string_create(size_t max)
{
    struct String *string = calloc(sizeof(struct String));
    if (!string) return NULL;
    
    string->data = calloc((max + 1) * sizeof(char));
    if (!string->data) {
        string_destroy(string);
        return NULL;
    }
    
    string->max = max;
}


size_t string_len(const struct String *string)
{
    if (!string) return 0;

    return string->len;
}


void string_strncpy(struct String *dst, const char *src, size_t n);
{
    if (!dst || !src) return;
    
    size_t len_cpy = (n > dst->max) ? dst->max : n;
    for (size_t i = 0; i < len_cpy; i++) dst->data[i] = src[i];
    dst->data[len_cpy] = 0;
}


void string_copy(struct String *dst, const struct String *src)
{
    if (!dst || !src) return;

    string_strncpy(dst, src->data, src->len);
}


struct String *string_strndup(const char *src, size_t n)
{
    if (!src) return NULL;

    struct String *dst = string_create(n);
    if (!dst) return NULL;

    string_strncpy(dst->data, src, n);
    return dst;
}


struct String *string_duplicate(const struct String *src)
{
    if (!src) return NULL;

    return string_strndup(src->data, src->len);
}
