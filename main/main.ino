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
#define GPS_TIMEOUT 240000
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

// FUNCTION DEFINITIONS
void flowCount();
void wake();
void gpsLocation();
void gsmPowerDown();
void httpPost();
void netConnect();

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
