#ifndef WEARABLE_CONNECTION_VARIABLES

#define WEARABLE_CONNECTION_VARIABLES

//Info about your network
#define WIFI_SSID "Your Network Name"
#define WIFI_PWD "Your Network Password"

//Info about the destination device for the data
#define DST_PORT 8000
IPAddress hostIP(10, 0, 1, 2);

//Info about accepting connections
#define RETURN_PORT 9000

//Sensor Sample Rate (1hz - 100hz)
#define SENSOR_SAMPLE_RATE 10

//Sensor OSC output Address
#define OSC_ADDR "/sensor1"

#endif
