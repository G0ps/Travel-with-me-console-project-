#ifndef application_interface_H
#define application_interface_H

#include<bits/stdc++.h>

using namespace std;
namespace application_interface
{   
    class application_interface{
            public:
            application_interface(){}

            //normal user
            virtual void book_buses(string id) = 0;
            virtual void write_review(string id) = 0;
            virtual void become_premium(string id) = 0;
            //for premium
            virtual pair<int,int> parse_points(string id) = 0;
            virtual void parse_bus_details_for_user(string id) = 0;
            virtual void use_points(string id) = 0;
            virtual void spot_booking(string id) = 0;
            //common
            virtual void run_app(string id) = 0;
            //for colaborators
            virtual void add_buses(string id) = 0;
            virtual void show_buses(string id) = 0;
            virtual void update_buses(string id) = 0;
            virtual void bus_ratings(string id) = 0;

        };
}
#endif