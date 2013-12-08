//
//  main.cpp
//  OS-HW3Client
//
//  Created by James Garcia on 11/20/13.
//  Copyright (c) 2013 James Garcia. All rights reserved.
//

/*
 ** client.c -- a stream socket client demo
 */

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 100 // max number of bytes we can get at once

using namespace std;


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
    
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int numberOfFlights;
    int flightNumber;
    int rows;
    int seats;
    int numberOfAgents;
    string command;
    int time;
    int flightDetailsNumber[numberOfFlights];
    vector<pair<int, int> > flightDetailsRows;
    vector<pair<int, int> > flightDetailsSeats;
    
    
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
        
        
        for (vector<pair<int, int> >::iterator iter = flightDetailsRows.begin(); iter!=flightDetailsRows.end(); iter++)
        {
            cout<<iter->first<<" "<<iter->second<<endl;
        }
        
        for (vector<pair<int, int> >::iterator iter = flightDetailsSeats.begin(); iter!=flightDetailsSeats.end(); iter++)
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
    
    
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
    
	if (argc != 2) {
	    fprintf(stderr,"usage: client hostname\n");
	    exit(1);
	}
    
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
    
	if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
    
	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}
        
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
        
		break;
	}
    
	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}
    
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
	printf("client: connecting to %s\n", s);

    
	freeaddrinfo(servinfo); // all done with this structure
    
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}
    
	buf[numbytes] = '\0';
    
	printf("client: received '%s'\n",buf);
    
    if (send(sockfd, "What up back!", 13, 0) == -1)
        perror("send");

    
	close(sockfd);
    
	return 0;
}
