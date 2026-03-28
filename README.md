# STM32 Mongoose TCP/IP

This repository contains example projects for Mongoose TCP/IP stack
integration for various STM32 development boards. Every board has
two projects:

```text
BOARD-NAME/
          make/       <--- a minimal, pure CMSIS implementation
          cubemx/     <--- CubeMX / vscode implementation
```

Each project demonstrates the same core functionality: aProfessional Web UI dashboard (LED control + OTA firmware update) and MQTT-based remote device control and OTA updates

<center>
  <img src="screenshot.webp" alt="Mongoose Wizard dashboard" width="75%"/>
</center>


The `make` project is the most minimal bare-metal implementation. It uses only Mongoose and CMSIS headers, no external frameworks or vendor libraries. It includes lightweight `hal.c` / `hal.h` implemented directly on top of CMSIS. Best suited for understanding low-level
integration, and production firmware with full control over the stack. In order to build
these projects on your workstation, [set up your build environment](https://mongoose.ws/docs/getting-started/build-environment/).

The `cubemx` project provides STM32CubeMX-based setup. It includes a `.ioc` configuration file, and comes with integration instructions in README.md . Workflow:
1. Open the `.ioc` file in STM32CubeMX  
2. Generate a project (VS Code, CubeIDE, or any IDE)  
3. Follow the README to integrate Mongoose  

This project is best suited for developers familiar with CubeMX ecosystem.


All projects functionality is identical and built using the Mongoose Visual  
[Web UI Builder](https://mongoose.ws/wizard/) . It is easy to alter its functionality and build a production firmware -
just load the `mongoose/mongoose_wizard.json` in the Web UI builder
and start altering it. No frontend or network programming skills are required.
