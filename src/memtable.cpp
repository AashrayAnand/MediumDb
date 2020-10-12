#include "../inc/memtable.h"

int
memtable::Size()
{
    return numEntries;
}

int
memtable::NumBytes()
{
    return numBytes;
}

void 
memtable::set(char* key, char* value)
{
    std::lock_guard<std::mutex> writerLock(tableMtx);
    root = setHelp(root, new kvnode(key, value));
}

kvnode*
memtable::setHelp(kvnode* curr, kvnode* newEntry)
{
    if (curr == nullptr)
    {
        numEntries++;
        numBytes += strlen(newEntry->Key());
        numBytes += strlen(newEntry->Value());
        return newEntry;
    }

    if (curr > newEntry)
    {
        curr->left = setHelp(curr->left, newEntry);
    }
    else if (curr < newEntry)
    {
        curr->right = setHelp(curr->right, newEntry);
    }
    else
    {
        newEntry->left = curr->left;
        newEntry->right = curr->right;
        curr = newEntry;
    }
    return curr;
}
    
char*
memtable::get(char* key)
{
    std::lock_guard<std::mutex> readerLock(tableMtx);
    return getHelp(root, key);
}

char*
memtable::getHelp(kvnode* curr, char* key)
{
    if (curr == nullptr)
    {
        return nullptr;
    }

    char* currKey = curr->Key();
    int currKeyLen = strlen(currKey);
    int searchKeyLen = strlen(key);
    int strComp = strncasecmp(currKey, key, std::min(currKeyLen, searchKeyLen));
    if (strComp == 0 && currKeyLen == searchKeyLen)
    {
        return curr->Value();
    }
    
    if (strComp > 0 || (strComp == 0 && currKeyLen > searchKeyLen))
    {
        return getHelp(curr->left, key);
    }
    if (strComp < 0 || (strComp == 0 && currKeyLen > searchKeyLen))
    {
        return getHelp(curr->right, key);
    }

    return '\0';
}
    
void 
memtable::remove(char* key){

}