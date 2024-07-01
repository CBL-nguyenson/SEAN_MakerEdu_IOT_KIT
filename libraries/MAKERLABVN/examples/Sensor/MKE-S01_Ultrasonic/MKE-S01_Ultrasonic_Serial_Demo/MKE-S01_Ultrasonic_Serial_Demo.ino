#include <MKL_HCSR04.h>

// Chọn chân đọc cảm biến.
// Select the pin to read the sensor.
#define ECHO_PIN 12
#define TRIG_PIN 13

// Cấu hình chân kết nối tín hiệu cho cảm biến siêu âm.
// Configure the signal connection pins for the ultrasonic sensor.
MKL_HCSR04 ultra(TRIG_PIN, ECHO_PIN);

void setup()
{
  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
}

void loop()
{
  // Truyền khoảng cách đo được của cảm biến siêu âm lên máy tính.
  // Transmit the measured distance of the ultrasonic sensor to the computer.
  Serial.print("Distance in cm: ");
  Serial.println(ultra.dist());

  // Chờ 60ms mỗi lần đọc để tránh nhiễu tín hiệu.
  // Wait 60ms per read to avoid signal interference.
  delay(60);
}