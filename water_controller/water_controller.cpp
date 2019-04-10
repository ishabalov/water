#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "water_controller.h"

/* Console */

void setup_console() {
    Serial.begin(SERIAL_BD);
}

/* Timer */

void IRAM_ATTR onTimer(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  isrCounter++;
  lastIsrAt = millis();
  portEXIT_CRITICAL_ISR(&timerMux);
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // It is safe to use digitalRead/Write here if you want to toggle an output
}

const unsigned long ALARM_INTERVAL = 100000;

void setup_timer() {
  // Create semaphore to inform us when the timer has fired
  timerSemaphore = xSemaphoreCreateBinary();

  // Use 1st timer of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(0, 80, true);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, ALARM_INTERVAL , true);

  // Start an alarm
  timerAlarmEnable(timer);
}

void read_timer() {
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
    uint32_t isrCount = 0, isrTime = 0;
    // Read the interrupt count and time
    portENTER_CRITICAL(&timerMux);
    isrCount = isrCounter;
    isrTime = lastIsrAt;
    portEXIT_CRITICAL(&timerMux);
    // Print it
    Serial.print("onTimer no. ");
    Serial.print(isrCount);
    Serial.print(" at ");
    Serial.print(isrTime);
    Serial.println(" ms");
  }  
}

uint32_t read_timer_last_millis() {
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
    uint32_t isrTime = 0;
    portENTER_CRITICAL(&timerMux);
    isrTime = lastIsrAt;
    portEXIT_CRITICAL(&timerMux);
    return isrTime;
  } else {
    return 0;
  }
}


/* BMP280 sensor */

void setup_bmp() {
  Serial.println("Setup bmp begin");
  if (!bmp.begin(BMP280_ADDRESS_ALT)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  } else {
    Serial.println("Successfully configured BMP280 sensor");
  }
  Serial.println("Setup bmp done");
}

void read_bmp() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  Serial.print("Approx altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
  Serial.println(" m");
}

/* GPIO */

void setup_GPIO() {
  pinMode (LED_SIG, OUTPUT);
  pinMode (LED_PIN, OUTPUT);
  delay(500);
  blink(1);
}

bool isOn = false;

void blink(int count) {
  for (int i=0;i<count;i++) {
    digitalWrite(LED_SIG, HIGH);
    delay(_on);
    digitalWrite(LED_SIG, LOW);
    if (i<count-1) {
      delay(_on);
    }
  }
}

void toggle() {
  if (isOn) {
    isOn = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("OFF");
  } else {
    isOn = true;
    digitalWrite(LED_PIN, HIGH);
    Serial.println("ON");
  }
}

/* UDP Communications */

void setup_wifi() {
  Serial.println("WiFi setup");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    delay(1000);
  }
  Serial.println("WiFi setup success");
}

void setup_udp_server() {
    if (udp.listen(UDP_PORT)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    blink(4);
    udp.onPacket([](AsyncUDPPacket packet) {
      handleUDPPacket(packet);
    });
  }
}

void handleUDPPacket(AsyncUDPPacket& packet) {
  Serial.print("UDP Packet Type: ");
  Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
  Serial.print(", From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(", To: ");
  Serial.print(packet.localIP());
  Serial.print(":");
  Serial.print(packet.localPort());
  Serial.print(", Length: ");
  Serial.print(packet.length());
  Serial.print(", Data: ");
  Serial.write(packet.data(), packet.length());
  Serial.println();
  //reply to the client
  float temperrature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  uint32_t last_timer = read_timer_last_millis();
  packet.printf(">>%s<<%.2f:%.2f>><<%d>>", packet.data(),temperrature,pressure,last_timer);
  toggle();
  blink(1);
}

/* General arduino core */
void setup() {
  setup_console();
  setup_bmp();
  setup_timer();
  setup_GPIO();
  setup_wifi();
  setup_udp_server();
}

void loop() {
  delay(2000);
  // read_timer();
  //  read_bmp();
}
