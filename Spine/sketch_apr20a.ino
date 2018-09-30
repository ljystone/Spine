int pin = 2; //定义引脚为D2
unsigned long duration=0; //定义duration变量为无符号长整数型变量
int i = 0;
void setup()
{
Serial.begin(9600); //串口波特率为9600
pinMode(pin, INPUT); //设置引脚为输入模式
delay(5000);
Serial.println("begin"); 
}


void loop()
{
duration=0;
for(i=0;i<5;i++){
duration += pulseIn(pin, HIGH); 
duration += pulseIn(pin, LOW); 
}
Serial.println(duration);
duration = duration/5;
Serial.println(duration);

duration=1000000/duration;
Serial.print(" f is "); 
Serial.print(duration); 
Serial.println(" HZ"); 
duration = duration*60;
Serial.print(" v is "); 
Serial.print(duration); 
Serial.println(" r/min"); 
delay(2000);
}
