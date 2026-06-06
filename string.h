#ifndef STRING_H
#define STRING_H

#include <stddef.h>

struct String;

/* lifecycle */
struct String *string_create(size_t max);
struct String *string_strndup(const char *src, size_t n);
struct String *string_duplicate(const struct String *src);
void           string_destroy(struct String *string);
void           string_clear(struct String *string);
size_t         string_realloc(struct String *string, size_t new);

/* query */
size_t string_len(const struct String *string);

/* primitive ops: char * source, never allocate, truncate to capacity */
void string_strcpy(struct String *dst, const char *src);
void string_strncpy(struct String *dst, const char *src, size_t n);
void string_strncat(struct String *dst, const char *src, size_t n);

/* string ops: String * source, reallocate as needed */
void string_copy(struct String *dst, const struct String *src);
void string_catenate(struct String *dst, const struct String *src);

#endif
