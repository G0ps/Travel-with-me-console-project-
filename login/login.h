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
                
                {    
                    string mobile_number;
                    string verification_password = "";
                    int option = -1;
                    while(option != 1)
                    {
                        cout << "\tEnter a valid mobile number : ";
                        cin >> mobile_number;
                
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        auto it = credentials::login_credentials::get_specific_data_as_copy(mobile_number);
                        if(get<0>(it) != "-1")
                        {
                            verification_password = get<1>(it);
                            break;
                        }
                        cout << "\t Enter 1 to exit or 2 to retry : ";
                        cin >> option;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    option = -1;
                    string password;
                    while(option != 1)
                    {
                        cout << "\tEnter a valid password: ";
                        cin >> password;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if(password == verification_password)
                        {
                            cout << "logged in\n";
                            break;
                        }
                        cout << "\t Enter 1 to exit or 2 to retry : ";
                        cin >> option;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } 
                }               
            }
        };
        
}
#endif