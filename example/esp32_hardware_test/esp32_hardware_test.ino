#include <ETH.h> //引用以使用ETH
#define ETH_ADDR 0
#define ETH_POWER_PIN -1
#define ETH_MDC_PIN 23
#define ETH_MDIO_PIN 18
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT

const int led_pin[8] = {32, 33, 14, 13, 15, 4, 16, 5};

void printETHInfo(void) // 打印基本信息
{
    Serial.print("ETH MAC: ");
    Serial.print(ETH.macAddress());
    Serial.print(", IPv4: ");
    Serial.print(ETH.localIP());
    if (ETH.fullDuplex())
    {
        Serial.print(", FULL_DUPLEX");
    }
    Serial.print(", ");
    Serial.print(ETH.linkSpeed());
    Serial.println("Mbps");
}
void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_ETH_START: // 启动ETH成功
        Serial.println("ETH Started");
        break;
    case SYSTEM_EVENT_ETH_CONNECTED: // 接入网络
        Serial.println("ETH Connected");
        break;
    case SYSTEM_EVENT_ETH_GOT_IP: // 获得IP
        Serial.println("ETH GOT IP");
        printETHInfo();
        break;
    case SYSTEM_EVENT_ETH_DISCONNECTED: // 失去连接
        Serial.println("ETH Disconnected");
        break;
    case SYSTEM_EVENT_ETH_STOP: // 关闭
        Serial.println("ETH Stopped");
        break;
    default:
        break;
    }
}
void setup()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(led_pin[i], OUTPUT);
    }

    Serial.begin(115200);
    delay(1000);
    Serial.println();
    WiFi.onEvent(WiFiEvent);                                                               // 注册事件
    ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE); // 启用ETH
    // ETH.begin();
}

void loop()
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(led_pin[i], HIGH);
        delay(300);
    }
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(led_pin[i], LOW);
        delay(300);
    }
}
