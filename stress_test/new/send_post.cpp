#include "send_post.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <json/json.h>
#include "http.h"

using namespace std;

int send_post()
{
    Json::Value jsonValue;
    jsonValue["code"] = Json::Value(1);

    Json::Value jsonPhoneNumValue;
    Json::Value jsonPasswordValue;
    Json::Value jsonVerificationValue;

    jsonPhoneNumValue["key"] = Json::Value("mobile");
    jsonPhoneNumValue["value"] = Json::Value("13600000000");

    jsonPasswordValue["key"] = Json::Value("password");
    jsonPasswordValue["value"] = Json::Value("12345");

    jsonVerificationValue["key"] = Json::Value("idcode");
    jsonVerificationValue["value"] = Json::Value("123456");

    jsonValue["attribute"].append(jsonPhoneNumValue);
    jsonValue["attribute"].append(jsonPasswordValue);
    jsonValue["attribute"].append(jsonVerificationValue);

    Json::FastWriter writer;
    string strRequest = writer.write(jsonValue);
    cout << "Json string is : " << strRequest << endl;

    string strReply;
    string strUrl = "http://172.19.180.166/fcgi-bin/rs";

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
