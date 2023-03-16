#include"string_transforme.h"

#include<string>
using namespace string_transforme;

void string_transforme::en_maj(std::string& str)
{
    for(unsigned i=0 ; i<str.size() ; i++)
        str[i]=toupper(str[i]);
}
void string_transforme::en_min(std::string& str)
{
    for(unsigned i=0 ; i<str.size() ; i++)
        str[i]=tolower(str[i]);
}
