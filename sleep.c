#define DEFAULT_WAKEUP_LEVEL    ESP_GPIO_WAKEUP_GPIO_HIGH
#define WATER_PIN /*input pin for the water meter*/

void Sleeper24hr(){
  esp_sleep_enable_ext0_wakeup(pin, DEFAULT_WAKEUP_LEVEL); //Enable waqkeup from external input - tied to water meter input pin
  esp_deep_sleep_start(8.64E10); //Enable wakeup from internal timer clock - 24hrs in microseconds (8.64x10^10us)
}
