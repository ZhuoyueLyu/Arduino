#include "esp_camera.h"
#include <WiFi.h>
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"
#include <HardwareSerial.h>
HardwareSerial mySerial(1); 

char mystr[11]; //Initialized variable to store recieved data

#define A 12      // the pin connected to the wire A of the coil A (or to the H-bridge pin controlling the same wire)
#define A_bar 15  // the pin connected to the wire A- of the coil A (or to the H-bridge pin controlling the same wire)
#define B 13      // the pin connected to the wire B of the coil A (or to the H-bridge pin controlling the same wire)
#define B_bar 14  // the pin connected to the wire B- of the coil A (or to the H-bridge pin controlling the same wire)
#define stepsPerRevolution 200  // you can the number of steps required to make a complete revolution in the data sheet of your motor
// smaller values may make the motor produce more speed and less torque
int x = 2100;  // the smaller the number, the faster
int speed_1 = 0; // stop
int speed_2 = 7000; // mid
int speed_3 = 2100; // fastest
bool shouldRun = true; // for the motor
int curr_speed = 2100;


// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid = "ESP32-CAM Access Point Zhuoyue";
const char* password = "66666666";
void startCameraServer();

void setup() {
  pinMode(A, OUTPUT);
  pinMode(A_bar, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(B_bar, OUTPUT);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  mySerial.begin(115200, SERIAL_8N1, 33, 2); // RX, TX
  // Serial.begin(9600, SERIAL_8N1, 2, 33); // using pin 2 as TX output, pin 33 is an LED as RX, never mind
  // Serial.begin(9600);  // this is the computer

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(config.pixel_format == PIXFORMAT_JPEG){
    if(psramFound()){
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    // Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  if(config.pixel_format == PIXFORMAT_JPEG){
    s->set_framesize(s, FRAMESIZE_QVGA);
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

  WiFi.softAP(ssid, password); // Zhuoyue



  startCameraServer();
  Serial.print("Camera Ready!");
  // Serial.print(WiFi.localIP());
  // Serial.println("' to connect");
}

void loop() {
     int num_faces = 0;
   // On the server side (python), we only send info
   // when there is changes. I tried to handle that on this side
   // but for some reason, whenever the board receive data
   // it stop spinning, so it makes the board very lagg
   if (Serial.available() > 0)
   {
      num_faces = Serial.parseInt();
      switch (num_faces)
      {
      case 0:
            update_motor2_speed(speed_3);
            curr_speed = speed_3;
            shouldRun = true;
            delay(500);
         break;
      case 1:
            update_motor2_speed(speed_2);
            curr_speed = speed_2;
            shouldRun = true;
            delay(500);
         break;
      case 2:
        // do nothing for motor 1
         update_motor2_speed(speed_1);
         shouldRun = false;
         delay(500);
         break;
      }
   }
  if (shouldRun) {
    run_motor1(curr_speed);
  }
}

void run_motor1 (int new_speed){

     if (x != new_speed)
   {
      x = new_speed;
   }
  for (int i = 0; i < (stepsPerRevolution / 4); i++) {
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, LOW);
    delayMicroseconds(x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delayMicroseconds(x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, LOW);
    delayMicroseconds(x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delayMicroseconds(x);
  }
}

void update_motor2_speed(int new_speed)
{
  itoa(new_speed * 12,mystr,10);
  mySerial.write(mystr,10); //Write the serial data
}
