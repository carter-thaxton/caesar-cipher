# caesar-cipher
Implementation of the simple caesar cipher in C++

## Build
    g++ -o caesar_cipher caesar_cipher.cpp
 
## Run
This will analyze the letter frequencies of the input file, and decode it automatically

    ./caesar_cipher < test.txt

This will shift every letter by 3

    ./caesar_cipher -s 3 < test.txt
