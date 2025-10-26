#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
DHT11 dht11(2);

int temp, humi;
bool peltierOn = false;

void setup() {                         //펠티어 온도 제어 
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int chk = dht11.readTemperatureHumidity(temp, humi);

  if (chk == 0) {
    lcd.setCursor(0,0);
    lcd.print("Temp: "); lcd.print(temp); lcd.print(" C   ");
    lcd.setCursor(0,1);
    lcd.print("Humi: "); lcd.print(humi); lcd.print(" %   ");

    // 히스테리시스 적용: 34이상 키고, 25이하 끄기
    if (!peltierOn && temp >=34) {
      digitalWrite(3, LOW);
      peltierOn = true;
    } 
    else if (peltierOn && temp <= 25) {
      digitalWrite(3, HIGH);
      peltierOn = false;
    }

  } else {
    Serial.println("DHT11 Error");
    digitalWrite(3, HIGH);
    peltierOn = false;
  }

  delay(2000);
}
 // 펠티어 이미지 링크: https://github.com/seungmin124/feltier-code/issues/1#issue-3553266081



