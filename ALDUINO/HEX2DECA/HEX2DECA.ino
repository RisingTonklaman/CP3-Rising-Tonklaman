//char hexValue[] = {'F', 'E'};
String hexValue = "BF";

void setup()
{
  Serial.begin(115200);

 
}

void loop()
{
 byte tens = (hexValue[0] < '9') ? hexValue[0] - '0' : hexValue[0] - '7';
  byte ones = (hexValue[1] < '9') ? hexValue[1] - '0' : hexValue[1] - '7';
  byte number = (16 * tens) + ones;
  Serial.println(number);
 
}
