///
.....
// ========== Wi-Fi НАСТРОЙКИ ==========
const char* ssid = "xxxxxxxxxxxxxxx";
const char* password = "xxxxxxxxxxxxxx";

#define CAM_ID 1
const String number_cam = "cam_" + String(CAM_ID);
IPAddress staticIP(x, x, x, x + int(CAM_ID));
IPAddress gateway(x, x, x, x);
IPAddress subnet(x, x, x, x);
IPAddress primaryDNS(x, x, x, x);
IPAddress secondaryDNS(0, 0, 0, 0);

// ========== ПОТОКОВЫЕ КОНСТАНТЫ ==========
#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";


// ========== ПРОТОТИПЫ ==========
void mqttCallback(char* topic, byte* payload, unsigned int length);
void processCommand(String cmd);
void fallbackBrightnessControl();
int calculateBrightness(camera_fb_t* fb);
void reconnectMQTT();
void startCameraServer();
void configInitCamera();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);

// ========== HTML СТРАНИЦА ==========
extern const char MAIN_page[];

// ========== HTTP-СЕРВЕР ==========
static httpd_handle_t camera_httpd = NULL;