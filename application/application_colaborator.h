#ifndef application_colaborator_H
#define application_colaborator_H

#include <bits/stdc++.h>
#include "application_interface.h"
#include "../credentials/bus_credentials.h"

using namespace std;
namespace application_colaborator
{   
    class application_colaborator : public application_interface::application_interface {
            
        public:
            application_colaborator(){}

            void book_buses(string id) override {
                cout << "\t[Not applicable for collaborators]\n";
            }
            void write_review(string id) override {
                cout << "\tCollaborators are not allowed to write reviews.\n";
            }
            void become_premium(string id) override {
                cout << "\t[Not applicable for collaborators]\n";
            }
            pair<int, int> parse_points(string id) override {
                cout << "\t[Not applicable for collaborators]\n";
                return {0, 0};
            }
            void parse_bus_details_for_user(string id) override {
                cout << "\t[Not applicable for collaborators]\n";
            }
            void use_points(string id) override {
                cout << "\t[Not applicable for collaborators]\n";
            }
            // Even though spot booking is not applicable, we must override it.
            void spot_booking(string id) override {
                cout << "\t[Not applicable for collaborators]\n";
            }
            void run_app(string s) override {
                cout << "\t[Run App] Running application for: " << s << "\n";
            }
            void add_buses(string id) override {
                string opt;
                do {
                    string bus_name;
                    do {
                        cout << "\tEnter a unique Bus Name : ";
                        cin >> bus_name;
                    } while(credentials::bus_credentials::bus_id_already_exist(id, id+"-"+bus_name) || bus_name.empty());
                    cout << "\tBus added successfully.\n";
                    
                    string route, time;
                    do {
                        cin.clear();
                        cout << "\tEnter a route : ";
                        cin >> route;
                        cout << "\tEnter a valid time : ";
                        cin >> time;
                        if(!credentials::bus_credentials::route_time_already_exist(route, time, id+"-"+bus_name)) {
                            string option;
                            cout << "\tRoute and time already exist.\n";
                            cout << "\tEnter 1 to retry and 0 to Exit : ";
                            cin >> option;
                            if(option != "1") {
                                break;
                            }
                        }
                        else {
                            credentials::bus_credentials::owerwrite_bus_route_data({id+"-"+bus_name, {route, time}});
                            cout << "\tData added successfully.\n";
                            cout << "\tEnter 1 to add more routes or 0 to Exit : ";
                            string option;
                            cin >> option;
                            if(option != "1") {
                                break;
                            }
                        }
                    } while(true);
                    cout << "\tEnter 1 to add more buses or 0 to Exit : ";
                    cin >> opt;
                    if(opt != "1") {
                        break;
                    }
                    cout << "\n";
                } while(true);
            }
            void show_buses(string id) override {
                cout << "\tCOLLABORATOR:\n";
                for(string it : credentials::bus_credentials::get_specific_data_as_copy_of_ownership(id)) {
                    cout << "Bus: " << it.substr(id.size()+1) << ":\n";
                }
            }
            void update_buses(string id) override {
                cout << "\tEnter Bus ID to update: ";
                string bus_id;
                cin >> bus_id;
                if(credentials::bus_credentials::get_specific_data_as_copy_of_ownership(id).find(bus_id) == 
                   credentials::bus_credentials::get_specific_data_as_copy_of_ownership(id).end()) {
                    cout << "\tBus ID not found under your ownership.\n";
                    return;
                }
                cout << "\tEnter new route: ";
                string route;
                cin >> route;
                cout << "\tEnter new time: ";
                string time;
                cin >> time;
                credentials::bus_credentials::update_bus_route_details(bus_id, {route, time});
                cout << "\tBus " << bus_id << " updated with new route and time.\n";
            }
            void bus_ratings(string id) override {
                cout << "\tEnter Bus ID to view ratings: ";
                string bus;
                cin >> bus;
                vector<int> ratings = credentials::bus_credentials::get_ratings(bus);
                if(ratings.empty()) {
                    cout << "\tNo ratings available for bus " << bus << ".\n";
                } else {
                    cout << "\tRatings for bus " << bus << ": ";
                    for(int r : ratings) {
                        cout << r << " ";
                    }
                    cout << "\n";
                }
            }
            void remove_bus(string id) {
                set<string> buses = credentials::bus_credentials::get_specific_data_as_copy_of_ownership(id);
                if(buses.empty()) {
                    cout << "\tNo buses to remove.\n";
                    return;
                }
                cout << "\tYour buses:\n";
                int count = 1;
                vector<string> bus_list;
                for(auto bus : buses) {
                    cout << "\t" << count << ". " << bus.substr(id.size()+1) << " (Full ID: " << bus << ")\n";
                    bus_list.push_back(bus);
                    count++;
                }
                cout << "\tEnter the option number of the bus to remove: ";
                int option;
                cin >> option;
                if(option < 1 || option > bus_list.size()) {
                    cout << "\tInvalid option.\n";
                    return;
                }
                string chosen = bus_list[option - 1];
                credentials::bus_credentials::overwrite_remove_bus_credentials_ownership(id, chosen);
                cout << "\tBus " << chosen.substr(id.size()+1) << " removed successfully.\n";
            }
            void run(string id) {
                int option;
                do {
                    cout << "\n\t\tCOLLABORATOR\n";
                    cout << R"(
                        Option 1 - Add Buses (Collaborate)
                        Option 2 - Show Buses and Routes
                        Option 3 - Update Bus Details
                        Option 4 - Check Bus Ratings
                        Option 5 - Remove Bus
                        Option 6 - Exit
                    )";
                    cout << "\tEnter Option: ";
                    cin >> option;
                    switch(option) {
                        case 1: add_buses(id); break;
                        case 2: show_buses(id); break;
                        case 3: update_buses(id); break;
                        case 4: bus_ratings(id); break;
                        case 5: remove_bus(id); break;
                        case 6: break;
                        default: cout << "\tInvalid option. Try again.\n";
                    }
                } while(option != 6);
            }
    };
}

#endif
