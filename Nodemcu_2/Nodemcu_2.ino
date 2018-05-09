

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <FirebaseArduino.h>


//define cho firebase
#define FIREBASE_AUTH ""
#define FIREBASE_HOST "rfid-a1290.firebaseio.com"//Thay bằng địa chỉ firebase của bạn

const char* ssid = "Tuan";
const char* password = "1a2b3c4d";
//const char* ssid = "Zest Cafe";
//const char* password = "sodatuoi";
WiFiServer server(80);

String receive_data = "";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s \n", ssid);
  SPI.begin();      // Initiate  SPI bus
  WiFi.begin(ssid, password);
  // WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  server.begin();
}

void docdulieu()
{
  for (int i; i <= 4; i++) {
    if (Firebase.getString("msg" + String(i)) != "")
    {
      // Firebase.remove("phoi1");
      // Firebase.setFloat("phoi1",0);
      receive_data = Firebase.getString("msg" + String(i));
      Firebase.remove("msg" + String(i));
      if (receive_data != "")
      {
        Serial.println(receive_data);
        delay(100);
        receive_data = "";
      }
      if (Firebase.failed()) {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        return;
      }
    }
  }
}

void hienthiweb()
{
      client.println("<!DOCTYPE html><html>");
         client.println(" <head>
  <title>Title of the document</title>
  <meta charset="utf-8"/>
  <style>
  
    #wrap{
      padding:40px;
      
      height:300px;
    }
    .title{
      border:1px solid #000;
      display:inline-block;
      padding:10px 10px 40px 10px;
      color:#000;
      font-weight: bold;
    }

    #content{
      margin-top:20px;
    }
    #left{
      
      width:48%;
      
      
      float:left;
    }
    
    #right{
      
      width:48%;
      
      
      float:right;
    }
    #stoprobot{     
      width:48%;            
      float:left;
    }
    #runrobot{        
      width:48%;            
      float:right;
    }
    #right button{
      
    }
  </style>
  
</head>

<body>
  <div id="wrap">
  
    <div style="text-align:center;">
      <div class="title">Giám sát hoạt động của robot delta</div>
      <div>
      Account đang đăng  nhập:
      </div>
      
    </div>
    <div id="content">
      <div id="left">
        <table width="100%" border="1">
          <thead>
            <tr>
              <th>
                STT phôi
              </th>
              <th>
                Mã phôi
              </th>
              <th>
                Vị trí đặt
              </th>
              <th>
                Chú thích
              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
              </th>
            </tr>
          </thead>
          <tbody>
            <tr>
              <td>
                1
              </td>
              <td>
                
              </td>
              <td>
              </td>
              <td>
              </td>
            </tr>
            <tr>
              <td>
                2
              </td>
              <td>
              </td>
              <td>
              </td>
              <td>
              </td>
            </tr>
            <tr>
              <td>
                3
              </td>
              <td>
              </td>
              <td>
              </td>
              <td>
              </td>
            </tr>
            <tr>
              <td>
                4
              </td>
              <td>
              </td>
              <td>
              </td>
              <td>
              </td>
            </tr>
            <tr>
              <td>
                5
              </td>
              <td>
              </td>
              <td>
              </td>
              <td>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
      <div id="right">
        <p>
        Phôi hiện đang xử lý:
        </p>
        <p>
        Số phôi đã xử lý:
        </p>
        <div id="stoprobot">
          <canvas id="stopcanvas" width="200" height="200"></canvas>
          <button>Ngưng robot</button>
        </div>
        <div id="runrobot">
          <canvas id="runcanvas" width="200" height="200"></canvas>
          <button>Chạy robot</button>
        </div>
        
      </div>    
    </div>    
    
    
  </div>
</body>
<script type="text/javascript">
    var canvas = document.getElementById('stopcanvas');
      var context = canvas.getContext('2d');
      var centerX = canvas.width / 2;
      var centerY = canvas.height / 2;
      var radius = 70;

      context.beginPath();
      context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);
      context.fillStyle = 'red';
      context.fill();
      context.lineWidth = 5;
      context.strokeStyle = 'red';
      context.stroke();
    
    var canvas1 = document.getElementById('runcanvas');
      var context1 = canvas1.getContext('2d');
      var centerX1 = canvas1.width / 2;
      var centerY1 = canvas1.height / 2;
      var radius1 = 70;

      context1.beginPath();
      context1.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);
      context1.fillStyle = '#5a9bd5';
      context1.fill();
      context1.lineWidth = 5;
      context1.strokeStyle = '#5a9bd5';
      context1.stroke();
    
    </script>
  </body>
</html>      
</script>
</html> ")

  }

void loop() {
  // put your main code here, to run repeatedly:
  docdulieu();
  hienthiweb();
  
}
