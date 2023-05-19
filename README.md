# Chat-Interface
A Chat interface written in C++. There is a Server side and a Client side.

# How to Run
Before running, you should install requirements:

```
sudo apt-get update
sudo apt-get install build-essential manpages-dev
sudo apt-get install libpthread-stubs0-dev
```

## Run Server
run:
```
chmod +x ./run-server
./run-server
```
Enter the port to listen on (default port for the server is `1153`).

## Run Client
run:
```
chmod +x ./run-client
./run-client
```
Enter the IP address of the server and then Enter the port of the server.
If the server and the client are the same then enter the IP address of `127.0.0.1` for the IP address.
After recieving `Connected!`, Enter message and press Enter. you can also recieve messages from server.

Enjoy!