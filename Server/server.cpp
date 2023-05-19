#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
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
		tag = "server> ";
		tag += str;
		send( socket_fd, tag.c_str(), tag.length(), 0 );
	}
}

int main( int argc, char* args[] ) {
	
	socklen_t client_len;
	std::string port_str = "";
	std::cout << "Enter the port to listen on (Defualt: 1153): ";
	std::getline( std::cin, port_str );
	if (port_str.empty()) {
		port_str = "1153";
	}
	int port_int = stoi(port_str);
	struct sockaddr_in local_addr, client_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons( port_int );
	
	char buffer[ 256 ];

	// Socket creation
	int socketfd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( socketfd < 0 )
		printf( "An error has occured! Socket could not be created.\n");

	// Binding a port
	if ( bind( socketfd, (struct sockaddr *) &local_addr, sizeof(local_addr) ) < 0 )
		printf( "An error has occured! Port binding didn't complete.\n");
	
	if ( listen( socketfd, 5 ) == -1 )
		printf( "An error has occured! Socket cannot listen to the port.\n");
		
	printf( "Listening ... \n" );

	int socketfd_new_connection = accept( socketfd, (struct sockaddr *)&local_addr, ( socklen_t * ) &client_len );
	if ( socketfd_new_connection < 0 )
		printf( "An error has occured! New socket cannot be created.\n" );
	send( socketfd_new_connection, "Connected!" , 11, 0 );
	
	std::thread th_read( read_data, socketfd_new_connection, buffer );
	std::thread th_write( write_data, socketfd_new_connection );

	th_read.join();
	th_write.join();
	
	close( socketfd_new_connection );
	close( socketfd );
	return 0;

}
