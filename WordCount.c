#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
int count_characters(FILE *file);
int count_words(FILE *file);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1];
    char *file_name = argv[2];

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    if (strcmp(parameter, "-c") == 0) {
        int char_count = count_characters(file);
        printf("字符数：%d\n", char_count);
    } else if (strcmp(parameter, "-w") == 0) {
        int word_count = count_words(file);
        printf("单词数：%d\n", word_count);
    } else {
        fprintf(stderr, "Invalid parameter. Use -c for character count or -w for word count.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int count_characters(FILE *file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

int count_words(FILE *file) {
    int count = 0;
    char ch;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        count++;
    }

    return count;
}
