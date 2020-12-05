#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <iostream>
using namespace std;

string getCurrentDateTime(string s)
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    if (s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return string(buf);
};

int main()
{
    int fd;

    if ((fd = serialOpen("/dev/ttyACM0", 9600)) < 0)
    {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }

    for (;;)
    {
        string now = getCurrentDateTime("now");
        freopen("output.txt", "a", stdout);

        cout << now << " :: " << serialGetchar(fd) << endl;

        usleep(10);
    }
}
