#ifndef application_H
#define application_H

#include <bits/stdc++.h>

#include "application_premium.h"
#include "application_colaborator.h"
#include "application_interface.h"

using namespace std;
namespace application
{   
    class application: public application_interface::application_interface {
        public:
            application(){}
            void run(tuple<string,string,string> details){
                string type = get<2>(details);
                string id = get<0>(details);

                if(type == "premium_user")
                {
                    application_premium::application_premium app;
                    app.run(id);
                    return;
                }
                else if(type == "colaborator")
                {
                    application_colaborator::application_colaborator app;
                    app.run(id);
                    return;
                }
                else{
                    int option = 1;
                    do{
                        cout<< R"(
                        Option 1 - book busses
                        Option 2 - write review
                        Option 3 - become premium to unlock features
                        Option 4 - exit
                        )";
                        cout << "\tEnter Option : ";
                        if (!(cin >> option)) {  // Input validation
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input! Please enter a number." << endl;
                            continue;
                        }
                        switch (option){
                            case 1: book_buses(id); break;
                            case 2: write_review(id); break;
                            case 3: become_premium(id); break;
                            case 4: break;
                        }
                    } while(option != 4);
                }
            }
            void book_buses(string id) override {
                cout << "\t[Book Buses] Available Buses:\n";
                // Use the new function to access bus ownership safely
                auto allOwnership = credentials::bus_credentials::get_all_bus_ownership();
                for (auto& owner_pair : allOwnership) {
                    cout << "\tOwner: " << owner_pair.first << "\n";
                    for (auto& bus : owner_pair.second) {
                        // Display bus name (remove owner id prefix)
                        cout << "\t   Bus: " << bus.substr(owner_pair.first.size() + 1) 
                             << " (Full ID: " << bus << ")\n";
                    }
                }
                cout << "\tEnter Bus ID to book: ";
                string bus_id;
                cin >> bus_id;
                // Simulate booking
                credentials::bus_credentials::add_booking(id, bus_id);
                cout << "\tBus " << bus_id << " booked successfully.\n";
            }
            void write_review(string id) override {
                cout << "\tEnter Bus ID for review: ";
                string bus_id;
                cin >> bus_id;
                cout << "\tEnter your review: ";
                string review;
                getline(cin >> ws, review);
                credentials::bus_credentials::add_review(bus_id, review);
                cout << "\tReview added successfully.\n";
            }
            void become_premium(string id) override {
                if (credentials::bus_credentials::premium_users.find(id) == credentials::bus_credentials::premium_users.end()) {
                    credentials::bus_credentials::add_premium_user(id);
                    cout << "\tUser " << id << " is now a premium member.\n";
                }
                else {
                    cout << "\tUser " << id << " is already a premium member.\n";
                }
            }
            // For normal users, the following features are not applicable.
            pair<int,int> parse_points(string id) override {
                cout << "\t[Not applicable for normal users]\n";
                return {0, 0};
            }
            void parse_bus_details_for_user(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            void use_points(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            void spot_booking(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            // Common function (if needed)
            void run_app(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            // Collaborator features are not applicable for normal users.
            void add_buses(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            void show_buses(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            void update_buses(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
            void bus_ratings(string id) override {
                cout << "\t[Not applicable for normal users]\n";
            }
    };
}
#endif
