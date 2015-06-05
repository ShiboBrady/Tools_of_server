#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "send_post.h"

using namespace std;

unsigned int count = 0;
pthread_mutex_t mutex;
void* ThreadFunc(void* argv)
{
    pthread_detach(pthread_self());
    
    while (1)
    {

        //send a post requrest.
        send_post();

        //sleep 0.1s
        //usleep(100000);
        
        pthread_mutex_lock(&mutex);
        ++count;
        cout << count << endl;
        pthread_mutex_unlock(&mutex);
    }
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage : exe + thread_num + minutes." << endl;
        return 1;
    }
    pthread_mutex_init(&mutex, NULL);

    int iThreadNum = ::atoi(argv[1]); 
    cout << "Thread num is : " << argv[1] << endl;

    int iMinutes = ::atoi(argv[2]);
    cout << "Program running time is : " << argv[2] << "minutes." << endl;
    
    pthread_t* pthread_id = new pthread_t[iThreadNum];

    for (int iIndex = 0; iIndex != iThreadNum; ++iIndex)
    {
        pthread_create(pthread_id + iIndex, NULL, ThreadFunc, NULL);    
        printf("Create a thread [ %u ]\n", pthread_id[iIndex]);
    }
    //pthread_join(pthread_id[1], NULL);
   // `sleep(iMinutes * 60);
   while(1);
    return 0;
}
