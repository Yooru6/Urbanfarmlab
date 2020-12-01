# Particle - Mikrokosmos
Here you will find the code used for the Mikrokosmos measuring equipment.

The measuring equipment was built with Particle-Photon and uses the sensors listed below:

| Parameter | Sensor | Info |
| ----------- | ----------- | ----------- |
| Temperature & Humidity | DHT22 |[Adafruit](https://www.adafruit.com/product/385 "Adafruit-DHT22")|
| Temperature | DS18B20 |[Adafruit](https://www.adafruit.com/product/381 "Adafruit-DS18B20")|
| pH | DFRobot SEN0161 v1.0 interface with Hanna HI-1286 electrode |[Hanna Instruments](https://www.hannanorden.se/shop/sv/elektroder-ph-och-orp/8726-ph-electrode-plastic-body.html?search_query=HI-1286&results=6 "Hanna Instruments - HI-1286"), [DFRobot](https://wiki.dfrobot.com/Analog_pH_Meter_Pro_SKU_SEN0169 "DFRobot v1.0 interface")|
| Electric conductivity | DFR0300 |[Adafruit](https://www.dfrobot.com/product-1123.html "DFRobot 0300 - electrical conductivity sensor")|
| Co2 | CCS811 |[Adafruit](https://www.sparkfun.com/products/14193 "Sparkfun - CCS811 Co2-sensor")|
| Light | TEMT6000 |[Adafruit](https://www.sparkfun.com/products/8688 "Sparkfun - TEMT6000 light-sensor")|


## Wiring Diagram
For the code and integration used in the instructions below to work, the particle sensor connections must be made according to the wiring diagram below.

<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Particle-Mikrokosmos_connections.png" width="50%" height="50%">

## Getting ready to import code

- Download the Particle app from the app store.
- Start up application
- Make a Particle account and log in
- Connect the power cable to the particle photon
- Go to the Particle application in your phone, press the "+" button in the lower right corner and select "set up a Photon"
- Follow the instructions provided by the application

<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/ParticleApp-alkun%C3%A4ytt%C3%B6.jpg" width="30%" height="30%">

## Uploading code to Particle

- Go to https://console.particle.io/devices
- Fill out required information and log in
  - You should now see same screen as in picture below
  - If a previously installed Particle photo is connected to the Internet, it should appear on the page and the color of the ball to its left should be blue
- Click "Web Ide" button from the left side of the site
<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Console_particle_io_v2.png" width="70%" height="70%">

- Click this link https://go.particle.io/shared_apps/5fbb9b63e6f0b000172c51bf
- Check that the correct particle device is selected in the lower right corner
  - If the correct device is not selected, press the yellow "P" icon to the left of the device name and select the device on which you want to install the program
- Press the "Flash" button at the top left to install the program

<IMAGE>

## Google integration
### Firestore/Firebase
First, we create a database for particle integration. In this project, we use a firebase database because of its features.
 - Go to https://console.cloud.google.com
 - Sign in with your google account
 - If you haven't used the free trial yet, you can activate it if you wish
 - Select "Firestore" from the navigation bar on the left side of the page
 - Click "Create Project" from the right up corner
   - Fill required information
 
 <img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Firestore-createproject.png" width="70%" height="70%">
 
 - After the project is successfully created, you will be presented with a view as shown below. Click "Select native mode".
 <img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Firestore-nativemode.png" width="70%" height="70%">
 
 - Now you have database has been created.
 - Next, we create a collection in the database. 
   - Press "START COLLECTION" and give it the name you want and press "SAVE"
<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/firestore-collection-v2.png" width="70%" height="70%">

### Pub/Sub
Next, we create a pub / sub topic for collecting sensor data from the particle service
- Click on the "pub / sub" heading in the navigation bar on the left side of the page.
- Click "CREATE TOPIC" and give it a descriptive name and "CREATE TOPIC"
<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/pubsub-topicname-v2.png" width="70%" height="70%">


