#ifndef registration_H
#define registration_H

#include<bits/stdc++.h>

#include "../credentials/login_credentials.h"
#include "user.h"

using namespace std;
namespace registration{
    class registration{
        public:
        registration(){
            int option = 1;
            cout << R"(
            Option 1 - Register as a user
            Option 2 - Register as a Colaborator
            )";
            cout << "\n\tEnter  Option : ";
            if (!(cin >> option)) {  // Input validation
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
            }
            user::user u = reg();
            if(option == 2)
            {
                u.set_user_type("colaborator");
            }
            string password = "";
            while(true)
            {
                cout << "\tEnter a password : ";
                cin >> password;
                if(password != "")
                {
                    break;
                }
            }
            credentials::login_credentials::overwrite_login_credentials(u.get_mobile() , password , u.get_user_type());
            // u.print_user();
        }


        user::user reg()
        {
            string name;
            string mobile_number;

            do {
                cout << "\tEnter name : ";
                cin >> name;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos);
            

            do{
                cout << "\tEnter valid mobile number : ";
                cin >> mobile_number;
            } while(mobile_number.length() != 10 || mobile_number.find_first_not_of("0123456789") != string::npos || get<0>(credentials::login_credentials::get_specific_data_as_copy(mobile_number)) != "-1");
            
            
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            user::user c;
            c.create_user(name , mobile_number);
            return c;
        }
    };
}
#endif