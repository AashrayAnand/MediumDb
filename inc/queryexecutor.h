#pragma once
#include <wchar.h>
#include <iostream>

#include "../inc/kvnode.h"
#include "../inc/memtable.h"

class queryexecutor {
public:
    void Set(char* key, char* value);
    char* Get(char* key);
};

// Query executor component
static queryexecutor qe;
static queryexecutor qv;