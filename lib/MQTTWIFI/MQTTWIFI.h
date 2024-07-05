#ifndef MQTTWiFi_H
#define MQTTWiFi_H
#define N_TOPICOS 3    //cantidad de topicos a los que se suscribe
#define MQTT_PORT 1883

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTWiFi
{
 public:
  //MQTT_WiFi();
  void conectar();
  bool conectado();
  void ciclo();
  //void conexion();

  private:
   WiFiClient wifi_client;
   PubSubClient mqtt_client; 
    
   void reconectar();
   void reconnectPublic();
   void publishMqtt(const char *topic, String mensaje);

   /**
   * Constantes para la conexión
   * Internet, MQTT y topicos 
   * nombre de los topicos: TOPIC_(param | public)_(sensor)_otro
   * TOPICOS EN MQTT: MHC/invernadero/(param | public)/(sensor)/(otro)
   */
  const char* SSID_RED = "MHC";
  const char* PASS_RED = "123456789";
  const char* MQTT_SERVER = "broker.hivemq.com";
  const char* MQTT_USER = "MHC";
  const char* TOPIC_PUBLIC_TEMP = "MHC/invernadero/public/temperatura";
  const char* TOPIC_PUBLIC_HUMIDITY = "MHC/invernadero/public/humedad";
  const char* TOPIC_PARAMS_TEMP_MIN = "MHC/invernadero/params/temperatura/min";
  const char* TOPIC_PARAMS_TEMP_MAX = "MHC/invernadero/params/temperatura/max";
  const char* TOPIC_PUBLIC_HUM_TIERRA = "MHC/invernadero/public/humedad_tierra";
  const char* TOPIC_PARAMS_HUM_TIERRA_MIN = "MHC/invernadero/params/humedad_tierra/min";
  const char* TOPIC_PUBLIC_LUZ = "MHC/invernadero/public/luz";
  const char* TOPIC_PARAMS_LUZ_MIN = "MHC/invernadero/params/luz/min";
  const char* TOPIC_PARAMS_LUZ_MAX = "MHC/invernadero/params/luz/max";
  const char* TOPICOS[N_TOPICOS] = {
   TOPIC_PARAMS_TEMP_MIN, TOPIC_PARAMS_TEMP_MAX, TOPIC_PARAMS_HUM_TIERRA_MIN
  };
};
#endif
