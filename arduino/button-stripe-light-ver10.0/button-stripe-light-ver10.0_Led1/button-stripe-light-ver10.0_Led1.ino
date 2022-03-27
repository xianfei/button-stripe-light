/*
author:zxw
fution:led1的对应控制程序
触发：红外
time: 2022-3-16
version: 10.0
bug：none
email：2474113608@qq.com
package:Fsatled、MsTimer
*/

#include <MsTimer2.h>     //定时器库的头文件
#include <FastLED.h>

#define NUM_LEDS_RING1 120 //
#define PIN_LED_RING1 13//
CRGB rgb_led_ring1[NUM_LEDS_RING1]; 
signed int index_ring1 = 0;//全局变量：用于定时器自加的变量，控制灯珠的位置


int flag1 = 0;//用来判断是哪条灯带触发点
int flag2 = 0;
int flag3 = 0;





/*--------------按键的初始化--------*/
 int button1=2;
 int button2=3;//这里貌似不需要led2，3的控制
 int button3=4;

/*--------setup初始化函数------------*/
void setup()
{
  Serial.begin(9600); //初始化串口
  FastLED.addLeds<WS2812, PIN_LED_RING1>(rgb_led_ring1, NUM_LEDS_RING1);//注册led1
  MsTimer2::set(10,onTimer); //设置中断，每1000ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时
  pinMode(button1,INPUT_PULLUP);//按键读取端口需要使用上拉电阻模式才可以实现    
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  
}
/*-------------loop循环----------------*/
void loop()
{
  MsTimer2::stop(); 
  clear();
  if(digitalRead(button1) == LOW)//按键1触发，流水灯+普通点灯的效果
  { 
    MsTimer2::start();//启动定时器 
    anime_of_buttonflowing(&flag1, &index_ring1, button1,rgb_led_ring1,0,120,255,255,255,10);//流水灯灯效
     MsTimer2::stop();
    /*--播放视频1--*/
    Serial.println("video_1\n");
  }
}

/*--------------中断服务程序----------*/
void onTimer()
{
  if(flag1==1) index_ring1++;
}


 /*--------------自定义灯效函数--------------------*/
  /*--------------流水灯函数--------------------*/
//bug:持续触发的时候如何只点亮一次
void anime_of_buttonflowing(int *flag,signed int *index, int button,CRGB lightarray[], int start , int end ,int R,int G,int B ,int brightness)//流水灯效果
{
  int buttonState;
    *flag=1;
    for(*index = start ; *index <end; )
    {
      buttonState=digitalRead(button);
      if(buttonState == HIGH ) //如果在点亮期间中断触发，那么就熄灭
      {
        MsTimer2::stop();//一旦按键抬起那么，定时器需要停止，防止继续计时产生误差
        *flag=0;
          for(*index = 0 ; *index < end ; *index++)
          {
            lightarray[*index]=CRGB(0,0,0);
          }
      FastLED.show(brightness);
      *index=start;
        return;    
      }
    lightarray[*index] = CRGB(R,G,B);
    FastLED.show(brightness);//show同样可以调节颜色
    }
    return;
}

 /*--------------闪烁函数--------------------*/
void anime_of_blink(CRGB lightarray1[], int start , int end ,int R,int G,int B ,int brightness,int times,int delaytimes)//闪烁效果
{
    int i,j;
    for(j=0;j<times;j++)
    {
      for(i = start ; i < end ; i++ )
      {
        lightarray1[i] = CRGB(R,G,B);
      }
      FastLED.show(brightness);//show同样可以调节颜色
      delay(delaytimes);    
      for(i = start ; i < 120 ; i++ )
     {
       lightarray1[i] = CRGB(0,0,0);
      }
      FastLED.show();//show同样可以调节颜色
      delay(delaytimes); 
    }
    return;
}

 /*--------------普通点灯函数，按键按下触发抬起熄灭--------------------*/
 //按下点亮抬起来熄灭
void anime_of_normallight(int button,CRGB lightarray1[], int start , int end ,int R,int G,int B ,int brightness)//闪烁效果
{
    int i;
    //FastLED.setBrightness(brightness);
    if(digitalRead(button) == LOW )
    {
      for(i = start ; i < end ; i++ )
      {
        lightarray1[i] = CRGB(R,G,B);
      }
      FastLED.show();//show同样可以调节颜色  

    }
    else
    {
        for(i=0 ; i<end ; i++ )
        {
          lightarray1[i] = CRGB(0,0,0);
        }
        FastLED.show();
        //Serial.print("light2\n");
    }      
     return; 

}

/*------------------clear函数--------------------*/
//想办法在无按压的时候让所有的灯带都清零

void clear()
{
    int i;
    Serial.print("clear\n");
  if(digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH)
  {
    for(i = 0 ; i < 120 ; i++ )
     {
        rgb_led_ring1[i] = CRGB(0,0,0);
      }
    FastLED.show();//show同样可以调节颜色
  }
  return;
}