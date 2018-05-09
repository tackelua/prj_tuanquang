//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "tuanquang-wifiapi.firebaseio.com"
#define FIREBASE_AUTH "33Hx0B3ywsAgHVoBT412VStfI9esAyn6ZA0cqBlB"
#define WIFI_SSID "Gith"
#define WIFI_PASSWORD "12345678()"


ESP8266WebServer server(80);

const int led = LED_BUILTIN;

void handleRoot() {
	digitalWrite(led, 1);
	FirebaseObject data = Firebase.get("/"); //đọc database
	if (Firebase.success()) { //nếu đọc thành công thì tách dữ liệu ra thành từng biến
		String acc = data.getString("acc");
		String num_done = data.getString("num_done");
		String num_xuly = data.getString("num_xuly");
		String phoi1 = data.getString("phoi1");
		String phoi2 = data.getString("phoi2");
		String phoi3 = data.getString("phoi3");
		String phoi4 = data.getString("phoi4");
		String phoi5 = data.getString("phoi5");
		String stt1 = data.getString("stt1");
		String stt2 = data.getString("stt2");
		String stt3 = data.getString("stt3");
		String stt4 = data.getString("stt4");
		String stt5 = data.getString("stt5");
		String note1 = data.getString("note1");
		String note2 = data.getString("note2");
		String note3 = data.getString("note3");
		String note4 = data.getString("note4");
		String note5 = data.getString("note5");

		//html là chuỗi của trang web hiển thị
		String html = F("<!DOCTYPE html><html><head><title>Title of the document</title><meta charset=\"utf-8\"/><style>#wrap{padding:40px;height:300px}.title{border:1px solid #000;display:inline-block;padding:10px 10px 40px 10px;color:#000;font-weight:bold}#content{margin-top:20px}#left{width:48%;float:left}#right{width:48%;float:right}#stoprobot{width:48%;float:left}#runrobot{width:48%;float:right}#right button{}</style></head><body><div id=\"wrap\"><div style=\"text-align:center;\"><div class=\"title\">Giám sát hoạt động của robot delta</div><div>Account đang đăng nhập: {acc}</div></div><div id=\"content\"><div id=\"left\"><table width=\"100%\" border=\"1\"><thead><tr><th>STT phôi</th><th>Mã phôi</th><th>Tình trạng</th><th>Ghi chú</th></tr></thead><tbody><tr><td>1</td><td>{phoi1}</td><td>{stt1}</td><td>{note1}</td></tr><tr><td>2</td><td>{phoi2}</td><td>{stt2}</td><td>{note2}</td></tr><tr><td>3</td><td>{phoi3}</td><td>{stt3}</td><td>{note3}</td></tr><tr><td>4</td><td>{phoi4}</td><td>{stt4}</td><td>{note4}</td></tr><tr><td>5</td><td>{phoi5}</td><td>{stt5}</td><td>{note5}</td></tr></tbody></table></div><div id=\"right\"><p>Phôi hiện đang xử lý: {num_xuly}</p><p>Số phôi đã xử lý: {num_done}</p><div id=\"stoprobot\"> <canvas id=\"stopcanvas\" width=\"200\" height=\"200\"></canvas> <button>Ngưng robot</button></div><div id=\"runrobot\"> <canvas id=\"runcanvas\" width=\"200\" height=\"200\"></canvas> <button>Chạy robot</button></div></div></div></div></body> <script type=\"text/javascript\">var canvas=document.getElementById('stopcanvas');var context=canvas.getContext('2d');var centerX=canvas.width/2;var centerY=canvas.height/2;var radius=70;context.beginPath();context.arc(centerX,centerY,radius,0,2*Math.PI,false);context.fillStyle='red';context.fill();context.lineWidth=5;context.strokeStyle='red';context.stroke();var canvas1=document.getElementById('runcanvas');var context1=canvas1.getContext('2d');var centerX1=canvas1.width/2;var centerY1=canvas1.height/2;var radius1=70;context1.beginPath();context1.arc(centerX,centerY,radius,0,2*Math.PI,false);context1.fillStyle='#5a9bd5';context1.fill();context1.lineWidth=5;context1.strokeStyle='#5a9bd5';context1.stroke();</script> </body></html> </script></html>");
		
		//thay thế data trong code html từ database lấy ở trên
		html.replace("{acc}", acc);
		html.replace("{num_done}", String(num_done));
		html.replace("{num_xuly}", String(num_xuly));
		html.replace("{phoi1}", phoi1);
		html.replace("{phoi2}", phoi2);
		html.replace("{phoi3}", phoi3);
		html.replace("{phoi4}", phoi4);
		html.replace("{phoi5}", phoi5);
		html.replace("{stt1}", stt1);
		html.replace("{stt2}", stt2);
		html.replace("{stt3}", stt3);
		html.replace("{stt4}", stt4);
		html.replace("{stt5}", stt5);
		html.replace("{note1}", note1);
		html.replace("{note2}", note2);
		html.replace("{note3}", note3);
		html.replace("{note4}", note4);
		html.replace("{note5}", note5);

		//gửi xuống client
		server.send(200, "text/html", html);
	}
	else {
		server.send(200, "text/plain", "Read database fail. Please try again");
	}
	digitalWrite(led, 0);
}

void handleNotFound() {
	digitalWrite(led, 1);
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i<server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
	digitalWrite(led, 0);
}

bool updateDatabase(String path, String data) {
	//path ở đây gồm
	//acc
	//num_done
	//num_xuly
	//phoi1 -> phoi5
	//stt1 -> stt5 (trạng thái)
	//note1 -> note5
	Serial.println("Save: " + path + " : " + data);
	Firebase.setString(path, data);
	return Firebase.success();
}


void setup() {
	Serial.begin(115200);

	// connect to wifi.
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	//WiFiManager wifiManager;
	//wifiManager.autoConnect("TUANQUANG");

	Serial.print("connecting");
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}
	Serial.println();
	Serial.print("connected: ");
	Serial.println(WiFi.localIP());

	Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}
	server.on("/", handleRoot);
	server.on("/inline", []() {
		server.send(200, "text/plain", "this works as well");
	});
	server.onNotFound(handleNotFound);
	server.begin();
}

int n = 0;

void loop() {
	server.handleClient();
}
