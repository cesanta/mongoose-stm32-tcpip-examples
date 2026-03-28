# STM32 Mongoose TCP/IP

This repository contains example Mongoose projects for various STM32 development boards.
[Mongoose](https://mongoose.ws/) is a networking library which includes built-in TCP/IP stack, TLS, HTTP, WebSocket, MQTT and firmware updates. Mongoose is a lightweight, 2-file alternative to lwIP or NetX, which is extremely easy to use in either bare metal or RTOS environment.
Mongoose is used by thousands of companies, including NASA who runs it on International
Space Station.

Every board has two direcotories containing projects for different build systems:

```text
BOARD-NAME/
          make/       <--- make+GCC: minimal, pure CMSIS
          cubemx/     <--- CubeMX: Vscode or CubeIDE
```

All projects implement the same core functionality: a professional Web UI dashboard with LED control and OTA firmware update.

<div align="center">
  <img src="screenshot.webp" alt="Mongoose Wizard dashboard" width="75%"/>
</div>

## make

The `make` project is the most minimal bare-metal implementation. It uses only Mongoose and CMSIS headers and no external frameworks or vendor libraries. It includes lightweight `hal.c` / `hal.h` implemented directly on top of CMSIS. Best suited for understanding low-level
integration, and production firmware with full control over the stack.

To build and run,
1. [Set up your build environment](https://mongoose.ws/docs/getting-started/build-environment/)
2. Clone this repository to your workstation
3. Connect your board to your workstation via Ethernet and ensure the network provides a DHCP server. The simplest setup is to use a USB-to-Ethernet adapter, enable Internet sharing on your workstation, and plug the board directly into that adapter.
4. Start serial console in a separate window
5. Flash the firmware using [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)
6. In the serial log, see the board's IP address, and load that IP address in the browser
7. To test firmware updates, make a change to the firmware, rebuild the firmware,
   then click on the firmware update button on the Firmware Update page,
   and choose the built `firmware.bin` file.

## CubeMX

The `cubemx` project provides STM32CubeMX-based setup. It includes a `.ioc` configuration file, and comes with integration instructions in README.md . To build and run,

1. Follow the instructions in the project's REAMDE.md file to build a firmware
2. Start serial console in a separate window
3. In the serial log, see the board's IP address, and load that IP address in the browser
4. To test firmware updates, make a change to the firmware, rebuild the firmware,
   then click on the firmware update button on the Firmware Update page,
   and choose the built `.bin` file in the `build/Debug/` directory

## Customising for production

The functionality is identical across all variants and is built using the [Web UI Builder](https://mongoose.ws/wizard/). To customize the dashboard for your production firmware,
1. Open [Web UI Builder](https://mongoose.ws/wizard/) in the Chrome or Bing browser
2. Click "Load" on the toolbar, choose `desktop/mongoose/mongoose_wizard.json`
3. In the "Settings" tab on the bottom panel, choose `desktop` as the output directory
4. Make the required changes
5. Click on the "Generate C/C++ code" on top right
6. Done! Now you can rebuild your embedded project, and it'll have an updated UI.

Note - no frontend or networking expertise is required.
See [Mongoose YouTube Videos](https://www.youtube.com/@mongoose-networking-library/videos)
for the reference.
