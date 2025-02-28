#ifndef application_premium_H
#define application_premium_H

#include <bits/stdc++.h>
#include "application_interface.h"
#include "../credentials/bus_credentials.h"

using namespace std;
namespace application_premium
{   
    class application_premium: public application_interface::application_interface {
    public:
        application_premium(){
            build_booking_details();
        }
        void build_booking_details(){
            // Simulate initialization of booking details and premium seat allocations
            cout << "\tPremium booking details initialized.\n";
        }
        void book_buses(string id) override {
            // Premium users book buses using their points (assume a fixed cost of 10 points per booking)
            cout << "\tEnter Bus ID to book: ";
            string bus_id;
            cin >> bus_id;
            pair<int, int> pts = credentials::bus_credentials::get_points(id);
            int available = pts.first - pts.second;
            if (available < 10) {
                cout << "\tNot enough points to book the bus. Required: 10, Available: " << available << "\n";
                return;
            }
            credentials::bus_credentials::add_booking(id, bus_id);
            // Deduct booking cost (10 points)
            credentials::bus_credentials::user_points[id].second += 10;
            cout << "\tBus " << bus_id << " booked successfully using points.\n";
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
            cout << "\tYou are already a premium user.\n";
        }
        // for premium
        pair<int, int> parse_points(string id) override {
            pair<int, int> pts = credentials::bus_credentials::get_points(id);
            cout << "\tUser " << id << " Points: Earned = " << pts.first << ", Used = " << pts.second << "\n";
            return pts;
        }
        void parse_bus_details_for_user(string id) override {
            set<string> buses = credentials::bus_credentials::get_specific_data_as_copy_of_ownership(id);
            if (buses.empty()){
                cout << "\tNo bus details available for user: " << id << "\n";
            } else {
                cout << "\tBus details for user: " << id << "\n";
                for (const string& bus : buses){
                    cout << "\tBus: " << bus.substr(id.size() + 1) << "\n";
                    set<pair<string, string>> details = credentials::bus_credentials::get_bus_route_details(bus);
                    if (details.empty()){
                        cout << "\t\tNo route details available.\n";
                    } else {
                        for (auto& dt : details){
                            cout << "\t\tRoute: " << dt.first << ", Time: " << dt.second << "\n";
                        }
                    }
                }
            }
        }
        void use_points(string id) override {
            auto pts = credentials::bus_credentials::get_points(id);
            int available = pts.first - pts.second;
            cout << "\tAvailable points: " << available << "\n";
            cout << "\tEnter points to redeem for booking: ";
            int redeem;
            cin >> redeem;
            if (redeem > available){
                cout << "\tNot enough points.\n";
            } else {
                cout << "\tEnter Bus ID to book using redeemed points: ";
                string bus_id;
                cin >> bus_id;
                credentials::bus_credentials::add_booking(id, bus_id);
                credentials::bus_credentials::user_points[id].second += redeem;
                cout << "\tRedeemed " << redeem << " points and booked bus " << bus_id << ".\n";
            }
        }
        void spot_booking(string id) override {
            // Premium users can spot book even at the last minute with reserved premium seats.
            cout << "\tEnter your current position (route): ";
            string position;
            cin >> position;
            cout << "\tEnter desired time: ";
            string time;
            cin >> time;
            
            vector<string> available = credentials::bus_credentials::get_available_buses(position, time);
            if (available.empty()){
                cout << "\tNo buses available at " << position << " for time " << time << ".\n";
                return;
            }
            cout << "\tAvailable buses:\n";
            int count = 0;
            for (int i = 0; i < available.size() && i < 10; i++) {
                cout << "\tOption " << i+1 << ": Bus " << available[i] << "\n";
                count++;
            }
            cout << "\tEnter option number to select bus: ";
            int option;
            cin >> option;
            if (option < 1 || option > count){
                cout << "\tInvalid option selected.\n";
                return;
            }
            string chosen = available[option - 1];
            // Simulate allocation of a premium seat (assume dedicated premium seats exist)
            cout << "\tPremium seat allocated for Bus " << chosen << " at " 
                 << position << " for time " << time << ".\n";
            credentials::bus_credentials::add_booking(id, chosen);
        }
        // The following functions are not applicable for premium users.
        void add_buses(string id) override { }
        void show_buses(string id) override { }
        void update_buses(string id) override { }
        void bus_ratings(string id) override { }
        void run_app(string id) override {
            cout << "\t[Run App] Running premium application for: " << id << "\n";
        }
        void run(string id)
        {
            int option = 0;
            do {
                cout << "\n\tPREMIUM USER\n";
                pair<int, int> pts = parse_points(id);
                cout << "\tPOINTS: " << pts.first - pts.second << "\n";
                // For simplicity, LEVEL is derived as used_points / 10
                cout << "\tLEVEL: " << pts.second / 10 << "\n";
                cout << R"(
Option 1 - Book buses (with points)
Option 2 - Write review
Option 3 - Spot Booking (last minute)
Option 4 - Use points to book buses
Option 5 - Exit
)";
                cout << "\tEnter Option: ";
                if (!(cin >> option)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tInvalid input! Please enter a number." << endl;
                    continue;
                }
                switch (option) {
                    case 1: book_buses(id); break;
                    case 2: write_review(id); break;
                    case 3: spot_booking(id); break;
                    case 4: use_points(id); break;
                    case 5: break;
                    default: cout << "\tInvalid option. Try again.\n";
                }
            } while (option != 5);
        }
    };
}
#endif
