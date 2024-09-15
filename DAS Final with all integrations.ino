#include <TinyGPS++.h>                      //for GPS
#include <SoftwareSerial.h>
static const int RXPin = 9, TXPin = 8;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
float Latitude=0;
float Longitude=0;
SoftwareSerial GPS(RXPin, TXPin);             //for GPS
void setup() {
 Serial.begin(9600);              //for GPS
  GPS.begin(GPSBaud);             //for GPS

}

void loop() {

//  while (GPS.available() > 0){            //for GPS
//    gps.encode(GPS.read());
//    if (gps.location.isUpdated()){
//      Serial.print("Latitude= ");
//      Latitude=(gps.location.isUpdated()); 
//      
//      //Serial.print(gps.location.lat(), 6);
//      Serial.print(" Longitude= "); 
//      Longitude=(gps.location.lng(), 6);
//      //Serial.println(gps.location.lng(), 6);
//    }
//  }                                             //for GPS

 boolean k;
 k=valuecheck(28.12,74.28);
 if(k==false){
  Serial.print("Access denied...Try again later");
  }
 else if(k==true){

  gsmsend(28.12,74.28);
 //GSM sending code...........Good night!!
  
  }

        //sending values of longitude and latitude to the
        //function
    
}//void loop ending



                     //FUNCTIONS

                     //Function 1

boolean valuecheck(float x, float y){

  int rows=5;
  int columns=5;
  float fetched1=x;
  float fetched2=y;
  boolean result=true;

                        //preset GPS values

  float prelong[]={74.28, 75.28, 76.28, 77.28, 78.28};
  float prelat[]={28.12, 29.12, 30.12 ,31.12 ,32.12};
                       //checking
                       
for(int i=0;i<rows;i++){
  if(prelong[i]==fetched1 && prelat[i]==fetched2){
       // result=false;
        return false;
    }
   else {
    //result=true;
    return true;
    }
  } //end of i for loop

 // return result;

  
} //ending of valuecheck



                                                                                           //Function 2


void  gsmsend(float x, float y)

{
  float fetched1=x;
  float fetched2=y;
  //Set Exact Baud rate of the GSM/GPRS Module.
  Serial.begin(9600);  
  Serial.print("\r");
  delay(1000);                  
  Serial.print("AT+CMGF=1\r");    
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number &  ZZ to 2 digit country code*/
  Serial.print("AT+CMGS=\"+917016377520\"\r");    
  delay(1000);
  //The text of the message to be sent.
  Serial.print("Longitude=>");
  Serial.print( fetched2);
  Serial.print("Latitude=>");
  Serial.print(fetched1);   
  delay(1000);
  Serial.write(0x1A);
  delay(1000); 
  boolean temp= gsmrec();
  if(temp=="#Yes*"||temp=="#yes*")
  {
    Serial.print("Access approved...Enjoy mf");
    }
  else
  {
    Serial.print("Access denied...better luck next time mf");
    }

}

String gsmrec(void)
{
  char str[15];
  int i = 0;
  Serial.begin(9600);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(2000);
  Serial.println("AT+CMGF=1");
  delay(1000);

   
    i = 0;      //while loop was there
   delay(1000);
   
//String msg= serialEvent();
 while(Serial.available()) 
  {
    if(Serial.find("#"))
    {
      delay(1000);
      while (Serial.available()) 
      {
        char inChar=Serial.read();
        str[i++]=inChar;
        if(inChar=='*')
        {
          return((String)str);
         exit;
          
        } 
       } 
     }
   
  }
}
    
  
