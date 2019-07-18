void determine_value(){
  float volt=0,cur=0,res=0,drop=0,con=0;
  unsigned int lcd_refresh_delay = 200;//set the value according the lcd refresh rate
  unsigned long start_time;
  switch (mode){
    case 1:
          //Do what ever you want to do for scaling your value for voltage measurement
          if(selected_option == 1){
            volt = average_ac();
            lcd.setCursor(0,1);
            lcd.print(F("        "));
            lcd.setCursor(0,1);
            lcd.print(volt,0);
          }else{
            switch (level_of_dc){
              case 1:
                    volt = analogRead(A1);
                    volt = my_map(volt,0,5,0,1023);
                    lcd.setCursor(0,1);
                    clear_the_specific();
                    lcd.setCursor(0,1);
                    lcd.print(volt,3);
                    break;
              case 2:
                    volt = analogRead(A0);
                    volt = my_map(volt,0,25,0,1023);
                    lcd.setCursor(0,1);
                    clear_the_specific();
                    lcd.setCursor(0,1);
                    lcd.print(volt,1);
                    break;
              case 3:
                    volt = analogRead(A0);
                    Serial.println(volt);
                    volt = my_map(volt,0,25,0,1023);
                    volt = volt*99;
                    lcd.setCursor(0,1);
                    clear_the_specific();
                    lcd.setCursor(0,1);
                    lcd.print(volt,0);
                    break;
            }
          }
          break;
    case 2:
          //Do what ever you want to do for scaling your value for current measurement
          if (selected_option == 1){
            cur = getVPP();
            
            cur = (cur/2.0)*0.707;
            cur = (cur*1000)/185;
            lcd.setCursor(0,1);
            clear_the_specific();
            lcd.setCursor(0,1);
            lcd.print(cur,2);
          }else{
            cur = analogRead(A2);
            Serial.println(cur);
            //measuring Dc current
            if (cur>=508 && cur <= 516)
               cur = 512; //As with zero current the sensor still have an error and it bounce in between 512+-2...
            cur = (cur/1024.0)*5000.0;
            cur = (cur-2500)/185;
            lcd.setCursor(0,1);
            clear_the_specific();
            lcd.setCursor(0,1);
            lcd.print(cur,2);
          }
          /*
          lcd.setCursor(0,1);
          clear_the_specific();
          lcd.setCursor(0,1);
          lcd.print(cur);
          */
          break;
    case 3:
          byte len = strlen(screen_3[1][mode_inside_3-1]);
          //Serial.println("Inside Mode 3");
          if (len !=0){
            lcd.setCursor(1+len,1);
            lcd.setCursor(1+len,1);
          }
          else{
            lcd.setCursor(0+len,1);
            clear_the_specific();
            lcd.setCursor(0+len,1);
          }
          switch (mode_inside_3){
            case 1:
                   res = analogRead(A3);
                   //Scale your vlue...
                   res = my_map(res,0,5,0,1023);
                   res = (5/res - 1)*980;
                   if(res<1){
                     res = 0;
                     lcd.print(res);
                   }
                   else if(res>20000){
                     lcd.print("inf");//setting the limit
                   }else{
                    lcd.print(res,1);
                   }
                   //Serial.println(res,1);
                   break;
            case 2:
                  con = analogRead(A3);
                  //Scale your vlue...
                  con = my_map(con,0,5,0,1023);
                  con = (5/con - 1)*980;
                  if(con<1)
                    con = 0;
                  if (con>50)
                    lcd.print("INF");
                  else{
                    lcd.print(con);
                    //if you have any buzzer beep it
                  }
                  break;
            case 3:
                  drop = analogRead(A3);
                  //Scale your vlue...
                  drop = my_map(drop,0,5,0,1023);
                  drop = 5-drop;
                  lcd.print(drop,2);
                  break;
            case 4:
                  //run your program to get the value from dht sensor
                  run_dht();
                  lcd_refresh_delay = 2000;
                  len = strlen(screen_3[0][mode_inside_3-1]);
                  lcd.setCursor(1+len,0);
                  lcd.print("  ");
                  lcd.setCursor(1+len,0);
                  lcd.print(temp);
                  len = strlen(screen_3[1][mode_inside_3-1]);
                  lcd.setCursor(1+len,1);
                  lcd.print(F("     "));
                  lcd.setCursor(1+len,1);
                  lcd.print(hum);
                  break;
            case 5:
                  lcd.clear();
                  if(!weather_station())
                     return;
                  break;
          }
  }
  start_time = millis();
  while (millis() < start_time+lcd_refresh_delay){
      detect_mode();
      if(prev_mode!=mode)
        return;
      detect_switch();
      if(pressed_switch != 0)
        return;
  }
}
float my_map(float var,float out_low,float out_high,float in_low,float in_high){
  float c = (out_high-out_low)/(in_high-in_low);
  float out = out_low + c*(var-in_low);
  return out;
}
void clear_the_specific(){
  lcd.print(F("          "));
}
float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 100) //sample for 1 Sec
   {
       readValue = analogRead(A2);
       //Serial.println(readValue);
        if (readValue>=505 && readValue <= 514)
               readValue = 512; //As with zero current the sensor still have an error and it bounce in between 512+-2...
       Serial.println(readValue); 
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   Serial.println(maxValue);
   Serial.println(minValue);
   result = ((maxValue - minValue) * 5.0)/1024.0;
   Serial.println(result);  
   return result;
 }
 float average_ac(){
  float temp=0,s=0;
  for(byte i =0;i<150;i++){
    temp = analogRead(A0);
    //Serial.println(temp);
    if(temp>s)
      s = temp;
  }
  temp = s*0.707106*2;
  temp = my_map(temp,0,25,0,1023);
  return temp*99;
 }

