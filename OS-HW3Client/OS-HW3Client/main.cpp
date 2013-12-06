//
//  main.cpp
//  OS-HW3Client
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
    int flightDetailsNumber[numberOfFlights];
    vector<pair<int, int>> flightDetailsRows;
    vector<pair<int, int>> flightDetailsSeats;
    
    
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
            
            flightDetailsNumber[i] = flightNumber;
            flightDetailsRows.push_back(make_pair(flightNumber, rows));
            flightDetailsSeats.push_back(make_pair(flightNumber, seats));
            
        }
        
        
        for (vector<pair<int, int>>::iterator iter = flightDetailsRows.begin(); iter!=flightDetailsRows.end(); iter++)
        {
            cout<<iter->first<<" "<<iter->second<<endl;
        }
        
        for (vector<pair<int, int>>::iterator iter = flightDetailsSeats.begin(); iter!=flightDetailsSeats.end(); iter++)
        {
            cout<<iter->first<<" "<<iter->second<<endl;
        }
        
        
        //get numberOfAgents
        getline(myfile,line);
        stringstream(line) >> numberOfAgents;
        cout<<numberOfAgents<<endl;
        
        //get agent operations
        
        for(int i = 0; i<numberOfAgents; i++)
        {
            getline(myfile,line);
            
            //get time
            for(int c = 0; c<4; c++)
            {
                
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
                iss.str(line);
                iss >> command;
                
                if(command == "reserve")
                {
                    cout<<line<<endl;
                }
                else if(command == "ticket")
                {
                    cout<<line<<endl;
                }
                else if(command == "cancel")
                {
                    cout<<line<<endl;
                }
                else if(command == "check_passenger")
                {
                    cout<<line<<endl;
                }
            }
            getline(myfile,line);
        }
    }
    else cout << "Unable to open file\n";
    myfile.close();
    /* END READ FILE */
    return 0;
}
