#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h> // Include the LCD library
#include "env.h" // Include the env.h file

// Initialize the LCD (16x2 with I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function prototypes
void initializeLCD();
void connectToWiFi();
void fetchAndDisplayMessage();

void setup() {
  Serial.begin(115200); // Initialize Serial communication

  initializeLCD(); // Initialize the LCD
  connectToWiFi(); // Connect to Wi-Fi
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    fetchAndDisplayMessage(); // Fetch and display the message
  } else {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Disconnected");
    WiFi.reconnect(); // Attempt to reconnect to Wi-Fi
  }
  delay(5000); // Wait 5 seconds before the next request
}

// Function to initialize the LCD
void initializeLCD() {
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight(); // Turn on the backlight
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set the cursor to the first column of the first row
  lcd.print("Connecting..."); // Display initial message
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  if (IS_WOKWI) {
    WiFi.begin(SSID, PASS, CHANNEL); // For Wokwi simulation
  } else {
    WiFi.begin(SSID, PASS); // For physical hardware
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected"); // Display Wi-Fi connection status
}

// Function to fetch data from the API and display it on the LCD
void fetchAndDisplayMessage() {
  HTTPClient httpClient; // Create an HTTPClient object
  httpClient.begin(ENDPOINT); // Initialize the HTTP request with the API endpoint
  httpClient.addHeader("api-key", API_KEY); // Add the API key header

  int httpResponseCode = httpClient.GET(); // Send the GET request

  if (httpResponseCode == HTTP_CODE_OK) { // Check if the request was successful
    String jsonResponse = httpClient.getString(); // Get the JSON response
    Serial.println("JSON Response: " + jsonResponse);

    // Parse the JSON response
    StaticJsonDocument<200> messageData;
    deserializeJson(messageData, jsonResponse);

    const char* line1 = messageData["line_1"]; // Extract line 1
    const char* line2 = messageData["line_2"]; // Extract line 2

    // Display the message on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1); // Display line 1
    lcd.setCursor(0, 1);
    lcd.print(line2); // Display line 2

    // Print the message to the Serial Monitor
    Serial.println("Line 1: " + String(line1));
    Serial.println("Line 2: " + String(line2));
  } else {
    Serial.println("Error fetching message. HTTP Code: " + String(httpResponseCode));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("API Error"); // Display error message
    lcd.setCursor(0, 1);
    lcd.print("Code: " + String(httpResponseCode)); // Display error code
  }

  httpClient.end(); // Close the HTTP connection
}