/* Shivam Patel
   Bonus Project EECS1011
   RssiChecker
*/

//Add BLE library to sketch
#include <ArduinoBLE.h>

// Define the name of the Bluetooth peripheral
const char* peripheralName = "R4";

// Create a BLE Service
BLEService fileTransferService("19B10000-E8F2-537E-4F6C-D104768A1214");

// Create a BLE Characteristic for receiving data
const char* dataCharacteristicUUID = "19B10001-E8F2-537E-4F6C-D104768A1214";
BLECharacteristic dataCharacteristic(dataCharacteristicUUID, BLEWrite | BLERead, "");

// Initalize Boolean 
bool isGettingRssi = false;

void setup() {
  // Initialize the Serial communication 
  Serial.begin(9600);
  //Delay by 5000 ms
  delay(5000);
  // Initialize the BLE library
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
  //Set BLE peripherals to be able to be connected to
  BLE.setConnectable(true);
  // Set the local name of the Bluetooth peripheral
  BLE.setLocalName(Arduino);
  BLE.setAdvertisedService(fileTransferService);
  // Add the characteristics to the service
  fileTransferService.addCharacteristic(dataCharacteristic);
  // Start advertising
  BLE.advertise();
}

void loop() {
  // Make a BLE Device object called central that stores the value of BLE.central() which checks if their are any centrals available 
  BLEDevice central = BLE.central();
  // if central is true (if there is a central available)
  if (central) {
    
    char receivedData [200] ;
    // While central is connected
    while (central.connected()) {
      // While isGettingRssi is false
      while(!isGettingRssi){  
      // Delay by 1000 ms
      delay(1000);  
      //Print out the rssi of the central into the serial monitor
      Serial.println(central.rssi());
      //If the central is not connected
      if (!central.connected()){
      // Disconnect any BLE devices that are connected
      BLE.disconnect();
      // Connect to central
      central.connect();
      /* This if statement makes it so that if the central disconnects because of the time interval of the central being connected runs out
         then it disconnects the BLE device and reconnects to the central making it always try to connect to the central and bypasses the 
         time interval disconnecting the central
      */
    }     
    }
     
    }
  }
}