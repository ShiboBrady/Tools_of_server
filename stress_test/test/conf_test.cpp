#include <iostream>
#include "Confaccess.h"

using namespace std;

int main(int argc, const char *argv[])
{
    CConfAccess* conf = CConfAccess::getInstance();
    conf->Load("./conf/main.conf");
    cout << conf->GetValue("method") << endl;
    cout << conf->GetValue("domain") << endl;;
    return 0;
}
