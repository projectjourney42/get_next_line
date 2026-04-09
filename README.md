*This project has been created as part of the 42 curriculum by **haranivo**.*

# get_next_line

## Description
The main goal of the 42 cursus GNL (Get Next Line) project is to teach an important concept in C programming: static variables.

This project implements the `get_next_line` function, which reads a file descriptor line by line and returns each line as a dynamically allocated string. The goal is to manage buffered reading, handle partial lines across multiple `read()` calls, and preserve any leftover content for subsequent calls. 


The repository includes both the mandatory version and the bonus version. The bonus version supports reading from multiple file descriptors independently.

The bonus part of the `get_next_line` function enhances its capability to handle multiple file descriptors by using a **static char \*stock[1024]** to store data for up to 1024 file descriptors independently. For each read operation, it checks if the file descriptor is valid and initializes the corresponding buffer if necessary. It then adds data to the buffer and extracts the line depending on the file being read, ensuring the function correctly handles data from multiple files simultaneously and returns the appropriate line for each file descriptor.


## Files

- `get_next_line.h`
- `get_next_line.c`
- `get_next_line_utils.c`

**Bonus part :**
- `get_next_line_bonus.h`
- `get_next_line_bonus.c`
- `get_next_line_utils_bonus.c`

## Instructions

### Compilation

Compile the mandatory version with:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42
```

Compile the bonus version with:

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c -D BUFFER_SIZE=42
```

> You can adjust `BUFFER_SIZE` via the `-D BUFFER_SIZE=<value>` compile-time definition.

### Execution

Use the compiled executable in a test program or manually call `get_next_line()` from a C program that opens a file descriptor.

Example usage in a simple test program:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return 1;
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## Algorithm

The implementation uses a buffered read strategy with the following behavior:

1. A static buffer (`stock`) is preserved between calls to keep leftover data after a newline.
2. On each call, the function reads from the file descriptor into a temporary buffer of size `BUFFER_SIZE` until a newline is found or no more bytes are available.
3. Read fragments are joined into the stored `stock` string using a custom `ft_strjoin` implementation.
4. When a newline character is found, the function splits `stock` into the returned line and the remaining substring.
5. If the end of file is reached without a newline, the remaining content is returned as the last line.
6. In the bonus version, a separate static buffer is maintained for each file descriptor, allowing simultaneous reads from multiple descriptors.

### Justification

This algorithm is chosen because it is efficient and safe for the `get_next_line` requirements:

- It avoids loading the full file into memory at once.
- It handles lines longer than `BUFFER_SIZE` by accumulating fragments until a newline appears.
- It preserves partial reads between function calls, ensuring correct boundary handling.
- The bonus implementation extends this logic to multiple file descriptors by using a separate static buffer per `fd`.

## Resources

- 42 project instructions and evaluation criteria for `get_next_line`
- `read()` documentation
- General tutorials on buffered file reading in C, static variables and get next line principals :
    - [read() principals](https://www.youtube.com/watch?v=w0mgn6OLKUs)
    - [Static variables](https://www.youtube.com/watch?v=OngGUoENgWo)
    - [Understand get_next_line](https://www.youtube.com/watch?v=-Mt2FdJjVno&list=PLPqnnyLDYcuGXkdP_yK63cA-GSwdgb7vm)
- Peer-to-peer : 42 school mindset

### AI usage
- Clarifying the project requirements and expectations.
- Assisting in restructuring the code to meet coding standards.
- Providing insights into memory leak principles.
- Explaining the advantages of heap vs. stack memory.
- AI assistance was used to structure and write this README, summarize the project behavior.

**Author**: [@haranivo]()
<center>
    Thanks for reading ME <3 <br>
    <b>2026-04-08</b>
</center>