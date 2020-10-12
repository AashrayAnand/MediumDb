#include "../inc/queryparser.h"

queryparser::queryparser(): 
    valid(false), 
    get(false), 
    key(nullptr), 
    value(nullptr)
{}

void
queryparser::parse(const char* input)
{
    valid = true;
    get = false;
    key = nullptr;
    value = nullptr;

    // Buffer to read operator to, will be static
    // length of 3 (either "get" or "set")
    char op[OPLEN + 1];

    // Get length of operator to read to buffer
    int opLen = 0;
    while (input[opLen] != '\0' && !std::isspace(input[opLen]))
    {
        opLen++;
    }

    if (opLen != OPLEN)
    {
        valid = false;
        std::cout << "Operator must be \"get\" or \"set\"" << std::endl;
        return;
    }

    strncpy(op, input, OPLEN);
    op[OPLEN] = '\0';

    const char* getOp = "GET\0";
    const char* setOp = "SET\0";

    if (strncasecmp(op, getOp, OPLEN) == 0){
        get = true;
    }
    else if (strncasecmp(op, setOp, OPLEN) == 0)
    {
        get = false;
    }
    else
    {
        valid = false;
        std::cout << "Operator must be \"get\" or \"set\"" << std::endl;
        return;
    }

    // Check that input includes more than just operator
    if (input[opLen] == '\0' || input[opLen + 1] == '\0')
    {
        valid = false;
        std::cout << "Must provide key/value in addition to operator" << std::endl;
        return;
    }

    opLen++;

    // Want to start copying characters from input where key starts
    int keyStart = opLen;

    while (input[opLen] != '\0' && !std::iswspace(input[opLen]))
    {
        opLen++;
    }

    // Length of key is current idx being read from input - start of key idx
    int keyLen = opLen - keyStart;

    // Write key to buffer
    key = new char[keyLen];
    strncpy(key, input + keyStart, keyLen);

    // No value to read if this is get operation
    if (get){
        std::cout << "GET request, Key: " << key << std::endl;
        return;
    }

    if (input[opLen] == '\0' || input[opLen + 1] == '\0')
    {
        valid = false;
        std::cout << "Must provide value in addition to key for set operation" << std::endl;
        return;
    }

    opLen++;

    // Want to start copying characters from input where value starts
    int valueStart = opLen;

    while (input[opLen] != '\0' && !std::iswspace(input[opLen]))
    {
        opLen++;
    }

    // Length of key is current idx being read from input - start of key idx
    int valLen = opLen - valueStart;

    // Write key to buffer
    value = new char[valLen];
    strncpy(value, input + valueStart, valLen);
    std::cout << "SET request, Key: " << key << ", Value: " << value << std::endl;
}

char*
queryparser::Key()
{
    return key;
}

char*
queryparser::Value()
{
    return value;
}

bool
queryparser::isGet()
{
    return get;
}

bool
queryparser::isValid()
{
    return valid;
}