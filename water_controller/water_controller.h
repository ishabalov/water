/*

Water controller v 2.0

GPIO 21 (SDA) BMP280
GPIO 22 (SCL) BMP280

use nc -u 198.128.29.254 18342

for udp communications

*/


/* Console */
const unsigned int SERIAL_BD = 115200;


/* BMP280 sensor */
uint8_t BMP280_ADDRESS_ALT = 0x76;

Adafruit_BMP280 bmp; // Use default I2C GPIO: 21(SDA) 22(SCL)

void setup_bmp();
void read_bmp();

/* GPIO */
const uint8_t LED_SIG = 2;
const uint8_t LED_PIN = 19;
const unsigned long BLINK_ON = 100;

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

/* Working structures */


