#pragma once
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <mutex>

#include "../inc/kvnode.h"

class memtable {
public:
    memtable(): 
        root(nullptr), 
        numEntries(0), 
        numBytes(0)
    {};

    void set(char* key, char* value);
    char* get(char* key);
    void remove(char* key);
    int Size();
    int NumBytes();
private:
    std::mutex tableMtx;
    kvnode* setHelp(kvnode* curr, kvnode* newEntry);
    char* getHelp(kvnode* curr, char* key);
    // Total number of k-v pairs in table
    int numEntries;
    // Total byte size of mem table
    int numBytes;
    kvnode* root;

    // TODO: add static instances of log manager and
    // disk manager, which respectively handle appending
    // to write-only log, and reading sorted segment tables
    // (memtables which have been flushed to disk)
    // static logmanager logmgr;
    // static diskmanager diskmgr;
};

// Memtable component
static memtable mt;