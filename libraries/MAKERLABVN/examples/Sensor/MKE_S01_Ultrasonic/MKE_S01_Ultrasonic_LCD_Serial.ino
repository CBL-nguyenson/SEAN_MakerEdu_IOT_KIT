// Thêm bộ thư viện LCD.
// Add the LCD library.
#include <MKL_LiquidCrystal_I2C.h>
#include <MKL_HCSR04.h>

// Khởi tạo LCD
//LCD config
MKL_LiquidCrystal_I2C lcd(0x27, 16, 2);

// Khởi tạo cảm biến
// Sensor config
#define ECHO_PIN 12
#define TRIG_PIN 13
MKL_HCSR04 ultra(TRIG_PIN, ECHO_PIN);

void setup()
{
  // Khởi động LCD
  // LCD start
  lcd.init();
  lcd.backlight();

  // Khởi động kết nối Serial UART ở tốc độ 115200 để truyền dữ liệu lên máy tính.
  // Start the Serial UART connection at 115200 to transfer data to the computer.
  Serial.begin(115200);
}

void loop()
{
  //Gửi giá trị khoảng cách lên LCD
  //Show the sensor value on LCD
  lcd.setCursor(4,0);
  lcd.print("Distance");
  lcd.setCursor(4,1);
  lcd.print(ultra.dist());
  lcd.setCursor(10,1);
  lcd.print("cm");

  // Truyền khoảng cách đo được của cảm biến siêu âm lên máy tính.
  // Show the sensor value on Arduno Serial Monitor
  Serial.print("Distance in cm: ");
  Serial.println(ultra.dist());
  
  // Chờ 500ms
  // Wait 500ms
  delay(500);
}