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

        
        for(int i = 1; i<numberOfAgents+1; i++)
        {
            getline(myfile,line);
            while(line == "end.")
            {
                cout<<line<<endl;
            }
        }
        
    }
    else cout << "Unable to open file\n";
    myfile.close();
    /* END READ FILE */
    return 0;
}

