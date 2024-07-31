

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */
//#####################################################################
//######## Các chân sau đã được kết nối sẵn với driver động cơ ########
//################## Không thay đổi chân (PIN GPIO) ###################



//----Motor_A----
#define in1 9  // L298n Motor Driver pins.
#define in2 8
#define pwm_1 6  // Speed motor
//----Motor_B----
#define in3 7
#define in4 4
#define pwm_2 5


//#####################################################################
//#####################################################################




// Định nghĩa các chân GPIO cho vi điều khiển
#define RELAY_PIN 11  // Chân điều khiển RELAY
#define LED_PIN 10    // Chân điều khiển LED


#define BLYNK_TEMPLATE_ID "TMPL6udENkXYk"
#define BLYNK_TEMPLATE_NAME "IT"
#define BLYNK_AUTH_TOKEN "XTybg-3Nm1BjnHSxvTD-WKpE91ldCm_g"


// Bao gồm các thư viện cần thiết
#include "BlynkGate.h"  // Thư viện BlynkGate cho kết nối Blynk


// Thiết lập WiFi
char auth[] = BLYNK_AUTH_TOKEN;    // Mã xác thực Blynk
char ssid[] = "QuangHop";  // Tên mạng Wi-Fi (chỉ hoạt động với băng tần 2.4Ghz)
char pass[] = "12345678";         // Mật khẩu Wi-Fi




// Định nghĩa các chân Virtual Pins như trên Web BLYNK
const int Virtual_Pins_LED = 0;
const int Virtual_Pins_Relay = 2;
const int Virtual_Pins_Motor = 1;


unsigned long lastTimeSend = 0;  // Biến thời gian gửi dữ liệu cuối cùng


int ledState = 0;     // Biến trạng thái của LED (bật/tắt)
int relayState = 0;   // Biến trạng thái của Relay (bật/tắt)
int motor_speed = 0;  // Biến lưu giá trị tốc độ motor


/* ------------------------------------------------------------------------- */
/*                                   Set_Up                                  */
/* ------------------------------------------------------------------------- */


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);


  pinMode(LED_PIN, OUTPUT);    // Thiết lập chân LED là OUTPUT
  pinMode(RELAY_PIN, OUTPUT);  // Thiết lập chân module Relay là OUTPUT


  Serial.begin(115200);                   // Khởi tạo giao tiếp Serial để debug
  Serial.println("Start BlynkGate I2C");  // In ra thông báo khởi tạo BlynkGate I2C


  Blynk.begin(auth, ssid, pass);  // Kết nối với Blynk bằng thông tin xác thực và Wi-Fi
}


/* ------------------------------------------------------------------------- */
/*                                   MAIN                                    */
/* ------------------------------------------------------------------------- */


void loop() {
  Blynk.run();  // Xử lý các yêu cầu từ Blynk, không sử dụng delay trong loop này
  digitalWrite(LED_PIN, ledState);       // Cập nhật trạng thái của LED (bật/tắt)
  digitalWrite(RELAY_PIN, !relayState);  // Cập nhật trạng thái của relay (bật/tắt)


  // Điều khiển Motor_A
  if (motor_speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(pwm_1, map(abs(motor_speed), 0, 100, 40, 100));
  } else if (motor_speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(pwm_1, map(abs(motor_speed), 0, 100, 40, 100));
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */


BLYNK_WRITE_DEFAULT() {  // Nhận giá trị từ Virtual Pin
  // double myDouble = param.asFloat();  // Nhận giá trị từ Blynk và chuyển đổi thành kiểu float
  // String myString = param.asString();
  int myInt = param.asInt();  // Nhận giá trị từ Blynk và chuyển đổi thành kiểu int


  Serial.print("input V");    // In ra pin đầu vào
  Serial.print(request.pin);  // In ra số pin
  Serial.print(": ");
  Serial.println(myInt);  // In ra giá trị nhận được

  if (request.pin == Virtual_Pins_LED) {  // Kiểm tra nếu là Virtual_Pins_LED
    if (myInt == 1) {                     // Nếu giá trị nhận được là 1
      ledState = 1;                       // Bật LED
    } else {                              // Nếu giá trị nhận được không phải là 1
      ledState = 0;                       // Tắt LED
    }
  }
  if (request.pin == Virtual_Pins_Relay) {  // Kiểm tra nếu là Virtual_Pins_Relay
    if (myInt == 1) {                       // Nếu giá trị nhận được là 1
      relayState = 1;                       // Bật Relay
    } else {                                // Nếu giá trị nhận được không phải là 1
      relayState = 0;                       // Tắt Relay
    }
  }
  if (request.pin == Virtual_Pins_Motor) {  // Kiểm tra nếu là Virtual_Pins_Motor
    motor_speed = myInt;                    // Lưu giá trị vào biến motor_speed
  }
}
