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
    int numberOfAgents;
    string command;
    int time;
    int pid;
    int childAgentNumber;
    string line;
    const char* message;
    
    
    /* GET NUMBER OF AGENTS */
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        
        //get numberOfFlights
        getline(myfile,line);
        stringstream(line) >> numberOfFlights;
        
        for(int i = 0; i<numberOfFlights; i++)
        {
            getline(myfile,line);
        }
        
        //get numberOfAgents
        getline(myfile,line);
        stringstream(line) >> numberOfAgents;
        cout<<numberOfAgents<<endl;
    }
    else cout << "Unable to open file\n";
    myfile.close();
    /* END GET NUMBER OF AGENTS */
    
    /* SOCKET COMMUNICATION */
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
    
	if (argc != 2) {
	    fprintf(stderr,"usage: client hostname\n");
	    exit(1);
	}
    
    /* FORKING */
    for(int i = 1; i <= numberOfAgents; i++)
    {
        pid = fork();
        if(pid == 0)
        {
            childAgentNumber = i;
            break;
        }
    }
    if(pid != 0) {
        exit(0);
    }
    
    cout<<"child: "<<childAgentNumber<<endl;
    
    /* READ FROM FILE */
    ifstream myfile1 ("input.txt");
    if (myfile1.is_open())
    {
        
        //get numberOfFlights
        getline(myfile1,line);
        stringstream(line) >> numberOfFlights;
        
        for(int i = 0; i<numberOfFlights; i++)
        {
            getline(myfile1,line);
        }
        
        //get numberOfAgents
        getline(myfile1,line);
        stringstream(line) >> numberOfAgents;
        
        /*GET AGENT OPERATIONS */
        int currentAgent = 0;
        
        for(int i = 1; i<numberOfAgents+1; i++)
        {
            getline(myfile1,line);
            if( line.compare(0,6, "agent_") ==  0)
            {
                cout<<i<<"="<<childAgentNumber<<endl;
                if( i == childAgentNumber )
                {
                    for(int c = 0; c<8; c++)
                    {
                        getline(myfile1,line);
                        //cout<<line<<endl;
                        message = line.c_str();
                        cout<<"message: "<<message<<endl;
                    }
                    
                }
                
            }
            getline(myfile1,line);
        }
    }
    else cout << "Unable to open file\n";
    myfile1.close();
    /* END READ FROM FILE */
    
    
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
			//perror("client: connect");
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
	//printf("client: connecting to %s\n", s);

    
	freeaddrinfo(servinfo); // all done with this structure
    
    
//    if (send(sockfd, "test", 256, 0) == -1)
//            perror("send");
    
//	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
//	    perror("recv");
//	    exit(1);
//	}
//    
//	buf[numbytes] = '\0';
//    
//	printf("client: received '%s'\n",buf);
    
    
    
    
	close(sockfd);
    /* SOCKET COMMUNICATION END */
    
	return 0;
}
