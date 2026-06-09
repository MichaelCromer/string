#ifndef STRING_H
#define STRING_H

#include <stddef.h>

struct String;

/* lifecycle */
struct String *string_create(size_t max);
size_t         string_realloc(struct String *string, size_t new);
void           string_destroy(struct String *string);

/* access */
size_t         string_len(const struct String *string);
size_t         string_max(const struct String *string);
const char    *string_str(const struct String *string);

/* primitive ops: char * source */
const char    *string_strstr(const struct String *haystack, const char *needle);
int            string_strcmp(const struct String *string, const char *str);
int            string_strncmp(const struct String *string, const char *str, size_t n);
struct String *string_strdup(const char *src);
struct String *string_strndup(const char *src, size_t n);
void           string_strcpy(struct String *dst, const char *src);
void           string_strncat(struct String *dst, const char *src, size_t n);
void           string_strncpy(struct String *dst, const char *src, size_t n);

/* string ops: String * source */
const char    *string_substring(const struct String *haystack, const struct String *needle);
int            string_compare(const struct String *string1, const struct String *string2);
struct String *string_duplicate(const struct String *src);
void           string_catenate(struct String *dst, const struct String *src);
void           string_clear(struct String *string);
void           string_copy(struct String *dst, const struct String *src);

#endif
