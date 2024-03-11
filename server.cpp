//Mikel Echarri 
//This code can only be run on Linux
//You first start the server.cpp, then the client.cpp, all the commands will be inputted via the client terminal

using namespace std;
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#define PORT 8081


bool isInt(const string& str)
{
    bool result = true;
    try
    {
        // Convert string to int
        int n = stoi(str);
    }
    catch (const invalid_argument& e)
    {
        result = false;
    }
    catch (const out_of_range& e)
    {
        result = false;
    }
    return result;
}


int main ( int argument, char const *argv[] )
{
    //create items for connection
    int obj_server, sock, reader;
    //create address
    struct sockaddr_in address;
    //prevents errors such as address already in use
    int opted = 1;
    //address length
    int address_length = sizeof(address);
    //our message buffer
    char buffer[1024] = {0};
    
    //std::string name3 = "SELECT account_id FROM players WHERE name = '" + portCall + "'";
    //try open socket
    if (( obj_server = socket ( AF_INET, SOCK_STREAM, 0)) == 0)
    {
    perror ( "Opening of Socket Failed !");
    exit ( EXIT_FAILURE);
    }
    //try set the socket
    if ( setsockopt(obj_server, SOL_SOCKET, SO_REUSEADDR, &opted, sizeof ( opted )))
    {
    perror ( "Can't set the socket" );
    exit ( EXIT_FAILURE );
    }
    //types of sockets
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    //try bind socket
    if (bind(obj_server, ( struct sockaddr * )&address, sizeof(address))<0)
    {
    perror ( "Binding of socket failed !" );
    exit(EXIT_FAILURE);
    }
    //try listening
    if (listen ( obj_server, 3) < 0)
    {
    perror ( "Can't listen from the server !");
    exit(EXIT_FAILURE);
    }
    //accept error
    if ((sock = accept(obj_server, (struct sockaddr *)&address, (socklen_t*)&address_length)) < 0)
    {
    perror("Accept");
    exit(EXIT_FAILURE);
    }
    //read message
    reader = read(sock, buffer, 1024);
    //client currently waiting for #1 response to continue
    std::string strtmp = "1";
    //convert string to char*
    const char* wait = strtmp.c_str();
    //send ok
    //send ( sock , wait , strlen(wait) , 0 );
    //text for server
    printf("Server Started \n");
    printf("\nListening on TCP 8081\n");
    printf("\nReceived String: ");
    printf("%s\n", buffer);
    //for number
    int ia;
    //convert char to int
    ia = atoi(buffer);
    //cout << ia;
    //for length of int
    int length = 1;




    //if = 0 conversion failed
    if (isInt(buffer))
    {
        
    }
    else
    {
        //read buffer for any message
        //reader = read(sock, buffer, 1024);
        //send error to client
        std::string strtm = "That isn't a number...";
        const char* negative = strtm.c_str();
        send ( sock , negative , strlen(negative) , 0 );
        printf("\nInvalid Input, Exiting Server Application\n");
        close(sock);
        return 0;
    }
    /*if(ia<0) {
        //read buffer for any message
        //reader = read(sock, buffer, 1024);
        //send error to client
        std::string strtm = "T";
        const char* negative = strtm.c_str();
        send ( sock , negative , strlen(negative) , 0 );
        printf("\nInvalid Input, Exiting Server Application\n");
        close(sock);
        return 0;
    }
    else {

        
        

    }*/
    //create second instance
    int iaa = ia+1;
    //vector for each dgit
    vector<int> digit;
        
    

    //the sum
    int total=0;
    //end program if true
    bool end = false;
    while(end == false) {
        //checking for wait
        int wait = 0;
        //clear buffer
        memset(buffer, 0, sizeof(buffer));
        
        
        //waiting for client ok to move forward
        /*while(wait==0) {
            reader = read(sock, buffer, 1024);
            wait = atoi(buffer);
            
        }*/
        
        string t = to_string(iaa);
        //convert to char
        char const *n_char = t.c_str();
        send(sock , n_char, strlen(n_char) , 0 );

        //checking for wait
        wait = 0;
        //clear buffer
        memset(buffer, 0, sizeof(buffer));
        
        
        //waiting for client ok to move forward
        
        reader = read(sock, buffer, 1024);
        wait = atoi(buffer);
            //ia = atoi(buffer);

            
        
        printf("\nReceived String: ");
        printf("%s\n", buffer);
        ia = atoi(buffer);
        iaa++;
        if(iaa==ia) {
            string t = "Nice";
            //convert to char
            char const *n_char = t.c_str();
            send(sock , n_char, strlen(n_char) , 0 );
        } else {
            string t = "Wrong";
            //convert to char
            char const *n_char = t.c_str();
            send(sock , n_char, strlen(n_char) , 0 );
        }

        close(sock);
        return 0;
        //count length of int
        /*while ( ia /= 10 ) {
            length++;
        }*/
        //populate vector
        /*for(int j=0 ; j<length ; j++ ) {
            digit.push_back(0);
        }*/
        //initialize
        total=0;
        /*
        //defining a loop for splitting the number
        for(int i=0; i<length ; i++) {
            digit[i]=iaa%10;
            iaa=iaa/10;
        }
        //add digits up
        for(int j=0 ; j<digit.size() ; j++ ) {
            total=total+digit.at(j);
        }
        //if < 10 goal achieved
        if(total<10) {
            //convert to string
            string t = to_string(total);
            //convert to char
            char const *n_char = t.c_str();
            //server message
            printf("Sending Digit Sum result: %s\n", n_char);
            //exit
            printf("\nDigit sum is a single digit, Exiting Server Application\n");
            //let client know of single digit
            send(sock , n_char, strlen(n_char) , 0 );
            //exit
            end = true;
            close(sock);
            return 0;
        }
        else {
            //int to string
            string t = to_string(total);
            //string to char
            char const *n_char = t.c_str();
            //server message
            printf("Sending Digit Sum result: %s\n", n_char);
            //send number
            send(sock , n_char, strlen(n_char) , 0 );
            //receive
            printf("Received String: %s\n", n_char);
            //set new number
            ia = total;
            iaa = total;
        }*/
        
        
    }
    //close sock
    close(sock);
    return 0;
}