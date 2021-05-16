
#include "Server.h"
#include <chrono>
#define CLIENT_NUMBER_PARALLEL 2
#define ACCEPT_TIMEOUT 5
#define CLIENTS_NUM_OVERALL 4
/*
struct Ru {
public:
    int operator()
}*/

mutex m;
//mutex m2;




Server::Server(int port)throw (const char*) {
    this->fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
        throw "socket failed";

    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = INADDR_ANY;
    this->server.sin_port = htons(port);

    if (bind(this->fd, (struct sockaddr *) &this->server, sizeof(this->server)) < 0) {
        throw "bind failure";
    }


    if(listen(fd, CLIENTS_NUM_OVERALL)<0) //it should be checked if 3 clients is enough
        throw "listen failure";


    this->boolNotStop = 1;
    //m.lock();
}

//volatile sig_atomic_t flag = 0;


void handle_sigalarm(int sig)
{
    cout<<"blablabla"<<endl;
    //m.lock();
    //exit(sig);

    //terminate();
    /*struct sigaction s;
    s.sa_handler = handle_sigalarm;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_INTERRUPT;
    sigaction(sig,&s, nullptr);*/
}


void Server::start(ClientHandler& ch)throw(const char*){

    //for(;i<CLIENT_NUMBER_PARALLEL;++i) {
        this->t = new thread([&ch, this]() {
            //cout<<"pending time (for any client to call)"<<endl;
            //int c;
            int i=0;

            //Instead of keeping "sockaddr_in client" as a data member I prefered to initialize a new one for every new thread
            //Because the number of clients can be as the number of threads and therefore it could be problematic if two threads
            //will count on common variable;
            sockaddr_in client;
            int clientFD;
            socklen_t cSize = sizeof(client);
            int nfds=0;
            struct timeval t;
            t.tv_sec = 3;
            fd_set active_fd_set, read_fd_set;

            FD_ZERO(&active_fd_set);
            FD_SET(this->fd,&active_fd_set);
            read_fd_set = active_fd_set;
            /*struct sigaction s;
            s.sa_handler = handle_sigalarm;
            sigemptyset(&s.sa_mask);
            //s.sa_flags = SA_INTERRUPT;
            s.sa_flags = SA_RESTART;
            sigaction(SIGALRM, &s, nullptr);*/

            while(this->boolNotStop) {
                if (select(nfds,&read_fd_set, nullptr, nullptr,&t)<0){
                    throw "select error";
                }

                //alarm(ACCEPT_TIMEOUT);
                clientFD = accept(this->fd, (struct sockaddr *) &client, &cSize);
                //alarm(0);


                if (clientFD < 0) {
                    break;
                }



                //std::cout << "Hello waiter\n" << std::flush;
                //auto start = std::chrono::high_resolution_clock::now();
                //std::this_thread::sleep_for(std::chrono::seconds(20));
                //cv.wait_for(lck,std::chrono::seconds(5));
                cout<<"thread"<<endl;
                //auto end = std::chrono::high_resolution_clock::now();
                //std::chrono::duration<double, std::milli> elapsed = end-start;
                //std::cout << "Waited " << elapsed.count() << " ms\n";


                this->tClients = new thread([&ch, clientFD]() {
                    ch.handle(clientFD);
                    close(clientFD);
                });
                this->tClients->detach();


            }
            close(this->fd);
        });
    //}
}


void Server::stop(){
    this->boolNotStop=0;

}

Server::~Server() {
    //m.unlock();
    this->t->join();

}

