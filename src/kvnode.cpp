#include "../inc/kvnode.h"

kvnode::kvnode(char* keyArg, char* valArg):
    left(nullptr),
    right(nullptr)
{
    // Get arg lengths
    int keyLen = strlen(keyArg);
    int valLen = strlen(valArg);

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

// This key is equal to other key if strcmp is 0
// and the string lengths are the same
bool
kvnode::operator==(const kvnode& other)
{
    return keyEqual(key, other.Key());
}

// This key is lesser than other key if strcmp is negative,
// or if strcmp is zero and this key length is shorter than other
bool
kvnode::operator<(const kvnode& other)
{
    return keyLess(key, other.Key());
}

// This key is greater than other key if strcmp is positive,
// or if strcmp is zero and this key length is longer than other
bool
kvnode::operator>(const kvnode& other)
{
    return keyGreater(key, other.Key());
}