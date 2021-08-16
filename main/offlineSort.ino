// Offline sort function. collates global variables into offline struct & extends struct head pointer
void offlineSort(){
dataRecs[store_count].b_count = boot_count;
dataRecs[store_count].w_con = wake_con;
dataRecs[store_count].Flow.tot_pulses = total_pulses;
dataRecs[store_count].Flow.pulse_cnt = pulse_count;
dataRecs[store_count].Loc.lat = latitude;
dataRecs[store_count].Loc.lon = longitude;
dataRecs[store_count].Loc.dat = date;
dataRecs[store_count].Loc.tim = Time; 
if ((store_count+1) > 99){
  DBG("Data Overflow");
}
else{
  store_count++;
}
}
