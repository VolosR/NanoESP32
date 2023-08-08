#include <TFT_eSPI.h>
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "NotoSansMonoSCB20.h"
#include "logo.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int red=57;
int green=125;
int blue=200;
unsigned short color=TFT_NAVY;
#define gray 0x4208
#define ard 0x738E
#define button 6
#define aRed 2
#define aGre 13
#define aBlu 14

int fromTop = 104;
int fromLeft = 40;
int w = 100;
int h = 40;
int values[11] = { 0 };
int values2[11] = { 0 };

bool led=0;
int deb=0;
int r,g,b=0;

void setup() {

  pinMode(48,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  digitalWrite(48,led);
  tft.init();
  tft.fillScreen(TFT_ORANGE);
  sprite.createSprite(240,240);
  sprite.setSwapBytes(1);

  for (int i = 0; i < 10; i++)
    values[i] = random(0, 40);

     ledcSetup(0, 10000, 8);
     ledcAttachPin(46, 0);
     ledcWrite(0, 160);  

     ledcSetup(1, 10000, 8);
     ledcAttachPin(0, 1);
     ledcWrite(1, 160);  
     
     ledcSetup(2, 10000, 8);
     ledcAttachPin(45, 2);
     ledcWrite(2, 160);  

      ledcSetup(3, 5000, 8);
     ledcAttachPin(10, 3);
     ledcWrite(3, 255);  
  }

void draw()
  {
    sprite.fillSprite(TFT_BLACK);
    sprite.setTextDatum(0);
    sprite.loadFont(NotoSansBold15);
    sprite.setTextColor(0x3473,TFT_BLACK);
    sprite.drawString("ARDUINO",42,38);
    
    sprite.fillRect(154,54,48,18,0xC082);
    sprite.setTextColor(TFT_WHITE,0xC082);
    sprite.drawString("ESP32",156,56);
    sprite.pushImage(154,76,48,24,logo);

    sprite.unloadFont();
    sprite.loadFont(NotoSansBold36);
    sprite.setTextColor(TFT_SILVER,TFT_BLACK);
    sprite.drawString("NANO",40,54);
    sprite.unloadFont();
   
    sprite.setTextColor(TFT_YELLOW,TFT_BLACK);
    sprite.drawString("LED_BUILT",150,110);
    sprite.setTextColor(TFT_ORANGE,TFT_BLACK);
    sprite.drawString("VOLOS PROJECTS",40,92);
    sprite.setTextColor(TFT_WHITE,TFT_BLACK);
    
    sprite.drawLine(40,88,148,88,ard);
    sprite.drawLine(148,88,148,104,ard);
    sprite.drawLine(148,104,202,104,ard);
    sprite.drawLine(40,148,86,148,ard);
    sprite.drawLine(156,148,202,148,ard);

    sprite.drawLine(86,160,156,160,ard);
    sprite.drawLine(86,148,86,160,ard);
    sprite.drawLine(156,148,156,160,ard);

    sprite.fillRect(90,166,60,9,color);
    sprite.fillRect(154,122,48,20,gray);
    sprite.fillRect(157+(led*28),125,14,14,TFT_SILVER);
    sprite.fillRect(120,39,82,11,0x3473);
   // sprite.fillRect(40,100,100,40,gray);

    for(int i=1;i<6;i++)
    sprite.drawLine(fromLeft,fromTop+h-(i*8),fromLeft+w,fromTop+h-(i*8),gray);

    for(int i=1;i<11;i++)
    sprite.drawLine(fromLeft+(i*10),fromTop,fromLeft+i*10,fromTop+h,gray);

    sprite.drawLine(fromLeft,fromTop,fromLeft,fromTop+h,TFT_WHITE);
    sprite.drawLine(fromLeft,fromTop+h,fromLeft+w,fromTop+h,TFT_WHITE);

      for (int i = 0; i < 10; i++) {
    sprite.drawLine(fromLeft + (i * 10), fromTop + values[i], fromLeft + ((i + 1) * 10), fromTop + values[i + 1], TFT_RED);
    //sprite.drawLine(fromLeft + (i * 10), fromTop + values[i] - 1, fromLeft + ((i + 1) * 10), fromTop + values[i + 1] - 1, TFT_RED);
  }

    sprite.drawSmoothArc(60,180 , 24, 21, 40, 320, 0x3B6D, TFT_BLACK);
    sprite.drawSmoothArc(180,180 , 24, 21, 40, 320, 0x3B6D, TFT_BLACK);
    sprite.drawSmoothArc(120,206 , 24, 21, 40, 320, 0x3B6D, TFT_BLACK);

    sprite.drawSmoothArc(60,180 , 24, 21, 40, map(red,0,255,40,320), 0xD90C, TFT_BLACK);
    sprite.drawSmoothArc(180,180 , 24, 21, 40, map(blue,0,255,40,320), 0x1B96, TFT_BLACK);
    sprite.drawSmoothArc(120,206 , 24, 21, 40, map(green,0,255,40,320), 0x26D6,TFT_BLACK);

    sprite.setTextDatum(4);
    sprite.loadFont(NotoSansBold15);
    sprite.drawString(String(red),60,180);
    sprite.drawString(String(green),120,206);
    sprite.drawString(String(blue),180,180);
 
    sprite.unloadFont();
    sprite.setTextColor(0x9CF3,TFT_BLACK);
    sprite.drawString("RED",60,204);
    sprite.drawString("GRE",120,230);
    sprite.drawString("BLU",180,204);
    sprite.drawString("COLOR RGB",120,154);

    sprite.setTextDatum(5);
    sprite.setTextColor(TFT_WHITE,0x3473);
    sprite.drawString(String(millis()),200,45);

    //sprite.fillRect(157+(1*28),125,14,14,TFT_SILVER);
     sprite.setTextDatum(0);
    sprite.setTextColor(gray,TFT_SILVER);
    sprite.drawString(String(led),161+(led*28),128);

    sprite.fillRect(215,20,25,180,gray);
    sprite.fillRect(10,0,200,28,gray);

    sprite.pushSprite(0,0);
  }

void loop() {

    red=map(analogRead(aRed),0,4095,0,255);
    green=map(analogRead(aGre),0,4095,0,255);
    blue=map(analogRead(aBlu),0,4095,0,255);
    
    r=map(red,0,255,255,0);
    g=map(green,0,255,255,0);
    b=map(blue,0,255,255,0);

    color= tft.color565(red, green, blue);

    ledcWrite(0, r); 
    ledcWrite(1, g); 
    ledcWrite(2, b); 

    if(digitalRead(button)==0)
    {
    if(deb==0)
    {deb=1; led=!led; digitalWrite(48,led);}
    }else deb=0;

    if (values[10] < 35 && values[10] > 5)
    values[10] = random(values[10] - 4, values[10] + 4);
    else
    values[10] = random(0, 40);

    for (int i = 0; i < 11; i++)
    values2[i] = values[i];

    for (int i = 11; i > 0; i--)
    values[i - 1] = values2[i];

  draw();

}
