#ifndef registration_H
#define registration_H

#include<bits/stdc++.h>

#include "../credentials/login_credentials.h"
#include "create_user.h"
#include "create_colaborator.h"
#include "create_premium_user.h"

using namespace std;
namespace registration{
    class registration{
        public:
        registration(){
            reg();
        }
        void reg()
        {
            string name;
            string mobile_number;

            cin >> name;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    };
}
#endif