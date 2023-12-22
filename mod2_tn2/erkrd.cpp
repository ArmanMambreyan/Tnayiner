#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;




int sigusr2_count = 0;

void sigint_handler(int signum) {
    cout << "SIGUSR2 stacvats" << sigusr2_count << endl;
    exit(0);
}

void sigusr1_handler(int signum) {
    cout << "chexarkum" << endl;
}

void sigusr2_handler(int signum) {
    sigusr2_count++;
}




int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);


  
    while (true) {
        cout << "Der goyutyun uni" << endl;
        sleep(5);
    }

    return 0;
}
