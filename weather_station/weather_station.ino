boolean weather_station(){
  byte i;
  Serial.println(F("Starting Weather Station"));
  lcd.clear();
  lcd.print(F("Starting Weather"));
  lcd.setCursor(0,1);
  lcd.print(F("Station"));
  esp.begin(4800);
  delay(200);
  wait_and_check(2000);
  dump_esp();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Checking"));
  lcd.setCursor(0,1);
  for(i=1;i<=16;i++){
    lcd.print(char(255));
    delay(200);
  }
  for(i=1;i<10;i++){
    if(esp_setup())
       break;
  }
  if (i==10){
    lcd.clear();
    lcd.print(F("NO WiFi Found !"));
    delay(2000);
    lcd.clear();
    lcd.print(F("Getting Back to"));
    lcd.setCursor(0,1);
    lcd.print(F("Main"));
    delay(2000);
    mode_inside_3 = 1;
    return 0;
  }else{
    lcd.clear();
    lcd.print(F("Everything's OK"));
    delay(2000);
  }
  while(1){
    dump_esp();
    //Read the value from the sensor
    //then show it in the lcd or serial
    run_dht();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Temperature "));
    lcd.print(temp);
    lcd.print(char(223));
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(F("Humidity "));
    lcd.print(hum);
    lcd.print("%");
    _sensor();
    if(!wait_and_check(10000))
      return 0;
  }
}
boolean wait_and_check(unsigned int timeout){
  unsigned long start_time;
  start_time = millis();
  while (millis() < start_time+timeout){
        detect_mode();
        if(prev_mode!=mode)
          return 0;
        detect_switch();
        if(pressed_switch != 0)
          return 0;
  }
  return 1;
}

