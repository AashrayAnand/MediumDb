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
    //std::lock_guard<std::mutex> writerLock(tableMtx);
    root = setHelp(root, key, value);
}

kvnode*
memtable::setHelp(kvnode* curr, char* key, char* value)
{
    if (curr == nullptr)
    {
        numEntries++;
        numBytes+= strlen(key);
        numBytes+= strlen(value);
        return new kvnode(key, value);
    }

    if (keyGreater(curr->Key(), key))
    {
        curr->left = setHelp(curr->left, key, value);
    }
    else if (keyLess(curr->Key(), key))
    {
        curr->right = setHelp(curr->right, key, value);
    }
    else
    {
        std::cout << "repeat value " << key << std::endl;
        kvnode* updatedEntry = new kvnode(key, value);
        updatedEntry->left = curr->left;
        updatedEntry->right = curr->right;
        curr = updatedEntry;
    }

    return curr;
}
    
char*
memtable::get(char* key)
{
    //std::lock_guard<std::mutex> readerLock(tableMtx);
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
    if (keyEqual(currKey, key))
    {
        return curr->Value();
    }
    
    if (keyGreater(currKey, key))
    {
        return getHelp(curr->left, key);
    }
    if (keyLess(currKey, key))
    {
        return getHelp(curr->right, key);
    }

    return "\0";
}
    
void 
memtable::remove(char* key){

}