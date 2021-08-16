// NET CONNECT FUNCTION - RESTARTS MODEM & PERFORMS APN HANDSHAKE
void netConnect() {
  // Initialize variables for network handshake
  int retry_count;
  
  // Initialize modem
  DBG("Initializing modem...");
  if (!modem.init()) {
    DBG("Failed to restart modem, delaying 10s and retrying");
    return;
  }
  // Print modem name & modem info
  /* NOT REQUIRED IN PRODUCTION - DEBUGGING ONLY */
  String name = modem.getModemName();
  DBG("Modem Name:", name);
  String modemInfo = modem.getModemInfo();
  DBG(" Modem Info:", modemInfo);

  do {
    // Begin APN handshake
    DBG("Connecting to", apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      delay(10000);
      return;
    }
    // Print connection status
    netstatus = modem.isGprsConnected();
    DBG("GPRS status:", netstatus ? "connected" : "not connected");
    // Split program flow based on wether handshake completes correctly
    // if true, continue as normal
    if (netstatus == true) {
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
    // If false, attempt to reconnect for 5 times.
    else {
      DBG("Retrying Connection");
      retry_count++;
    }
  // If unconnected after 5 attempts, store data offline  
  } while (netstatus != true && retry_count > 5);
  if (netstatus != true){
    DBG("APN Handshake Failed, storing data offline.");
    offlineSort();
  }
}
