
# Project documentation

# Introduction

Example on how to use the *Microsoft IoT Edge SDK*

## More Information

- [Azure IoT device SDK for C (Documentation)]( https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-device-sdk-c-intro )
- [Microsoft Azure IoT SDKs and libraries for C (Git Repository)]( https://github.com/Azure/azure-iot-sdk-c )
- [Microsoft Azure IoT Device SDK for C (API reference)]( https://azure.github.io/azure-iot-sdk-c/index.html )

## Steps

### Azure portal registration

- [Create an IoT hub using the Azure portal]( https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-create-through-portal )
    - [Create an Azure account]( https://azure.microsoft.com/en-us/ )
    - [Create an IoT Hub]( https://portal.azure.com/#create/Microsoft.IotHub )
        - Name: iotedgeexample
        - Resource Group: examples
        - Price and Tier: free 
        - Location: West US
        - Event Hub Compatible Name: iothub-ehub-iotedgeexa-366274-dc6d27cefc
        - Event Hub Compatible Endpoint: Endpoint=sb://ihsuprodbyres019dednamespace.servicebus.windows.net/;SharedAccessKeyName=iothubowner;SharedAccessKey=C5h93KWLcrrnvxi41+7Ay8OlSFlCAdvCRdnLVDOTVp8=
        - Host name: iotedgeexample.azure-devices.net
        - Connection String Primary Key: HostName=iotedgeexample.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=C5h93KWLcrrnvxi41+7Ay8OlSFlCAdvCRdnLVDOTVp8=
    - To allow *bi-directional* communication with *Azure IoT Hub* it will be necessary to use the [Microsoft Azure IoT Protocol Gateway]( https://github.com/Azure/azure-iot-protocol-gateway )

### Compiling Microsoft Iot Edge

    - Prepare the Linux Environment:
``` sh
sudo apt-get update
sudo apt-get install -y git cmake build-essential curl libcurl4-openssl-dev libssl-dev uuid-dev pkg-config
```
		- Clone the project and all submodules
		- Init all submodules recursivelly. 
``` sh
git submodule update --init --recursive
```
    - Compile it. 
``` sh
mkdir cmake
cd ./cmake

# for release
cmake ..

# for debug with tests
cmake -Drun_e2e_tests=ON -Drun_unittests=ON -DCMAKE_BUILD_TYPE=Debug ..
``` 
    - The toolkit has several examples located at *azure-iot-sdk-c/iothub_client/samples*

### Setting the Device Credentials

    - Download and install the [Device Explorer]( https://github.com/Azure/azure-iot-sdk-csharp/releases )
    - Inform the host name. Instructions to find the HostName can be found [here](https://github.com/Azure/azure-iot-sdk-csharp/blob/master/doc/setup_iothub.md) 
    - On the Management tab create a new device:
        - Device name: iot_edge_device_example
        - PrimaryKey: 5CiOHu2MJWVxHgPcue6dHaz91FF3410tnvzpUmjX4s4=
        - SecondaryKey: drTuxzMdQNA9tsw0wQmfCLKKaLaCxfMH0kFqh2yzbmc=
        - Device connection string: HostName=iotedgeexample.azure-devices.net;DeviceId=iot_edge_device_example;SharedAccessKey=5CiOHu2MJWVxHgPcue6dHaz91FF3410tnvzpUmjX4s4=

### Change and compile the sample

    - Edit the sample source code *azure-iot-sdk-c/iothub_service_client/samples/iothub_client_sample_amqp_shared.c* to have your device configuration:
``` c
static const char* hubName = "iotedgeexample";
static const char* hubSuffix = "azure-devices.net";
static const char* deviceId1 = "iot_edge_device_example";
static const char* deviceId2 = "";
static const char* deviceKey1 = "5CiOHu2MJWVxHgPcue6dHaz91FF3410tnvzpUmjX4s4=";
static const char* deviceKey2 = "drTuxzMdQNA9tsw0wQmfCLKKaLaCxfMH0kFqh2yzbmc=";
``` 
    - Go to the *~/roger/third-party/iot_edge/azure-iot-sdk-c/cmake/iothub_client/samples/* and use `make` to compile your example. 

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

