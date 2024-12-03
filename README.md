# AwsSensor

- [Översikt](#översikt)
- [Introduktion](#introduktion)
  - [Komponenter](#komponenter)
- [Instruktioner](#instruktioner)
  - [Steg 1: Nedladdningar](#steg-1-nedladdningar)
  - [Steg 2: Konfigurera projektet](#Steg-2-Konfigurera-projektet)
  - [Steg 3: Sätt upp Databas](#steg-3-Sätt-upp-Databas)
  - [Steg 4: Visualisering och Notifiering](#Steg-4-Visualisering-och-Notifiering)
- [Säkerhet och Skalbarhet](#säkerhet-och-skalbarhet)
- [Slutsats](#slutsats)



# Översikt




![Skärmbild 2024-12-03 191140](https://github.com/user-attachments/assets/dc142f1e-7064-4e0b-8eb1-76f0a553b5b0)

---

# Introduktion

Detta projekt är en omfattande guide för att konfigurera och använda AWS och DynamoDB för att samla in och analysera data från en ESP32-enhet kopplad till en DHT11-sensor. Genom att följa denna guide kommer du att kunna skapa en IoT-lösning som samlar in, bearbetar och lagrar data i realtid. Lösningen kan användas för olika IoT-applikationer, som att övervaka miljöförhållanden, skapa smarta hemlösningar eller förbättra affärsprocesser med hjälp av datainsikter. Det slutliga resultatet är en skalbar IoT-lösning som hanterar stora mängder data, med möjligheten att använda AWS-tjänster som AWS IoT Core för hantering av enheter och DynamoDB för effektiv lagring. Insikterna från denna data kan visualiseras med verktyg som grafana eller externa plattformar för datavisualisering. Samt koppling till Telegram bot för att kunna se online/offline status. 

# Komponenter

- Ett aktivt AWS-konto.
- En DynamoDB-tabell för att lagra data.
- En ESP32 och DHT11 som är korrekt konfigurerad och ansluten.
- Arduino IDE för att programmera ESP32.
- AWS IoT Core för att hantera och bearbeta data från sensorn.
- Grafana för att visualisera data i realtid.
- Telegram för att skicka notifieringar eller larm baserat på insamlade data.

  ![Esp32Koppling](https://github.com/user-attachments/assets/25985ab3-d8e2-42a1-bf7b-79dd067df8e9)
  
  *ESP32 och DHT11 Setup*

  






  ![Flöde](https://github.com/user-attachments/assets/6440c8f7-87c2-423d-b179-2615f5685ab7)

  *Flöde*


# Instruktioner 

## Steg 1: Nedladdningar

1. **Installera Arduino IDE**  
   - Ladda ner och installera den senaste versionen av Arduino IDE från [Arduino:s officiella webbplats](https://www.arduino.cc/).  

2. **Installera ESP32-paketet i Arduino IDE**  
   - Öppna Arduino IDE och gå till **File > Preferences**.  
   - Lägg till följande URL i "Additional Boards Manager URLs":  
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Gå till **Tools > Board > Boards Manager**, sök efter "ESP32" och installera paketet.

3. **Installera nödvändiga bibliotek**  
   Installera följande bibliotek via **Tools > Manage Libraries**:  
   - **ArduinoJson**: Hanterar JSON-data.  
   - **MQTTclient**: Använder MQTT-protokollet.  
   - **DHT Sensor Library**: Läser temperatur- och luftfuktighetsdata från DHT11-sensorn.  
   - **WiFiClientSecure**: Använder TLS/SSL för säker anslutning till AWS IoT Core.

---

## Steg 2: Konfigurera projektet

   **Skapa `secrets_example.h`**  
   Skapa en fil kallad `secrets_example.h` och lägg till följande information:

   ```cpp
   #define SECRETS

   // WiFi-konfiguration
   #define WIFI_SSID "DittWiFiSSID"
   #define WIFI_PASSWORD "DittWiFiLösenord"

   // AWS IoT Core-konfiguration
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(-----BEGIN CERTIFICATE-----"DittCertifikat"-----END CERTIFICATE-----)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(-----BEGIN CERTIFICATE-----"DittCertifikat"-----END CERTIFICATE-----)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(-----BEGIN RSA PRIVATE KEY-----"DittCertifikat"-----END RSA PRIVATE KEY-----)KEY";

   #endif
   ```




## Steg 3: Sätt upp Databas

1. **Datainsamling via DynamoDB**  
   - Konfigurera DynamoDB för att effektivt lagra och hantera data från DHT11-sensorerna som skickas via AWS IoT Core.  
   - Skapa en tabell med följande struktur för att lagra insamlade mätvärden:
     - **Partition Key:** `deviceId` (String) – Identifierar vilken enhet som skickade datan.  
     - **Sort Key:** `timestamp` (Number) – Tidsstämpel för mätningen.
    

## Steg 4: Visualisering och Notifiering

### Visualisering med Grafana

1. **Konfigurera din unika URL som datakälla**  
   - Din IoT-lösning genererar data som är åtkomlig via en unik URL, som kan användas som datakälla i Grafana.  
   - Gå till **Configuration > Data Sources** i Grafana:  
     - Klicka på "Add data source".  
     - Välj yesoireyeram-infinity-datasource.
     - Ange din unika URL som datakälla.  
       - Exempel: `https://din-unika-url/api/data`.  
     - Konfigurera autentisering med  Header `authorization` samt `din-key`.  

2. **Skapa Dashboards i Grafana**  
   - Designa anpassade dashboards för att visualisera realtidsdata:  
     - **Panel 1:** Temperatur över tid.  
     - **Panel 2:** Luftfuktighet över tid.   
   - Använd Grafanas frågefunktioner för att specificera vilka datapunkter som ska visas.  
     - Exempel: Använd tidsfilter för att visa data för senaste 1 timmen, 24 timmar, eller 7 dagar.

  
    ![SensorDataGrafana](https://github.com/user-attachments/assets/595bb1da-8992-4e06-9b73-5143ace2daf1)

---

### Notifieringar med Telegram

1. **Skapa en Telegram-bot**  
   - Öppna Telegram och starta en konversation med [BotFather](https://core.telegram.org/bots#botfather).  
   - Skapa en ny bot genom att skicka `/newbot` och följ instruktionerna.  
   - Kopiera botens **API-token**, som används för att skicka meddelanden.  

2. **Konfigurera AWS Lambda för notifieringar**  
   - Skapa en Lambda-funktion som skickar notifieringar till Telegram när specifika villkor uppfylls.  

3. **Notifieringarna**  
   - Starta din device och avsluta den, då skickas ett meddelande från Lambda till Telegram med online/offlinestatus.
  
    ![Telegram](https://github.com/user-attachments/assets/d91f217d-899b-4be0-9469-f6f42cc56302)

---


## Säkerhet och Skalbarhet

- **Automatiserad hantering**: Använd **AWS IoT Device Management** för att registrera och övervaka IoT-enheter.
   
- **Skydda data**: Hantera API-nycklar och certifikat med **AWS Secrets Manager** i framtiden för ytterligare säkerhet.
   
- **Skalbarhet**: Skala DynamoDB automatiskt och utnyttja AWS:s flexibla prissättning.  

- **Säkra anslutningar**: Använd MQTTS (SSL/TLS) med `WiFiClientSecure` och unika certifikat.  

- **Åtkomstkontroll**: Begränsa enheters rättigheter med **AWS IoT Policies**.

---

## Slutsats

I denna guide har vi framgångsrikt byggt en skalbar IoT-lösning med ESP32, DHT11 och AWS IoT Core. Genom att lagra data i DynamoDB och använda Grafana för avancerad visualisering har vi skapat ett system som möjliggör realtidsövervakning och analys av temperatur- och luftfuktighetsdata. Med Telegram-integrationen kan vi dessutom få notifikationer om enheten slutar sända data vilket ökar systemets användbarhet.






     

