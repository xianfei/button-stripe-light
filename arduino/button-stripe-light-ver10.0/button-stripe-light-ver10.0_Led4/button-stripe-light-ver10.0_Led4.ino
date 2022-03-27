/*
author:zxw
fution:led4的控制程序
触发：红外线
time: 2022-3-27
version: 10.0
bug：none
email：2474113608@qq.com
package:Fsatled、MsTimer
*/
#include <FastLED.h>
#define NUM_LEDS_RING4 120 
#define PIN_LED_RING4 13
CRGB rgb_led_ring4[NUM_LEDS_RING4]; 
signed int index_ring4 = 0;//全局变量：用于定时器自加的变量，控制灯珠的位置
int flag1 = 0;//用来判断是哪条灯带触发点
int flag2 = 0;
int flag3 = 0;
/*--------------按键的初始化--------*/
 int button1=2;
 int button2=3;
 int button3=4;
/*--------setup初始化函数------------*/
void setup()
{
  Serial.begin(9600); //初始化串口
  FastLED.addLeds<WS2812, PIN_LED_RING4>(rgb_led_ring4, NUM_LEDS_RING4);//注册led1
  pinMode(button1,INPUT_PULLUP);//按键读取端口需要使用上拉电阻模式才可以实现    
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
}
/*-------------loop循环----------------*/
void loop()
{
  if(digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH)//按键1触发->按键2->按键3触发，流水灯效果
  { 
    anime_of_breath(rgb_led_ring4, 0, 120 ,255,0,0,70,30);
    // anime_of_breath2(rgb_led_ring4, 0, 120 ,255,0,0,55);
    Serial.print("4\n");
  
  } 
  else if(digitalRead(button1) == LOW && digitalRead(button2) == LOW && digitalRead(button3) == LOW )//按键1触发->按键2->按键3触发，流水灯效果
  { 
    anime_of_lightall(rgb_led_ring4, 0, 120 ,255,0,0,255);
        /*--播放视频3--*/
        //Serial.print("video_3\n");
        Serial.print("3\n");
  } 
  else if (digitalRead(button1) == LOW && digitalRead(button2) == LOW)//按键1->按键2触发,变色流水灯
  { 
    anime_of_lightall(rgb_led_ring4, 0, 120 ,255,0,0,100);
    Serial.print("2\n");    
  }       
  else if(digitalRead(button1) == LOW)//按键1触发，流水灯+普通点灯的效果
  { 
    anime_of_lightall(rgb_led_ring4, 0, 120 ,255,0,0,20);
    Serial.print("1\n");
  }
  


}




/*----------普通点灯程序，只触发不熄灭，与按键控无关----------*/
void anime_of_lightall(CRGB lightarray1[], int start , int end ,int R,int G,int B ,int brightness)//闪烁效果
{
    int i;
    FastLED.setBrightness(brightness);
      for(i = start ; i < end ; i++ )
      {
        lightarray1[i] = CRGB(R,G,B);
      }
      FastLED.show();//show同样可以调节颜色  
      //Serial.print("light2\n");     
     return; 
}

/*--------呼吸灯-----------*/
void anime_of_breath(CRGB lightarray1[], int start , int end ,int R,int G,int B ,int brightness,int lasttime)//闪烁效果
{
    int n,m;
    for(m=0;m<brightness;m++)
    {
    FastLED.setBrightness(m);        
      for(n = start ; n < end ; n++ )
      {
        lightarray1[n] = CRGB(R,G,B);
      }
      FastLED.show();//show同样可以调节颜色  
      Serial.print("breath1\n");   
      delay(lasttime);      
    }

    for(m=brightness; m>0; m--)
    {
      FastLED.setBrightness(m);        
      for(n = start ; n < end ; n++ )
      {
        lightarray1[n] = CRGB(R,G,B);
      }
      FastLED.show();//show同样可以调节颜色  
      Serial.print("breath2\n");   
      delay(lasttime);      
    }
    return; 
}






