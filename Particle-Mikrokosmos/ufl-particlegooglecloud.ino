// This #include statement was automatically added by the Particle IDE.
#include <SparkFunCCS811.h>
#include <Wire.h>

// This #include statement was automatically added by the Particle IDE.
#include <spark-dallas-temperature.h>

// Humidity adn Temp
#include <Adafruit_DHT_Particle.h>
#include <MQTT.h>
#define DHTPIN 2 //Digital pin 2
#define DHTTYPE DHT22		// DHT 22

// light sensor
#define temt6000Pin A0

//PH sensor
#define sens161Pin A2//A1

//EC sensor
#define dfr0300Pin A1//A2

//soil moisture sensor
#define yl38Pin A3

// Temperature sensor
//#include <DS18B20.h>
#include <OneWire.h>

//Co2
#define CCS811_ADDR 0x5b


/****************
 *  Variables   *
*****************/
//for delay
unsigned long int start = 0;

//DHT22 (Temp & humidity)
DHT dht(DHTPIN, DHTTYPE);

//DS18B20 (Temp)
OneWire oneWire(D4);
DallasTemperature sensors(&oneWire);

//Co2
CCS811 myCCS811(CCS811_ADDR);

//Temperature and Humidity (DHT22)
int ID = 0; 
double h = 0;
double t = 0;
double dp =0; // Milloin muuttuu "vedeksi"

//Water and Air temperature (ds18b20)
double temperature=0.0; //tempW
double temperatureW=0.0; //tempW2

//Light (TEMT6000)
int lightvalue = 0.0;
double Lvolts= 0.0;
double Lamps =0.0;
double Lmicroamps= 0.0;
double lux=0.0;

//PH
double phValue=0.0;
double avgValuePH;
//PH Config(Done with avg values)
float ph7= 1629;
float ph4 = 1028;
float ph9 = 2040;
float multiplier7=7/ph7;
float cornerPlus4=(4-ph4*multiplier7)/3;
float cornerPlus9=(9.21-ph9*multiplier7)/2.2;

//EC
double ecValue=0.0;

//Soil moisture
double soilMoisture=0.0;

//Co2 & TVOC
double co2=0.0;
double tvoc=0.0;

//Time
String checkTime;
String checkDate;


//update Time and Date
void updateTime() {
    checkTime=Time.format(Time.local(), "%Y-%m-%d %H:%M:%S");
    checkDate=Time.format(Time.local(),"%Y-%m-%d %H:%M:%S");
}


/****************
 *  Callback    *
*****************/
void callback(char* topic, byte* payload, unsigned int length);

MQTT client("broker.hivemq.com", 1883, callback);

void callback(char* topic, byte* payload, unsigned int length) { }


/****************
 *    Setup     *
*****************/
//Only called once
void setup() {
    //Use external antenna
    STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));
    
    //TimeZone
    Time.zone(1.0);
    updateTime();
    
    //Start Co2 sensor
    Wire.begin();
    CCS811Core::CCS811_Status_e returnCode = myCCS811.beginWithStatus();
    sensors.begin();//For DS18B20
    
    //Particle Variables
    Particle.variable("temperature",temperature);
    Particle.variable("temperatureW",temperatureW);
    Particle.variable("temperatureDHT22",t);
    Particle.variable("humidity",h);
    Particle.variable("light",lux);
    Particle.variable("ph",phValue);
    Particle.variable("ec",ecValue);
    Particle.variable("co2",co2);
    Particle.variable("tvoc",tvoc);
    Particle.variable("time",checkTime);
    Particle.variable("date",checkDate);
    
    
    start = millis();
    client.connect("");
    Particle.publish("UrbanPhoton", "Minttu sanoo moi!");
    
      // Subscribe to the integration response event
    Particle.subscribe("hook-response/sensori-data", myHandler, MY_DEVICES);
    
    //wait for sensors to warm up
    delay(5000);
    updateSensorValues();
}


int i = 0;
void myHandler(const char *event, const char *data) {
  // Handle the integration response
    i++;
  Serial.print(i);
  Serial.print(event);
  Serial.print(", data: ");
  if (data)
    Serial.println(data);
  else
    Serial.println("NULL");
  
}

/****************
 * Publish Data *
*****************
This function is called in main and is used to publish data*/
void publishData(){
    
    char data[164];
    snprintf(data, sizeof(data), "{\"id\":1, \"h\":%.2f, \"temp\":%.2f, \"tempW\":%.2f, \"light\":%.0f, \"ph\":%.2f, \"ec\":%.3f, \"co2\":%.1f, \"tvoc\":%.2f, \"time\":\"%s\"}", h, temperature,temperatureW,lux,phValue,ecValue,co2,tvoc,(const char*)checkTime); // output: t: 12.34°C, h: 45.67%
    Particle.publish("mikrokosmos", data, PRIVATE);
    delay(100);
    client.publish("mikrokosmos-hive", data); //julkaisee datan HiveMq.com -palvelun kautta
        
}


/****************
 *  pH value    *
*****************
Hanna instruments & DFRobot*/
void checkPH(){
    	unsigned long int avgValue;  //Store the average value of ph sensor
        float b;
        int buf[10],temp;
	    
	    for(int i=0;i<10;i++)       //Get 10 sample value from the sensor
         { 
            buf[i]=analogRead(sens161Pin);
            delay(10);
          }
        for(int i=0;i<9;i++)        //sort values from small to large
          {
            for(int j=i+1;j<10;j++)
            {
                if(buf[i]>buf[j])
                  {
                    temp=buf[i];
                    buf[i]=buf[j];
                    buf[j]=temp;
                  }
            }
        }
          
        avgValue=0;
        for(int i=2;i<8;i++)      //take the average value of 6 center samples
            avgValue+=buf[i];
                
        phValue=(float)avgValue/6*multiplier7; //calculate average value from avgValue list and transform value to scale 1-14
        float checkRange = 7-phValue; // is used to check is value smaller or higher than 7
        if (checkRange>0){
              phValue=phValue+checkRange*cornerPlus4;
          }
        if(checkRange<0){
              phValue=phValue-checkRange*cornerPlus9;
          }
}

/****************
 *  EC value    *
*****************/
//DFR0300
void checkEC(){
    ecValue=analogRead(dfr0300Pin)*3300/4095.0;
    ecValue=ecValue/1000.0;
}

/****************************
 * Temperature and Humidity *
*****************************/
//DHT22
void tempAndHum(){
     //Temperature & humidity
    ID = 0; 
    h = dht.getHumidity();
    t = dht.getTempCelcius();
    delay(50);
}

void light(){
	lightvalue = analogRead(temt6000Pin);
    Lvolts= lightvalue* 3.3/4095.0; // 4095, Koska photon 3.3V 12 bittiä. 5V = 1023
    Lamps = Lvolts /10000.0;
    Lmicroamps= Lamps * 1000000.0;
    lux=Lmicroamps*2.0;
    
    if(lux<=39){
        lux=0;
    }else{
        lux=1;
    }
}

/****************
 *Water and temp*
*****************/
//DS18B20
void waterAndAirTemp(){
	sensors.requestTemperatures();
    temperature=sensors.getTempCByIndex(0);
    temperatureW=sensors.getTempCByIndex(1)+0.5;//compensate +0.5 error in temperature sensor(Air sensor)
}

/****************
 * Co2 and TVOC *
*****************/
//CCS811
void co2AndTvoc(){
    myCCS811.setEnvironmentalData(h,t);
    myCCS811.readAlgorithmResults();
    
    co2=myCCS811.getCO2();
    tvoc=myCCS811.getTVOC();
}

/****************
 *    Loop      *
*****************/
//Update sensor values to variables
void updateSensorValues(){
    
        //Update time
        updateTime();
        
        //Temperature and humidity from dht22
        tempAndHum();
	    
	    //Light
        light();
	    
	    //Water temperatures
        waterAndAirTemp();
	    
	    //PH
        checkPH();
	    
        //Electronic Conductivity
        checkEC();
        
        //Soil Moisture
        soilMoisture=((analogRead(yl38Pin)/4095.0));
        
        //Co2
        co2AndTvoc();
}


/****************
 *  MAIN LOOP   *
*****************/
//Main Loop
void loop() {
    
    if (client.isConnected()) client.loop();
    
    int delay_ = 1800000;//30min // 1800000
    
    if(millis() - start > delay_) {
        
        updateSensorValues();
        publishData();
        start = millis();
        
    }else{
        updateSensorValues();
    };
        
}