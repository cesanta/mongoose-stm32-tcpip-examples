# Mongoose CubeMX integration

## Generate project code
- Clone this repo to your workstation. Open the .ioc file in your CubeMX
- Click on "Project Manager"
  - If you're using CubeIDE, select "CubeIDE" in the toolchain/IDE dropdown
  - If you're using VSCode, select "Cmake" in the toolchain/IDE dropdown
- Click "Generate Code" button on the top right

This should generate project code in this directory the directory where .ioc file lives.
Open this directory in your IDE.

## Add `mongoose_config.h`

Add `Core/Inc/mongoose_config.h` file with the following contents:
```c
#define MG_ARCH MG_ARCH_CUBE
#define MG_ENABLE_PACKED_FS 1
```

This file contains Mongoose settings. As you can see, there only a few settings
to set. Unlike other software, Mongoose does not provide you with dozens of
options you have no clue about.
However if you want to know about all settable build options, see https://mongoose.ws/docs/getting-started/build-options/

## Add Mongoose files to the build

This examples repo contains project for various architectures. Since Mongoose
is cross-platform, one of the architectures is "desktop" - that's your workstation:
Windows, Linux or Mac.

The networking functionality on all these architectures is absolutely identical.
Only the `mongoose_config.h` may be different.

The "desktop" project has the actual Mongoose files. On this step, we tell our IDE to pick
Mongoose files from the "desktop" project. This way we avoid duplication of identical
files for every single project.

- If you're using CubeIDE right click on the project name on the left tree view,
  select New / Folder, Advanced, Link to alternate location, then select
  `desktop/mongoose` in this repo. When it is added, right-click on it and choose
  "Add/remove include path".
- If you're using VSCode, edit two sections in the top-level `CMakeLists.txt`:

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

6. Configure your IDE to generate .bin firmware flash image file.
- If you're using CubeIDE, select Project / Properties / C/C++ build / Settings
  / MCU/MPU Post build outputs, enable "Convert to binary file (-O binary)"
- If you're using VSCode, add a section to the end of the top-level `CMakeLists.txt`:
```cmake
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary
          ${PROJECT_NAME}.elf
          ${PROJECT_NAME}.bin
)
```

## Call Mongoose from main.c

Edit `Core/Src/main.c` and update the following snippets - notice the `USER CODE BEGIN` / `USER CODE END` placeholders. At the top of the file:

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
  data->led2 = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_4);
  data->led3 = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_4);
}

void my_set_leds(struct leds *data) {
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, data->led1);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, data->led2);
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, data->led3);
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

## Build, flash, test

Build the firmware. See [top level README](../../README.md#cubemx) on how to test it
