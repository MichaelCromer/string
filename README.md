# String

A dynamic string library for C built around `struct String`, which tracks both length and capacity.

`struct String` is opaque: its fields are not accessible outside `string.c`. Always create with `string_create` (or `string_duplicate` or `string_strndup`) and free with `string_destroy`.

## Naming convention

Operations on strings are divided into two types:

- **`string_str<fn>`** — primitive operations taking a `char` pointer with names matching those in the standard `string.h` library. Unlike their namesakes, they always respect the existing string max capacity and truncate silently if the source is too large.
- **`string_<verb>`** — struct-aware operations taking a `String` pointer. Reallocate as needed to preserve the full value.

## API

### Lifecycle

| Function | Description |
|---|---|
| `string_create(max)` | Allocate a new String with initial capacity `max` |
| `string_destroy(string)` | Free a String and its buffer |
| `string_realloc(string, new)` | Resize the buffer; truncates content if shrinking.  Returns new size on success, 0 on failure. |

### Access

| Function | Description |
|---|---|
| `string_len(string)` | Return the current length |
| `string_max(string)` | Return the maximum length |
| `string_str(string)` | Return a const pointer to the string contents |

### Primitive operations (`char` pointer)

| Function | Description |
|---|---|
| `string_strcpy(dst, src)` | Copy `src` into `dst`, stopping at null or capacity |
| `string_strncat(dst, src, n)` | Append up to `n` bytes of `src` to `dst`, capped at remaining capacity |
| `string_strncpy(dst, src, n)` | Copy exactly `n` bytes of `src` into `dst`, capped at capacity |
| `string_strndup(src, n)` | Allocate a new String from the first `n` bytes of `src` |


### String operations (`String` pointer)

| Function | Description |
|---|---|
| `string_catenate(dst, src)` | Append `src` to `dst`, reallocating `dst` if needed |
| `string_copy(dst, src)` | Copy `src` into `dst`, reallocating `dst` if needed |
| `string_duplicate(src)` | Allocate a new String copied from `src` |
| `string_clear(string)` | Reset length to 0 without freeing the buffer |
