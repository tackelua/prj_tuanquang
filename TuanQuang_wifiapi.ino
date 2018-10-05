#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define _VERSION_ "v0.4"

// Set these to run example.
#define FIREBASE_HOST "tuanquang-wifiapi.firebaseio.com"
#define FIREBASE_AUTH "33Hx0B3ywsAgHVoBT412VStfI9esAyn6ZA0cqBlB"

/*
 * MUSH READ
 * Need change "FirebaseObject.h" 
 * #define FIREBASE_JSONBUFFER_SIZE JSON_OBJECT_SIZE(32)
 * to
 * #define FIREBASE_JSONBUFFER_SIZE JSON_OBJECT_SIZE(35)
 */

ESP8266WebServer server(80);

const int led = LED_BUILTIN;

const char text_html[] PROGMEM = "text/html";
const char HTML_WEBPAGE_PROGMEM[] PROGMEM = "<!DOCTYPE html><html><head> <title>Title of the document</title> <meta charset=\"utf-8\"/> <style>#wrap{max-width: 1080px; padding: 40px; height: 300px; margin: 0 auto;}.title{border: 1px solid #000; display: inline-block; padding: 10px 10px 40px 10px; color: #000; font-weight: bold;}.title-right-parent{text-align: center;}.title-right{border: 1px solid #000; display: inline-block; padding: 10px; color: #000; font-weight: bold;}#content{margin-top: 20px;}#left{width: 48%; float: left;}#right{width: 48%; float: right;}#right button{}table{border-collapse: collapse;text-align: center;}table,th,td{border: 1px solid black; padding: 4px; height: 20px;}table td{}.create-cirle{width: 60px; height: 60px; background: red; -moz-border-radius: 50px; -webkit-border-radius: 50px; border-radius: 50%; /*display: inline-block;*/}.button-control{cursor: pointer; margin-top: 8px; width: 100px; padding: 4px; border: 1px solid black; background: transparent;}</style></head><body> <div id=\"wrap\"> <div style=\"text-align:center;\"> <div class=\"title\">Giám sát hoạt động của robot delta</div><div style=\"text-align: right;\">Account đang đăng nhập: <spand id=\"acc\"></span> </div></div><div id=\"content\"> <div id=\"left\"> <table width=\"100%\"> <thead> <tr> <th>STT phôi</th> <th>Mã phôi</th> <th>Tình trạng</th> <th>Ghi chú</th> </tr></thead> <tbody> <tr> <td>1</td><td id=\"phoi1\"></td><td id=\"stt1\"></td><td id=\"note1\"></td></tr><tr> <td>2</td><td id=\"phoi2\"></td><td id=\"stt2\"></td><td id=\"note2\"></td></tr><tr> <td>3</td><td id=\"phoi3\"></td><td id=\"stt3\"></td><td id=\"note3\"></td></tr><tr> <td>4</td><td id=\"phoi4\"></td><td id=\"stt4\"></td><td id=\"note4\"></td></tr><tr> <td>5</td><td id=\"phoi5\"></td><td id=\"stt5\"></td><td id=\"note5\"></td></tr><tr> <td>6</td><td id=\"phoi6\"></td><td id=\"stt6\"></td><td id=\"note6\"></td></tr><tr> <td>7</td><td id=\"phoi7\"></td><td id=\"stt7\"></td><td id=\"note7\"></td></tr><tr> <td>8</td><td id=\"phoi8\"></td><td id=\"stt8\"></td><td id=\"note8\"></td></tr></tbody> </table> </div><div id=\"right\"> <div class=\"title-right-parent\"> <div class=\"title-right\">Vị trí robot</div></div><table style=\"margin-top: 12px;\" width=\"100%\"> <thead> <tr> <th>X</th> <th>Y</th> <th>Z</th> </tr></thead> <tbody> <tr> <td id=\"rb_x\"></td><td id=\"rb_y\"></td><td id=\"rb_z\"></td></tr></tbody> </table> <div style=\"margin-top: 12px;\" class=\"title-right-parent\"> <div class=\"title-right\">Vị trí Động Cơ</div></div><table style=\"margin-top: 12px;\" width=\"100%\"> <thead> <tr> <th>1</th> <th>2</th> <th>3</th> </tr></thead> <tbody> <tr> <td id=\"dc1\"></td><td id=\"dc2\"></td><td id=\"dc3\"></td></tr></tbody> </table> <div> <div style=\"margin-top: 8px; min-width: 240px;\" class=\"title-right\"> Phôi hiện đang xử lý: <span id=\"num_xuly\"></span> </div></div><div> <div style=\"margin-top: 8px; min-width: 240px;\" class=\"title-right\"> Số phôi đã xử lý: <span id=\"num_done\"></span> </div></div><div style=\"margin-top: 12px;\"> <div style=\"float: right; margin-left: 12px;\"> <div style=\"background: #5a9bd5;margin-left: 20px;\" class=\"create-cirle\"> </div><button id=\"runrobot\" class=\"button-control\" onclick=\"robotrun()\">Chạy robot</button> </div><div style=\"float: right;\"> <div style=\"background: red; margin-left: 20px;\" class=\"create-cirle\"> </div><button id=\"stoprobot\" class=\"button-control\" onclick=\"robotstop()\">Ngưng robot</button> </div></div></div><div style=\"clear: both;padding-top: 20px;\"> <div style=\"border: 1px solid green; height: 200px;text-align: center;\"> Camera </div></div></div></div></div></body><script type=\"text/javascript\">setInterval(function(){updateData();}, 3000); function updateData(){var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){var obj=JSON.parse(this.responseText); document.getElementById(\"acc\").innerHTML=obj.acc; document.getElementById(\"num_done\").innerHTML=obj.num_done; document.getElementById(\"num_xuly\").innerHTML=obj.num_xuly; document.getElementById(\"phoi1\").innerHTML=obj.phoi1; document.getElementById(\"phoi2\").innerHTML=obj.phoi2; document.getElementById(\"phoi3\").innerHTML=obj.phoi3; document.getElementById(\"phoi4\").innerHTML=obj.phoi4; document.getElementById(\"phoi5\").innerHTML=obj.phoi5; document.getElementById(\"phoi6\").innerHTML=obj.phoi6; document.getElementById(\"phoi7\").innerHTML=obj.phoi7; document.getElementById(\"phoi8\").innerHTML=obj.phoi8; document.getElementById(\"stt1\").innerHTML=obj.stt1; document.getElementById(\"stt2\").innerHTML=obj.stt2; document.getElementById(\"stt3\").innerHTML=obj.stt3; document.getElementById(\"stt4\").innerHTML=obj.stt4; document.getElementById(\"stt5\").innerHTML=obj.stt5; document.getElementById(\"stt6\").innerHTML=obj.stt6; document.getElementById(\"stt7\").innerHTML=obj.stt7; document.getElementById(\"stt8\").innerHTML=obj.stt8; document.getElementById(\"note1\").innerHTML=obj.note1; document.getElementById(\"note2\").innerHTML=obj.note2; document.getElementById(\"note3\").innerHTML=obj.note3; document.getElementById(\"note4\").innerHTML=obj.note4; document.getElementById(\"note5\").innerHTML=obj.note5; document.getElementById(\"note6\").innerHTML=obj.note6; document.getElementById(\"note7\").innerHTML=obj.note7; document.getElementById(\"note8\").innerHTML=obj.note8; document.getElementById(\"rb_x\").innerHTML=obj.rb_x; document.getElementById(\"rb_y\").innerHTML=obj.rb_y; document.getElementById(\"rb_z\").innerHTML=obj.rb_z; document.getElementById(\"dc1\").innerHTML=obj.dc1; document.getElementById(\"dc2\").innerHTML=obj.dc2; document.getElementById(\"dc3\").innerHTML=obj.dc3;}}; xhttp.open(\"GET\", \"/apidata\", true); xhttp.send();}function robotrun(){var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){if (this.responseText==\"run\"){alert(\"Robot run!\");}}}; xhttp.open(\"GET\", \"/run\", true); xhttp.send();}function robotstop(){var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){if (this.responseText==\"stop\"){alert(\"Robot stop!\");}}}; xhttp.open(\"GET\", \"/stop\", true); xhttp.send();}</script></html>";


void handleRoot() {
	Serial.println("/");
	digitalWrite(led, 1);
	//FirebaseObject data = Firebase.get("/"); //đọc database
	//if (Firebase.success()) { //nếu đọc thành công thì tách dữ liệu ra thành từng biến
	//  String acc = data.getString("acc");
	//  String num_done = data.getString("num_done");
	//  String num_xuly = data.getString("num_xuly");
	//  String phoi1 = data.getString("phoi1");
	//  String phoi2 = data.getString("phoi2");
	//  String phoi3 = data.getString("phoi3");
	//  String phoi4 = data.getString("phoi4");
	//  String phoi5 = data.getString("phoi5");
	//  String stt1 = data.getString("stt1");
	//  String stt2 = data.getString("stt2");
	//  String stt3 = data.getString("stt3");
	//  String stt4 = data.getString("stt4");
	//  String stt5 = data.getString("stt5");
	//  String note1 = data.getString("note1");
	//  String note2 = data.getString("note2");
	//  String note3 = data.getString("note3");
	//  String note4 = data.getString("note4");
	//  String note5 = data.getString("note5");
	//
	//  //html là chuỗi của trang web hiển thị
	//  String html = F("<!DOCTYPE html><html><head> <title>Title of the document</title> <meta charset=\"utf-8\"/> <style>#wrap{padding: 40px; height: 300px;}.title{border: 1px solid #000; display: inline-block; padding: 10px 10px 40px 10px; color: #000; font-weight: bold;}#content{margin-top: 20px;}#left{width: 48%; float: left;}#right{width: 48%; float: right;}#stoprobot{width: 48%; float: left;}#runrobot{width: 48%; float: right;}#right button{}</style></head><body> <div id=\"wrap\"> <div style=\"text-align:center;\"> <div class=\"title\">Giám sát hoạt động của robot delta</div><div>Account đang đăng nhập: <spand id=\"acc\">{acc}</span> </div></div><div id=\"content\"> <div id=\"left\"> <table width=\"100%\" border=\"1\"> <thead> <tr> <th>STT phôi</th> <th>Mã phôi</th> <th>Tình trạng</th> <th>Ghi chú</th> </tr></thead> <tbody> <tr> <td>1</td><td id=\"phoi1\">{phoi1}</td><td id=\"stt1\">{stt1}</td><td id=\"note1\">{note1}</td></tr><tr> <td>2</td><td id=\"phoi2\">{phoi2}</td><td id=\"stt2\">{stt2}</td><td id=\"note2\">{note2}</td></tr><tr> <td>3</td><td id=\"phoi3\">{phoi3}</td><td id=\"stt3\">{stt3}</td><td id=\"note3\">{note3}</td></tr><tr> <td>4</td><td id=\"phoi4\">{phoi4}</td><td id=\"stt4\">{stt4}</td><td id=\"note4\">{note4}</td></tr><tr> <td>5</td><td id=\"phoi5\">{phoi5}</td><td id=\"stt5\">{stt5}</td><td id=\"note5\">{note5}</td></tr></tbody> </table> </div><div id=\"right\"> <p>Phôi hiện đang xử lý: <span id=\"num_xuly\">{num_xuly}</span></p><p>Số phôi đã xử lý: <span id=\"num_done\">{num_done}</span></p><div id=\"stoprobot\"> <canvas id=\"stopcanvas\" width=\"200\" height=\"200\"></canvas> <button>Ngưng robot</button> </div><div id=\"runrobot\"> <canvas id=\"runcanvas\" width=\"200\" height=\"200\"></canvas> <button>Chạy robot</button> </div></div></div></div></body><script type=\"text/javascript\">var canvas=document.getElementById('stopcanvas'); var context=canvas.getContext('2d'); var centerX=canvas.width / 2; var centerY=canvas.height / 2; var radius=70; context.beginPath(); context.arc(centerX, centerY, radius, 0, 2 * Math.PI, false); context.fillStyle='red'; context.fill(); context.lineWidth=5; context.strokeStyle='red'; context.stroke(); var canvas1=document.getElementById('runcanvas'); var context1=canvas1.getContext('2d'); var centerX1=canvas1.width / 2; var centerY1=canvas1.height / 2; var radius1=70; context1.beginPath(); context1.arc(centerX, centerY, radius, 0, 2 * Math.PI, false); context1.fillStyle='#5a9bd5'; context1.fill(); context1.lineWidth=5; context1.strokeStyle='#5a9bd5'; context1.stroke(); setInterval(function(){updateData();}, 1000); function updateData(){var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){var obj=JSON.parse(this.responseText); document.getElementById(\"acc\").innerHTML=obj.acc; document.getElementById(\"num_done\").innerHTML=obj.num_done; document.getElementById(\"num_xuly\").innerHTML=obj.num_xuly; document.getElementById(\"phoi1\").innerHTML=obj.phoi1; document.getElementById(\"phoi2\").innerHTML=obj.phoi2; document.getElementById(\"phoi3\").innerHTML=obj.phoi3; document.getElementById(\"phoi4\").innerHTML=obj.phoi4; document.getElementById(\"phoi5\").innerHTML=obj.phoi5; document.getElementById(\"stt1\").innerHTML=obj.stt1; document.getElementById(\"stt2\").innerHTML=obj.stt2; document.getElementById(\"stt3\").innerHTML=obj.stt3; document.getElementById(\"stt4\").innerHTML=obj.stt4; document.getElementById(\"stt5\").innerHTML=obj.stt5; document.getElementById(\"note1\").innerHTML=obj.note1; document.getElementById(\"note2\").innerHTML=obj.note2; document.getElementById(\"note3\").innerHTML=obj.note3; document.getElementById(\"note4\").innerHTML=obj.note4; document.getElementById(\"note5\").innerHTML=obj.note5;}}; xhttp.open(\"GET\", \"/apidata\", true); xhttp.send();}</script></html>");
	//  
	//  //thay thế data trong code html từ database lấy ở trên
	//  html.replace("{acc}", acc);
	//  html.replace("{num_done}", String(num_done));
	//  html.replace("{num_xuly}", String(num_xuly));
	//  html.replace("{phoi1}", phoi1);
	//  html.replace("{phoi2}", phoi2);
	//  html.replace("{phoi3}", phoi3);
	//  html.replace("{phoi4}", phoi4);
	//  html.replace("{phoi5}", phoi5);
	//  html.replace("{stt1}", stt1);
	//  html.replace("{stt2}", stt2);
	//  html.replace("{stt3}", stt3);
	//  html.replace("{stt4}", stt4);
	//  html.replace("{stt5}", stt5);
	//  html.replace("{note1}", note1);
	//  html.replace("{note2}", note2);
	//  html.replace("{note3}", note3);
	//  html.replace("{note4}", note4);
	//  html.replace("{note5}", note5);
	//
	//  //gửi xuống client
	//  server.send(200, "text/html", html);
	//}
	//else {
	//  server.send(200, "text/plain", "Read database fail. Please try again");
	//}

	server.send_P(200, text_html, HTML_WEBPAGE_PROGMEM);
	digitalWrite(led, 0);
}

void handleGetDataApi() {
	Serial.println("/apidata");
	digitalWrite(led, 1);

	//Serial.print("RAM before get firebase: ");
	//Serial.println(ESP.getFreeHeap());

	FirebaseObject data = Firebase.get("/"); //đọc database
	if (Firebase.success()) { //nếu đọc thành công thì tách dữ liệu ra thành từng biến
		//Serial.print("RAM after get firebase: ");
		//Serial.println(ESP.getFreeHeap());

		StaticJsonBuffer<1000> jsBuffer;
		JsonObject& jsData = jsBuffer.createObject();

		//JsonVariant jsDataX = data.getJsonVariant("/");
		//String jsDataStrX = jsDataX.asString();
		//Serial.println(jsDataStrX);

		jsData["acc"] = data.getString("acc");
		jsData["num_done"] = data.getString("num_done");
		jsData["num_xuly"] = data.getString("num_xuly");
		jsData["phoi1"] = data.getString("phoi1");
		jsData["phoi2"] = data.getString("phoi2");
		jsData["phoi3"] = data.getString("phoi3");
		jsData["phoi4"] = data.getString("phoi4");
		jsData["phoi5"] = data.getString("phoi5");
		jsData["phoi6"] = data.getString("phoi6");
		jsData["phoi7"] = data.getString("phoi7");
		jsData["phoi8"] = data.getString("phoi8");

		jsData["stt1"] = data.getString("stt1");
		jsData["stt2"] = data.getString("stt2");
		jsData["stt3"] = data.getString("stt3");
		jsData["stt4"] = data.getString("stt4");
		jsData["stt5"] = data.getString("stt5");
		jsData["stt6"] = data.getString("stt6");
		jsData["stt7"] = data.getString("stt7");
		jsData["stt8"] = data.getString("stt8");

		jsData["note1"] = data.getString("note1");
		jsData["note2"] = data.getString("note2");
		jsData["note3"] = data.getString("note3");
		jsData["note4"] = data.getString("note4");
		jsData["note5"] = data.getString("note5");
		jsData["note6"] = data.getString("note6");
		jsData["note7"] = data.getString("note7");
		jsData["note8"] = data.getString("note8");

		jsData["dc1"] = data.getString("dc1");
		jsData["dc2"] = data.getString("dc2");
		jsData["dc3"] = data.getString("dc3");

		jsData["rb_x"] = data.getString("rb_x");
		jsData["rb_y"] = data.getString("rb_y");
		jsData["rb_z"] = data.getString("rb_z");

		String jsDataStr;
		Serial.println(jsDataStr);
		jsData.printTo(jsDataStr);
		//gửi xuống client
		server.send(200, "application/json", jsDataStr);
	}
	else {
		Serial.println("Read database fail");
		server.send(404, "application/json", "{}");
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
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
	digitalWrite(led, 0);
}

void handleRobotRun() {
	Serial.println("/run");
	digitalWrite(led, 1);
	server.send(200, "text/plain", "run");
	digitalWrite(led, 0);
	robotRun();
}

void handleRobotStop() {
	Serial.println("/stop");
	digitalWrite(led, 1);
	server.send(200, "text/plain", "stop");
	digitalWrite(led, 0);
	robotStop();
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

void robotRun() {
	Serial.println("Robot running.");
	//viết thêm vào đây
}
void robotStop() {
	Serial.println("Robot stoped.");
	//viết thêm vào đây
}

void setup() {
	Serial.begin(115200);
	Serial.println("Version: " _VERSION_);
	// connect to wifi.
	WiFi.mode(WIFI_STA);
	//WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	WiFiManager wifiManager;
	wifiManager.autoConnect("TUANQUANG");
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
	//  Serial.println("MDNS responder started");
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
