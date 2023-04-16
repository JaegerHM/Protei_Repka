#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

ServerSocket::ServerSocket(int port){

    if(!Socket::create())
        throw SocketException ("Could not create server socket.");


    if(!Socket::bind(port))
        throw SocketException ("Could not bind to port.");


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
        words.push_back(s);
    }

    int command = 0;

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
    if((words[0] == "EXIT\n") || (words[0] == "EXIT"))
        command = 10;


    switch(command){
        case 1:
            if(words.size() == 3)
            {
                string key = words[1];
                string value = words[2];
                string answer = "";
                if (this->vault.find(key) == vault.end())
                {
                    answer = "OK\n";
                    this->vault.insert(std::pair<string, string>(key, value));

                }
                else{
                    answer = "OK " + this->vault.find(key)->second + "\n";
                    this->vault.erase(key);
                    this->vault.insert(std::pair<string, string>(key, value));
                }
                return answer;
            }
            else{
                string answer = "NE\n";
                return answer;
            }

        case 2:
            if(words.size() == 2){
                string key = words[1];
                string answer = "";

                map<string, string>::iterator it = this->vault.find(key);
                if (it == vault.end())
                    answer = "NE\n";
                else
                    answer = "OK res " + it->second + "\n";

                return answer;
            }
            else{
                string answer = "NE\n";
                return answer;
            }

        case 3:
            if(words.size() == 2){
                string key = words[1];

                string answer = "";
                if (this->vault[key] == "")
                {
                    answer = "NE\n";
                }
                else{
                    answer = "OK " + this->vault[key] + "\n";
                    this->vault.erase(key);
                }
                return answer;
            }
            else{
                string answer = "NE\n";
                return answer;
            }

        case 4:
            if(words.size() == 1){
                int s = this->vault.size();
                stringstream ss;
                ss << s;
                string answer = ss.str() + "\n";
                return answer;
            }
            else{
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
                        str = it->first + " " + it->second + "\n";
                        file << str;
                    }
                    file.close();
                    answer = "OK\n";
                }
                else{
                    cout << "Error opening file for writing!" << endl;
                    answer = "NE\n";
                }
                return answer;
            }
            else{
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
                            read_pair.push_back(st);
                        }

                        string key = read_pair[0];
                        string value = read_pair[1];

                        this->vault.insert(pair<string, string>(key, value));
                    }
                    file.close();
                    string answer = "OK\n";
                    return answer;
                }
                else{
                    cout << "Error opening the file for reading!" << endl;
                    string answer = "NE\n";
                    return answer;
                }
            }
            else{
                    cout << "Error opening the file for reading!" << endl;
                    string answer = "NE\n";
                    return answer;
            }

        case 10:
            return "EXIT\n";



        case 0:
            string answer = "Acceptable commands:\nPUT <key> <value>\nGET<key>\nDEL<key>\nCOUNT\n";
            return answer;
    }
}

