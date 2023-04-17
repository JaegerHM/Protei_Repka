#include <iostream>

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    CRITICAL,
    ERROR
};

class LOG {
public:
    LOG() {}
    LOG(typelog type) {
        msglevel = type;
        operator << ("["+getLabel(type)+"]");
    }
    ~LOG() {
        if(opened) {
            cout << endl;
        }
        opened = false;
    }
    template<class T> LOG &operator<<(const T &msg) {

        cout << msg;
        opened = true;
        return *this;
    }

private:
    bool opened = false;
    typelog msglevel = INFO;
    inline string getLabel(typelog type) {
        string label;
        switch(type) {
            case DEBUG: label = "DEBUG"; break;
            case INFO:  label = "INFO"; break;
            case WARN:  label = "WARN"; break;
            case CRITICAL:  label = "CRITICAL"; break;
            case ERROR: label = "ERROR"; break;
        }
        return label;
    }
};
