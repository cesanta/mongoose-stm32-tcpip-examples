# Mongoose CubeMX integration

## Generating Cmake-based VSCode project

1. Clone this repo to your workstation. Open the .ioc file in your CubeMX
2. Click on "Project Manager", select "Cmake" as toolchain/IDE, click "Generate Code" on the right top. It will populate this directory with the generated project code.
3. Open this directory in Vscode. Make sure you have STM32 Cube extension installed
4. Add `Core/Inc/mongoose_config.h` file with the following contents:
```c
#define MG_ARCH MG_ARCH_CUBE
#define MG_ENABLE_PACKED_FS 1
```
5. Edit two sections in the top-level `CMakeLists.txt` to add Mongoose to the build:
```cmake
# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ../../desktop/mongoose/mongoose.c
    ../../desktop/mongoose/mongoose_glue.c
    ../../desktop/mongoose/mongoose_impl.c
    ../../desktop/mongoose/mongoose_fs.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ../../desktop/mongoose/
)
```
6. Add a section to the end of top-level `CMakeLists.txt` to generate .bin file:
```cmake
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary
          ${PROJECT_NAME}.elf
          ${PROJECT_NAME}.bin
)
```
6. Edit `Core/Src/main.c` and update the following snippets - notice the `USER CODE BEGIN` / `USER CODE END` placeholders. At the top of the file:
```c
/* USER CODE BEGIN Includes */
#include "mongoose_glue.h"
/* USER CODE END Includes */
```
Before the `main()` function:
```c
/* USER CODE BEGIN 0 */
int _write(int fd, unsigned char *buf, int len) {
  HAL_UART_Transmit(&huart3, buf, len, HAL_MAX_DELAY);
  return len;
}

void my_get_leds(struct leds *data) {
  data->led1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
  data->led2 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);
  data->led3 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
}

void my_set_leds(struct leds *data) {
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, data->led1);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, data->led2);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, data->led3);
}

// This blocks forever. Call it at the end of main(), or in a
// separate RTOS task. Give that task 8k stack space.
void run_mongoose(void) {
  mongoose_init();
  mongoose_set_http_handlers("leds", my_get_leds, my_set_leds);
  for (;;) {
    mongoose_poll();
  }
}
/* USER CODE END 0 */
```

Inside the `main()` function:
```c
/* USER CODE BEGIN WHILE */
run_mongoose();  // <----------------- Add this line
while (1)
{
  /* USER CODE END WHILE */
```
7. Edit `STM32H723XG_FLASH.ld`, add the following line before the `.bss (NOLOAD)` line:
```text
.eth_ram : { *(.eth_ram .eth_ram*) } > RAM_D2 AT > FLASH
```
8. Build the firmware. See [top level README](../../README.md#cubemx) on how to test it
