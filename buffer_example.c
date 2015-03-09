
/* 
 * File:    buffer_example.c
 * Author:  Mike Curry
 * License: The MIT License (MIT)
 *
 * Created on February 27, 2015, 12:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "buffer.h"

int main() {
        
    buffer_data *buff;
    buff = buffer_init(10);
    
    // proceed only if we have a valid buffer...
    if (buff != NULL) {
        ssize_t rtval = 0;
        int i;

        // original string
        for (i = 1; i < 100; ++i) {
            fprintf(stdout, "String: -->|%s|<--\n\n", buff->content);
            rtval = buffer_append(buff, "ABCDEFGH");
            if (rtval < 1) {
                fprintf(stderr, "Error appending, stopping!\n");
                exit(1);
            } else {
                fprintf(stdout, "appended %zd\n", rtval);
            }
        }
    }
    
    // free the buffer
    buffer_destroy(buff);

    return 0;
}