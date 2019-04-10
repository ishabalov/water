/*

Water controller v 2.0

GPIO 21 (SDA) BMP280
GPIO 22 (SCL) BMP280

use nc -u 198.128.29.254 18342

for udp communications

*/


/* Console */
const unsigned int SERIAL_BD = 115200;

/* Timer */
hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

void IRAM_ATTR onTimer();
void setup_timer();
void read_timer();
uint32_t read_timer_last_millis();

/* BMP280 sensor */
uint8_t BMP280_ADDRESS_ALT = 0x76;

Adafruit_BMP280 bmp; // Use default I2C GPIO: 21(SDA) 22(SCL)

void setup_bmp();
void read_bmp();

/* GPIO */
const unsigned int LED_SIG = 2;
const unsigned int LED_PIN = 19;
const unsigned long _on = 100;

void setup_GPIO();
void blink(int count);
void toggle();

/* UDP Communications */
//const char * ssid = "shabalov5";
//const char * password = "zeRo07grOw=";
const char * ssid = "lbnl-visitor-offsite";
const char * password = "redpingfreed27";
const unsigned int UDP_PORT = 18342;

AsyncUDP udp;

void setup_wifi();
void setup_udp_server();
void handleUDPPacket(AsyncUDPPacket& packet);
