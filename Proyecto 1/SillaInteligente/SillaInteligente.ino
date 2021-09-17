const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el Echo del sensor
enum SENTADO {
       NO_SENTADO   = 0,
       SENTADO_BIEN = 1,
       SENTADO_MAL_1= 2,
       SENTADO_MAL_2= 3
};

SENTADO sentado; 
void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  pinMode(A2, INPUT);
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

}
 

void loop()
{
  long t; //timepo que demora en llegar el eco
  long distancia_ultrasonica; //distancia en centimetros
  String coso;
  float peso = analogRead(A2) * 0.572 - 185;

  if (peso <= 0){
    peso = 0;
  }
  
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  distancia_ultrasonica = t/59;             //escalamos el tiempo a una distancia en cm

  if(distancia_ultrasonica >= 1170){distancia_ultrasonica = 0;}
  
  //******************Sensor Ultrasonico*************************   
  /*Serial.println("La distancia del sensor Ultrasonico");
  Serial.println(distancia_ultrasonica);*/
  if(distancia_ultrasonica >= 35){
     sentado = NO_SENTADO;
     coso = "{\"sentado\":"+ String(sentado)+ ", \"peso\": " + String(0);
  }else{

        float sensor_p1=analogRead(A0);
        float sensor_p2=analogRead(A1);
          
 //******************Sensor de Peso1*************************   
 /* Serial.println("*************Cantidad del sensor de presion 1**************");
  Serial.println(sensor_p1);
  //******************Sensor de Peso2*************************   
  Serial.println("************Cantidad del sensor de presion 2***************");
  Serial.println(sensor_p2);*/
 //******************Sensor de Peso1*************************   
  
        
        if(sensor_p1 >=50 && sensor_p2 >=50){
             sentado = SENTADO_BIEN;
        }else if(sensor_p1 >= 50){
             sentado = SENTADO_MAL_1;
        }else if(sensor_p2 >= 50){
              sentado = SENTADO_BIEN;
        }else{
            sentado = NO_SENTADO;
        }
        coso = "{\"sentado\":"+ String(sentado)+ ", \"peso\": " + String(peso);
  }
  Serial.println(coso);
  //Prueba();   
  delay(60000);          //Hacemos una pausa de 100ms
  
}

 void Prueba (){
      switch(sentado){
          case  SENTADO_BIEN:
                   Serial.println("Sentado bien");
          break;
          case  SENTADO_MAL_1:
                   Serial.println("Sentado Mal 1");
          break;
          case  SENTADO_MAL_2:
                  Serial.println("Sentado Mal 2");
          break;
          case  NO_SENTADO:
                   Serial.println("No esta Sentado");
          break;
          
        }     
 }
