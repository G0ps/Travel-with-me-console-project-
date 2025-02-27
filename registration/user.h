#ifndef user_H
#define user_H

#include <bits/stdc++.h>

using namespace std;

namespace user
{   
    class user{
            string name;
            string mobile_number; // alias id
            string user_type = "user";
            public:
            
            user(){}
            void create_user(string name , string number){
                this->name = name;
                this->mobile_number = number;
            }
            void set_user_type(string s)
            {
                this->user_type = s;
            }
            string get_name()
            {
                return this->name;
            }
            string get_mobile()
            {
                return this->mobile_number;
            }
            string get_user_type()
            {
                return this->user_type;
            }
            void print_user()
            {
                cout << "\n";
                cout <<"\tname - "<<name <<"\n";
                cout <<"\tmobile_number - "<<mobile_number <<"\n";
                cout <<"\ttype - "<<user_type <<"\n";
            }
        };
}
#endif