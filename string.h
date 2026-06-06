#ifndef STRING_H
#define STRING_H

#include <stddef.h>

struct String;

/* lifecycle */
struct String *string_create(size_t max);
size_t         string_realloc(struct String *string, size_t new);
void           string_destroy(struct String *string);

/* access */
size_t      string_len(const struct String *string);
size_t      string_max(const struct String *string);
const char *string_str(const struct String *string);

/* primitive ops: char * source */
struct String *string_strndup(const char *src, size_t n);
void           string_strcpy(struct String *dst, const char *src);
void           string_strncat(struct String *dst, const char *src, size_t n);
void           string_strncpy(struct String *dst, const char *src, size_t n);

/* string ops: String * source */
struct String *string_duplicate(const struct String *src);
void           string_clear(struct String *string);
void           string_catenate(struct String *dst, const struct String *src);
void           string_copy(struct String *dst, const struct String *src);

#endif
