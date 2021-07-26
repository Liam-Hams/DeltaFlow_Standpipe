// MODEM DEFINITION
#define TINY_GSM_MODEM_SIM7600

// SERIALMON DEFINITION
#define SerialMon Serial

// HARDWARE SERIAL & DEBUG DEFINITION
#define SerialAT Serial1
#define TINY_GSM_DEBUG SerialMon

// GPRS DEFINITIONS
const char apn[]  = "telstra.iph";
const char gprsUser[] = "";
const char gprsPass[] = "";

// VARIABLE DEFINITIONS
#define PULSE_TIMEOUT 60000
#define GPS_TIMEOUT 120000
// Timer value is in microseconds (24hrs = 24*3600*10^6)
/* VALUE SET TO 30s FOR DEBUGGING ONLY */
#define SLEEP_TIME 30000000

// GPIO DEFINTIONS
#define PIN_TX     27
#define PIN_RX     26
#define UART_BAUD  115200
#define PWR_PIN    4
#define POWER_PIN  25
#define LED_PIN    12
#define IND_PIN    36

#define FLOW_PIN   GPIO_NUM_33

// LIBRARY INCLUSIONS
#include <TinyGsmClient.h>
#include <Ticker.h>

// GLOBAL VARIABLES
unsigned int total_pulses = 0;
int pulse_count = 0;
float latitude;
float longitude;


// LIBRARY INSTANCES
Ticker tick;
TinyGsm modem(SerialAT);

//  SETUP FUNCTION
void setup() {
  // Enable sleep wakeups from timer & EXT_0
  esp_sleep_enable_ext0_wakeup(FLOW_PIN, 1);
  esp_sleep_enable_timer_wakeup(SLEEP_TIME);

  // Set flow meter connection as input
  pinMode(FLOW_PIN, INPUT);
  // Commence Serial connection & wait for connection to be established
  SerialMon.begin(115200);
  while (!Serial) {
    ;
  }

  // SIM7600 pin operations & definitions
  // POWER_PIN : This pin controls the power supply of the SIM7600
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);

  // PWR_PIN ： This Pin is the PWR-KEY of the SIM7600
  // The time of active low level impulse of PWRKEY pin to power on module , type 500 ms
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH);
  delay(500);
  digitalWrite(PWR_PIN, LOW);

  // IND_PIN: It is connected to the SIM7600 status Pin,
  // through which you can know whether the module starts normally.
  pinMode(IND_PIN, INPUT);

  attachInterrupt(IND_PIN, []() {
    detachInterrupt(IND_PIN);
    // If SIM7600 starts normally, then set the onboard LED to flash once every 1 second
    tick.attach_ms(1000, []() {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    });
  }, CHANGE);

  // Commence SIM7600 booting process
  DBG("Initialising Modem, please wait...");
  delay(3000);
  SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);
  if (!modem.init()) {
    DBG("Failed to restart modem, delaying 10s and retrying");
    return;
  }

  // Set GSM mode to auto
  bool result;
  do {
    result = modem.setNetworkMode(2);
    delay(500);
  } while (result != true);
}

// LOOP FUNCTION - REINITIATES SLEEP
void loop() {
  wake();
  DBG("Going to sleep for %d s", SLEEP_TIME); 
  esp_light_sleep_start();

}

// FLOW COUNTING FUNCTION - RETURNS TOTAL FLOW FROM LAST USAGE AS AN INT
void flowCount() {
  // Define time variable & store current time
  unsigned long last_pulse = millis();
  // Loop until timeout
  while ((millis() - last_pulse) < PULSE_TIMEOUT) {
    // If a pulse is detected, iterate pulse count
    if (digitalRead(FLOW_PIN == HIGH)) {
      pulse_count++;
      last_pulse = millis();
    }
    // Every 5 pulses, post total flow to serial
    /* DEBUG PURPOSES ONLY. REMOVE IN PRODUCTION */
    if ((pulse_count % 5) == 0) {
      int flow_litres = pulse_count * 100;
      String flow_plot = "Total Flow = " + flow_litres;
      flow_plot = flow_plot + " Litres.";
      DBG(flow_plot);
    }
  }
}

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

// NET CONNECT FUNCTION - RESTARTS MODEM & PERFORMS APN HANDSHAKE
void netConnect() {
  // Initialize modem
  DBG("Initializing modem...");
  if (!modem.restart()) {
    DBG("Failed to restart modem, delaying 10s and retrying");
    return;
  }
  // Print modem name & modem info
  /* NOT REQUIRED IN PRODUCTION - DEBUGGING ONLY */
  String name = modem.getModemName();
  DBG("Modem Name:", name);
  String modemInfo = modem.getModemInfo();
  DBG(" Modem Info:", modemInfo);


  // Begin APN handshake
  DBG("Connecting to", apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    delay(10000);
    return;
  }
  // Print connection status
  bool res = modem.isGprsConnected();
  DBG("GPRS status:", res ? "connected" : "not connected");
  // Print board details
  /* DEBUG ONLY - NOT REQUIRED IN PRODUCTION CODE */
  String ccid = modem.getSimCCID();
  DBG("CCID:", ccid);
  String imei = modem.getIMEI();
  DBG("IMEI:", imei);
  String cop = modem.getOperator();
  DBG("Operator:", cop);
  IPAddress local = modem.localIP();
  DBG("Local IP:", local);
  // Print signal quality details
  /* RESEARCH WAY TO OBTAIN BIT ERROR, STORE TRANSMISSIONS FOR LATER IF ERROR RATE IS TOO HIGH */
  int csq = modem.getSignalQuality();
  if (csq < 2) {
    DBG("Signal quality is poor (less than -109dB)");
  }
  else if (2 <= csq < 14) {
    DBG("Signal quality is fair (between -100dB & -86dB)");
  }
  else if (14 <= csq < 22) {
    DBG("Signal quality is good (between -85dB & -71dB)");
  }
  else if (csq >= 22) {
    DBG("Signal quality is excellent (greater than -70dB)");
  }
  DBG("Handshake Complete.");
}

// GPS LOCATION FUNCTION - STORES LOCATION IN GLOBAL VARIABLES AS LAT/LONG
void gpsLocation() {
  // Enable GPS functionality
  modem.enableGPS();
  // Set commencement time to test against timeout
  unsigned long gps_start_time = millis();
  // Retireve location through GPS
  while ((millis() - gps_start_time) < GPS_TIMEOUT) {
    if (modem.getGPS(&latitude, &longitude)) {
    DBG("Current Location: Latitude:%f, Longitude:%f",latitude, longitude);
    }

    else {
      DBG("Retrieving location");
    }
  }
  // Disable gps to save power
  modem.disableGPS();
}

// HTTP CONNECTION FUNCTION. CONNECT TO SERVER & POST DATA
void httpPost(){
  /* INCLUDE HTTP POST CODE HERE */
  /* temp "sending" line */ 
  DBG("Sending data UwU!");
}

// MODEM SHUTDOWN FUNCTION - SEPARATED FOR CLARITY
void gsmPowerDown(){
  // Shut down modem to save power.
  modem.poweroff();
  DBG("Modem powered down.");
}
