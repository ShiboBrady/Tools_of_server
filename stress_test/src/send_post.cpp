#include "send_post.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "json/json.h"
#include "http.h"
#include "Confaccess.h"

using namespace std;

extern string strUrl;
extern string strRequest;

void GetMobile(char* strMobile)
{
    const static char* strHead = "136";
    strcat(strMobile, strHead);
    int iStart = 3;
    int iEnd = 11;
    for (int iIndex = iStart; iIndex != iEnd; ++iIndex)
    {
        strMobile[iIndex] = rand() % 10 + '0';
    }
    strMobile[iEnd] = 0;
}

void GetData(char* strData)
{
    Json::Value jsonValue;
    jsonValue["code"] = Json::Value(1);

    Json::Value jsonPhoneNumValue;
    Json::Value jsonPasswordValue;
    Json::Value jsonVerificationValue;

    char strMobile[12] = {0};
    GetMobile(strMobile);
    jsonPhoneNumValue["key"] = Json::Value("mobile");
    jsonPhoneNumValue["value"] = Json::Value(strMobile);

    jsonPasswordValue["key"] = Json::Value("password");
    jsonPasswordValue["value"] = Json::Value("12345");

    jsonVerificationValue["key"] = Json::Value("idcode");
    jsonVerificationValue["value"] = Json::Value("565099");

    jsonValue["attribute"].append(jsonPhoneNumValue);
    jsonValue["attribute"].append(jsonPasswordValue);
    jsonValue["attribute"].append(jsonVerificationValue);

    Json::FastWriter writer;
    std::string strJson = writer.write(jsonValue);
    std::cout << "Json string is : " << strJson << std::endl;

    strcpy(strData, strJson.c_str());
}
bool send_post()
{
    string strReply;
    char strData[1024] = {0};
    GetData(strData);
    //发送post请求类型的url
    CCurlWrapper curlWrapper;
    int iRet = curlWrapper.PostFile(strUrl, string(strData), strReply);
    if (0 != iRet)
    {
        cout << "Curl send post request failed!" << endl;
        printf("iRet = %d\n", iRet);
        return false;
    }
    else
    {
        cout << "Curl send post request successed!" << endl;
    }
    cout << "reply : " + strReply << endl;
    return true;
}
