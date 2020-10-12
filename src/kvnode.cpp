#include "../inc/kvnode.h"

kvnode::kvnode(char* keyArg, char* valArg)
{
    // Get arg lengths
    int keyLen = strlen(keyArg);
    std::cout << keyLen << std::endl;
    int valLen = strlen(valArg);
    std::cout << valLen << std::endl;

    // Create buffer for key and copy key arg
    key = new char[keyLen];
    strncpy(key, keyArg, keyLen);

    // Create buffer for value and copy value arg
    value = new char[valLen];
    strncpy(value, valArg, valLen);
}

kvnode::~kvnode()
{
    delete[] key;
    delete[] value;
}

// Getters

char*
kvnode::Key() const
{
    return key;
}

char*
kvnode::Value() const
{
    return value;
}

// Comparison operators

// This key is lesser than other key if strcmp is negative,
// or if strcmp is zero and this key length is shorter than other
bool
kvnode::operator<(const kvnode& other)
{
    char* otherKey = other.Key();
    int minKeyLength = std::min(strlen(key), strlen(otherKey));
    int strComp = strncasecmp(key, otherKey, minKeyLength);
    return strComp < 0 || (strComp == 0 && strlen(key) < strlen(otherKey));
}

// This key is greater than other key if strcmp is positive,
// or if strcmp is zero and this key length is longer than other
bool
kvnode::operator>(const kvnode& other)
{
    char* otherKey = other.Key();
    int minKeyLength = std::min(strlen(key), strlen(otherKey));
    int strComp = strncasecmp(key, otherKey, minKeyLength);
    return strComp > 0 || (strComp == 0 && strlen(key) > strlen(otherKey));
}