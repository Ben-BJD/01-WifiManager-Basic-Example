#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

void setup() 
{
    // Start serial communication
    Serial.begin(115200);
    Serial.println("--- Starting ESP32 ---");

    // Initialize WiFiManager
    // Local intialization. There is no need to keep it in memory after setup() has finished.
    WiFiManager wm;

    // --- OPTIONAL SETTINGS ---
    // Uncomment the line below to wipe saved WiFi credentials. 
    //    - Stored SSID/password via NVS are removed
    // Recommended when you are testing so the AP spawns every time.
    //wm.resetSettings();

    // Set a timeout so the ESP doesn't hang forever if nobody configures the WiFi
    wm.setConfigPortalTimeout(300); // Auto close portal after 5 minutes

    // Print debug info to the Serial monitor (helpful for troubleshooting)
    wm.setDebugOutput(true); 
    // -------------------------

    Serial.println("Starting WiFiManager...");
    Serial.println("If no valid WiFi is saved, it will create an Access Point.");

    // autoConnect() performs the magic.
    // It tries to connect to the last saved WiFi. 
    //    - WiFiManager stores the SSID/password as key/value pairs via NVS and reads them back on boot.
    // If it fails or no WiFi is saved, it sets up an Access Point.
    // AP Name: "ESP32_Config_AP", AP Password: "pizza4tree"
    bool res;
    res = wm.autoConnect("ESP32_Config_AP", "pizza4tree");

    // Check the result
    if(!res) 
    {
        Serial.println("Failed to connect or hit timeout.");
        Serial.println("Rebooting to try again...");
        delay(3000);
        ESP.restart();
    } 
    else 
    {
        // If you get here, you have successfully connected to the local router!
        Serial.println("");
        Serial.println("SUCCESS! Connected to WiFi.");
        Serial.print("Assigned IP Address: ");
        Serial.println(WiFi.localIP());
    }
}

void loop() 
{
    // Your main project code goes here.
    
    // For demonstration, we just print a heartbeat every 5 seconds
    if (WiFi.status() == WL_CONNECTED) 
    {
        Serial.println("Running normally... WiFi is connected.");
    } 
    else 
    {
        Serial.println("WiFi is disconnected! Attempting to reconnect...");
        WiFi.reconnect(); 
    }
    
    delay(5000);
}