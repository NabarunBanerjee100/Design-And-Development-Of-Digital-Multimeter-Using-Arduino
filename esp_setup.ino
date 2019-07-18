boolean esp_setup(){
  //Here ESP RESET is not available as no relay left for this purpose.
  dump_esp();
  const char keyword_OK[]="OK";
  const char no_AP[]="No AP";
  esp.print("AT\r\n");
  if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,500))
    Serial.println(F("Esp check OK"));
  else{
    Serial.println(F("Esp check fail"));
    esp.print("AT+RST\r\n");
    if (esp_read_until(keyword_OK,sizeof(keyword_OK),10000,500))
      Serial.println(F("Esp RESET OK"));
    else{
       /*
       //i have ran out of dynamic memory so i have to earase a bit of code
       Serial.println(F("Esp RESET Fail"));
       delay(2000);
       Serial.println(F("Esp Hardware RESET"));
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("ESP HARD RESET");
       digitalWrite(esp_reset_pin,LOW);
       delay(200);
       digitalWrite(esp_reset_pin,HIGH);
       delay(40000);
       dump_esp();
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("RESET DONE");
        Serial.println(F("Esp Hardware RESET Done"));
       delay(2000);
       lcd.clear();
       lcd.setCursor(0,0);
       */
       return 0;
    }
    return 0;
  }

  dump_esp();
  
  esp.print("AT+CWMODE=1\r\n");
  if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,500))
    Serial.println(F("AT+CWMODE check OK"));
  else{
    Serial.println(F("AT+CWMODE check fail"));
    return 0;
  }

  dump_esp();
  esp.print("AT+CWJAP?\r\n");
  //Now check whether it is connected to wifi or not
  if (!esp_read_until(no_AP,sizeof(no_AP),2000,1000)){
    Serial.println(F("Connected to Wifi"));
  }
  else{
    dump_esp();
    Serial.println(F("It's not connected to wifi"));
    esp.print("AT+CWJAP=\"Wifi SSID\",\"password\"\r\n");
    Serial.println(F("AT+CWJAP=\"Wifi SSID\",\"password\"\r\n"));
    if (esp_read_until(keyword_OK,sizeof(keyword_OK),30000,5000))
        Serial.println(F("Esp is connected to Wifi Station 1."));
    else{
        Serial.println(F("Wifi 1 connection failed."));
        dump_esp();
        esp.print("AT+CWJAP=\"Wifi SSID\",\"\"\r\n");
        Serial.println(F("AT+CWJAP=\"Wfif SSID\",\"password\"\r\n"));
        if (esp_read_until(keyword_OK,sizeof(keyword_OK),30000,5000))
            Serial.println(F("Esp is connected to Wifi Station 2."));
        else{
             Serial.println(F("Wifi 2 connection failed."));
             return 0;
        }
    }
   }
  

  dump_esp();
  
  esp.print("AT+CIPMUX=0\r\n");
  if (esp_read_until(keyword_OK,sizeof(keyword_OK),5000,500))
    Serial.println(F("AT+CIPMUX=0 check OK"));
  else{
    Serial.println(F("AT+CIPMUX=0 check fail"));
    return 0;
  }

  dump_esp();
  
  return 1;
  
}

