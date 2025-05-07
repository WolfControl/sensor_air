#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "cJSON.h"
#include "messaging.h"
#include "provisioning.h"
#include "sensor_manager.hpp"
#include "sensor_interface.hpp"

// ---------- sensor.h ---------- //

// Sensor manager
extern SensorManager sensorManager;


// ---------- provisioning.h ---------- //

char *nodes[] = {
    "Temp",
};

const int numNodes = sizeof(nodes) / sizeof(nodes[0]);


EventGroupHandle_t adoption_event_group;

TimerHandle_t heartbeatTimer;
int s_retry_num = 0;

char* deviceId;
char* espnowmac;

esp_now_peer_info_t gatewayPeer;
uint8_t* gatewayAddress;
SemaphoreHandle_t mutex;

const char* firmwareVersionClient = "SETDURINGCOMPILATION";

// ---------- messaging.h ---------- //

esp_now_peer_info_t broadcastPeer;
TaskHandle_t receiveESPNowTaskHandle, sendESPNowTaskHandle;
QueueHandle_t incomingESPNowQueue, outgoingESPNowQueue;

// ---------- led.h ---------- //

rgb_led_t bootLED = {
    LEDC_CHANNEL_0,
    5,
    LEDC_CHANNEL_1,
    6,
    LEDC_CHANNEL_2,
    7};
 
led_t activityLED1 = {LEDC_CHANNEL_6, 8};

// Unused LEDs
rgb_led_t connectivityLED = {};
led_t activityLED2 = {};


