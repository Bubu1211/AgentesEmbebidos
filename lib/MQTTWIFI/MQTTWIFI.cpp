#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTTWiFi.h"
void MQTTWiFi::reconnectPublic()
{
 while(!mqtt_client.connected()){
  if(mqtt_client.connect(MQTT_USER)){
   Serial.print("Conexión exitosa con usuario: ");
   Serial.println(MQTT_USER);
  }else{   //en caso de fallar
   Serial.print("Falló la conexión, error rc = ");
   Serial.print(mqtt_client.state());
   Serial.println("Intentar de nuevo en 2.5 segundos");
   delay(2500);
  }
 }
  
}
void MQTTWiFi::conectar()
{
 mqtt_client.setClient(wifi_client);
 WiFi.begin(SSID_RED, PASS_RED);
 while(WiFi.status() != WL_CONNECTED){
  Serial.print(" No conectado...");
  delay(20);
 }
 Serial.print("Conectado con IP: ");
 Serial.println(WiFi.localIP());
 delay(2000);
 mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
 //mqtt_client.setCallback(callback);
 delay(1000);
}

void MQTTWiFi::reconectar()
{
 Serial.println("Reconectando...");
 while(!mqtt_client.connected()){   //mientras no este conectado al servidor
  if(mqtt_client.connect(MQTT_USER)){ //se reintenta la conexión con el usuario
   //volver a suscribirse a los topicos
   for(int i = 0; i<N_TOPICOS; i++){
     mqtt_client.subscribe(TOPICOS[i]);
   }
  }
  else{    //en caso de fallar
   Serial.print("Falló la conexión, error rc = ");
   Serial.print(mqtt_client.state());
   Serial.println("Intentar de nuevo en 2.5 segundos");
   delay(2500);
  }
}



void MQTTWiFi::publishMqtt(const char *topic, String mensaje)
{
 if(!mqtt_client.connected())
  reconnectPublic();
 int len = mensaje.length()+1;
 char m[len];
 mensaje.toCharArray(m, len);
 Serial.printf("Mensaje: %s enviado al topic: %s\n", m, topic);
 mqtt_client.publish(topic, m);
}

void MQTTWiFi::setFCallback(Funcion f)
{
  mqtt_client.setCallback(f);
}


bool MQTTWiFi::conectado()
{
 return mqtt_client.connected();
}

void MQTTWiFi::ciclo()
{
 this->mqtt_client.loop();
}

/*void MQTT_WiFi::conexion()
{
 if(!mqtt_client.connected()){
    reconectar();
  }
 mqtt_client.loop();
}*/
