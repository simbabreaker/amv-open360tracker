#include "inttypes.h"
#include <EEPROM.h>
#include "settings.h"
#include "defines.h"
#include <Arduino.h>

uint8_t EEPROM_DEFAULT[EEPROM_SETTINGS]={
/* 00 */ FMW_VER,
/* 01 */ DEF_S_PID_P,
/* 02 */ DEF_S_PID_I,
/* 03 */ DEF_S_PID_D,
/* 04 */ DEF_S_MAX_PID_ERROR,
/* 05 */ DEF_S_TILT_0,
/* 06 */ DEF_S_TILT_90,
/* 07 */ DEF_S_TILT_EASING,
/* 08 */ DEF_S_TILT_EASING_STEPS, 
/* 09 */ DEF_S_TILT_EASING_MIN_ANGLE, 
/* 10 */ DEF_S_TILT_EASING_MILIS, 
/* 11 */ DEF_S_PAN_0,
/* 12 */ DEF_S_MIN_PAN_SPEED,
/* 13 */ DEF_S_DECLINATION,
/* 14 */ DEF_S_OFFSET,
/* 15 */ DEF_S_LOCAL_GPS,
/* 16 */ DEF_S_MTK,
/* 17 */ DEF_S_GPS_BAUD_RATE,
/* 18 */ DEF_S_START_TRACKING_DISTANCE,
/* 19 */ DEF_S_LCD_DISPLAY,
/* 20 */ DEF_S_LCD_SIZE_ROW,
/* 21 */ DEF_S_LCD_I2C_ADDR,
/* 22 */ DEF_S_LCD_MODEL,
/* 23 */ DEF_S_BATTERYMONITORING,
/* 24 */ DEF_S_BATTERYMONITORING_RESISTOR_1,
/* 25 */ DEF_S_BATTERYMONITORING_RESISTOR_2,
/* 26 */ DEF_S_BATTERYMONITORING_CORRECTION
};

uint8_t Settings[EEPROM_SETTINGS];
char *param_names[EEPROM_SETTINGS]={
/* 00 */"check",
/* 01 */"P",
/* 02 */"I",
/* 03 */"D",
/* 04 */"max_pid_error",
/* 05 */"tilt0",
/* 06 */"tilt90",
/* 07 */"easing",
/* 08 */"easing_steps",
/* 09 */"easing_min_angle",
/* 10 */"easing_milis",
/* 11 */"pan0",
/* 12 */"min_pan_speed",
/* 13 */"declination",
/* 14 */"offset",
/* 15 */"local_gps",
/* 16 */"gps_mtk",
/* 17 */"gps_bauds",
/* 18 */"start_track_dist",
/* 19 */"lcd",
/* 20 */"lcd_rows",
/* 21 */"lcd_addr",
/* 22 */"lcd_model",
/* 23 */"bat_mon",
/* 24 */"bat_res1",
/* 25 */"bat_res2",
/* 26 */"bat_corr"
 };
void writeEEPROM(void)
{
  for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
    EEPROM.write(en+ADDR_OFFSET,Settings[en]);
  } 
  EEPROM.write(0+ADDR_OFFSET,FMW_VER);
}

void readEEPROM(void)
{
  for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
     Settings[en] = EEPROM.read(en+ADDR_OFFSET);
  }
}
void checkEEPROM(void)
{
  uint8_t EEPROM_Loaded = EEPROM.read(0+ADDR_OFFSET);
  if (EEPROM_Loaded!=FMW_VER){
    defaultsEEMPROM();
  }
}
void defaultsEEMPROM(void)
{
  for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
      EEPROM.write(en+ADDR_OFFSET,EEPROM_DEFAULT[en]);
  }
}
void dumpSettings(){
  int param_value;
  Serial.println(F("List settings: "));
  for(uint8_t i=1;i<EEPROM_SETTINGS;i++){
    param_value=getParamValue(param_names[i]);
    Serial.print("set ");Serial.print(param_names[i]);Serial.print("=");Serial.println(param_value);
    Serial.flush();
  }
  Serial.println(F(">"));
}
uint8_t setParamValue(String param_name,int param_value){
  uint8_t index;
  uint8_t value;
  uint8_t divider;
  if(param_name=="P" || param_name=="I" || param_name=="D" || param_name=="tilt0" || param_name=="tilt90" || param_name=="pan0" || param_name=="offset")
    divider=10;
  else if(param_name=="bat_res1" || param_name=="bat_res2" || param_name=="gps_bauds")
    divider=100;
  else
    divider=1;
  value=param_value/divider;
  //Serial.print(param_value);Serial.print("/");Serial.print(divider);Serial.print("=");Serial.println(value);
  index = getParamIndex(param_name);
  Settings[index]=value;
  Serial.println("Ok\n>");
}
int getParamValue(String param_name){
  uint8_t index = getParamIndex(param_name);
  int value=0;
  uint8_t multiplier;
  if(param_name=="P" || param_name=="I" || param_name=="D" || param_name=="tilt0" || param_name=="tilt90" || param_name=="pan0" || param_name=="offset")
    multiplier=10;
  else if(param_name=="bat_res1" || param_name=="bat_res2" || param_name=="gps_bauds")
    multiplier=100;
  else
    multiplier=1;
  if(index>0) 
      value=Settings[index]*multiplier;
  return value;
}
uint8_t getParamIndex(String param_name){
  uint8_t found = false;
  for(uint8_t i=1;i<EEPROM_SETTINGS;i++){
    for(uint8_t x=0;x<param_name.length();x++)
    {
      if(param_names[i][x]==param_name[x])
        found=true;
      else {
        found=false;
        break;
      }
    }
    if(found==true)
      return i;
  }
  Serial.println(F("Parameter not found"));
  return 0;
}

