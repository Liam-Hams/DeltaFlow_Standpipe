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
