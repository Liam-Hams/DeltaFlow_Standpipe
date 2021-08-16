// Data Clear funciton - clears on-board data struct to ensure correct data storage

void dataClear() {
  for (int i = 0; i = store_count; i++) {
    dataRecs[store_count].b_count = NULL;
    dataRecs[store_count].w_con = NULL;
    dataRecs[store_count].Flow.tot_pulses = NULL;
    dataRecs[store_count].Flow.pulse_cnt = NULL;
    dataRecs[store_count].Loc.lat = NULL;
    dataRecs[store_count].Loc.lon = NULL;
    dataRecs[store_count].Loc.dat = NULL;
    dataRecs[store_count].Loc.tim = NULL;
  }
}
