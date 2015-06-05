#include <stdio.h>
#include <iostream>
#include <string>
#include <json/json.h>
#include "http.h"

using namespace std;

int main()
{
    Json::Value jsonValue;
    jsonValue["code"] = Json::Value("10");
    jsonValue["subcode"] = Json::Value("00");

    Json::Value jsonPhoneNumValue;
    Json::Value jsonPasswordValue;
    Json::Value jsonVerificationValue;

    jsonPhoneNumValue["name"] = Json::Value("phonenum");
    jsonPhoneNumValue["id"] = Json::Value("101");
    jsonPhoneNumValue["value"] = Json::Value("123456789");

    jsonPasswordValue["name"] = Json::Value("password");
    jsonPasswordValue["id"] = Json::Value("153");
    jsonPasswordValue["value"] = Json::Value("12345");

    jsonVerificationValue["name"] = Json::Value("verification");
    jsonVerificationValue["id"] = Json::Value("100");
    jsonVerificationValue["value"] = Json::Value("1234");

    jsonValue["value"].append(jsonPhoneNumValue);
    jsonValue["value"].append(jsonPasswordValue);
    jsonValue["value"].append(jsonVerificationValue);

    Json::FastWriter writer;
    string strRequest = writer.write(jsonValue);
    cout << "Json string is : " << strRequest << endl;

    string strReply;
    string strUrl = "https://api.weixin.qq.com/sns/oauth2/access_token?";

    //发送post请求类型的url
    cout << "url : " + strUrl << endl;
    CCurlWrapper curlWrapper;
    int iRet = curlWrapper.PostFile(strUrl, strRequest, strReply);
    if (0 != iRet)
    {
        cout << "Curl send post request failed!" << endl;
        printf("iRet = %d\n", iRet);
        return 1;
    }
    else
    {
        cout << "Curl send post request successed!" << endl;
    }
    cout << "reply : " + strReply << endl;
    return 0;
}