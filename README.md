# Mikrokosmos
<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Mikrokosmos.jpg" width="50%" height="50%">

The Mikrokosmos is a greenhouse equipped with measuring equipment and it is located on the Metropolia's Myyrmäki campus. It is equipped with an ebb and flow hydroponic system and the growing medium used is leca-gravel. The climate of Mikrokosmos is optimized to be optimal for plant growth. Mikrokosmos's climate related data is collected by sensors and stored in a firebase database and on a google sheet by utilizing Particle Cloud and Google Cloud Platform.

The Mikrokosmos has also been provided with an open-API with which anyone can access the data.

<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Mikrokosmos-diagram1.PNG" width="50%" height="50%">

In this repository you will find the work steps and source codes related to building a Mikrokosmos.

## Particle - Mikrokosmos
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


### Wiring Diagram
<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/Particle-Mikrokosmos_connections.png" width="50%" height="50%">

### Getting ready to import code

- Download the Particle app from the app store.
- Start up application
- Make a Particle account and log in
- Connect the power cable to the particle photon
- Go to the Particle application in your phone, press the "+" button in the lower right corner and select "set up a Photon"
- Follow the instructions provided by the application

<img src="https://github.com/Yooru6/Urbanfarmlab/blob/main/Pictures/ParticleApp-alkun%C3%A4ytt%C3%B6.jpg" width="30%" height="30%">

### Uploading code to Particle

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

## Mikrokosmos-API
With this API you can get data from hydroponic greenhouse located in urbanfarmlab.

#### JSON data example:
{"id":"YETNqaxhk4QUv2elcq0a","name":"mikrokosmos","data":{"tvoc":266,"ph":7.98,"light":1,"co2":1624,"h":79.3,"ec":0.023,"id":1,"temp":25.5,"time":"2020-11-15 17:30:16","tempW":20.88},"publishTime":"2020-11-15T15:30:02.141Z"}

### Data parameters:

| Parameter | Info |
| ----------- | ----------- |
| id | ID |
| name | name of the greenhouse |
| data | Temperature(C), Humidity(%), Air Temperature(C), lightvalue(on/off), pH(1-14), EC(analog value), Co2(ppm), TVOC(ppm), Local Time(yyyy-mm-dd hh-mm-ss-) |
| publishTime | date and time in time zone zero(yyyy-mm-dd hh:mm:ss) |

### Commands:
<ul>
 
<li>Get by ID</li>
<ul>
   <li>https://us-central1-amiable-hydra-279814.cloudfunctions.net/mikrokosmos/api/read/IDHERE</li>
</ul>
 
<li>Get ALL</li>
<ul>
  <li>https://us-central1-amiable-hydra-279814.cloudfunctions.net/mikrokosmos/api/read</li>
  <li>Ordered New->Old</li>
</ul>
 
<li>Get by DATE</li>
<ul>
  <li>https://us-central1-amiable-hydra-279814.cloudfunctions.net/mikrokosmos/api/read/datetime/yyyy-mm-dd</li>
  <li>Uses time variable from data</li>
</ul>
 
 <li>Get by TIME</li>
 <ul>
   <li>https://us-central1-amiable-hydra-279814.cloudfunctions.net/mikrokosmos/api/read/datetime/hh:</li>
   <li>Uses time variable from data</li>
 </ul>

</ul>
