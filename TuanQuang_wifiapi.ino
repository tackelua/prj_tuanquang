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

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define _VERSION_ "v0.2"

// Set these to run example.
#define FIREBASE_HOST "tuanquang-wifiapi.firebaseio.com"
#define FIREBASE_AUTH "33Hx0B3ywsAgHVoBT412VStfI9esAyn6ZA0cqBlB"
#define WIFI_SSID "IoT Wifi"
#define WIFI_PASSWORD "mic@dtu12345678()"


ESP8266WebServer server(80);

const int led = LED_BUILTIN;

void handleRoot() {
	Serial.println("/");
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
		String html = F("<!DOCTYPE html><html><head> <title>Title of the document</title> <meta charset=\"utf-8\"/> <style>#wrap{padding: 40px; height: 300px;}.title{border: 1px solid #000; display: inline-block; padding: 10px 10px 40px 10px; color: #000; font-weight: bold;}#content{margin-top: 20px;}#left{width: 48%; float: left;}#right{width: 48%; float: right;}#stoprobot{width: 48%; float: left;}#runrobot{width: 48%; float: right;}#right button{}</style></head><body> <div id=\"wrap\"> <div style=\"text-align:center;\"> <div class=\"title\">Giám sát hoạt động của robot delta</div><div>Account đang đăng nhập: <spand id=\"acc\">{acc}</span> </div></div><div id=\"content\"> <div id=\"left\"> <table width=\"100%\" border=\"1\"> <thead> <tr> <th>STT phôi</th> <th>Mã phôi</th> <th>Tình trạng</th> <th>Ghi chú</th> </tr></thead> <tbody> <tr> <td>1</td><td id=\"phoi1\">{phoi1}</td><td id=\"stt1\">{stt1}</td><td id=\"note1\">{note1}</td></tr><tr> <td>2</td><td id=\"phoi2\">{phoi2}</td><td id=\"stt2\">{stt2}</td><td id=\"note2\">{note2}</td></tr><tr> <td>3</td><td id=\"phoi3\">{phoi3}</td><td id=\"stt3\">{stt3}</td><td id=\"note3\">{note3}</td></tr><tr> <td>4</td><td id=\"phoi4\">{phoi4}</td><td id=\"stt4\">{stt4}</td><td id=\"note4\">{note4}</td></tr><tr> <td>5</td><td id=\"phoi5\">{phoi5}</td><td id=\"stt5\">{stt5}</td><td id=\"note5\">{note5}</td></tr></tbody> </table> </div><div id=\"right\"> <p>Phôi hiện đang xử lý: <span id=\"num_xuly\">{num_xuly}</span></p><p>Số phôi đã xử lý: <span id=\"num_done\">{num_done}</span></p><div id=\"stoprobot\"> <canvas id=\"stopcanvas\" width=\"200\" height=\"200\"></canvas> <button>Ngưng robot</button> </div><div id=\"runrobot\"> <canvas id=\"runcanvas\" width=\"200\" height=\"200\"></canvas> <button>Chạy robot</button> </div></div></div></div></body><script type=\"text/javascript\">var canvas=document.getElementById('stopcanvas'); var context=canvas.getContext('2d'); var centerX=canvas.width / 2; var centerY=canvas.height / 2; var radius=70; context.beginPath(); context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false); context.fillStyle='red'; context.fill(); context.lineWidth=5; context.strokeStyle='red'; context.stroke(); var canvas1=document.getElementById('runcanvas'); var context1=canvas1.getContext('2d'); var centerX1=canvas1.width / 2; var centerY1=canvas1.height / 2; var radius1=70; context1.beginPath(); context1.arc(centerX, centerY, radius, 0, 2 * Math.PI, false); context1.fillStyle='#5a9bd5'; context1.fill(); context1.lineWidth=5; context1.strokeStyle='#5a9bd5'; context1.stroke(); setInterval(function(){updateData();}, 1000); function updateData(){var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){var obj=JSON.parse(this.responseText); document.getElementById(\"acc\").innerHTML=obj.acc; document.getElementById(\"num_done\").innerHTML=obj.num_done; document.getElementById(\"num_xuly\").innerHTML=obj.num_xuly; document.getElementById(\"phoi1\").innerHTML=obj.phoi1; document.getElementById(\"phoi2\").innerHTML=obj.phoi2; document.getElementById(\"phoi3\").innerHTML=obj.phoi3; document.getElementById(\"phoi4\").innerHTML=obj.phoi4; document.getElementById(\"phoi5\").innerHTML=obj.phoi5; document.getElementById(\"stt1\").innerHTML=obj.stt1; document.getElementById(\"stt2\").innerHTML=obj.stt2; document.getElementById(\"stt3\").innerHTML=obj.stt3; document.getElementById(\"stt4\").innerHTML=obj.stt4; document.getElementById(\"stt5\").innerHTML=obj.stt5; document.getElementById(\"note1\").innerHTML=obj.note1; document.getElementById(\"note2\").innerHTML=obj.note2; document.getElementById(\"note3\").innerHTML=obj.note3; document.getElementById(\"note4\").innerHTML=obj.note4; document.getElementById(\"note5\").innerHTML=obj.note5;}}; xhttp.open(\"GET\", \"/apidata\", true); xhttp.send();}</script></html>");
		
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

void handleGetDataApi() {
	Serial.println("/apidata");
	digitalWrite(led, 1);
	FirebaseObject data = Firebase.get("/"); //đọc database
	if (Firebase.success()) { //nếu đọc thành công thì tách dữ liệu ra thành từng biến
		StaticJsonBuffer<500> jsBuffer;
		JsonObject& jsData = jsBuffer.createObject();

		jsData["acc"] = data.getString("acc");
		jsData["num_done"] = data.getString("num_done");
		jsData["num_xuly"] = data.getString("num_xuly");
		jsData["phoi1"] = data.getString("phoi1");
		jsData["phoi2"] = data.getString("phoi2");
		jsData["phoi3"] = data.getString("phoi3");
		jsData["phoi4"] = data.getString("phoi4");
		jsData["phoi5"] = data.getString("phoi5");
		jsData["stt1"] = data.getString("stt1");
		jsData["stt2"] = data.getString("stt2");
		jsData["stt3"] = data.getString("stt3");
		jsData["stt4"] = data.getString("stt4");
		jsData["stt5"] = data.getString("stt5");
		jsData["note1"] = data.getString("note1");
		jsData["note2"] = data.getString("note2");
		jsData["note3"] = data.getString("note3");
		jsData["note4"] = data.getString("note4");
		jsData["note5"] = data.getString("note5");

		String jsDataStr;
		jsData.printTo(jsDataStr);
		//Serial.println(jsDataStr);
		//gửi xuống client
		server.send(200, "text/plain", jsDataStr);
	}
	else {
		server.send(404, "text/plain", "{}");
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
	Serial.println("Version: " _VERSION_);
	// connect to wifi.
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	//WiFiManager wifiManager;
	//wifiManager.autoConnect("TUANQUANG");
	WiFi.printDiag(Serial);
	Serial.print("connecting");
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}
	Serial.println();
	Serial.print("connected: ");
	Serial.println(WiFi.localIP());

	Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

	//if (MDNS.begin("esp8266")) {
	//	Serial.println("MDNS responder started");
	//}
	server.on("/", handleRoot);
	server.on("/apidata", handleGetDataApi);
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
