#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <thread>
#include <string.h>

void read_data( int socket_fd, char *buffer ) {
        bool quit = false;
        int n = 0;
        while ( !quit ) {
        	bzero(buffer,256);
		n = read( socket_fd, buffer, 255 );
                if ( buffer == "//exit" )
                        break;
                if( n > 0 )
                        printf( "%s\n", buffer );
        }
}

void write_data( int socket_fd ) {
		bool quit = false;
		std::string tag;
		while ( !quit ) {
			std::string str;
			std::getline( std::cin, str );
			if ( str == "//exit" )
					break;
			/*tag = "client> ";*/
			tag = str;
			send( socket_fd, tag.c_str(), tag.length(), 0 );
		}
}

int main( int argc, char* args[] ) {
	std::string str;
	std::cout << "Enter IP Address of the server: ";
	std::cin >> str;
	int portn;
	std::cout << "Enter the port of the server: ";
	std::cin >> portn;
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	if ( inet_pton( AF_INET, str.c_str(), &serv_addr.sin_addr ) <= 0 )  
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
    	}
       	serv_addr.sin_port = htons( portn );

	char buffer[ 256 ] = "";
	
	int socket_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( socket_fd < 0 )
		printf( "An error has occured! could not create socket!\n" );
	if ( connect( socket_fd, ( struct sockaddr * ) &serv_addr, sizeof( serv_addr ) ) < 0 )
		printf( "A connection could not be established!\n" );
	else {
		printf( "Connected!\n" );
		std::thread th_read( read_data, socket_fd, buffer );
		std::thread th_write( write_data, socket_fd );
	
		th_read.join();
		th_write.join();
	}
	close( socket_fd );
	return 0;
}
