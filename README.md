This lab demonstrates how to use an ESP32 microcontroller to consume a RESTful API, parse the JSON response, and display the data on a 16x2 LCD. The ESP32 connects to Wi-Fi, fetches data from the API and updates the LCD with the received message. 
The functions expected behaciours: 
connectToWifi() is usedto connect the ESP32 to a Wi-Fi network that is specified in env.h. 
fetchAndDisplayMessage() is used to fetch the data from the API and display it on the LCD. It send a GET request to the API endpoint, parses the JSON response to extract "line_1" and "line_2". Then displays
the extracted data on the LCD. It then prints the data and any errors to the Serial Monitor. 
setup() is used to initialize the serial monitor, LCD and Wi_Fi connection. 
loop() calls the fetchAndDisplayMessage() every 5 seconds if the Wi-Fi is connected, also attempts to reconnnect to the Wi-Fi if the 
connection is lost. 
The code was written as a part of the ECSE3038 Lab 5, focusing on using embedded systems to 
consume APIs. 


Riddle : I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?
