#include <SPI.h>
#include <MFRC522.h>
#include<SoftwareSerial.h>
#define RST_PIN         9        
#define SS_PIN          10
SoftwareSerial mySerial(2,3);

MFRC522 mfrc522(SS_PIN, RST_PIN); 
int state1 =0;// Create MFRC522 instance
void setup() {
  Serial.begin(9600);   
  while (!Serial);    
  SPI.begin();
  mySerial.begin(9600);
  mfrc522.PCD_Init();   
  delay(4);       
  mfrc522.PCD_DumpVersionToSerial();  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

 
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String content="";
  byte letter;
  for(byte i=0;i<mfrc522.uid.size;i++){
    Serial.print(mfrc522.uid.uidByte[i]<0x10?"0":" ");
    Serial.print(mfrc522.uid.uidByte[i],HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10? "0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
content.toUpperCase();
 if(content.substring(1)=="62 3B C8 51" && state1==0){
  Message1();
}
}
void Message1(){
mySerial.println("AT+CMGF=1");
delay(100);
mySerial.println("AT+CMGS=\"+919025130470\"\r");
delay(100);
mySerial.println("Warning!Animal Detected");
mySerial.println("Location:https://maps.app.goo.gl/5P8yGuztZ1QRNXdU8");
mySerial.println((char)26);
delay(100);
}     
