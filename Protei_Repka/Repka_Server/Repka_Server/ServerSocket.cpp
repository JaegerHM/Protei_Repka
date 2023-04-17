#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "Log.h"

using namespace std;

ServerSocket::ServerSocket(int port){

    if(!Socket::create())
        throw SocketException ("Could not create server socket.");

    LOG(DEBUG) << "Socket created";

    if(!Socket::bind(port))
        throw SocketException ("Could not bind to port.");

    LOG(DEBUG) << "Socket binded";

    if (!Socket::listen())
        throw SocketException ( "Could not listen to socket." );
}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << (const std::string& s) const{
    if (!Socket::send(s))
        throw SocketException ( "Could not write to socket." );

  return *this;
}


const ServerSocket& ServerSocket::operator >> (std::string& s) const{
    if (!Socket::recv(s))
        throw SocketException ( "Could not read from socket." );

  return *this;
}

void ServerSocket::accept(ServerSocket& sock){
    if (!Socket::accept(sock))
        throw SocketException ( "Could not accept socket." );
}

std::string ServerSocket::process_command(std::string request){

    stringstream ss(request);
    string s;
    vector<string> words;
    while(ss >> s)    {
        words.push_back(s);  //breaking request into words
    }

    int command = 0;

    //defining a command type
    if(words[0] == "PUT")
        command = 1;
    if(words[0] == "GET")
        command = 2;
    if(words[0] == "DEL")
        command = 3;
    if(words[0] == "COUNT")
        command = 4;
    if(words[0] == "DUMP")
        command = 5;
    if(words[0] == "LOAD")
        command = 6;

    LOG(DEBUG) << "Command is defined";

    switch(command){
        case 1:
            if(words.size() == 3)
            {
                string key = words[1];
                string value = words[2];
                string answer = "";
                //if there is no element with given key -- creates one
                if (this->vault.find(key) == vault.end())
                {
                    LOG(DEBUG) << "Command is OK";
                    answer = "OK\n";
                    this->vault.insert(std::pair<string, string>(key, value));

                }
                //if there is an element with given key -- replaces it with new
                else{
                    LOG(DEBUG) << "Command is OK";
                    answer = "OK " + this->vault.find(key)->second + "\n";
                    this->vault.erase(key);
                    this->vault.insert(std::pair<string, string>(key, value));
                }
                return answer;
            }
            else{
                LOG(DEBUG) << "Command is wrong";
                string answer = "NE\n";
                return answer;
            }

        case 2:
            if(words.size() == 2){
                string key = words[1];
                string answer = "";

                map<string, string>::iterator it = this->vault.find(key);
                if (it == vault.end())
                    answer = "NE\n";    //if there is no element with given key
                else
                    answer = "OK res " + it->second + "\n";     //if there is an element with given key
                LOG(DEBUG) << "Command is OK";
                return answer;
            }
            else{
                LOG(DEBUG) << "Command is wrong";
                string answer = "NE\n";
                return answer;
            }

        case 3:
            if(words.size() == 2){
                string key = words[1];

                string answer = "";
                if (this->vault[key] == ""){    //if there is no element with given key
                    LOG(DEBUG) << "Command is wrong";
                    answer = "NE\n";
                }
                else{
                    LOG(DEBUG) << "Command is OK";  //if there is an element with given key
                    answer = "OK " + this->vault[key] + "\n";
                    this->vault.erase(key);
                }
                return answer;
            }
            else{
                LOG(DEBUG) << "Command is wrong";
                string answer = "NE\n";
                return answer;
            }

        case 4:
            if(words.size() == 1){
                LOG(DEBUG) << "Command is OK";
                int s = this->vault.size();     // counting all elements in the vault
                stringstream ss;
                ss << s;
                string answer = ss.str() + "\n";
                return answer;
            }
            else{
                LOG(DEBUG) << "Command is wrong";
                string answer = "NE\n";
                return answer;
            }

            case 5:
            if(words.size() == 2){
                string path = words[1];
                map<string, string>::iterator it = this->vault.begin();
                string answer;
                fstream file;
                file.open(path, ios::out);
                if (file){
                    string str;

                    for (it; it != this->vault.end(); ++it)
                    {
                        str = it->first + " " + it->second + "\n";      //saving every element into file
                        file << str;
                    }
                    file.close();
                    LOG(DEBUG) << "Command is OK";
                    answer = "OK\n";
                }
                else{
                    LOG(DEBUG) << "Command is wrong";
                    answer = "NE\n";
                }
                return answer;
            }
            else{
                LOG(DEBUG) << "Command is wrong";
                string answer = "NE\n";
                return answer;
            }

        case 6:
            if(words.size() == 2){
                string path = words[1];
                fstream file;
                string str;
                file.open(path, ios::in);

                if (file){
                    while(getline(file, str)){

                        stringstream reader(str);
                        string st;
                        vector<string> read_pair;
                        while(reader >> st)    {
                            read_pair.push_back(st);        //loading every element from given file in the vault
                        }

                        string key = read_pair[0];
                        string value = read_pair[1];

                        this->vault.insert(pair<string, string>(key, value));
                    }
                    file.close();
                    LOG(DEBUG) << "Command is OK";
                    string answer = "OK\n";
                    return answer;
                }
                else{
                    LOG(DEBUG) << "Command is wrong";
                    string answer = "NE\n";
                    return answer;
                }
            }
            else{
                    LOG(DEBUG) << "Command is wrong";
                    string answer = "NE\n";
                    return answer;
            }

        case 0:
            string answer = "Acceptable commands:\nPUT <key> <value>\nGET<key>\nDEL<key>\nCOUNT\n";
            return answer;
    }
}

