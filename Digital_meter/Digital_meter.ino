#include <LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>
#include <dht.h>
#define DHT11_PIN 2
#define espRx 11
#define espTx 12
#define pin_range 10
#define pin_ac_dc 9
#define esp_reset_pin 13

dht DHT;

SoftwareSerial esp(espRx,espTx);//connect esp 8266 tx rx with digital pin of aruino uno 10 and 11

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define no_of_switches 6
#define debounce 50 // will provide a debounce effect of switches , 50ms

const char* screen_1_2[][9][4] = {{"Voltage","Range","Type of Signal","About",
                                   "","Below 5V","AC","Smart DM V1.0",
                                   "","Below 20V","DC","Developed by",
                                   "","Below 400V","","Koushik",
                                   "","","","Moouboni",
                                   "","","","Nabarun",
                                   "","","","Prasun",
                                   "","","","Subhranil",
                                   "","","","Santanu"},
                                {"Current","Range","Type of Signal","About",
                                   "","Below 5V","AC","Smart DM V1.0",
                                   "","Below 20V","DC","Developed by",
                                   "","Below 400V","","Koushik",
                                   "","","","Moouboni",
                                   "","","","Nabarun",
                                   "","","","Prasun",
                                   "","","","Subhranil",
                                   "","","","Santanu"}
};
const char* unit_of_screen_1_2[] = {"Volt","Amp"};
const char* screen_3[][6] = {"Resistance","Continuity","Forward Drop","Temperature","Weather","About",
                            "","","","Humidity","Station","Smart DM V1.0",
                            "","","","","","Developed by",
                            "","","","","","Koushik",
                            "","","","","","Moouboni",
                            "","","","","","Nabarun",
                            "","","","","","Prasun",
                            "","","","","","Subhranil",
                            "","","","","","Santanu"
  
};
const char* unit_of_screen_3[] = {"Ohm","","Volt","°C","%"};
const char busy[]="busy";
byte mode = 1; // 1 -> Voltage, 2 -> Current, 3 -> Rest of the Things  connected with 3,4,6
byte prev_mode = 1;
byte pressed_switch = 0;// 0 for no switch; 1 for menu/ok ; 2 for < ; 3 for >
byte current_screen = 1;
byte degree_of_inside = 0;
byte in_page = 0;
byte line_no = 0;
byte selected_option = 1;//varies from 1 and 2 for AC and DC
byte mode_inside_3 = 1;//Varies from 1 to 5
byte count_sensor = 2;
String instrument_data_in;
byte level_of_dc = 3;//1 for very low < 5V;2 for <20V;3 for >20V and <400V;
float sensor[2];
byte temp=27,hum=45;//Setting up default value for dht sensor.

void setup(){
  pinMode(espTx,OUTPUT);
  pinMode(espRx,INPUT);
  pinMode(esp_reset_pin,OUTPUT);//Putting esp_reset_pin as a hardware reset of esp..
  pinMode(pin_range,OUTPUT);//9 for High range dc
  pinMode(pin_ac_dc,OUTPUT);//10 for ac or dc
  digitalWrite(pin_range,HIGH);
  digitalWrite(pin_ac_dc,HIGH);
  for (byte i=3;i<(3+no_of_switches);i++){
    pinMode(i,INPUT);
  }
  Serial.begin(115200);
  delay(100);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.println(F("Starting Engine"));
  lcd.setCursor(0,0);
  lcd.print(F("Starting Engine"));
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(F("    Smart DM"));
  delay(1000);
  action_for_ac_dc();
  action_for_DC_range();
  delay(100);
  detect_mode();
  display_param();
}

void loop(){
  detect_mode();
  //Serial.println(mode);
  if (mode == 1)
     mode_1_2(1);
  else if (mode == 2)
     mode_1_2(2);
  else if (mode == 3)
     mode_3();
  if (degree_of_inside==0)
     determine_value();

}

void detect_mode(){
  prev_mode = mode;
  if (digitalRead(3) == HIGH )
    mode = 1;
  else if(digitalRead(4) == HIGH )
    mode = 2;
  else if (digitalRead(5) == HIGH )
    mode = 3;
  if ( mode != prev_mode ){
    Serial.print (F("Mode Changed to "));
    Serial.println (mode);
    line_no = 0;
    in_page = 0;
    degree_of_inside = 0;
    display_param();
    delay (debounce);
  }
}

void detect_switch(){
  if (digitalRead(6) == HIGH )
    pressed_switch = 1;
  else if(digitalRead(7) == HIGH )
    pressed_switch = 2;
  else if (digitalRead(8) == HIGH )
    pressed_switch = 3;
  else
    return;
  delay(debounce);
  while(digitalRead(pressed_switch+5) == HIGH);//Wait until the switch goes again to zero.
  Serial.print(F("Pressed Switch  "));
  Serial.println(pressed_switch);
}
void action_for_ac_dc(){
  //1 for ac and 2 for dc
  if (selected_option == 1){
    //Serial.println(F("Relay -> AC"));
    digitalWrite(pin_ac_dc,HIGH);
    level_of_dc = 3;
  }else{
    //Serial.println(F("Relay -> DC"));
    digitalWrite(pin_ac_dc,LOW);
  }
}
void action_for_DC_range(){
  switch (level_of_dc){
      case 1:
            digitalWrite(pin_ac_dc,LOW);
            digitalWrite(pin_range,LOW);
            break;
      case 2:
            digitalWrite(pin_ac_dc,LOW);
            digitalWrite(pin_range,HIGH);
            break;
      case 3:
            digitalWrite(pin_ac_dc,HIGH);
            digitalWrite(pin_range,HIGH);//hmm bit of experiment
            break;
  }

}
void display_param(){
  lcd.clear();
  if (mode == 1 || mode ==2){
    lcd.setCursor(0,0);
    lcd.print(screen_1_2[mode-1][0][0]);
    if(selected_option == 2 && mode == 1){
      lcd.print(" ");
      switch (level_of_dc){
        case 1:
              lcd.print("<5V");
              break;
        case 2:
              lcd.print("<20V");
              break;
        case 3:
              lcd.print("<400V");
              break;
      }
    }
    lcd.setCursor(14,0);
    lcd.print(screen_1_2[mode-1][selected_option][2]); //print AC or DC
    byte len = strlen(unit_of_screen_1_2[mode-1]);
    lcd.setCursor(16-len,1);
    lcd.print(unit_of_screen_1_2[mode-1]);
  }
  else if (mode == 3){
    lcd.setCursor(0,0);
    lcd.print(screen_3[0][mode_inside_3-1]);
    if (screen_3[1][mode_inside_3-1] != ""){
      lcd.setCursor(0,1);
      lcd.print(screen_3[1][mode_inside_3-1]);
    }
    byte len = strlen(unit_of_screen_3[mode_inside_3-1]);
    if (mode_inside_3 == 4){
      Serial.println(len);
      lcd.setCursor(14,0);
      lcd.print(char(223));
      lcd.print("C");
      len = strlen(unit_of_screen_3[mode_inside_3]);
      lcd.setCursor(16-len,1);
      lcd.print(unit_of_screen_3[mode_inside_3]);
    }
    else{
      lcd.setCursor(16-len,1);
      lcd.print(unit_of_screen_3[mode_inside_3-1]);
    }
  }
}
void run_dht(){
  int chk = DHT.read11(DHT11_PIN);
  if (chk == 0){
         temp = DHT.temperature;
         hum = DHT.humidity;
         sensor[0]=temp;
         sensor[1]=hum;
  }
}

