#include "serial.h"

#define MAX_MESSAGE_SIZE 100
#define TERMINAL         "/dev/tty.usbmodem1101"

// https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
int main() {
    int fd = open(TERMINAL, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", TERMINAL, strerror(errno));
        return -1;
    }

    serial_set_interface_attribs(fd, B115200);

    char buffer[MAX_MESSAGE_SIZE];
    fgets(buffer, MAX_MESSAGE_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    printf("%s\n", buffer);

    //    do {
    //        unsigned char buf[80];
    //        long len = read(fd, buf, sizeof(buf) - 1);
    //
    //        if (len > 0) {
    //            buf[len] = 0;
    //            buf[strcspn(buf, "\n")] = 0;
    //            printf("%s\n", buf);
    //        } else if (len < 0) {
    //            printf("Error from read: %ld: %s\n", len, strerror(errno));
    //        } else {
    //            printf("Timeout from read\n");
    //        }
    //    } while (1);
}
