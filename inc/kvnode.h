#pragma once
#include <wchar.h>
#include <algorithm>
#include <iostream>

class kvnode {
public:
    kvnode(char *key, char* value);
    ~kvnode();
    char* Key() const;
    char* Value() const;
    
    bool operator<(const kvnode& other);
    bool operator>(const kvnode& other);
    kvnode* left;
    kvnode* right;
private:
    char* key;
    char* value;
};