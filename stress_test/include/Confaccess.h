#ifndef __CONFACCESS_H__ 
#define __CONFACCESS_H__ 

#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <map>

class CConfAccess
{
    public:
        static CConfAccess* getInstance()
        {
            pthread_once(&once_, &initInstance);
            return pInstance_;
        }

        static void initInstance()
        {
            ::atexit(&destoryInstance);
            pInstance_ = new CConfAccess;
        }

        static void destoryInstance()
        {
            delete pInstance_;
        }

        bool Load(const std::string& filename);

        std::string GetValue(const std::string& strKey);

    private:
        CConfAccess() {};
        CConfAccess(const CConfAccess&);
        void operator=(const CConfAccess&);

        static CConfAccess* pInstance_;
        static pthread_once_t once_;

        std::map<std::string, std::string> mapKeyValue_; 
};


#endif //__CONFACCESS_H__ 
