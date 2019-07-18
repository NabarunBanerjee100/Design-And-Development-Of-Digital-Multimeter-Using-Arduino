boolean esp_connect(int length_url){
  const char keyword_OK[]="OK";
  const char keyword_carrot[]=">";
  char server_connection_url[]="AT+CIPSTART=\"TCP\",\"connectionmakeeasy.com\",80\r\n";
  length_url--;
  //Serial.println(length_url);
  esp.print(server_connection_url);
  if(esp_read_until(keyword_OK,sizeof(keyword_OK),10000,6000))
    Serial.println(F("Esp8266 is connected to My Server"));
  else{
    Serial.println(F("Fail to connect with my Server"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Network Problem");
    return 0;
  }
  dump_esp();
   esp.print("AT+CIPSEND=");
  esp.print(length_url);
  esp.print("\r\n");
  if(esp_read_until(keyword_carrot,sizeof(keyword_carrot),10000,500)){
    Serial.println(F("Ready to send"));
    return 1;
  }
  else{
    Serial.println(F("Esp isn't ready to send"));
    return 0;
  }
   
}

