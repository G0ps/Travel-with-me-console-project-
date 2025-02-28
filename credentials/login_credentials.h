#ifndef LOGIN_CREDENTIALS_H
#define LOGIN_CREDENTIALS_H

#include <bits/stdc++.h>

using namespace std;

namespace credentials {   
    class login_credentials {
        // Declare static map
        static map<string, pair<string, string>> login_data;

    public:
        login_credentials() {}

        // For data dumping and retrieval
        void get_all_login_credentials_as_address() {}
        void get_all_login_credentials_as_copy() {}

        // For data processing
        void get_specific_data_as_address() {}
        static tuple<string,string,string> get_specific_data_as_copy(string id) {
            auto it = login_data.find(id);
            if(it == login_data.end())
            {
                return make_tuple("-1","-1","-1");
            }
            else{
                return make_tuple(id , login_data[id].first , login_data[id].second);
            }
        }

        // Updating credentials
        static void overwrite_login_credentials(const string& id, const string& password, const string& type) {
            login_data[id] = {password, type};
            
            cout << "\tLogin saved\n";
        }
    };

    // Define static member properly outside the class
    map<string, pair<string, string>> login_credentials::login_data;

}

#endif // LOGIN_CREDENTIALS_H
