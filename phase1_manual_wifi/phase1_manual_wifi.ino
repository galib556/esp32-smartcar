#include <WiFi.h>
#include <WebServer.h>

// ================= MOTOR PINS =================

// Right Motor
int enableRightMotor = 22;
int rightMotorPin1 = 16;
int rightMotorPin2 = 17;

// Left Motor
int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

// ================= PWM =================

const int PWMFreq = 1000;
const int PWMResolution = 8;

const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

#define MAX_MOTOR_SPEED 200

// ================= WIFI =================

const char* ssid = "ESP32_CAR";
const char* password = "12345678";

WebServer server(80);

// ================= MOTOR CONTROL =================

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  // RIGHT MOTOR
  if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // LEFT MOTOR
  if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));
}

// ================= WEBPAGE =================

String webpage = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<title>ESP32 WiFi Car</title>

<style>

body{
  background:#111;
  color:white;
  text-align:center;
  font-family:Arial;
}

h1{
  margin-top:20px;
}

.button{
  width:120px;
  height:120px;
  font-size:28px;
  margin:10px;
  border:none;
  border-radius:20px;
  color:white;
  font-weight:bold;
}

.forward{
  background:green;
}

.backward{
  background:red;
}

.left{
  background:orange;
}

.right{
  background:orange;
}

.stop{
  background:gray;
}

.middle{
  display:flex;
  justify-content:center;
  align-items:center;
}

</style>

</head>

<body>

<h1>ESP32 WiFi Car</h1>

<button class="button forward"
ontouchstart="sendCommand('forward')"
ontouchend="sendCommand('stop')">
FORWARD
</button>

<div class="middle">

<button class="button left"
ontouchstart="sendCommand('left')"
ontouchend="sendCommand('stop')">
LEFT
</button>

<button class="button stop"
onclick="sendCommand('stop')">
STOP
</button>

<button class="button right"
ontouchstart="sendCommand('right')"
ontouchend="sendCommand('stop')">
RIGHT
</button>

</div>

<button class="button backward"
ontouchstart="sendCommand('backward')"
ontouchend="sendCommand('stop')">
BACKWARD
</button>

<script>

function sendCommand(command)
{
  fetch("/" + command);
}

</script>

</body>
</html>
)rawliteral";

// ================= WEB HANDLERS =================

void handleRoot()
{
  server.send(200, "text/html", webpage);
}

void handleForward()
{
  rotateMotor(MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  server.send(200, "text/plain", "Forward");
}

void handleBackward()
{
  rotateMotor(-MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
  server.send(200, "text/plain", "Backward");
}

// FIXED LEFT/RIGHT

void handleLeft()
{
  rotateMotor(MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);
  server.send(200, "text/plain", "Left");
}

void handleRight()
{
  rotateMotor(-MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  server.send(200, "text/plain", "Right");
}

void handleStop()
{
  rotateMotor(0, 0);
  server.send(200, "text/plain", "Stop");
}

// ================= SETUP =================

void setup()
{
  Serial.begin(115200);

  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);

  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel);

  rotateMotor(0,0);

  WiFi.softAP(ssid, password);

  Serial.println("WiFi Started");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);

  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);

  server.begin();
}

// ================= LOOP =================

void loop()
{
  server.handleClient();
}