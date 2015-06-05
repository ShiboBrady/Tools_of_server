#include "Confaccess.h"
#include <fstream>

#define MAX_LINE 1024
using namespace std;

pthread_once_t CConfAccess::once_ = PTHREAD_ONCE_INIT;
CConfAccess* CConfAccess::pInstance_ = NULL;

//Trim space in the beginning and ending of the string.
string StrTrim(const string& strOriginal)
{
     static const char* whiteSpace = " \t\r\n";

     if (strOriginal.empty())
     {
        return strOriginal;
     }

     string::size_type uFrontPos = strOriginal.find_first_not_of(whiteSpace);

     if (string::npos == uFrontPos)
     {
        return "";
     }

     string::size_type uRearPos = strOriginal.find_last_not_of(whiteSpace);

     return string(strOriginal, uFrontPos, uRearPos - uFrontPos + 1);
}

bool CConfAccess::Load(const string& filename)
{
    ifstream initFile(filename.c_str());
    if (!initFile)
    {
        return false;
    }

    string strLine;
    while (getline(initFile, strLine))
    {   
        if ("" == StrTrim(strLine))
        {
            continue;
        }

        string::size_type uPos = strLine.find("#");
        if (uPos > 0 || (string::npos == uPos))
        {
            strLine = strLine.substr(0, uPos);
        }
        else
        {
            continue;
        }

        uPos = strLine.find("=");
        if (string::npos == uPos)
        {
            continue;
        }

        string strKey = StrTrim(strLine.substr(0, uPos));
        string strValue = StrTrim(strLine.substr(uPos + 1));
        
        mapKeyValue_[strKey] = strValue;
    }

    return true;
}

string CConfAccess::GetValue(const string& strKey)
{
    if (strKey.empty() || (mapKeyValue_.end() == mapKeyValue_.find(strKey)))
    {
        return "";
    }

    return mapKeyValue_[strKey];
}
