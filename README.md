# C Buffer Manager
A tool set for managing large buffers. Currently it handles creating the buffer,
appending to the buffer, as well as destroying the buffer. More features may, or 
may not be added down the road.

Ultimately I wrote this to make things easier for me when managing a large
amount of buffer "chunks" returned from a buffered file handle. I use this for
my recv() calls when dealing with sockets.

Pretty simple to use, just include "buffer.h" and copy the code below, or
better, just check out buffer_example.c. 

'''
    // create the buffer container
    buffer_data *buff;
    buff = buffer_init(64); // make the initial size anything you want.
    
    // If things went well, we will have a buffer!
    if (buff != NULL) {
        ssize_t rtval = 0;
        int i;

        // original string
        for (i = 1; i < 100; ++i) {
            fprintf(stdout, "String: |%s|\n\n", buff->content);
            rtval = buffer_append(buff, "ABCDEFGH");
            if (rtval < 1) {
                fprintf(stderr, "Error appending, stopping!\n");
                exit(1);
            } else {
                fprintf(stdout, "appended %zd bytes of data\n", rtval);
            }
        }
    }
    
    // free the buffer
    buffer_destroy(buff);
'''

## License
MIT license. Copyright © 2015 Mike Curry