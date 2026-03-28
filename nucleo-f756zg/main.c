// Copyright (c) 2026 Cesanta Software Limited
// All rights reserved

#include "hal.h"
#include "mongoose_glue.h"

#define DEBUG_UART USART3
#define LED1 PIN('B', 0)
#define LED2 PIN('B', 7)
#define LED3 PIN('B', 14)

int _write(int fd, char *ptr, int len) {
  if (fd == 1) hal_uart_write_buf(DEBUG_UART, ptr, (size_t) len);
  return len;
}

static void blink_task(void) {
  static uint64_t blink_timer = 0;
  if (hal_timer_expired(&blink_timer, 500, hal_get_tick())) {
    hal_gpio_toggle(LED1);
    printf("Tick: %lu\r\n", (unsigned long) hal_get_tick());
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

void my_get_leds(struct leds *data) {
  data->led1 = hal_gpio_read(LED1);
  data->led2 = hal_gpio_read(LED2);
  data->led3 = hal_gpio_read(LED3);
}
void my_set_leds(struct leds *data) {
  hal_gpio_write(LED1, data->led1);
  hal_gpio_write(LED2, data->led2);
  hal_gpio_write(LED3, data->led3);
}

int main(void) {
  hal_clock_init();
  hal_rng_init();
  hal_gpio_output(LED1);
  hal_uart_init(DEBUG_UART, 115200);
  printf("Initialised. CPU clock: %lu\r\n", SystemCoreClock / 1000000);

  mongoose_init();
  mongoose_set_http_handlers("leds", my_get_leds, my_set_leds);

  for (;;) {
    mongoose_poll();
    blink_task();
  }

  return 0;
}
