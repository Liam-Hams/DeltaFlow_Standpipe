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
      break; // seems neater than the bool variable and works
    }

    else if (((millis() - gps_start_time)) % 200 == 0){
      DBG("Retrieving location"); //don't know why this modulo code works better but it does 
    }
  }
  // Disable gps to save power
  modem.disableGPS();
}
