
#include "WiFiEsp.h"

// Emulate Serial1 on pins 7/6 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#endif


char ssid[] = "Twim";    // network SSID (name)
char pwd[] = "12345678";  // network password
char pwdErr[] = "xxxx";    // wrong password


void setup()
{
  // Initialize serial and wait for port to open
  Serial.begin(115200);
  while (!Serial);

  WiFi.init(115200);
}

void loop()
{
  assertEquals("Firmware version", WiFi.firmwareVersion(), "1.3.0");
  assertEquals("Status is (WL_DISCONNECTED)", WiFi.status(), WL_DISCONNECTED);
  assertEquals("Connect", WiFi.begin(ssid, pwd), WL_CONNECTED);
  assertEquals("Check status (WL_CONNECTED)", WiFi.status(), WL_CONNECTED);
  assertEquals("Check SSID", WiFi.SSID(), ssid);

  IPAddress ip = WiFi.localIP();
  assertNotEquals("Check IP Address", ip[0], 0);
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  byte mac[6]={0,0,0,0,0,0};
  WiFi.macAddress(mac);

  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
  Serial.println();
  
  assertEquals("Disconnect", WiFi.disconnect(), WL_DISCONNECTED);
  assertEquals("Check status (WL_DISCONNECTED)", WiFi.status(), WL_DISCONNECTED);
  assertEquals("IP Address", WiFi.localIP(), 0);
  assertEquals("Check SSID", WiFi.SSID(), "");
  assertEquals("Wrong pwd", WiFi.begin(ssid, pwdErr), WL_CONNECT_FAILED);

  Serial.println("END OF TESTS");
  delay(60000);
}


////////////////////////////////////////////////////////////////////////////////////


void assertNotEquals(const char* test, int actual, int expected)
{
  if(actual!=expected)
    pass(test);
  else
    fail(test, actual, expected);
}

void assertEquals(const char* test, int actual, int expected)
{
  if(actual==expected)
    pass(test);
  else
    fail(test, actual, expected);
}

void assertEquals(const char* test, char* actual, char* expected)
{
  if(strcmp(actual, expected) == 0)
    pass(test);
  else
    fail(test, actual, expected);
}


void pass(const char* test)
{
  Serial.print(F("********************************************** "));
  Serial.print(test);
  Serial.println(" > PASSED");
  Serial.println();
}

void fail(const char* test, char* actual, char* expected)
{
  Serial.print(F("********************************************** "));
  Serial.print(test);
  Serial.print(" > FAILED");
  Serial.print(" (actual=\"");
  Serial.print(actual);
  Serial.print("\", expected=\"");
  Serial.print(expected);
  Serial.println("\")");
  Serial.println();
  delay(10000);
}

void fail(const char* test, int actual, int expected)
{
  Serial.print(F("********************************************** "));
  Serial.print(test);
  Serial.print(" > FAILED");
  Serial.print(" (actual=");
  Serial.print(actual);
  Serial.print(", expected=");
  Serial.print(expected);
  Serial.println(")");
  Serial.println();
  delay(10000);
}

