String Kaijuu[5];
String str = "3C:61:05:FE:1E:BCK58:BF:25:D7:6A:28K3C:61:05:FE:1E:BCK58:BF:25:D7:6A:28";
int i,y ;
String EDEN[4];
uint8_t broadcastAddress[4][6];
    
void setup () {
  Serial.begin (115200);
}

void loop () { 
  for(y=0;y<=3;y++){
    EDEN[y]=getValue(str,'K',y);
    Serial.printf("EDEN[%d]=",y);
    Serial.println(EDEN[y]);
for(i=0;i<=5;i++){
  Kaijuu[i] = getValue(EDEN[y],':',i); 
  Serial.printf("Kaijuu[%d]=",i);
  Serial.println(Kaijuu[i]);
  String hexValue = Kaijuu[i];
  byte tens = (hexValue[0] < '9') ? hexValue[0] - '0' : hexValue[0] - '7';
  byte ones = (hexValue[1] < '9') ? hexValue[1] - '0' : hexValue[1] - '7';
  byte number = (16 * tens) + ones;
  broadcastAddress[y][i] = number;
  Serial.println(number);
  Serial.printf("broadcastAddress[%d][%d]=",y,i);
  Serial.println(broadcastAddress[y][i]);
}
//Serial.printf("broadcastAddress[%d][%d]",y,i);
//String Kamon=broadcastAddress[2][6];
   // Serial.println(Kamon);
   Serial.println("_____________");
}
//EDEN[0]=broadcastAddress1[];
//Serial.println(EDEN[y]);
Serial.println("---------------------");
/*Serial.println(broadcastAddress1[0]);
Serial.println(broadcastAddress1[1]);*/
//uint8_t*Kaijuu[5];
delay(500);
  
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
