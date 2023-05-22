# get_next_line

✅ Passed with **100**/100

My version of **get next line** School 42 project @ [Hive Helsinki](https://www.hive.fi/en/)

## Task summary

This project is about programming a function that returns a line read from a file descriptor.

- Repeated calls (e.g., using a loop) to your get_next_line() function should let you read the text file pointed to by the file descriptor, one line at a time.
- Your function should return the line that was read. If there is nothing else to read or if an error occurred, it should return NULL.
- Make sure that your function works as expected both when reading a file and when reading from the standard input.
- Please note that the returned line should include the terminating \n character, except if the end of file was reached and does not end with a \n character.
- Because you will have to read files in get_next_line(), add this option to your compiler call: -D BUFFER_SIZE=n. It will define the buffer size for read(). The buffer size value will be modified by your peer-evaluators and the Moulinette in order to test your code.
- We must be able to compile this project with and without the -D BUFFER_SIZE flag in addition to the usual flags. You can choose the default value of your choice.
- You will compile your code as follows (a buffer size of 42 is used as an example):

  `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`
