#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "send_post.h"
#include "Confaccess.h"
#include "timer.h"

using namespace std;

string strUrl;
string strRequest;
Timer timer(100);
pthread_mutex_t mutex;

void* ThreadFunc(void* argv)
{
    pthread_detach(pthread_self());
    
    while (1)
    {

        //send a post requrest.
        send_post();
        
        //add a tast finished number to timer.
        pthread_mutex_lock(&mutex);
        timer.add();
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

bool ConfInit()
{
    CConfAccess* conf = CConfAccess::getInstance();
    if (!conf->Load("../conf/main.conf"))
    {
        cout << "Configure file load failed!" << endl;
        return false;
    }

    strUrl = conf->GetValue("protocol") + "://" + conf->GetValue("domain") + conf->GetValue("path");

    cout << "URL is : " << strUrl <<  endl;

    ifstream initFile(conf->GetValue("data").c_str());
    if (!initFile)
    {
        cout << "Cannot open file: " << conf->GetValue("data") << endl;
        return false;
    }

    string strLine;
    stringstream ssStr;
    while (getline(initFile, strLine))
    {
        ssStr << strLine;
    }
   
    strRequest = ssStr.str();
    
    cout << "Request data is : " << strRequest << endl;
    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage : exe + thread_num + minutes." << endl;
        return 1;
    }

    int iThreadNum = ::atoi(argv[1]); 
    cout << "Thread num is : " << argv[1] << endl;

    int iMinutes = ::atoi(argv[2]);
    cout << "Program running time is : " << argv[2] << "minutes." << endl;

    if (!ConfInit())
    {
        cout << "Init configure failed!" << endl;
        return 1;
    }
    
    pthread_mutex_init(&mutex, NULL);

    timer.begin();

    srand(time(NULL));

    pthread_t* pthread_id = new pthread_t[iThreadNum];

    for (int iIndex = 0; iIndex != iThreadNum; ++iIndex)
    {
        pthread_create(pthread_id + iIndex, NULL, ThreadFunc, NULL);    
        printf("Create a thread [ %lu ]\n", pthread_id[iIndex]);
    }

    char buffer[1024];
    //while(NULL != fgets(buffer, 1024, stdin));
    while (1);

    timer.end();
    //sleep(iMinutes * 60);
    return 0;
}
