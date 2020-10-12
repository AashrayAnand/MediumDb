#include <iostream>
#include <string>
#include "../inc/memtable.h"
#include "../inc/kvnode.h"
#include "../inc/queryparser.h"
#include "../inc/queryexecutor.h"

#define MAX_INPUT_LENGTH 2048

int main(){
    while (true)
    {
        std::cout << "Enter a query (GET/SET)" << std::endl;
        std::string query;
        std::getline(std::cin, query);
        const char* cquery = query.c_str();
        qp.parse(cquery);
        if (qp.isValid())
        {
            if (qp.isGet())
            {
                const char* res = qe.Get(qp.Key());
                std::cout << "Key: " << qp.Key() << ", Value: " << (res == '\0' ? "NOT FOUND\0" : res) << std::endl;
            }
            else
            {
                qe.Set(qp.Key(), qp.Value());
            }
            
        }
    }
}