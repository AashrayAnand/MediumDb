#pragma once
#include <wchar.h>
#include <iostream>

#define OPLEN 3

class queryparser {
public:
    queryparser();

    char* Key();
    char* Value();
    bool isGet();
    bool isValid();
    void parse(const char* input);
private:
    bool valid;
    bool get;
    char* key;
    char* value;
};

// Query parser component
static queryparser qp;