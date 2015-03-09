
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "buffer.h"


////////////////////////////////////////////////////////////////////////////////
// 
//  Function buffer_init
//
//  Purpose: 
// 
//     This function will return a struct with the values it needs before it
//     can be used with buffer_append. The default "expand_length" is 
// 
//  Parameters:
// 
//     initial_size (IN) This parameter will preallocate the buffer with this 
//     size in bytes.
// 
//  Returns:
// 
//     returns a struct, or NULL on error
// 
//  Error Definitions:
// 
//     NULL = Couldn't create the structure
//
////////////////////////////////////////////////////////////////////////////////

buffer_data * buffer_init(const size_t initial_size) {
    
    buffer_data * buffer = NULL;
    
    // malloc the space for a pointer to a buffer_data
    buffer = malloc(sizeof(buffer_data));
    if (buffer == NULL) {
        return NULL;
    }
    
    // only allow max initial size of SIZE_MAX
    if (initial_size > SIZE_MAX) {
        return NULL;
    }
    
    // fill the struct up
    buffer->expand_length = initial_size;
    buffer->capacity = initial_size;
    buffer->length = 0;
    
    // allocate the buffer space
    buffer->content = malloc(sizeof(char) * initial_size);
    if (buffer->content == NULL) {
        // can't allocate the buffer, therefore we need to clean everything up
        free(buffer);
        return NULL;
    }
    
    // return a pointer to our buffer_data structure
    return buffer;
}


////////////////////////////////////////////////////////////////////////////////
// 
//  Function buffer_append
//
//  Purpose: 
// 
//     This function will take data and append it into a buffer in the struct
//     given. It will growing as required (or as allowed by realloc) by the
//     length desired in the structure element "expand_length" plus the length 
//     of the data being appended. If additional expansion is not desired, you 
//     can set the struct element "expand_length" to zero.
// 
//  Parameters:
// 
//     buffer_data (IN/OUT) This parameter is a struct (mapped below) to
//     keep track of the internal buffer and its working parameters.
//
//       typedef struct {
//           size_t length;        // the current length of the content in bytes
//           size_t capacity;      // the total capacity of "content" in bytes
//           size_t expand_length; // the amount to expand the buffer on resize
//           char * content;       // the target for appending data
//       } buffer_data;
//
//
//     append_data (IN) This parameter is a const char * that is the data
//     to be appended.
// 
//  Returns:
// 
//     This function will return the amount of bytes appended. If the
//     return value is <= 0 there was an error.
// 
//  Error Definitions:
// 
//     -1 = No data was given to append
//     -2 = Additional space could not be allocated for the buffer.
// 
////////////////////////////////////////////////////////////////////////////////

ssize_t buffer_append(buffer_data * buffer, const char * append_data) {

    // ensure there IS something to append.. 
    const size_t append_len = strlen(append_data) + 1; // +1 for NUL Byte
    if (append_len < 1) {
        return -1;
    }

    // is there enough space, or should we reallocate memory?
    if (buffer->capacity > buffer->length + append_len) {

        const size_t realloc_size = 
            buffer->capacity + append_len + buffer->expand_length;
        
        // allocate the new buffer
        char *new_buffer = realloc(buffer->content, realloc_size);
        
        // resize success.. 
        if (new_buffer == NULL) {
            return -2;
        }

        // copy the data to append into the new content buffer
        strcat(new_buffer, append_data);
        
        // update the struct with the new values
        buffer->content = new_buffer;       // new buffer content
        buffer->capacity = realloc_size;    // add the amount to expand beyond our initial needs
        buffer->length += append_len;
        
    } else {
        // append the string
        strcat(buffer->content, append_data);
    }

    // update the buffer length
    buffer->length += append_len;
    
    // return the amount appended
    return append_len;
}


////////////////////////////////////////////////////////////////////////////////
// 
//  Function buffer_destroy
//
//  Purpose: 
// 
//     This function will destroy the inner buffer and reset all of the data
//     if the struct was dynamically allocated, it is expected that you will
//     take care of freeing the data.
// 
//  Parameters:
// 
//     buffer_data (IN) This parameter is a struct (mapped below) to
//     keep track of the internal buffer and its working parameters.
//
//       typedef struct {
//           size_t length;        // the current length of the content in bytes
//           size_t capacity;      // the total capacity of "content" in bytes
//           size_t expand_length; // the amount to expand the buffer on resize
//           char * content;       // the target for appending data
//       } buffer_data;
//
//  Returns:
// 
//     returns nothing
// 
////////////////////////////////////////////////////////////////////////////////

void buffer_destroy(buffer_data * buffer) {

    // only work with valid data.. 
    if (buffer != NULL) {
        
        // if the content is not null, free it.
        if (buffer->content != NULL) {
            free(buffer->content);
        }
        
        // free the buffer
        free(buffer);
    }

}
