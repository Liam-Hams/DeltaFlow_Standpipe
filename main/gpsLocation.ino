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

    else if (((millis() - gps_start_time)/1000) % 5 == 0){
      DBG("Retrieving location");
    }
  }
  // Disable gps to save power
  modem.disableGPS();
}
