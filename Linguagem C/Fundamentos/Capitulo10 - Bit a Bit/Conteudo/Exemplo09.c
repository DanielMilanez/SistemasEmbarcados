#include <stdint.h>
#include <stdio.h>

typedef struct data_port {
    unsigned P0 : 1;
    unsigned P1 : 1;
    unsigned P2 : 1;
    unsigned P3 : 1;
    unsigned P4 : 1;
    unsigned P5 : 1;
    unsigned P6 : 1;
    unsigned P7 : 1;
} data_port;

void Bin_convert(uint8_t data, data_port *port);

int main(void) {
    data_port myPort;
    uint8_t hexValue = 0x01; // Exemplo: 0xA5 = 10100101 em binário

    Bin_convert(hexValue, &myPort);

    return 0;
}

void Bin_convert(uint8_t data, data_port *port) {
    port->P0 = (data >> 7) & 1;
    port->P1 = (data >> 6) & 1;
    port->P2 = (data >> 5) & 1;
    port->P3 = (data >> 4) & 1;
    port->P4 = (data >> 3) & 1;
    port->P5 = (data >> 2) & 1;
    port->P6 = (data >> 1) & 1;
    port->P7 = (data >> 0) & 1;

    printf("P0: %d\n", port->P0);
    printf("P1: %d\n", port->P1);
    printf("P2: %d\n", port->P2);
    printf("P3: %d\n", port->P3);
    printf("P4: %d\n", port->P4);
    printf("P5: %d\n", port->P5);
    printf("P6: %d\n", port->P6);
    printf("P7: %d\n", port->P7);
}
