#include <stddef.h>
#include <stdlib.h>
#include <string.h>


struct String
{
    size_t len;
    size_t max;
    char *data;
};


void string_clear(struct String *string)
{
    if (!string) return;

    string->data[0] = 0;
    string->len = 0;
}


void string_destroy(struct String *string)
{
    if (!string) return;

    free(string->data);
    free(string);
}


size_t string_realloc(struct String *string, size_t new)
{
    if (!string) return 0;

    char *tmp = realloc(string->data, new + 1);
    if (!tmp) return 0;

    string->data = tmp;
    string->max = new;
    if (string->len > string->max) string->len = string->max;
    string->data[string->len] = 0;

    return new;
}


struct String *string_create(size_t max)
{
    struct String *string = malloc(sizeof(struct String));
    if (!string) return NULL;
    
    string->data = calloc((max + 1), sizeof(char));
    if (!string->data) {
        string_destroy(string);
        return NULL;
    }
    
    string->max = max;
    string->len = 0;
    return string;
}


size_t string_len(const struct String *string)
{
    if (!string) return 0;

    return string->len;
}


size_t string_max(const struct String *string)
{
    if (!string) return 0;

    return string->max;
}


const char *string_str(const struct String *string)
{
    if (!string) return 0;

    return (const char *)string->data;
}


int string_strcmp(const struct String *string, const char *str)
{
    return strcmp((!string) ? NULL : string->data, str);
}


int string_strncmp(const struct String *string, const char *str, size_t n)
{
    return strncmp((!string) ? NULL : string->data, str, n);
}


int string_compare(const struct String *string1, const struct String *string2)
{
    return string_strcmp(string1, (!string2) ? NULL : string2->data);
}


/* stops at null byte; string_strncpy copies exactly n bytes regardless */
void string_strcpy(struct String *dst, const char *src)
{
    if (!dst || !src) return;

    size_t i = 0;
    for (i = 0; (i < dst->max) && (src[i]); i++) dst->data[i] = src[i];
    dst->len = i;
    dst->data[i] = 0;
}


void string_strncpy(struct String *dst, const char *src, size_t n)
{
    if (!dst || !src) return;
    
    size_t len_cpy = (n > dst->max) ? dst->max : n;
    for (size_t i = 0; i < len_cpy; i++) dst->data[i] = src[i];
    dst->data[len_cpy] = 0;
    dst->len = len_cpy;
}


void string_copy(struct String *dst, const struct String *src)
{
    if (!dst || !src) return;

    if (src->len > dst->max) {
        if (!string_realloc(dst, src->len)) return;
    }

    string_strncpy(dst, src->data, src->len);
}


struct String *string_strdup(const char *src)
{
    if (!src) return NULL;
    size_t n = strlen(src);

    struct String *dst = string_create(n);
    if (!dst) return NULL;

    string_strncpy(dst, src, n);
    return dst;
}


struct String *string_strndup(const char *src, size_t n)
{
    if (!src) return NULL;

    struct String *dst = string_create(n);
    if (!dst) return NULL;

    string_strncpy(dst, src, n);
    return dst;
}


struct String *string_duplicate(const struct String *src)
{
    if (!src) return NULL;

    return string_strndup(src->data, src->len);
}


void string_strncat(struct String *dst, const char *src, size_t n)
{
    if (!dst || !src) return;

    size_t len_cat = (dst->len + n > dst->max) ? (dst->max - dst->len) : n;
    for (size_t i = 0; i < len_cat; i++) dst->data[dst->len + i] = src[i];

    dst->len += len_cat;
    dst->data[dst->len] = 0;
}


void string_catenate(struct String *dst, const struct String *src)
{
    if (!dst || !src) return;

    if (dst->len + src->len > dst->max) {
        if (!string_realloc(dst, dst->len + src->len)) return;
    }

    string_strncat(dst, src->data, src->len);
}


const char *string_strstr(const struct String *haystack, const char *needle)
{
    return strstr((!haystack) ? NULL : haystack->data, needle);
}


const char *string_substring(const struct String *haystack, const struct String *needle)
{
    return string_strstr(haystack, (!needle) ? NULL : needle->data);
}
