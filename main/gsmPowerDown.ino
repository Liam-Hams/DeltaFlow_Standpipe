// MODEM SHUTDOWN FUNCTION - SEPARATED FOR CLARITY
void gsmPowerDown(){
  // Shut down modem to save power.
  modem.poweroff();
  DBG("Modem powered down.");
}
