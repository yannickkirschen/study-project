#include "hardware/uart.h"

#include <stdio.h>

#include "hardware/irq.h"
#include "pico/stdlib.h"

#define UART_ID_1     uart0
#define UART_ID_2     uart1
#define BAUD_RATE     115200
#define DATA_BITS     8
#define STOP_BITS     1
#define PARITY        UART_PARITY_NONE

#define UART_1_TX_PIN 0
#define UART_1_RX_PIN 1

#define UART_2_TX_PIN 4
#define UART_2_RX_PIN 5

void on_uart_rx_1() {
    printf("Received message on UART0 (UART_ID_1)\n");

    while (uart_is_readable(UART_ID_2)) {
        if (uart_is_writable(UART_ID_1)) {
            uart_puts(UART_ID_1, "ping\n");
            printf("ping\n");
        }
    }
}

void on_uart_rx_2() {
    printf("Received message on UART1 (UART_ID_2)\n");

    while (uart_is_readable(UART_ID_1)) {
        if (uart_is_writable(UART_ID_2)) {
            //            uart_puts(UART_ID_2, "pong\n");
            printf("pong\n");
        }
    }
}

int main() {
    stdio_init_all();

    uart_init(UART_ID_1, 2400);
    uart_init(UART_ID_2, 2400);

    gpio_set_function(UART_1_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_1_RX_PIN, GPIO_FUNC_UART);

    gpio_set_function(UART_2_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_2_RX_PIN, GPIO_FUNC_UART);

    uart_set_baudrate(UART_ID_1, BAUD_RATE);
    uart_set_baudrate(UART_ID_2, BAUD_RATE);

    uart_set_hw_flow(UART_ID_1, false, false);
    uart_set_hw_flow(UART_ID_2, false, false);

    uart_set_format(UART_ID_1, DATA_BITS, STOP_BITS, PARITY);
    uart_set_format(UART_ID_2, DATA_BITS, STOP_BITS, PARITY);

    uart_set_fifo_enabled(UART_ID_1, false);
    uart_set_fifo_enabled(UART_ID_2, false);

    int UART_IRQ_1 = UART0_IRQ;
    int UART_IRQ_2 = UART1_IRQ;

    irq_set_exclusive_handler(UART_IRQ_1, on_uart_rx_1);
    irq_set_exclusive_handler(UART_IRQ_2, on_uart_rx_2);

    irq_set_enabled(UART_IRQ_1, true);
    irq_set_enabled(UART_IRQ_2, true);

    uart_set_irq_enables(UART_ID_1, true, false);
    uart_set_irq_enables(UART_ID_2, true, false);

    //    printf("\nWaiting to start...\n");
    sleep_ms(5000);

    uart_puts(UART_ID_1, "ping\n");

    while (1)
        tight_loop_contents();
}
