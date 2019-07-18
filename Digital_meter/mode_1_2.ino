void mode_1_2(byte mode_pr){
  mode_pr--;
  byte page_count = 3;//no of pages in mod 1 and 2;
  byte max_degree_of_inside = 2;
  byte max_line_no = 8;//Maximum Row value that could have been assigned in the arraay screen_1_2[][][]
  if (pressed_switch == 0)
      detect_switch();
  if (pressed_switch == 0 || (degree_of_inside == 0 && pressed_switch != 1)){
     pressed_switch = 0;
     return;
  }
  switch (pressed_switch){
      case 1:
             if (degree_of_inside < max_degree_of_inside){
                if (degree_of_inside == 0){
                  if (selected_option == 2 && mode == 1){
                    in_page = 1;//only for DC and voltage measurement the range option will be visible
                  }else{
                    in_page = 2;
                  }
                }
                if (degree_of_inside == 1 && in_page != page_count)
                   line_no++;
                degree_of_inside ++;
             }
             else{
                if (in_page == 2){
                  selected_option = line_no;
                  Serial.print(F("Selected Option\t"));
                  Serial.println(selected_option);
                }
                else if (in_page == 1){
                 level_of_dc = line_no;
                 Serial.print(F("Level of DC\t"));
                 Serial.println(level_of_dc);
                }
                degree_of_inside = 0;
                in_page = 0;
                line_no = 0;
             }
             break;
      case 2:
             if (degree_of_inside == 1){
                if (selected_option == 2 && mode == 1){
                  if (in_page == 1)
                     in_page = page_count;
                  else
                     in_page --;
                }
                else{
                  if (in_page == 2)
                     in_page = page_count;
                  else
                     in_page --;
                }
             }
             else if (degree_of_inside == 2){
                if(in_page != page_count){
                  if(line_no==1){
                    byte i;
                    for(i=max_line_no;i>0;i--){
                      if (screen_1_2[mode_pr][i][in_page] != ""){
                         break;
                      }
                      Serial.println(i);
                    }
                    line_no = i;
                  }else{
                    line_no--;
                  }
                }else{
                  if(line_no > 1)
                    line_no--;
                }
              }
             break;
      case 3:
             if (degree_of_inside == 1){
              if (in_page == page_count ){
                if (selected_option == 2 && mode == 1)
                 in_page = 1;
                else
                 in_page = 2;
              }
              else
                 in_page ++;
             }
             else if (degree_of_inside == 2){
              if (in_page != page_count){
                if (screen_1_2[mode_pr][line_no+1][in_page] != "" && line_no < max_line_no)
                  line_no++;
                else
                  line_no = 1;
              }
              else if(line_no <max_line_no)
                  line_no++;
             }
              break;
  }
  Serial.print("Degree of Inside = ");
  Serial.print(degree_of_inside);
  Serial.print("\tPage ");
  Serial.print(in_page);
  Serial.print("\tIn line ");
  Serial.println(line_no);
  if(degree_of_inside == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("<");
    lcd.print(screen_1_2[mode_pr][degree_of_inside-1][in_page]);
    lcd.setCursor(15,0);
    lcd.print(">");
  }
  else if(degree_of_inside == 2){
    if (in_page == 1 || in_page == 2){
      lcd.setCursor(0,0);
      lcd.print(F(" "));
      lcd.setCursor(15,0);
      lcd.print(F(" "));
      lcd.setCursor(0,1);
      lcd.print(F("<          "));
      lcd.setCursor(15,1);
      lcd.print(F(">"));
      lcd.setCursor(1,1);
      lcd.print(screen_1_2[mode_pr][line_no][in_page]);
    }
    else{
      if (line_no == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(screen_1_2[mode_pr][line_no][in_page]);
        lcd.setCursor(0,1);
        lcd.print(screen_1_2[mode_pr][line_no+1][in_page]);
        line_no++;
      }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(screen_1_2[mode_pr][line_no-1][in_page]);
        lcd.setCursor(0,1);
        lcd.print(screen_1_2[mode_pr][line_no][in_page]);
        
      }
    }
  }
  else{
    Serial.print(F("Level of DC "));
    Serial.print(level_of_dc);
    Serial.print(F("\tSelected Option "));
    Serial.println(selected_option);
    action_for_ac_dc();
    action_for_DC_range();
    display_param();
  }
  pressed_switch = 0;
}

