// WAKE FUNCTION - WAKES DEVICE & CHECKS WAKEUP CONDITION / PATH
void wake() {
  // Define wake cause variable & find wake cause
  esp_sleep_wakeup_cause_t wake_cause;
  wake_cause = esp_sleep_get_wakeup_cause();
  // Branch program path based on wake cause
  switch (wake_cause) {
    // For flow, count flow & update total
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Woke from flow counter");
      pulse_count++;
      flowCount();
      total_pulses = total_pulses + pulse_count;
      break;
    // For timer, update location only
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Woke from timer overflow");
      break;
  }
  // After every wake cycle, connect to network, send data, and disconnect.
  netConnect();
  gpsLocation();
  httpPost();
  gsmPowerDown();
}
