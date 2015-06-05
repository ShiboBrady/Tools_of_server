#ifndef _HTTP_H_
#define _HTTP_H_

#include <string>
#include <set>
#include <curl/curl.h>

class CCurlWrapper
{
public:
    CCurlWrapper ();
    ~CCurlWrapper ();

    int PostFile (const std::string& strUrl, const std::string& strRequest, std::string& strReply);
    int GetFile (const std::string& strUrl, std::string& strReply);
    void AddHttpHeader (const std::string& strHeader);

private:
    int Init ();
    static size_t WriteDataCallback (void *ptr, size_t size, size_t nCount, void *pData);

    CURL *m_pCurl;
    std::set<std::string> m_setHeaders;

};


#endif

