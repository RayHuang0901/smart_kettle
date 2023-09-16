#include "HX711.h"
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int buzzer=3;                   //設定蜂鳴器接腳為第3孔
int duration = 500;
int aSo = 392;
int bDo = 523;
int bRe = 587;
int bMi = 659;
int bFa = 698;
int bSo = 784;
int bLa = 880;
int bSi = 988;
int bDDo = 1047;

int t_weight = 0;
int weight = 0;
// 接線設定
const int DT_PIN = 9;
const int SCK_PIN = 10;

const int scale_factor = 419; //比例參數，從校正程式中取得

HX711 scale;


void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzer,OUTPUT);          //設定蜂鳴器為輸出

  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);

  scale.set_scale(scale_factor);       // 設定比例參數
  scale.tare();				        // 歸零
  
  Serial.println("Readings:");  //在這個訊息之前都不要放東西在電子稱上
  lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print("Put water bottle"); 
  lcd.setCursor(0, 1); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print("on the platform."); 
}
int f = 0;
int d = 0;
int time = 0;
int drink = 0;
void loop() {
  
  delay(2000);
  while(t_weight <=1 && t_weight >= -1){
    Serial.println("put button"); 
    f = 1;
    t_weight = scale.get_units(3);
    Serial.println(t_weight); 
    delay(1000);
  }
  if(d==0){
    d = 1;
    lcd.clear();
    lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
    lcd.print("drink"); 
    lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
    lcd.print("0ml");
  }
  if(f == 1){
    t_weight = scale.get_units(3);
    Serial.println(t_weight); 
  }
  scale.power_down();			        // 進入睡眠模式
  Serial.println(t_weight); 
  delay(1000);
  while(true){
    time++;
    if (time>10){
      scale.power_up();               // 結束睡眠模式
      weight = scale.get_units(3);
      Serial.println(weight);
      while(true){
        Serial.println("drink"); 
        tone(3,bDo,duration);
        delay(1000);
        weight = scale.get_units(3);
        Serial.println(weight); 
        if (weight >= t_weight-1 && weight <= t_weight+1){
          continue;
        }
        else{
          weight = scale.get_units(3);
          delay(2000);
          weight = scale.get_units(3);
          while(weight <=1 && weight >= -1){
            delay(1000);
            weight = scale.get_units(3);
            Serial.println(weight); 
          }
          delay(1000);
          weight = scale.get_units(3);
          weight = scale.get_units(3);
          Serial.println(weight); 
          if (t_weight-weight>100){
            drink += t_weight-weight;
            String t = String(drink)+"ml";
            Serial.println(drink); 
            lcd.clear();
            lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
            lcd.print("drink"); 
            lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
            lcd.print(t);
            break;
          }
          else{
            lcd.setCursor(10, 0); // (colum, row)從第一排的第三個位置開始顯示
            String t = String(100-(t_weight-weight))+"ml";
            lcd.print(t); 
            lcd.setCursor(10, 1); // (colum,row)從第二排第三格位置開始顯示
            lcd.print("left.");
          }
        }
      }

      time = 0;
      t_weight = 0;
      break;
    }
    delay(1000);
  }
  

  scale.power_up();               // 結束睡眠模式
  
}

void play()
{
  tone(3,bDo,duration);
  delay(600);
  tone(3,bRe,duration);
  delay(600);
  tone(3,bMi,duration);
  delay(600);
  tone(3,bDo,duration);
  delay(800);
  
  tone(3,bDo,duration);
  delay(600);
  tone(3,bRe,duration);
  delay(600);
  tone(3,bMi,duration);
  delay(600);
  tone(3,bDo,duration);
  delay(800);
  
  tone(3,bMi,duration);
  delay(600);
  tone(3,bFa,duration);
  delay(600);
  tone(3,bSo,duration);
  delay(800);
  
  tone(3,bMi,duration);
  delay(600);
  tone(3,bFa,duration);
  delay(600);
  tone(3,bSo,duration);
  delay(800);

  tone(3,bSo,duration);
  delay(600);
  tone(3,bLa,duration);
  delay(600);
  tone(3,bSo,duration);
  delay(600);
  tone(3,bFa,duration);
  delay(600);
  tone(3,bMi,duration);
  delay(700);
  tone(3,bDo,duration);
  delay(800);

  tone(3,bSo,duration);
  delay(600);
  tone(3,bLa,duration);
  delay(600);
  tone(3,bSo,duration);
  delay(600);
  tone(3,bFa,duration);
  delay(600);
  tone(3,bMi,duration);
  delay(700);
  tone(3,bDo,duration);
  delay(800);

  tone(3,bDo,duration);
  delay(700);
  tone(3,aSo,duration);
  delay(700);
  tone(3,bDo,duration);
  delay(800);

  tone(3,bDo,duration);
  delay(700);
  tone(3,aSo,duration);
  delay(700);
  tone(3,bDo,duration);
  delay(800);
  delay(2000);
}