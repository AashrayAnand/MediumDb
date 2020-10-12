#include "../inc/queryexecutor.h"

void
queryexecutor::Set(char* key, char* value)
{
    mt.set(key, value);
}

char*
queryexecutor::Get(char* key)
{
    return mt.get(key);
}