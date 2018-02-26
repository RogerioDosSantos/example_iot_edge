
# Project documentation

# Introduction

Example on how to use the *Microsoft IoT Edge SDK*

## More Information

- [Azure IoT device SDK for C (Documentation)]( https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-device-sdk-c-intro )
- [Microsoft Azure IoT SDKs and libraries for C (Git Repository)]( https://github.com/Azure/azure-iot-sdk-c )
- [Microsoft Azure IoT Device SDK for C (API reference)]( https://azure.github.io/azure-iot-sdk-c/index.html )

## Steps

- [Create an IoT hub using the Azure portal]( https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-create-through-portal )
    - [Create an Azure account]( https://azure.microsoft.com/en-us/ )
    - [Create an IoT Hub]( https://portal.azure.com/#create/Microsoft.IotHub )
        - Name: iotedgeexample
        - Resource Group: examples
        - Price and Tier: free 
        - Location: West US
        - Event Hub Compatible Name: iothub-ehub-iotedgeexa-366274-dc6d27cefc
        - Event Hub Compatible Endpoint: Endpoint=sb://ihsuprodbyres019dednamespace.servicebus.windows.net/;SharedAccessKeyName=iothubowner;SharedAccessKey=C5h93KWLcrrnvxi41+7Ay8OlSFlCAdvCRdnLVDOTVp8=
        -
        

## How to compile

### Linux

- Run */build/compile_linux_default.sh*

### Windows

- Open *The project on Visual Studio (2017 or later)* using the *Open CMAKE* option.
- Compile the desired projects

## Output location and details

  The compiled binaries will be located on the */stage* folder which follows the structure below:

      /stage
      ├── build
      │   └── cmake - CMake project files that can be used on to find the libraries by other projects
      │       ├── project-config.cmake
      │       └── project-configversion.cmake
      ├── include
      │       └── project.h
      └── Linux-4.4.0-43-Microsoft - It can change depending on the platform
          └── x86_64 - It can change depending on the platform
              ├── bin
              │   └── project - Executable or shared libraries
              ├── lib
              │   └── project.a - Static libraries
              └── cmake - CMake target for that specific platform
                  ├── project.cmake
                  └── project-noconfig.cmake

