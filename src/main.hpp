#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "cJSON.h"
#include "messaging.h"
#include "provisioning.h"
#include "sensor_manager.hpp"
#include "sensor_interface.hpp"
#include "bme280_adapter.hpp"
#include "bme280_i2c.hpp"

// ---------- sensor manager / interface ---------- //

// Sensor manager
extern SensorManager sensorManager;

// BME280 object
extern BME280 *bme280;

// BME280Adapter object
extern BME280Adapter* bme280Adapter;


// ---------- provisioning.h ---------- //

char *nodes[] = {
    "TMP",
    "PRS",
    "HUM",
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


