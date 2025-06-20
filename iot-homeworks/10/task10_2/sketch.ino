#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>

// Настройки Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Настройки OpenWeatherMap
String apiKey = "cdecb72a7903eb3bb1964c39615f1764";
String city = "Kemerovo"; 
String countryCode = "RU";

#define BUTTON_PIN 25 // пин кнопки
#define DEBOUNCE_TIME 200 // дребезг


// LCD (адрес 0x27 для 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Данные о погоде
float temp = 0.0;       // температура
float feels_like = 0.0; // ощущается
int humidity = 0;       // влажность

// Таймер
unsigned long lastUpdate = 0;
const long interval = 30000; // 30 секунд интервал опроса

// Режим отображения (0: температура, 1: ощущается, 2: влажность)
int displayMode = 0;
int lastButtonState = HIGH;

// Вывод данных на экран
void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(city);
  
  lcd.setCursor(0, 1);
  switch (displayMode) {
    case 0:
      lcd.print("Temp: " + String(temp) + "C");
      break;
    case 1:
      lcd.print("Feels: " + String(feels_like) + "C");
      break;
    case 2:
      lcd.print("Humidity: " + String(humidity) + "%");
      break;
  }
}

// Обновление показаний погоды
void updateWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    String url = "http://api.openweathermap.org/data/2.5/weather?q=" 
                 + city + "," + countryCode + "&units=metric&appid=" + apiKey;
    
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode == 200) {
      String payload = http.getString();
      JSONVar data = JSON.parse(payload);
      
      // Парсинг данных
      temp = (double)data["main"]["temp"];
      feels_like = (double)data["main"]["feels_like"];
      humidity = (int)data["main"]["humidity"];
      
      updateDisplay();
    } else {
      lcd.clear();
      lcd.print("HTTP Error: " + String(httpCode));
    }
    http.end();
  } else {
    lcd.clear();
    lcd.print("WiFi Disconnected!");
  }
}

// Настройки программы
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.print("Connecting WiFi...");
  
  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  lcd.clear();
  lcd.print("WiFi connected!");
  
  // Настройка кнопки
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Первоначальное обновление данных
  updateWeatherData();
}

// Основной цикл
void loop() {
  // Обработка кнопки
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && lastButtonState == HIGH) {
    displayMode = (displayMode + 1) % 3; // Циклическое переключение
    updateDisplay();
    delay(DEBOUNCE_TIME); // Защита от дребезга
  }
  lastButtonState = buttonState;

  // Обновление данных каждые 30 секунд
  if (millis() - lastUpdate > interval) {
    updateWeatherData();
    lastUpdate = millis();
  }
}
