#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

typedef struct {
  size_t length;
  size_t capacity;
  size_t expand_length;
  char * content;
} buffer_data;

buffer_data * buffer_init(const size_t initial_size);
ssize_t buffer_append(buffer_data *buffer, const char *append_data);
void buffer_destroy(buffer_data * buffer);

#endif // STRING_UTILS_H_