//
//  main.cpp
//  OS-HW3
//
//  Created by James Garcia on 11/20/13.
//  Copyright (c) 2013 James Garcia. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main(int argc, const char * argv[])
{
    int numberOfFlights;
    int flightNumber;
    int rows;
    int seats;
    int numberOfAgents;
    string command;
    int time;
    

    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        string line;
        //get numberOfFlights
        getline(myfile,line);
        stringstream(line) >> numberOfFlights;
        
        cout<<numberOfFlights<<endl;
        
        
        //get flight seating information
        istringstream iss;
        stringstream ss;
        
        for(int i = 0; i<numberOfFlights; i++)
        {
            getline(myfile,line);
            iss.str(line);
            iss >> flightNumber;
            iss >> rows;
            iss >> seats;
            
            cout<<flightNumber<<" "<<rows<<" "  <<seats<<endl;
        }
        
        //get numberOfAgents
        getline(myfile,line);
        stringstream(line) >> numberOfAgents;
        cout<<numberOfAgents<<endl;

        //get agent operations
        getline(myfile,line);
        for(int i = 0; i<numberOfAgents; i++)
        {
            //get time
            for(int c = 0; c<4; c++)
            {
                cout<<"i = "<<i<<endl;
                getline(myfile,line);
                iss.str(line);
                iss >> command;
                iss >> time;
                if(command == "reserve")
                {
                    cout<<command<<" "<<time<<endl;
                }
                else if(command == "ticket")
                {
                    cout<<command<<" "<<time<<endl;
                }
                else if(command == "cancel")
                {
                    cout<<command<<" "<<time<<endl;
                }
                else if(command == "check_passenger")
                {
                    cout<<command<<" "<<time<<endl;
                }
            }
            for(int c = 0; c<4; c++)
            {
                getline(myfile,line);
            }
        }
            
            
//            if(command == "reserve")
//            {
//                cout<<command<<endl;
//            }
//            else if(command == "ticket")
//            {
//                cout<<command<<endl;
//            }
//            else if(command == "cancel")
//            {
//                cout<<command<<endl;
//            }
//            else if(command == "check_passenger")
//            {
//                cout<<command<<endl;
//            }
//            else
//            {
//                if(line == "end.\r" || line =="end.")
//                {
//                    continue;
//                }
//                cout<<line<<endl;
//            }
        
    }
    else cout << "Unable to open file\n";
    myfile.close();
    /* END READ FILE */
    return 0;
}

