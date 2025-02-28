#ifndef bus_credentials_H
#define bus_credentials_H

#include <bits/stdc++.h>

using namespace std;

namespace credentials {   
    class bus_credentials {
        // Declare static maps
        static map<string, set<pair<string, string>>> bus_route_data_owners;
        // bus : bus id , [[place,time],[place,time]]
        // bus_id = owner_id+"-"+bus_name
        static map<string, set<pair<string, string>>> bus_route_time;
        // set<route/time , id_bus>
        static map<string, set<pair<string, string>>> bus_time_route;
        static map<string, set<string>> bus_ownership;
        // bus : owner , [[bus1][bus2]]//name vector
        
    public:
        bus_credentials() {}

        // For data dumping and retrieval
        void get_all_bus_credentials_as_address() {}
        void get_all_bus_credentials_as_copy() {}

        // For data processing
        void get_specific_data_as_address() {}
        static set<string> get_specific_data_as_copy_of_ownership(string id) {
            // returns busses of owners
            return bus_ownership[id];
        }

        // Updating credentials
        static void overwrite_add_bus_credentials_ownership(string owner_id, string bus) {
            // bus_ownership[owner_id].insert(bus);            
        }
        static void overwrite_remove_bus_credentials_ownership(string owner_id, string bus) {
            // Remove bus from owner's ownership
            if(bus_ownership.find(owner_id) != bus_ownership.end()){
                bus_ownership[owner_id].erase(bus);
            }
            // Remove all route/time details associated with this bus
            bus_route_data_owners.erase(bus);
            // For each route, remove entries with bus as the bus id
            for(auto &entry : bus_route_time) {
                auto &s = entry.second;
                for(auto it = s.begin(); it != s.end(); ){
                    if(it->second == bus)
                        it = s.erase(it);
                    else
                        ++it;
                }
            }
            // Similarly, for each time entry, remove entries with bus as the bus id
            for(auto &entry : bus_time_route) {
                auto &s = entry.second;
                for(auto it = s.begin(); it != s.end(); ){
                    if(it->second == bus)
                        it = s.erase(it);
                    else
                        ++it;
                }
            }
            // Remove any reviews and ratings associated with this bus
            bus_reviews.erase(bus);
            bus_ratings.erase(bus);
            // Remove this bus from any user's booking list
            for(auto &p : bus_bookings){
                auto &vec = p.second;
                vec.erase(remove(vec.begin(), vec.end(), bus), vec.end());
            }
        }

        static void owerwrite_bus_route_data(pair<string, pair<string, string>> bus) {
            // supporting verifier function bus_id_already_exist();
            // bus route_time_already_exist()
            bus_route_data_owners[bus.first].insert(bus.second);
        }
        static bool bus_id_already_exist(string owner_id, string bus_id) {
            // it adds bus_ownership_data
            if(bus_ownership[owner_id].find(bus_id) == bus_ownership[owner_id].end()){
                bus_ownership[owner_id].insert(bus_id);
                return false;
            }
            else return true;
        }
        static bool route_time_already_exist(string route, string time, string bus_id) {
            if(bus_route_time[route].find({time, bus_id}) == bus_route_time[route].end()){
                bus_route_time[route].insert({time, bus_id});
                bus_time_route[time].insert({route, bus_id});
                return true;
            }
            else return false;
            // rewrites route_time and time_route data if unique
        }
        
        // Additional functions for application features
        static map<string, vector<string>> bus_reviews;
        static void add_review(string bus_id, string review) {
            bus_reviews[bus_id].push_back(review);
        }
        
        static set<string> premium_users;
        static void add_premium_user(string id) {
            premium_users.insert(id);
        }
        
        static map<string, pair<int, int>> user_points;
        static pair<int, int> get_points(string id) {
            if(user_points.find(id) == user_points.end()){
                user_points[id] = {100, 0}; // default: 100 earned, 0 used
            }
            return user_points[id];
        }
        
        static map<string, vector<string>> bus_bookings;
        static void add_booking(string user, string bus) {
            bus_bookings[user].push_back(bus);
        }
        
        static set<pair<string, string>> get_bus_route_details(string bus_id) {
            return bus_route_data_owners[bus_id];
        }
        
        static void update_bus_route_details(string bus_id, const pair<string, string>& new_details) {
            bus_route_data_owners[bus_id].clear();
            bus_route_data_owners[bus_id].insert(new_details);
        }
        
        static map<string, vector<int>> bus_ratings;
        static void add_rating(string bus_id, int rating) {
            bus_ratings[bus_id].push_back(rating);
        }
        static vector<int> get_ratings(string bus_id) {
            if(bus_ratings.find(bus_id) == bus_ratings.end()){
                return vector<int>();
            }
            return bus_ratings[bus_id];
        }
        
        // New public function to access bus_ownership
        static map<string, set<string>> get_all_bus_ownership() {
            return bus_ownership;
        }
        
        // New public function to get available buses for a given route and time.
        static vector<string> get_available_buses(string route, string time) {
            vector<string> result;
            if(bus_route_time.find(route) != bus_route_time.end()){
                for(auto &entry : bus_route_time[route]){
                    if(entry.first == time)
                        result.push_back(entry.second);
                }
            }
            return result;
        }
    };

    // Define static members properly outside the class
    map<string, set<pair<string, string>>> bus_credentials::bus_route_data_owners;
    map<string, set<pair<string, string>>> bus_credentials::bus_route_time;
    map<string, set<pair<string, string>>> bus_credentials::bus_time_route;
    map<string, set<string>> bus_credentials::bus_ownership;
    
    // Definitions for additional features
    map<string, vector<string>> bus_credentials::bus_reviews;
    set<string> bus_credentials::premium_users;
    map<string, pair<int, int>> bus_credentials::user_points;
    map<string, vector<string>> bus_credentials::bus_bookings;
    map<string, vector<int>> bus_credentials::bus_ratings;
}

#endif // bus_credentials_H
