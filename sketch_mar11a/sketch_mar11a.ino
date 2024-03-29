[28/05/2023 16:43:29] Đinh Tuấn Anh: #include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "html.h"
ESP8266WebServer webServer(80);
const char* ssid = "DTA";
const char* pass = "88888888";

void ketnoi()
{
  String s = MainPage;
  webServer.send(200,"text/html",s);
}

void nhandulieu()
{
if (Serial.available()) {
    String receivedString;
    char receivedChar = Serial.read();
    while (receivedChar != '\n' && receivedChar != '\r') {
      receivedString += receivedChar;
      receivedChar = Serial.read();
    }
    Serial.println(receivedString);
    webServer.send(200,"text/plain",receivedString);
 }
}
const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="UTF-8">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
      max-width: 800px;
      height: 400px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
      color: palevioletred;
    }
  </style>
</head>
<body>
  <h2>Đồ thị giám sát tốc độ động cơ</h2>
  <div id="chart-temperature" class="container"></div>
  <div id="chart-humidity" class="container"></div>
</body>
<script>
var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-temperature' },
  title: { text: 'Đồ thị nhiệt độ' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Độ C' }
    //title: { text: 'Temperature (Fahrenheit)' }
  },
  credits: { enabled: false }
});
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var x = (new Date()).getTime(),
          y = parseFloat(this.responseText);
      //console.log(this.responseText);
      if(chartT.series[0].data.length > 40) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", "/doctocdo", true);
  xhttp.send();
}, 1000 ) ;

var chartH = new Highcharts.Chart({
  chart:{ renderTo:'chart-humidity' },
  title: { text: 'Đồ thị độ ẩm' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    }
  },
  xAxis: {
    type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: ' (%)' }
  },
  credits: { enabled: false }
});
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var x = (new Date()).getTime(),
[28/05/2023 16:47:16] Đinh Tuấn Anh: #include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "html.h"
ESP8266WebServer webServer(80);
const char* ssid = "DTA";
const char* pass = "88888888";

void ketnoi()
{
  String s = MainPage;
  webServer.send(200,"text/html",s);
}

void nhandulieu()
{
if (Serial.available()) {
    String receivedString;
    char receivedChar = Serial.read();
    while (receivedChar != '\n' && receivedChar != '\r') {
      receivedString += receivedChar;
      receivedChar = Serial.read();
    }
    Serial.println(receivedString);
    webServer.send(200,"text/plain",receivedString);
 }
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
WiFi.begin(ssid,pass);
Serial.print("Dang ket nôi ");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".....");
  }
  Serial.println(WiFi.localIP());
webServer.on("/",ketnoi);
webServer.on("/doctocdo",nhandulieu);
webServer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
webServer.handleClient();
}
[28/05/2023 16:47:33] Đinh Tuấn Anh: const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="UTF-8">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
      max-width: 800px;
      height: 400px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
      color: palevioletred;
    }
  </style>
</head>
<body>
  <h2>Đồ thị giám sát tốc độ động cơ</h2>
  <div id="chart-temperature" class="container"></div>
  <div id="chart-humidity" class="container"></div>
</body>
<script>
var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-temperature' },
  title: { text: 'Đồ thị nhiệt độ' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Độ C' }
    //title: { text: 'Temperature (Fahrenheit)' }
  },
  credits: { enabled: false }
});
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var x = (new Date()).getTime(),
          y = parseFloat(this.responseText);
      //console.log(this.responseText);
      if(chartT.series[0].data.length > 40) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", "/doctocdo", true);
  xhttp.send();
}, 1000 ) ;

var chartH = new Highcharts.Chart({
  chart:{ renderTo:'chart-humidity' },
  title: { text: 'Đồ thị độ ẩm' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    }
  },
  xAxis: {
    type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: ' (%)' }
  },
  credits: { enabled: false }
});
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var x = (new Date()).getTime(),
          y = parseFloat(this.responseText);
      //console.log(this.responseText);
      if(chartH.series[0].data.length > 40) {
        chartH.series[0].addPoint([x, y], true, true, true);
      } else {
        chartH.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", "/docdoam", true);
  xhttp.send();
}, 1000 ) ;

</script>
</html>
)=====";