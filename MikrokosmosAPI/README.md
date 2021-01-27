# Mikrokosmos-API
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
   <li>https://us-central1-amiable-hydra-279814.cloudfunctions.net/mikrokosmos/api/read/WRITEIDHERE</li>
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
