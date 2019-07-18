boolean data_send(byte no_of_sensor,char url[]){
  //forming the url;
  const char keyword_feed_ok[]="Feed OK";
  
  String sensor_url = "";
  sensor_url += url;
 
  for(byte b=1;b<=no_of_sensor;b++){
    sensor_url += "&sensor";
    sensor_url += b;
    sensor_url += "=";
    sensor_url += sensor[b-1];
  }
  sensor_url += "\r\n\r\n";
  
  char charUrl[sensor_url.length()+1];
  sensor_url.toCharArray(charUrl,sensor_url.length()+1);
  Serial.println(charUrl);
  if(esp_connect(sizeof(charUrl))){
    if(get_package(charUrl)){
      if(esp_read_until(keyword_feed_ok,sizeof(keyword_feed_ok),15000,8000)){
        return 1;
      }
    }
  }
  return 0;
}

