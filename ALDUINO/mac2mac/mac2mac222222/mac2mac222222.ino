void setup () {
  Serial.begin (115200);
}
String str = "13:45,21:40,23:08";
    
void loop () { 

  String part02 = getValue(str,',',1); // get 2 in str

  Serial.println(part02);

  String subpart02 = getValue(part02,':',0); // get 1 in part02

  Serial.println(subpart02);

  
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
