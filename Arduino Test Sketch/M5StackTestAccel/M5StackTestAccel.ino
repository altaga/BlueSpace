/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/core2
*
* describe：MPU6886 example.  惯性传感器
* date：2021/7/21
*******************************************************************************
*/
#include <M5Core2.h>

float accX = 0.0F;  // Define variables for storing inertial sensor data
float accY = 0.0F;  //定义存储惯性传感器相关数据的相关变量
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float temp = 0.0F;

/* After M5Core2 is started or reset
the program in the setUp () function will be run, and this part will only be run once.
在 M5Core2 启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup(){
  M5.begin(); //Init M5Core.  初始化 M5Core
  M5.IMU.Init();  //Init IMU sensor.  初始化惯性传感器
  M5.Lcd.fillScreen(BLACK); //Set the screen background color to black. 设置屏幕背景色为黑色
  M5.Lcd.setTextColor(GREEN , BLACK); //Sets the foreground color and background color of the displayed text.  设置显示文本的前景颜色和背景颜色
  M5.Lcd.setTextSize(2);  //Set the font size.  设置字体大小
}

void loop(){
  M5.IMU.getAccelData(&accX, &accY, &accZ);    //Passing Acc Reference
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);  //Passing Gyro Reference  
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);     //Passing Ahrs Reference
  M5.IMU.getTempData(&temp);                   //Passing Temp Reference

/* The M5Core screen is 320x240 pixels, starting at the top left corner of the screen (0,0).
gyroscope output related
M5Stack屏幕像素为 320x240,以屏幕左上角为原点 (0,0)*/

//gyroscope output related.  陀螺仪输出相关
  M5.Lcd.setCursor(0, 20);  //Move the cursor position to (x,y).  移动光标位置到(x,y)处
  M5.Lcd.printf("gyroX,  gyroY, gyroZ"); //Screen printingformatted string.  输出格式化字符串
  M5.Lcd.setCursor(0, 42);
  M5.Lcd.printf("%6.2f %6.2f%6.2f o/s", gyroX, gyroY, gyroZ);

// Accelerometer output is related
//加速度计输出相关
  M5.Lcd.setCursor(0, 70);
  M5.Lcd.printf("accX,   accY,  accZ");
  M5.Lcd.setCursor(0, 92);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);

// Pose output is related
//姿态输出相关
  M5.Lcd.setCursor(0, 120);
  M5.Lcd.printf("pitch,  roll,  yaw");
  M5.Lcd.setCursor(0, 142);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f deg", pitch, roll, yaw);

// Inertial sensor temperature output related
//惯性传感器温度输出相关
  M5.Lcd.setCursor(0, 175);
  M5.Lcd.printf("Temperature : %.2f C", temp);

  delay(1000);  // Delay 1000ms (1 sec)  //延迟1000ms（1秒）
}
