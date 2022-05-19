#include <LiquidCrystal.h>
#include <Keypad.h>
const byte satir = 4; // 4 satir
const byte sutun = 3; //3 sutun
unsigned long ilkZaman=0;
unsigned long sonZaman;

    char keys[satir][sutun] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
    };

    char* sifre="1234";
    byte Pinsatir[satir] = {25, 26, 27, 28}; 
    byte Pinsutun[sutun] = {24, 23, 22}; 
    int sifresay=0;
    int sayi=0;
    Keypad keypad = Keypad(makeKeymap(keys), Pinsatir, Pinsutun, satir, sutun );

    int val2=0;
    int val=0;
    int isikPin = 14;              
    int girisPin = 15;             
    int pirState = LOW;  
    float sicaklik=0.0;
    int kullanici=0;

    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
    int buzzer=13;

    #define yanginPin A1
    #define sicaklikPin A0

    void setup() {
        lcd.begin(16, 2);
        pinMode(isikPin, OUTPUT);     
        pinMode(girisPin, INPUT);
        pinMode(yanginPin,INPUT_PULLUP);
        pinMode(buzzer,OUTPUT);
        pinMode(30,OUTPUT);
        pinMode(29,OUTPUT);
        Serial.begin(4800);
    }

    void loop() {
        kilitsensor();
        hareketsensor();
        sicakliksensor();
        yanginsensor();
    }

    void hareketsensor(){
        val2= digitalRead(girisPin);  // read input value
        if (val2 == 1) {
            digitalWrite(isikPin, HIGH);} 
        if (val2 == 0)
        {
            digitalWrite(isikPin, LOW);}
    }


    void yanginsensor(){
        int yangin = digitalRead(yanginPin);
        if(yangin==HIGH){
            digitalWrite(buzzer, HIGH);}
        if(yangin==LOW){
            digitalWrite(buzzer, LOW); }
    }


    void kilitsensor(){
        char key = keypad.getKey();
        if (key != NO_KEY)
        {
            sayi++;
            if(key==sifre[sifresay]){
                sifresay++;
                if(sifresay==4){
                    digitalWrite(30,HIGH);
                    //delay(400); 
                    sifresay=0; 
                }  
            }
            else if(sayi>3){
                digitalWrite(29,HIGH);
                //delay(400); 
                sifresay=0;
                sayi=0;
            }
        }
    }


    void sicakliksensor(){
        sonZaman=millis();

        val = analogRead(sicaklikPin);
        sicaklik = val * 4.887;
        sicaklik = sicaklik/10.0;

      if(sonZaman-ilkZaman>=100)
        {
            lcd.print("SICAKLIK:");
            lcd.setCursor(10, 0);
            lcd.print(sicaklik);
            yazdir();
            ilkZaman=sonZaman;
           
      
        }
    
     
        
    }

    void yazdir(){
        if(sicaklik>30){
            lcd.setCursor(0, 2);
            lcd.print("SICAKLIK YUKSELDI");
           
        }
        else if(sicaklik<20){
            lcd.setCursor(0, 2);
            lcd.print("SICAKLIK DUSTU  ");
            
         
        }
    }
