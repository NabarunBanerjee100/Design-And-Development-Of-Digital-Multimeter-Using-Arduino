//pr_time refers to processing time of esp
boolean esp_read_until(const char keyword[],int sizeof_keyword,int timeout,int pr_time){
  char data_in[20];
  unsigned long time_start;
  time_start=millis();
  sizeof_keyword--;
  //Serial.println(sizeof_keyword);
  //check whether the any data available or not
  for(byte b=0;b<sizeof_keyword;b++){
       while(!esp.available()){
         if(millis()>=(time_start+timeout)){
           Serial.println(F("Timeout 1"));
           return 0;
         }
       }
       data_in[b]=esp.read();
       
    }
  
  //check for the keyword
  while(1){
  
    for(byte b=0;b<sizeof_keyword;b++){
      unsigned long int pr_start = millis();
      while(!esp.available()){
        if((millis() >= (pr_start+pr_time))||(millis()>=(time_start+timeout)))
           break;
      }
      if(data_in[b]!=keyword[b])
        break;
      else if (b==(sizeof_keyword-1)){
        //Serial.println(F("Yay keyword matched! :)"));
        return 1;
      }
        
    }
   

    //Rolling the buffer
    for(byte b=0;(b<(sizeof_keyword-1));b++){
         data_in[b]=data_in[b+1];
    }
    
    unsigned long int pr_start = millis();
      while(!esp.available()){
        if((millis() >= (pr_start+pr_time))||(millis()>=(time_start+timeout)))
           break;
      }   
    data_in[sizeof_keyword-1]=esp.read();
    
    //timeout control
    if (millis()>=(time_start+timeout)){
        Serial.println(F("Timeout 2"));
        return 0;
    }
    
  }
}

