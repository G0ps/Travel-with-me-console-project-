#include <bits/stdc++.h>
#include <fstream>


using namespace std;

#include "registration/registration.h"
#include "login/login.h"



int main()
    {
        //rebuilding credentials
        //end rebuilding credentials

        int option = 3;
        //startted
        cout << "\n\t   <== TRAVEL WITH US ==>\n";
        do{
            cout<< R"(
            Option 1 : Register
            Option 2 : Login
            Option 3 : exit
            )";
            cout << "Enter Option : ";
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            if(option == 1)
            {
                registration::registration r;
                continue;
            }
            else if(option == 2)
            {
                login::login l;
            }

        }while(option != 3);
        cout << "\n\t   <== THANKS FOR USING OUR APPLICATION ==>";
        //updating credentials
        //end updating credentials
        return 0;
    }
/*
g++ interface.cpp -o output
*/
