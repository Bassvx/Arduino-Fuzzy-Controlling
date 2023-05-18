#define FIS_TYPE float
#define FIS_RESOLUSION 101
#define FIS_MIN -3.4028235E+38
#define FIS_MAX 3.4028235E+38
typedef FIS_TYPE (*_FIS_MF)(FIS_TYPE, FIS_TYPE*);
typedef FIS_TYPE (*_FIS_ARR_OP)(FIS_TYPE, FIS_TYPE);
typedef FIS_TYPE (*_FIS_ARR)(FIS_TYPE*, int, _FIS_ARR_OP);

#include <DHT.h>

#define ldr_luar
#define ldr_dalam
int Brightness = 0;



// Number of inputs to the fuzzy inference system
const int fis_gcI = 2;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 1;
// Number of rules to the fuzzy inference system
const int fis_gcR = 9;

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

DHT dht(A5, DHT11);  //Pin, Jenis DHT
int LDR_Outdoor = A4;
int Lampu = 5;
int Kipas = 6;
String dataSerial;

void setup() {

  Serial.begin(115200);
  dht.begin();
  pinMode(LDR_Outdoor, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Lampu, OUTPUT);
  pinMode(Kipas, OUTPUT);
  digitalWrite(Lampu, 0);
}

void loop() {
  int k = dht.readHumidity();
  int s = dht.readTemperature();
  LDR_Outdoor = analogRead(A4);
  int LDR_O = map(LDR_Outdoor,0,1023,0,511);
  int Fan = map(g_fisOutput[0],0, 100, 0, 255);
  
  int Ldr_Luar = map(LDR_O, 0, 511, 100, 0);
  analogWrite(Lampu, LDR_O);
  // Read Input: Suhu
  g_fisInput[0] = s;
  // Read Input: Kelembapan
  g_fisInput[1] = k;
  g_fisOutput[0] = 0;
  fis_evaluate();
  analogWrite(Kipas, Fan + 50);

  Serial.print("A");
  Serial.print(s);  // In Suhu
  Serial.print("B");
  Serial.print(k);  // In Kelembaban
  Serial.print("C");
  Serial.print(Ldr_Luar);  //In Cahaya
  Serial.print("D");
  Serial.print(g_fisOutput[0]);  //Out Kipas
  Serial.print("E");
  Serial.print(LDR_O / 5.12);  //Out Kipas
  Serial.println("F");
  while(s < 19){
  int k = dht.readHumidity();
  int s = dht.readTemperature();
  int LDR_O = map(LDR_Outdoor,0,1023,0,511);
  int Fan = map(g_fisOutput[0],0, 100, 0, 255);
  LDR_Outdoor = analogRead(A0);
  int Ldr_Luar = map(LDR_O, 0, 511, 100, 0);
  analogWrite(Lampu, LDR_O);
  // Read Input: Suhu
  g_fisInput[0] = s;
  // Read Input: Kelembapan
  g_fisInput[1] = k;
  g_fisOutput[0] = 0;
  fis_evaluate();
  analogWrite(Kipas, 0);

  Serial.print("A");
  Serial.print(s);  // In Suhu
  Serial.print("B");
  Serial.print(k);  // In Kelembaban
  Serial.print("C");
  Serial.print(Ldr_Luar,0);  //In Cahaya
  Serial.print("D");
  Serial.print(g_fisOutput[0], 0);  //Out Kipas
  Serial.print("E");
  Serial.print(LDR_O / 5.12);  //Out Kipas
  Serial.println("F");
  delay(100);
  }
  delay(100);
}
