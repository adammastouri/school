#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

const int undinar  = A0;    // capteur de 1  Dt
const int deuxdinars = A1;    // capteur de 2  Dt
const int sinqdinars  = A2;  // capteur de 5  Dt

int ir1000,ir2000,ir5000 = 0;
int cnt1000r,cnt2000r,cnt5000r,cnttotal = 0;
void setup() {
  Serial.begin(9600); 
 pinMode(undinar , INPUT);
  pinMode(deuxdinars ,INPUT);
  pinMode(sinqdinars,INPUT);
  
 
 lcd.setBacklightPin(3,POSITIVE);
 lcd.setBacklight(LOW); // Vous pouvez désactiver le rétroéclairage en le réglant sur LOW au lieu de HIGH
 lcd.begin(16, 2);
lcd.write(EEPROM.read(5));
}

void loop() {
 ir1000 =digitalRead(undinar);  //lire l'état d'undinar et le stocker comme ir1000
  ir2000 =digitalRead(deuxdinars); //lire l'état d'undinar et le stocker comme ir2000
  ir5000=digitalRead(sinqdinars);  //lire l'état d'undinar et le stocker comme ir5000
  
 if(ir1000 ==LOW){cnt1000r+=1000;  delay(1000);}
 if(ir2000 ==LOW){cnt2000r+=2000;  delay(1000);}
 if(ir5000 ==LOW){cnt5000r+=5000;  delay(1000);}
 
 cnttotal =cnt1000r+cnt2000r+cnt5000r;
 
EEPROM.write(5,cnttotal);
Serial.println(EEPROM.read(5)); 


lcd.setCursor(0,0);
lcd.print("TOTAL:");
lcd.setCursor(0,1);
lcd.print(cnttotal);
}