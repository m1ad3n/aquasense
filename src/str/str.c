#include "../deps.h"
#include "str.h"

char* sReadDataFromFile(const char* _path) {
    FILE* fptr;
    fptr = fopen(_path, "r");
    if (!fptr) {
        fprintf(stderr, "FILE ERROR: Failed to open %s\n", _path);
        return NULL;
    }
    
    fseek(fptr, 0, SEEK_END);
    size_t fSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char* data = NULL;
    data = (char*)malloc(fSize + 1);
    
    fread(data, fSize, 1, fptr);
    fclose(fptr);

    data[fSize] = '\0';
    return data;
}

void seperateTextWithSub(char* _text, char* _sub, char** _first, char** _second) {
    if (_text == NULL) return;

    char* found = strstr(_text, _sub);
    size_t pos = found - _text;

    // first part
    *_first = (char*)malloc(pos + 1);
    strncpy(*_first, _text, pos);
    (*_first)[pos] = '\0';

    // second part
    *_second = strdup(found);
}

char* newPath(int count, ...) {
    int os = 1;
    va_list list;
    char* path = (char*)malloc(1);
    char* sep = (char*)malloc(3);
    
    path[0] = '\0';
    sep[0] = '/';
    sep[1] = '\0';

#ifdef _WIN32
    os++;
    sep[0] = '\\';
    sep[1] = '\\';
    sep[2] = '\0';
#endif

    va_start(list, count);

    for (int i = 0; i < count; i++) {
        char* tmp = va_arg(list, char*);
        path = (char*)realloc(path, strlen(path) + strlen(tmp) + 1);
        strcat(path, tmp);
        strcat(path, sep);
    }

    path[strlen(path) - os] = '\0';
    va_end(list);
    free(sep);

    return path;
}