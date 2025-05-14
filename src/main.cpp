#include "main.hpp"


// Sensor manager
SensorManager sensorManager;

// BME280 object - initialized with address only
BME280 bme280_board(BME280_I2C_ADDRESS_PRIMARY);

// BME280 adapter object - initialized to null, will be created after bus initialization
BME280Adapter* bme280_sensor = nullptr;


esp_err_t initializeBME280() {
    static const char* TAG = "initializeBME280";
    esp_err_t status;
    
    // Create BME280 adapter with the bus handle
    bme280_sensor = new BME280Adapter(sensorManager.getBusHandle());
    
    // Register BME280 with sensor manager
    ESP_LOGI(TAG, "Registering BME280 sensor");
    status = sensorManager.registerSensor(bme280_sensor);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register BME280 sensor: %s", esp_err_to_name(status));
        return status;
    }
    
    return ESP_OK;
}

extern "C" void app_main(void)
{
    static const char* TAG = "MAIN";
    esp_err_t status;

    // Initialize the sensor manager
    ESP_LOGI(TAG, "Initializing sensor manager...");
    status = sensorManager.init();
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize sensor manager: %s", esp_err_to_name(status));
        return;
    }

    // Initialize and register BME280 sensor
    ESP_LOGI(TAG, "Initializing BME280 sensor");
    status = initializeBME280();
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize BME280 sensor: %s", esp_err_to_name(status));
        return;
    }

    ESP_LOGI(TAG, "Setting up WolfClient...");
    status = setupWolfClient(SENSOR_ATMOSPHERE);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize WolfClient: %s", esp_err_to_name(status));
        return;
    }

    // Start the sensor monitoring and reporting
    ESP_LOGI(TAG, "Starting sensor monitoring...");
    status = sensorManager.startMonitoring(gatewayAddress);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start sensor monitoring: %s", esp_err_to_name(status));
        return;
    }

    ESP_LOGI(TAG, "Setup complete.");
}