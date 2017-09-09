//static const uint8_t D0   = 16;            // to translate the gipo pins to the bord pins
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4; // D2
//static const uint8_t strobe   = 0;  //D3
//static const uint8_t res   = 2;  //D4
static const uint8_t strobe   = 14; //D5
static const uint8_t res   = 12;  //D6
//static const uint8_t D7   = 13; // ledstrip
//static const uint8_t D8   = 15; // D8
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;
/*
  for all extra help....
  https://github.com/Links2004/arduinoWebSockets 
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>


#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <ESP8266WebServer.h>
IPAddress    apIP(192, 168, 2, 200);         // Private network address: local & gateway

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);




Adafruit_SSD1306 display;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, D7, NEO_GRB + NEO_KHZ800); //gpio 13

String lastCommandLed = ""; // commands used to give a new client the latest data
String lastCommandText = "";
String lastCommandColor1 = "";
String lastCommandColor2 = "";
String lastCommandColor3 = "";
String lastCommandSensitivity = "";
String lastCommandLedMode = "";
String lastCommandBackMode = "";

boolean ledOnOff = false;  //determines if the device is on or off (void loop)
int color1[] = {0, 0, 0};
int color2[] = {0, 0, 0};
int color3[] = {0, 0, 0};
int colorMatrix[24][5][3];
int sensitivity = 250;
String ledMode = "Single-Color";
String backMode = "Ambient-light";

int sound[5];                               //global used vatiable which stores the latest sounds (already filtered)
int soundFilter[5] = {45, 80, 65, 55, 70};    //the soundChip is not very accurate, these are the values to filter the input

int tcounter = 0; //3 variables to determine if the incoming sound is trash(idle),,, or if there is actual music
int gcounter = 0;
int thrashold = 5;  //the sum of all sound[] variables should not exeed this value

void loop()
{

  webSocket.loop();
  server.handleClient();

  if (ledOnOff == true) {  //will only be executed when clients are on the ESP (at least thats is what is supposed to be)
    
    readMSGEQ7();
    printMSGEQ7();
    setLedStrip();
    strip.show();
    

    
  }

}






static const char PROGMEM INDEX_HTML[] = R"rawliteral(  // all HTML, CSS and JAVASCRIPT. (dont bother to look... it's a big mess)
<!DOCTYPE html>
<html>
<head>
    <meta name = "viewport" content = "width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
    <title>ESP8266 WebSocket Demo</title>
    <style>
        .box {
            margin: 20px;
            border: 1px solid rgba(0, 0, 0, .2);
            background-color: white;
            display: inline-block;
        }
    </style>
    <script>
        var websock;
        function start() {
            websock = new WebSocket('ws://' + window.location.hostname + ':81/');
            websock.onopen = function (evt) {
                console.log('websock open');
                fillBoxColor1();
                fillBoxColor2();
                fillBoxColor3();
            };
            websock.onclose = function (evt) {
                console.log('websock close');
            };
            websock.onerror = function (evt) {
                console.log(evt);
            };





            websock.onmessage = function(evt) {
                console.log(evt);
                var inp = evt.data;
                var command = inp.substring(0,inp.indexOf(":"));
                var data = inp.substring(inp.indexOf(":")+1,inp.length);
                var e = document.getElementById('ledstatus');
                var t = document.getElementById('test');
                t.innerHTML = command + ":  " + data;




                if(command == "powerOnOff"){
                    if (data == "ledon") {
                        e.style.color = 'red';
                        e.innerHTML = "the ledstrip is on!";
                        document.body.style.backgroundColor = "green";
                    }
                    else if (data == "ledoff") {
                        e.style.color = 'black';
                        e.innerHTML = "the ledstrip is off!";
                        document.body.style.backgroundColor = "#adff2f";
                    }
                } else if(command == "text"){
                    document.getElementById('firstname').value = data;
                } else if(command == "color1"){
                    var redValue = data.substring(data.indexOf("R")+1,data.indexOf("G"));
                    var greenValue = data.substring(data.indexOf("G")+1,data.indexOf("B"));
                    var blueValue = data.substring(data.indexOf("B")+1,data.length);
                    document.getElementById('rangeRcolor1').value = redValue;
                    document.getElementById('rangeGcolor1').value = greenValue;
                    document.getElementById('rangeBcolor1').value = blueValue;
                    fillBoxColor1();
                } else if(command == "color2"){
                    var redValue = data.substring(data.indexOf("R")+1,data.indexOf("G"));
                    var greenValue = data.substring(data.indexOf("G")+1,data.indexOf("B"));
                    var blueValue = data.substring(data.indexOf("B")+1,data.length);
                    document.getElementById('rangeRcolor2').value = redValue;
                    document.getElementById('rangeGcolor2').value = greenValue;
                    document.getElementById('rangeBcolor2').value = blueValue;
                    fillBoxColor2();
                } else if(command == "color3"){
                    var redValue = data.substring(data.indexOf("R")+1,data.indexOf("G"));
                    var greenValue = data.substring(data.indexOf("G")+1,data.indexOf("B"));
                    var blueValue = data.substring(data.indexOf("B")+1,data.length);
                    document.getElementById('rangeRcolor3').value = redValue;
                    document.getElementById('rangeGcolor3').value = greenValue;
                    document.getElementById('rangeBcolor3').value = blueValue;
                    fillBoxColor3();
                }else if(command == "sensitivity"){
                    document.getElementById('rangeSensitivity').value = data;
                } else if(command == "ledMode"){
                    document.getElementById('ledModeMenu').value = data;
                } else if(command == "backMode"){
                    document.getElementById('backModeMenu').value = data;
                }
                else {
                    console.log('unknown event');
                    t.innerHTML = "unknown command  -> " + inp;
                }
            };


        }


        function buttonclick(e) {
            websock.send("powerOnOff:"+e.id);
        }
        function textclick(e) {
            var r = "text:";
            r += document.getElementById("firstname").value;

            if(r.length >1){
                websock.send(r);
            } else {
                websock.send("user has no data");
            }
        }
        function changeRGBcolor1(e) {
            var result = "color1:"
            result += "R";
            result += document.getElementById("rangeRcolor1").value;
            result += "G";
            result += document.getElementById("rangeGcolor1").value;
            result += "B";
            result += document.getElementById("rangeBcolor1").value;
            websock.send(result);
        }
        function changeRGBcolor2(e) {
            var result = "color2:"
            result += "R";
            result += document.getElementById("rangeRcolor2").value;
            result += "G";
            result += document.getElementById("rangeGcolor2").value;
            result += "B";
            result += document.getElementById("rangeBcolor2").value;
            websock.send(result);
        }
        function changeRGBcolor3(e) {
            var result = "color3:"
            result += "R";
            result += document.getElementById("rangeRcolor3").value;
            result += "G";
            result += document.getElementById("rangeGcolor3").value;
            result += "B";
            result += document.getElementById("rangeBcolor3").value;
            websock.send(result);
        }
        function fillBoxColor1() {
            var box = document.getElementById("colorBox1");
            var R = document.getElementById("rangeRcolor1").value;
            var G = document.getElementById("rangeGcolor1").value;
            var B = document.getElementById("rangeBcolor1").value;
            box.style.backgroundColor = 'rgb(' + R + ',' + G + ',' + B + ')';
        }
        function fillBoxColor2() {
            var box = document.getElementById("colorBox2");
            var R = document.getElementById("rangeRcolor2").value;
            var G = document.getElementById("rangeGcolor2").value;
            var B = document.getElementById("rangeBcolor2").value;
            box.style.backgroundColor = 'rgb(' + R + ',' + G + ',' + B + ')';
        }
        function fillBoxColor3() {
            var box = document.getElementById("colorBox3");
            var R = document.getElementById("rangeRcolor3").value;
            var G = document.getElementById("rangeGcolor3").value;
            var B = document.getElementById("rangeBcolor3").value;
            box.style.backgroundColor = 'rgb(' + R + ',' + G + ',' + B + ')';
        }
        function changeSensitivity() {
            var result = "sensitivity:";
            result += document.getElementById("rangeSensitivity").value;
            websock.send(result);
        }
        function changeLedMode() {
            var result = "ledMode:";
            result += document.getElementById("ledModeMenu").value;
            websock.send(result);
        }
        function changeBackMode() {
            var result = "backMode:";
            result += document.getElementById("backModeMenu").value;
            websock.send(result);
        }



    </script>



</head>
<body onload="javascript:start();" bgcolor="#adff2f">

<div align="center" STYLE="background-color: #d0fbce; width: 800px; margin:0 auto;">

    <h1>ESP8266 Sound visualiser control panel</h1>
    <div id="ledstatus"><b>Device is in default state</b></div>


    select on/off to toggle the sound visualiser <br>
    <button id="ledon"  type="button" onclick="buttonclick(this);">On</button>
    <button id="ledoff" type="button" onclick="buttonclick(this);">Off</button><br><br>

    select the desired mode of the analiser<br>
    <select id="ledModeMenu" size="1" onChange="changeLedMode()">
        <option>Single-Color</option>
        <option>Standard</option>
        <option>Dual-Color</option>
        <option>Drop</option>
        <option>One-Line</option>
    </select> <br><br><br>




    this panel will allow you to set the first and second color of the analiser <br>
    <div class = "box" id = "colorBox1">
        <div class = "box">
            R: <input type="range" min="0" max="255" id="rangeRcolor1" value="0" onChange ="changeRGBcolor1()" oninput ="fillBoxColor1()"><br>
            G:  <input type="range" min="0" max="255" id="rangeGcolor1" value="0" onChange ="changeRGBcolor1()" oninput ="fillBoxColor1()"><br>
            B: <input type="range" min="0" max="255" id="rangeBcolor1" value="0" onChange ="changeRGBcolor1()" oninput ="fillBoxColor1()">
        </div>
    </div>


    <div class = "box" id = "colorBox2">
        <div class = "box">
            R: <input type="range" min="0" max="255" id="rangeRcolor2" value="0" onChange ="changeRGBcolor2()" oninput ="fillBoxColor2()"><br>
            G:  <input type="range" min="0" max="255" id="rangeGcolor2" value="0" onChange ="changeRGBcolor2()" oninput ="fillBoxColor2()"><br>
            B: <input type="range" min="0" max="255" id="rangeBcolor2" value="0" onChange ="changeRGBcolor2()" oninput ="fillBoxColor2()">
        </div>
    </div>
    <br>
    Sensitivity: <input type="range" min="0" max="1024" id="rangeSensitivity" value="250" onChange ="changeSensitivity()"> <br>
    <a href = '/hackerman'><Button>HACKBUTTON</Button></a> <br>
    <input type="text" id="firstname" onchange="textclick(this);"> <br><br><br>

    v<div class = "box" id = "colorBox3">
        <div class = "box">
            R: <input type="range" min="0" max="255" id="rangeRcolor3" value="0" onChange ="changeRGBcolor3()" oninput ="fillBoxColor3()"><br>
            G:  <input type="range" min="0" max="255" id="rangeGcolor3" value="0" onChange ="changeRGBcolor3()" oninput ="fillBoxColor3()"><br>
            B: <input type="range" min="0" max="255" id="rangeBcolor3" value="0" onChange ="changeRGBcolor3()" oninput ="fillBoxColor3()">
        </div>
    </div>
    <br>
    select the desired mode of the backlight<br>
    <select id="backModeMenu" size="1" onChange="changeBackMode()">
        <option>Ambient-light</option>
        <option>Bass</option>
        <option>Volume</option>
    </select> <br><br><br>
    <div id="test"><b>debugging area</b></div>

</div>
</body>
</html>



)rawliteral";
