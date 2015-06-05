#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <json/json.h>

using namespace std;

bool ParseJson(const string& strJson);

int main()
{
    ifstream in;
    in.open("json.txt");
    if (!in)
    {
        cout << "Open file failed!" << endl;
        return 1;
    }
    stringstream ssJson;
    string strLine;
    string strJson;
    while (in >> strLine)
    {
        ssJson << strLine;
    }
    strJson = ssJson.str();
    cout << "Json is : " << strJson << endl;
    in.close();
    if (!ParseJson(strJson))
    {
        cout << "Parse json string failed! " << endl;
        return 1;
    }
    return 0;
}

bool ParseJson(const string& strJson)
{
    Json::Reader reader;
    Json::Value jsonInput;

    //Transcate to json format.
    bool isSuccess = reader.parse(strJson, jsonInput);

    if (!isSuccess)
    {
        cout << "Post data is not json format !" << endl;
        return false;
    }
    if (!jsonInput["code"].isString())
    {
        cout << "Can't get code value." << endl;
        return false;
    }
    if (!jsonInput["subcode"].isString())
    {
        cout << "Can't get subcode value." << endl;
        return false;
    }

    //Get code and subcode.
    std::string strCode  = jsonInput["code"].asString();
    std::string strSubCode = jsonInput["subcode"].asString();
    
    cout << "code: " << strCode << endl;
    cout << "subcode: " << strSubCode << endl;

    const Json::Value& jsonValue = jsonInput["value"];
    int iValueSize = jsonValue.size();

    //Get parameter from each json object.
    for (int index = 0; index != iValueSize; index++)
    {
        if (!jsonValue[index]["id"].isString())
        {
            cout << "Can't get id value." << endl;
            return false;
        }
        if (!jsonValue[index]["value"].isString())
        {
            cout << "Can't get value." << endl;
            return false;
        }
        string id = jsonValue[index]["id"].asString();
        string value = jsonValue[index]["value"].asString();

        cout << "id : " << id << endl;
        cout << "value : " << value << endl;
    }
    return true;
}