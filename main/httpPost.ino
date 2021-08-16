// HTTP CONNECTION FUNCTION. CONNECT TO SERVER & POST DATA
void httpPost() {
  // Set server location
  const char* serverName = "http://192.168.86.235:1880/flow_upload";
  HttpClient http(client, serverName);
  
  if (store_count > 0) {
    for (int i = 0; i = store_count; i++) {
      // Generate Location Id
      Loc_Id = Loc_Id + Pipe_Id;
      Loc_Id = Loc_Id + "_" + dataRecs[i].b_count;

      // Generate Location String
      String Location;;
      Location = Location + dataRecs[i].Loc.lat;
      Location = Location + " ";
      Location = Location + dataRecs[i].Loc.lon;

      // Add header to specify url-encoding for data (required for node-red)
      http.sendHeader("Content-Type", "application/x-www-form-urlencoded");
      // Define body of data message
      String httpRequestData = "Pipe_Id=";
      httpRequestData = httpRequestData + Pipe_Id;
      httpRequestData = httpRequestData + "&Location" + Location;
      httpRequestData = httpRequestData + "&Usage_C" + dataRecs[i].Flow.pulse_cnt;
      httpRequestData = httpRequestData + "&Usage_T" + dataRecs[i].Flow.tot_pulses;
      httpRequestData = httpRequestData + "&Loc_Id" + Loc_Id;
      httpRequestData = httpRequestData + "&Wake_Con" + dataRecs[i].w_con;

      int httpResponseCode = http.post(httpRequestData);
      DBG("HTTP Response Code = " + httpResponseCode);
      delay(500);
    }
    dataClear();
    store_count = 0;
  }
  
  else {
    // Generate Location Id
    Loc_Id = Loc_Id + Pipe_Id;
    Loc_Id = Loc_Id + "_" + boot_count;

    // Generate Location String
    String Location;;
    Location = Location + latitude;
    Location = Location + " ";
    Location = Location + longitude;

    // Add header to specify url-encoding for data (required for node-red)
    http.sendHeader("Content-Type", "application/x-www-form-urlencoded");
    // Define body of data message
    String httpRequestData = "Pipe_Id=";
    httpRequestData = httpRequestData + Pipe_Id;
    httpRequestData = httpRequestData + "&Location" + Location;
    httpRequestData = httpRequestData + "&Usage_C" + pulse_count;
    httpRequestData = httpRequestData + "&Usage_T" + total_pulses;
    httpRequestData = httpRequestData + "&Loc_Id" + Loc_Id;
    httpRequestData = httpRequestData + "&Wake_Con" + wake_con;

    int httpResponseCode = http.post(httpRequestData);
    DBG("HTTP Response Code = " + httpResponseCode);
  }
}
