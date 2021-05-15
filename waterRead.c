#define WATER_PIN /*input pin for the water meter*/

bool waterRead(){
  int pulseCount = 0;
  int fcheck_present = 0;
  int fcheck_past = 0;
  while(fcheck_present != 0 && fcheck_past != 0){
    if(WATER_PIN == HIGH){
      pulsecount++
    }
    if(pulsecount % 10 == 0){
      flowUpload();
    }
  }
}

void flowUpload(){
  
}
