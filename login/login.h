#ifndef login_H
#define login_H

#include<bits/stdc++.h>

#include "../credentials/login_credentials.h"
//use as copy
#include "../application/application.h"
// after declaring use run

using namespace std;
namespace login
{   
    class login{
            public:
            login(){
                credentials::login_credentials l;
                application::application a;
                a.run();
            }
        };
}
#endif