#include "../inc/utils.h"

bool keyEqual(char* key1, char* key2)
{
    int key1Len = strlen(key1);
    int key2Len = strlen(key2);
    int strComp = strncasecmp(key1, key2, std::min(key1Len, key2Len));
    return strComp == 0 && key1Len == key2Len;
}

bool keyGreater(char* key1, char* key2)
{
    int key1Len = strlen(key1);
    int key2Len = strlen(key2);
    int strComp = strncasecmp(key1, key2, std::min(key1Len, key2Len));
    return strComp > 0 || (strComp == 0 && key1Len > key2Len);
}

bool keyLess(char* key1, char* key2)
{
    int key1Len = strlen(key1);
    int key2Len = strlen(key2);
    int strComp = strncasecmp(key1, key2, std::min(key1Len, key2Len));
    return strComp < 0 || (strComp == 0 && key1Len < key2Len);
}