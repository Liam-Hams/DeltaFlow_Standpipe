/*  Shoalhaven Water standpipe code - main File */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


void app_main(void){
   Sleeper24hr();
   switch(esp_sleep_get_wakeup_cause()){
     case ESP_SLEEP_WAKEUP_EXT0:
      printf("Wake up from Water Meter input");
      waterRead();
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      printf("Wake up from internal Timer.");
   }
}
