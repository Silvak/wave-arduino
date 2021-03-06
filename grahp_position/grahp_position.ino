#include <LedControl.h> //la libreria es LedControl-master.zip
int xPin = A1; // lee X_OUT
int yPin = A2; // lee Y_OUT
int  x = 0; //Almacena el xPin
int  y = 0; //Almacena el yPin
int gx = 0; //Almacena el resultado de la division entre x / 10
int gy = 0; //Almacena el resultado de la division entre y / 10
int mode = 0; //un valor a ser untilizado posteriormente para un cambio de modos al pulsar un boton

int DIN = 12; 
int CS =  11;
int CLK = 10;

byte  px[]=   {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01}; //Puntos de posicion en el eje X
byte  py[8]=  {0,0,0,0,0,0,0,0}; //Puntos de posicion en el eje Y
//Animacion inicial a0, a1 y a2
byte a0[8]=  {0,0,0,0,0,0,0,0}; 
byte a1[8]=  {0x00,0x00,0x00,0x18,0x18,0x08,0x00,0x00};
byte a2[8]=  {0x00,0x00,0x00,0x38,0x18,0x08,0x00,0x00};

LedControl lc=LedControl (DIN,CLK,CS,0);

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(xPin, INPUT);       // establece xPin como variable de entrada
  pinMode(yPin, INPUT);       // establece yPin como variable de entrada
  lc.shutdown(0,false);       // El MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 5);      // Configuracion del brillo para max o min valor 5 - 30...
  lc.clearDisplay(0);         // Limpiador de pantalla
  Serial.println("Wave_arduino grafica un punto en matriz 8x8 con acelerometro"); delay(100);
  Serial.println("               Recordar leer todo por anticipado            "); delay(900);
}

void loop() {
  //Llamado a la funcion logo y comprobacion si se ha ejecutado con anterioridad
  if(mode == 0) { Logo(); } 
  //Llamado a la funcion para graficar el punto en la matriz
  if(mode == 1) { GraficaPoint(); }
}

void Logo(){
  int i = 0;
  int ib = 0; 
  for(i=0;i<6;i++){
    a0 [i] = 8;
    printByte(a0);
    delay(100);
    if (i == 2){      
        for(ib=0;ib<3;ib++){
          if(ib < 3){
            a0[ib] = 0; 
            printByte(a0);
            delay(100);
            }
        }  
     } 
  }
  printByte(a1);
    delay(120);
  printByte(a2);
    delay(2000);
  mode = ++mode; //cambia el valor de modo de 0 a 1
  }

void GraficaPoint(){
    //leemos y almacenamos la posicion en x & y  
    x = analogRead(xPin) - 501; 
    y = analogRead(yPin) - 510; 
    //la dividimos entre diez para obtener enteros de menor valor
    gx = x / 10;
    Serial.print(gx);
    Serial.print(":x\t y:");
    gy = y / 10;
    Serial.println(gy);
    if(gy >= 0){  //Si gy >= 0 ejecutar...
        /*la pocicion Y esta definida dinamicamente por gy utilizando los valores del 0 al 7, 
        mientras que gx toma un valor de la matriz px utilizando 0 or 7 para graficar la posicion en X*/
        py[gy] = px[gx]; 
        printByte(py); //Se ejecuta la funcion printByte(namematriz); para imprimir el resultado
        py[gy]= 0; //Restablece la posicion en el eje Y a su valor inicial
        }
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
