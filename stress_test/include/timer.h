#ifndef _TIMER_H_  
#define _TIMER_H_  
#include <string>  
#include <fstream>
#include <sys/time.h>  

using namespace std;  

class Timer{  
private:
        timeval tstart;  
        timeval tend;  
        unsigned count;  
        unsigned print_count;  
        ofstream output;

        void OpenFile();
public:  
        Timer():count(0),print_count(10000){  
            OpenFile();
        }  
        Timer(int pc):count(0),print_count(pc){  
            OpenFile();
        }  
        ~Timer(){ output.close(); }

        void add(){  
                count++;  
                if(count % print_count == 0){  
                        end();  
                        begin();  
                }  
        }  
        void begin(){  
                gettimeofday(&tstart, NULL);  
        }  
        void end(){  
                gettimeofday(&tend, NULL);  
                double linStart = ((double)tstart.tv_sec * 1000000 + (double)tstart.tv_usec);   //unit S  
                double linEnd = ((double)tend.tv_sec * 1000000 + (double)tend.tv_usec);         //unit S  
                double delta = (linEnd-linStart)/1000000;                                       //second  
                output << "Timer : " << print_count << " " << count << " " << delta << " " << print_count/delta << endl;
        }  
};  

void Timer::OpenFile()
{
    output.open("timer.txt", ios::ate|ios::out);
    if (!output)
    {
        printf("Create file failed!");
        exit(-1);
    }
    output << "       " << "count" << " " << "total" << " " << "time" << " " << "frequence" << endl;
}
#endif /*_TIMER_H_*/  
