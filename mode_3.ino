void mode_3(){
  byte page_count = 6;//no of pages in mod 3;
  byte max_degree_of_inside = 2;
  byte max_line_no = 8;//Maximum Row value that could have been assigned in the arraay screen_3[][]
  if (pressed_switch == 0)
      detect_switch();
  if (pressed_switch == 0 || (degree_of_inside == 0 && pressed_switch != 1)){
     pressed_switch = 0;
     return;
  }
  switch (pressed_switch){
      case 1:
             if (degree_of_inside < max_degree_of_inside){
                if (degree_of_inside == 1){
                  if (in_page != 6){
                     degree_of_inside = 0;
                     mode_inside_3 = in_page;
                     in_page = 0;
                  }
                  else{
                     in_page = 6;
                     degree_of_inside ++;
                  }
                }
                else if(degree_of_inside == 0){
                  in_page=1;
                  degree_of_inside++;
                }
             }
             else{
                degree_of_inside = 0;
                in_page = 0;
                line_no = 0;
             }
             break;
      case 2:
             if (degree_of_inside == 1){
              if (in_page == 1)
                 in_page = page_count;
              else
                 in_page --;
             }
             else if (degree_of_inside == 2 && in_page == 6){
                if(line_no>1)
                   line_no--;
              }
             break;
      case 3:
             if (degree_of_inside == 1){
              if (in_page == page_count )
                 in_page = 1;
              else
                 in_page ++;
             }
             else if (degree_of_inside == 2 && in_page == 6){
              if (line_no < max_line_no)
                 line_no++;
             }
             break;
  }
  Serial.print("Degree of Inside = ");
  Serial.print(degree_of_inside);
  Serial.print("\tPage ");
  Serial.println(in_page);
  if(degree_of_inside == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("<");
    lcd.print(screen_3[degree_of_inside-1][in_page-1]);
    lcd.setCursor(15,0);
    lcd.print(">");
    if (in_page != 6 && screen_3[degree_of_inside][in_page-1] != ""){
       lcd.setCursor(1,1);
       lcd.print(screen_3[degree_of_inside][in_page-1]);
    } 
  }
  else if(degree_of_inside == 2){
    if (line_no == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(screen_3[line_no][in_page-1]);
        lcd.setCursor(0,1);
        lcd.print(screen_3[line_no+1][in_page-1]);
        line_no++;
      }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(screen_3[line_no-1][in_page-1]);
        lcd.setCursor(0,1);
        lcd.print(screen_3[line_no][in_page-1]);
      }
  }
  else{
    display_param();
  }
  pressed_switch = 0;
  
}

