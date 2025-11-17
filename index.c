#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD 10000
#define MAX_LEN 1000
#define MAX_LINE_LEN 10000
#define MAX_LINE_LIST 3000

typedef struct {
    char word[MAX_LEN];
    int count;                // số lần xuất hiện
    char lines[MAX_LINE_LIST]; // các số dòng
} IndexItem;

IndexItem indexList[MAX_WORD];
int indexCount = 0;

char stopWords[MAX_WORD][MAX_LEN];
int stopCount = 0;

int isStopWord(const char *w) {
    for (int i = 0; i < stopCount; i++)
        if (strcmp(w, stopWords[i]) == 0) return 1;
    return 0;
}

void toLowerStr(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

int isProperNoun(const char *original, char prev) {
    return (isupper(original[0]) && prev != '.');
}

int findWord(const char *w) {
    for (int i = 0; i < indexCount; i++)
        if (strcmp(indexList[i].word, w) == 0) return i;
    return -1;
}

void addWord(const char *w, int line) {
    int pos = findWord(w);

    char lineStr[12];
    snprintf(lineStr, sizeof(lineStr), "%d", line);

    if (pos == -1) {
        strncpy(indexList[indexCount].word, w, MAX_LEN - 1);
        indexList[indexCount].count = 1;
        strncpy(indexList[indexCount].lines, lineStr, MAX_LINE_LIST - 1);
        indexCount++;
    } else {
        indexList[pos].count++;
        if (strlen(indexList[pos].lines) + strlen(lineStr) + 3 < MAX_LINE_LIST) {
            strcat(indexList[pos].lines, ", ");
            strcat(indexList[pos].lines, lineStr);
        }
    }
}

int cmp(const void *a, const void *b) {
    return strcmp(((IndexItem*)a)->word, ((IndexItem*)b)->word);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Cách dùng: %s <file_van_ban>\n", argv[0]);
        return 1;
    }

    FILE *fs = fopen("stopw.txt", "r");
    FILE *fv = fopen(argv[1], "r");

    if (!fs) {
        printf("Không mở được stopw.txt\n");
        return 1;
    }
    if (!fv) {
        printf("Không mở được file văn bản: %s\n", argv[1]);
        return 1;
    }

    while (fscanf(fs, "%999s", stopWords[stopCount]) != EOF) {
        toLowerStr(stopWords[stopCount]);
        stopCount++;
    }
    fclose(fs);

    char line[MAX_LINE_LEN];
    int lineNum = 0;

    while (fgets(line, sizeof(line), fv)) {
        lineNum++;
        int len = strlen(line);

        char word[MAX_LEN];
        int wi = 0;

        for (int i = 0; i <= len; i++) {
            if (isalpha(line[i])) {
                if (wi < MAX_LEN - 1)
                    word[wi++] = line[i];
            } else {
                if (wi > 0) {
                    word[wi] = '\0';

                    char prev = (i > 0 ? line[i - 1] : ' ');

                    char wLower[MAX_LEN];
                    strncpy(wLower, word, MAX_LEN);
                    toLowerStr(wLower);

                    if (!isProperNoun(word, prev) && !isStopWord(wLower))
                        addWord(wLower, lineNum);

                    wi = 0;
                }
            }
        }
    }
    fclose(fv);

    qsort(indexList, indexCount, sizeof(IndexItem), cmp);

    FILE *fo = fopen("index.txt", "w");
    if (!fo) {
        printf("Không thể tạo file index.txt\n");
        return 1;
    }

    for (int i = 0; i < indexCount; i++) {
        printf("%-12s %d %s\n", indexList[i].word, indexList[i].count, indexList[i].lines);
        fprintf(fo, "%-12s %d %s\n", indexList[i].word, indexList[i].count, indexList[i].lines);
    }

    fclose(fo);
    printf("Đã xuất kết quả ra file: index.txt\n");
    return 0;
}
