#include <stdio.h>
#include <stdlib.h>

int main() {
    long long int wordCount = 0, lineCount = 0, byteCount = 0, longestWordLength = 0, length = 0;
    int input = 0;
    int inWord = 0;
    while ((input = getchar()) != EOF){
        ++byteCount;
        if((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z') || (input >= '0' && input <= '9')){
            inWord = 1;
            ++length;
            if(longestWordLength < length)
                longestWordLength = length;
        } else {
            length = 0;
            if(inWord == 1){
                ++wordCount;
                inWord = 0;
            }
            if(input == '\n')
                ++lineCount;
        }
    }
    printf("Longest Word Length: %lld\n", longestWordLength);
    printf("Word Count: %lld\n", wordCount);
    printf("Line Count: %lld\n", lineCount);
    printf("Byte Count: %lld\n", byteCount);
    return 0;
}
