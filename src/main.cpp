#include "main.hpp"


// Sensor manager
SensorManager sensorManager;

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

    // Initialize and register sensors
    //ESP_LOGI(TAG, "Initializing sensors...");
    //status = initializeSensors();
    //if (status != ESP_OK) {
    //    ESP_LOGE(TAG, "Failed to initialize sensors: %s", esp_err_to_name(status));
    //    return;
    //}

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