#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <azure_c_shared_utility/crt_abstractions.h>
#include <azure_c_shared_utility/optimize_size.h>
#include <azure_c_shared_utility/platform.h>
#include <azure_c_shared_utility/shared_util_options.h>
#include <azure_c_shared_utility/threadapi.h>
#include <iothub_client.h>
#include <iothub_client_options.h>
#include <iothub_message.h>
#include <iothubtransportamqp.h>

// #ifdef MBED_BUILD_TIMESTAMP
// #define SET_TRUSTED_CERT_IN_SAMPLES
// #endif // MBED_BUILD_TIMESTAMP
//
// #ifdef SET_TRUSTED_CERT_IN_SAMPLES
// #include "certs.h"
// #endif // SET_TRUSTED_CERT_IN_SAMPLES

bool RunIoTDevice(const char* hub_name, const char* hub_domain, const char* device_id, const char* device_key)
{
    printf("Starting Device:\n\t- IoT Hub URL: %s.%s\n\t- Device ID: %s\n\t- Device Key: %s\n", hub_name, hub_domain, device_id, device_key);

    if (platform_init() != 0)
    {
        printf("ERROR: Failed to initialize the platform.\n");
        return false;
    }

    TRANSPORT_HANDLE transport = IoTHubTransport_Create(AMQP_Protocol, hub_name, hub_domain);
    if (transport == NULL)
    {
        platform_deinit();
        printf("ERROR: Failed to creating the protocol handle.\n");
        return false;
    }

    IOTHUB_CLIENT_CONFIG client_config;
    client_config.deviceId = device_id;
    client_config.deviceKey = device_key;
    client_config.deviceSasToken = NULL;
    client_config.iotHubName = hub_name;
    client_config.iotHubSuffix = hub_domain;
    client_config.protocol = AMQP_Protocol;
    client_config.protocolGatewayHostName = NULL;

    IOTHUB_CLIENT_HANDLE iot_hub_client = IoTHubClient_CreateWithTransport(transport, &client_config);
    if (iot_hub_client == NULL)
    {
        printf("ERROR: Could not create the IoT Hub client.\n");
        IoTHubTransport_Destroy(transport);
        platform_deinit();
        return false;
    }




    IoTHubTransport_Destroy(transport);
    platform_deinit();
    return true;
}

int main(int argc, char const* argv[])
{
    std::string arguments[5];
    switch (argc)
    {
    case 6:
        arguments[4] = argv[5];
    case 5:
        arguments[3] = argv[4];
    case 4:
        arguments[2] = argv[3];
    case 3:
        arguments[1] = argv[2];
    case 2:
        arguments[0] = argv[1];
        break;
    default:
        break;
    }

    if (!arguments[0].compare("run"))
        RunIoTDevice(arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
    else
        std::cout << "Invalid Command (" << argc << "):\n\t" << arguments[0] << "\nOptions:\n"
                  << "\nrun <hub_name> <hub_domain> <device_id> <device_key>\n\t\t-E.g.: run \"iotedgeexample\" \"azure-devices.net\" "
                     "\"iot_edge_device_example\" \"5CiOHu2MJWVxHgPcue6dHaz91FF3410tnvzpUmjX4s4=\"\n"
                  << "\n";

    return 0;
}
