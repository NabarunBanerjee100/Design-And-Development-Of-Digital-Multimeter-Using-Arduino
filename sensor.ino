boolean _sensor(){
  const char no_AP[]="No AP";
  const char keyword_OK[]="OK";
  esp.print("AT+CWJAP?\r\n");
  //now check if the esp is busy or not,
  if (esp_read_until(busy,sizeof(busy),1000,500)){
        //Hold on for a few second then send a at command
        Serial.println(F("Busy"));
        dump_esp();
        if(!wait_and_check(20000))
           return 0;
        esp.print("AT\r\n");
        if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,500)){
            Serial.println(F("Esp check Fine"));
            delay(200);
            esp.print("AT+CWJAP?\r\n");
        }
           
        else{
           /*
           //i have ran out of dynamic memory so i have to earase a bit of code
           Serial.println(F("Esp Hardware RESET"));
           //oh no! now you have to reset the hardware interrupt of esp
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print(F("ESP RESET"));
           digitalWrite(esp_reset_pin,LOW);
           delay(200);
           //here thing is i could give it to high again but its 5v so, declaring the pin 9 will do remove the connection from it
           //that's fine
           digitalWrite(esp_reset_pin,HIGH);
           wait_and_check(40000);
           dump_esp();
           lcd.print("RESET DONE");
           wait_and_check(2000);
           lcd.clear();
           esp.print("AT+CWJAP?\r\n");
           */
        }
   }
    
  if (!esp_read_until(no_AP,sizeof(no_AP),2000,500))
    Serial.println(F("Connected to Wifi"));
  else{
    Serial.println(F("It's not connected to wifi, delay ing attempting again"));
    dump_esp();
    wait_and_check(2000);
    esp.print("AT+CWJAP?\r\n");
    if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,1000)){
      Serial.println(F("NOW its connected"));
    }
    else
      esp_setup();
    
  }
  dump_esp();
  char sensor_feed_url[] = "GET http://connectionmakeeasy.com/data_feed.php?channel_id=1069&write_key=9W9d1VaMaUrhzIFg";
  byte attempt=0;
  for(attempt=0;attempt<1;attempt++){
    if(data_send(count_sensor,sensor_feed_url)){
       digitalWrite(13,HIGH);
       Serial.println(F("Sensor Data Sended Successfully"));
       break;
    }
    else{
      Serial.println(F("Sensor Data Send Failed"));
    }
  }
 return 1;
}

