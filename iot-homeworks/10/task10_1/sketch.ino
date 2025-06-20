#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

// Инициализация I2C LCD (адрес 0x27, 16 символов, 2 строки)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Пин кнопки
const int buttonPin = 25;

// Переменные для работы с сетями
int networkCount = 0;         // счетчик сетей
int currentNetworkIndex = 0;  // текущий индекс сети
const unsigned long debounceDelay = 10; // дребезг кнопки

bool more_than_one = false; // признак, в Wokwi больше 1-ой сети
int lastButtonState;    // предыдущее состояние кнопки
int currentButtonState; // текущее состояние кнопки

// структура для имитации сети
struct WiFiNetwork {
  char* ssid;     // название сети
  int16_t rssi;   // индикатор уровня принимаемого сигнала
  bool crypt;     // открытая/закрытая
};

// Массив сетей
const WiFiNetwork nets[] = {
  {"Home_Net_5G", -45, false}, {"Home_Net_4G", -52, true},
  {"Xiaomi_AB12", -68, false}, {"TP-Link", -82, true}
};

// Функция подавления дребезга
// last - предыдущее состояние кнопки
int debounce (int last) {
  int current = digitalRead(buttonPin);
  if (last != current) { //если состояние изменилось
    delay(debounceDelay);
    current = digitalRead(buttonPin);
  }
  return current;
}

// Сканирование сетей
void scanNetworks() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning WiFi...");
  lcd.setCursor(0, 1);
  lcd.print("Please wait");

  Serial.println("Старт сканирования WiFi");

  // Запуск сканирования
  networkCount = WiFi.scanNetworks();

  Serial.println("Закончено сканирование WiFi");

  if (networkCount == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No networks");
    lcd.setCursor(0, 1);
    lcd.print("found");
    Serial.println("Сетей WiFi не нашлось");
    return;
  }

  if (networkCount == 1) {  // в бесплатном wokwi у меня находит одну сеть
    networkCount = 5; // добавляем 4 сети из массива сетей
  } else {
    // тут нашлось больше одной сети (т.е. при симуляции в wokwi
    // можно перебирать несколько сетей, массивом не пользуемся)
    more_than_one = true;
  }
  Serial.print(networkCount);
  Serial.println(" сетей найдено");

  // Показать первую сеть
  currentNetworkIndex = 0;
  displayCurrentNetwork();
}

// Показать текущую сеть на экране
void displayCurrentNetwork() {
  if (networkCount == 0) return;

  lcd.clear();
  // Первая строка: номер сети и название
  lcd.setCursor(0, 0);
  lcd.print(String(currentNetworkIndex + 1) + "/" + String(networkCount) + " ");

  String ssid = currentNetworkIndex == 0 || more_than_one ? WiFi.SSID(currentNetworkIndex) :
                nets[currentNetworkIndex - 1].ssid ;
  lcd.print(ssid);

  // Вторая строка: мощность сигнала
  lcd.setCursor(0, 1);
  int rssi = currentNetworkIndex == 0 || more_than_one ? WiFi.RSSI(currentNetworkIndex) :
             nets[currentNetworkIndex - 1].rssi;
  lcd.print("Sig:");
  lcd.print(rssi);
  lcd.print("dBm");

  // Индикатор качества сигнала
  if (rssi > -50) {
    lcd.print(" Excellent");
  } else if (rssi > -60) {
    lcd.print(" Good");
  } else if (rssi > -70) {
    lcd.print(" Fair");
  } else {
    lcd.print(" Weak");
  }

  // Индикатор шифрования в правом углу (*)
  bool is_array = (currentNetworkIndex > 0) && !more_than_one;
  lcd.setCursor(15, 0);
  if (!is_array && (WiFi.encryptionType(currentNetworkIndex) != WIFI_AUTH_OPEN)) {
    lcd.print("*");
  }
  if (is_array && nets[currentNetworkIndex - 1].crypt) {
    lcd.print("*");
  }
}

// Начальные установки
void setup() {
  Serial.begin(115200);

  // Настройка LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Scanner");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  // Настройка кнопки
  pinMode(buttonPin, INPUT_PULLUP);
  currentButtonState = digitalRead(buttonPin);

  // Инициализация WiFi в режиме станции
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Serial.println("Setup отработал");

  // Сканирование сетей при запуске
  scanNetworks();
}

// Цикл перебора по нажатию кнопки
void loop() {
  // Проверка нажатия кнопки
  lastButtonState = currentButtonState;
  currentButtonState = debounce(lastButtonState); // read new state
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    // Serial.println("Кнопка нажата, показать следущую сеть..");


    // Переход к следующей сети
    if (networkCount > 0) {
      currentNetworkIndex = (currentNetworkIndex + 1) % networkCount;
      displayCurrentNetwork();
    }
    delay(80);
  }
}

