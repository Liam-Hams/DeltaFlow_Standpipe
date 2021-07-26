// MAIN FILE (BASE EDITION)

//Global Variables
int bootcount = 0; // Global variable for number of times woken.
int wake_cause = 0; // Global variable to track current cause of waking.

void setup() {
  // put your setup code here, to run once:
  // Initiate serial monitor output. Debugging only - to be replaced with 4G connectivity.
  Serial.begin(115200);
  // Enable sleep wakeup methods (timer & ext wakeup)
  esp_sleep_enable_timer_wakeup(5000000);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_7,1);
}

void loop() {
  // PROGRAM START
  bootcount++;
  if (bootcount > 1) {
    Serial.println("Program commence");
  }
  else {
    switch (wake_cause) {
      case 4:
        // transmission4G
        Serial.println("Woke from timer overflow");
        break;
      case 3:
        // transmission4G
        Serial.println("Woke from external Interrupt");
        break;
    }
  }
  esp_light_sleep_start();

}

float flow_count(){
  // Function for counting pulses from encoder.
  // Returns flow value as a float for precision.
}

void transmission4G(){
  // Function to facilitate 4G transmisison of data to server.
  // Split into two parts - 24hr wakeup cycle & flow counting
  switch (wake_cause) {
    case 4:
      // Timer wakeup cycle
      // Send location & time only
      break;
    case 3:
      // Flow Counting wakeup
      // Send flow, location & time
      break;
  }
}

void network_test(){
  // Function for checking network status
  // If online, continue as normal. If offline, start timer & store data locally in temporary struct.
}
