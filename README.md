# Mongoose TCP/IP examples for STM32

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

The `make` project is the most minimal bare-metal implementation. It uses only Mongoose and CMSIS headers, with no external frameworks or vendor libraries. It includes lightweight `hal.c` / `hal.h` implemented directly on top of CMSIS. This variant is best suited for understanding low-level integration and building production firmware with full control over the stack.

To build and run,

1. [Set up your build environment](https://mongoose.ws/docs/getting-started/build-environment/)  
2. Clone this repository to your workstation  
3. Connect your board to your workstation via Ethernet and ensure the network provides a DHCP server. The simplest setup is to use a USB-to-Ethernet adapter, enable Internet sharing on that adapter, and plug the board into that adapter  
4. Start a serial console in a separate window  
5. Flash the firmware using [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)  
6. Check the serial log for the board's IP address and open it in a browser  
7. To test firmware updates, make a change to the firmware and rebuild it,  
   then click the firmware update button on the Firmware Update page  
   and select the generated `firmware.bin` file  

## CubeMX

The `cubemx` project provides an STM32CubeMX-based setup. It includes a `.ioc` configuration file and comes with integration instructions in README.md. To build and run,

1. Follow the instructions in the project's README.md file to build the firmware  
2. Start a serial console in a separate window  
3. Check the serial log for the board's IP address and open it in a browser  
4. To test firmware updates, make a change to the firmware and rebuild it,  
   then click the firmware update button on the Firmware Update page  
   and select the generated `.bin` file from the `build/Debug/` directory

## Customising for production

The functionality is identical across all projects and is built using the [Web UI Builder](https://mongoose.ws/wizard/). To customize the dashboard for your production firmware,

1. Open the [Web UI Builder](https://mongoose.ws/wizard/) in Chrome or Bing  
2. Click "Load" on the toolbar and select `desktop/mongoose/mongoose_wizard.json`  
3. In the "Settings" tab at the bottom panel, set the output directory to `desktop`  
4. Make the required changes  
5. Click "Generate C/C++ code" in the top right corner  
6. Done - rebuild your embedded project to apply the updated UI  

Note - no frontend or networking expertise is required. References and guides:
- [Mongoose YouTube Videos](https://www.youtube.com/@mongoose-networking-library/videos)
- [Board pinouts reference](https://mongoose.ws/docs/hardware/board-pinouts/)

## Commercial use

Mongoose is dual-licensed: GPLv2 and commercial. Use GPLv2 for evaluation and prototyping.
Choose a commercial license when shipping production devices.

Request a quote using the [quotation form](https://mongoose.ws/quote/) - we typically respond the same day. We also offer support, consultancy, and integration services.

[Schedule a free, hands-on 45-minute session](https://calendar.app.google/QYLx4VD9is1PnYCG8) with a Mongoose engineer to troubleshoot or optimize development on your own hardware. Have your device and development environment ready.

For any questions, please contact us at support@cesanta.com
