<h1>🚗 Vehicle Speed Monitoring and Overspeed Alert System with ESP32 + Blynk 📲 </h1>

<p>This project uses an <strong>IR sensor</strong>, <strong>ESP32</strong>, and the <strong>Blynk IoT platform</strong> to detect vehicle speed and trigger an <strong>overspeed alert</strong> if a threshold is exceeded. Perfect for smart traffic systems and embedded systems learners!</p>

<h2>🧠 Features</h2>
<ul>
  <li>🔍 IR Sensor-based speed detection</li>
  <li>📡 Real-time data to <strong>Blynk mobile app</strong></li>
  <li>🔔 Buzzer alert for overspeed</li>
  <li>📱 Smart interface using <strong>Blynk Dashboard</strong></li>
</ul>

<h2>🛠️ Hardware Components</h2>
<table>
  <tr><th>Component</th><th>Quantity</th></tr>
  <tr><td>ESP32 Dev Board</td><td>1</td></tr>
  <tr><td>IR Sensor</td><td>1</td></tr>
  <tr><td>Buzzer</td><td>1</td></tr>
  <tr><td>Jumper Wires</td><td>As needed</td></tr>
  <tr><td>Smartphone with Blynk App</td><td>1</td></tr>
</table>

<h2>📦 Software & Libraries</h2>
<p>Install the following libraries in <strong>Arduino IDE</strong>:</p>
<ul>
  <li><code>WiFi.h</code> (Built-in for ESP32)</li>
  <li><code>BlynkSimpleEsp32.h</code> (Install from Blynk Library)</li>
</ul>

<h2>🔐 Blynk Setup</h2>
<p>Before using the code, configure the following with your Blynk credentials:</p>

<pre><code>#define BLYNK_TEMPLATE_ID "YourTemplateIDHere"
#define BLYNK_TEMPLATE_NAME "YourTemplateNameHere"
#define BLYNK_AUTH_TOKEN "YourAuthTokenHere"
</code></pre>

<ul>
  <li>🆔 <strong>Template ID</strong> and <strong>Name</strong>: From Blynk Console → Templates</li>
  <li>🔑 <strong>Auth Token</strong>: From Blynk Console or Blynk App device</li>
</ul>

<p>⚠️ <strong>Do not share</strong> your credentials publicly.</p>

<h2>🌐 Wi-Fi Credentials</h2>
<p>Replace these with your mobile hotspot or home Wi-Fi credentials:</p>

<pre><code>char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";
</code></pre>

<h2>📈 How It Works</h2>
<ul>
  <li>The <strong>IR sensor</strong> detects wheel rotation.</li>
  <li>The time between IR pulses calculates <strong>RPM</strong> and <strong>Speed</strong>.</li>
  <li>If speed > 2.46 km/h:
    <ul>
      <li>Buzzer turns ON with a siren effect 🔊</li>
      <li>Overspeed event is logged in Blynk 📱</li>
      <li>Red LED (virtual pin V2) glows in Blynk</li>
    </ul>
  </li>
  <li>Otherwise:
    <ul>
      <li>Green LED (V1) stays ON</li>
      <li>Buzzer remains OFF</li>
    </ul>
  </li>
</ul>

<h2>📊 Blynk App Virtual Pins</h2>
<table>
  <tr><th>Virtual Pin</th><th>Purpose</th></tr>
  <tr><td>V0</td><td>Display Speed (km/h)</td></tr>
  <tr><td>V1</td><td>Green LED (Normal Speed)</td></tr>
  <tr><td>V2</td><td>Red LED (Overspeed Warning)</td></tr>
</table>

<h2>📋 Code Flow Summary</h2>
<ol>
  <li><strong>Setup Section</strong>: Connects to Wi-Fi and Blynk, sets up pins and interrupt for IR sensor</li>
  <li><strong>Interrupt Function</strong>: Triggered when the IR beam is cut</li>
  <li><strong>Speed Calculation</strong>: Uses wheel circumference and time interval, converts to km/h and sends to Blynk</li>
  <li><strong>Overspeed Alert</strong>: Triggers buzzer with alternating siren tones, sends notification via <code>Blynk.logEvent()</code></li>
</ol>

<h2>🧪 Testing Steps</h2>
<ol>
  <li>Upload code via Arduino IDE to ESP32</li>
  <li>Open Serial Monitor (baud: 115200)</li>
  <li>Rotate the wheel/simulate IR cuts manually</li>
  <li>Observe speed updates in Blynk</li>
  <li>Trigger overspeed by increasing rotation frequency</li>
</ol>

<h2>🛡️ Safety Tips</h2>
<ul>
  <li>Ensure accurate sensor placement</li>
  <li>Use external power for peripherals if needed</li>
  <li>Secure the hardware to avoid movement during testing</li>
</ul>

<h2>❓ FAQ</h2>
<p><strong>Q: Why isn’t my ESP32 connecting to Wi-Fi?</strong><br>
A: Double-check <code>ssid</code> and <code>pass</code>, and ensure your phone hotspot is active.</p>

<p><strong>Q: Blynk app doesn’t update?</strong><br>
A: Ensure you’re using the correct Auth Token, Template ID, and that the ESP32 is online.</p>

<h2>👨‍💻 Author</h2>
<p><strong>Naragam Manikanta Raghava</strong><br>
<a href="https://github.com/NMRL24/Vehicle-Speed-Monitoring-Overspeed-Alert-System">GitHub Project Link</a></p>

<h2>📜 License</h2>
<p>This project is open-source and free to use for learning and non-commercial purposes. Attribution appreciated.</p>
