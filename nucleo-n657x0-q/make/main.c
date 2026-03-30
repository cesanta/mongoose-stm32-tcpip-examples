// Copyright (c) 2026 Cesanta Software Limited
// All rights reserved

#include "hal.h"
#include "mongoose_glue.h"

#define DEBUG_UART USART1
#define UART_TX PIN('E', 5)
#define UART_RX PIN('E', 6)

#define LED_1 PIN('G', 0)   // Green LED
#define LED_2 PIN('G', 8)   // Blue LED
#define LED_3 PIN('G', 10)  // Red LED

// Redirect stdout debug output to UART
int _write(int fd, char *ptr, int len) {
  if (fd == 1) hal_uart_write_buf(DEBUG_UART, ptr, (size_t) len);
  return len;
}

// Blink green LED every 500ms
static void blink_task(void) {
  static uint64_t blink_timer = 0;
  if (hal_timer_expired(&blink_timer, 500, hal_get_tick())) {
    hal_gpio_toggle(LED_1);
  }
}

uint64_t mg_millis(void) {
  return hal_get_tick();
}

bool mg_random(void *buf, size_t len) {
  for (size_t n = 0; n < len; n += sizeof(uint32_t)) {
    uint32_t r = hal_rng_read();
    memcpy((char *) buf + n, &r, n + sizeof(r) > len ? len - n : sizeof(r));
  }
  return true;
}

// void my_get_leds(struct leds *data) {
//   data->led1 = hal_gpio_read(LED1);
//   data->led2 = hal_gpio_read(LED2);
//   data->led3 = hal_gpio_read(LED3);
// }
// void my_set_leds(struct leds *data) {
//   hal_gpio_write(LED1, data->led1);
//   hal_gpio_write(LED2, data->led2);
//   hal_gpio_write(LED3, data->led3);
// }

int main(void) {
  hal_uart_init(DEBUG_UART, UART_TX, UART_RX, 115200);
  hal_rng_init();
  // hal_ethernet_init();

  // Initialise pins and turn them off: they are active high
  hal_gpio_output(LED_1), hal_gpio_write(LED_1, true);
  hal_gpio_output(LED_2), hal_gpio_write(LED_2, true);
  hal_gpio_output(LED_3), hal_gpio_write(LED_3, true);

  printf("Initialised. CPU clock: %lu MHz\r\n", SystemCoreClock / 1000000);
  printf("APB1: %u, APB2: %u\r\n", HAL_APB1_FREQUENCY, HAL_APB2_FREQUENCY);

  // mongoose_init();
  // mongoose_set_http_handlers("leds", my_get_leds, my_set_leds);

  for (;;) {
    // mongoose_poll();
    blink_task();
  }

  return 0;
}
