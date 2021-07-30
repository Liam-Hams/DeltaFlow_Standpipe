// FLOW COUNTING FUNCTION - UPDATES GLOBAL FLOW VARIABLES

void flowCount() {
  // Define time variable & store current time
  unsigned long last_pulse = millis();
  // Loop until timeout
  bool pulse_check = LOW;
  while ((millis() - last_pulse) < PULSE_TIMEOUT) {
    // If a pulse is detected, iterate pulse count
    bool data_read = digitalRead(FLOW_PIN);
    if (data_read == HIGH && data_read != pulse_check) {
      pulse_count++;
      last_pulse = millis();
      pulse_check = HIGH;
    }
    else if(data_read == LOW && data_read != pulse_check){
      pulse_check = LOW;
    }
  }
  SerialMon.print("Flow Usage = ");
  SerialMon.println(pulse_count);
  total_pulses = total_pulses + pulse_count;
  SerialMon.print("Total Usage = ");
  SerialMon.println(total_pulses);
  pulse_count = 0;
}
