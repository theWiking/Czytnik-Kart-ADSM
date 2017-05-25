#include <SoftwareSerial.h>
 #define userNumber  2
 #define userAdminNumber 1
SoftwareSerial SoftSerial(11, 12);
unsigned char buffer[64];       // buffer array for data receive over serial port
int count = 0; 
//int userNumber=2;// counter for buffer array
char checkAdmin[userAdminNumber][15]={'','7','C','0','0','7','1','5','C','5','D','0','C',''};
int user[userNumber][14]={
  {2,55,67,48,48,55,49,65,67,65,49,48,48,3},
  {2,55,67,48,48,55,49,57,56,69,65,55,70,3}
};

int RED = 5;
int BLUE = 7;
int GREEN = 6;
int Flaga[userNumber]={0};
int FlagaAdmin[userAdminNumber]={0};
void setup()
{
   pinMode(RED, OUTPUT);
   pinMode(BLUE, OUTPUT);
   pinMode(GREEN, OUTPUT);
    SoftSerial.begin(9600);     // the SoftSerial baud rate
    Serial.begin(9600);         // the Serial port of Arduino baud rate.
}
 
void loop()
{
    // if date is coming from software serial port ==> data is coming from SoftSerial shield
    if (SoftSerial.available())              
    {
        while(SoftSerial.available())               // reading data into char array
        {
            buffer[count++] = SoftSerial.read();      // writing data into array
  
            if(count == 64)break;
    
        }
       //Serial.write(buffer, count);     // if no data transmission ends, write buffer to hardware serial port
       if(count==14){
        CheckBuffers();
        clearBufferArray();             // call clearBufferArray function to clear the stored data from the array
        count = 0;  
       }   
        // set counter of while loop to zero
    }
    if (Serial.available()) {            // if data is available on hardware serial port ==> data is coming from PC or notebook
   //SoftSerial.write(Serial.read());    // write it to the SoftSerial shield
    }
}
void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
}
void CheckBuffers(){
                
               
  Serial.print("Testing Cards\n");
  for(int userCheck=0;userCheck<userNumber;userCheck++){
    Flaga[userCheck]=0;
        for(int i=0;i<14;i++){
         // Serial.println(buffer[i]); /// do sprawdzania numerów z karty odkowować spisać dodać do odpowiedniej rubryki i zablokować
              if(buffer[i]!=user[userCheck][i]){
                Flaga[userCheck]++;
                }
            
          }
  }
  for(int userAdminCheck=0;userAdminCheck<userAdminNumber;userAdminCheck++){
    FlagaAdmin[userAdminCheck]=0;
    for(int i=0;i<14;i++){
             if(buffer[i]!=checkAdmin[userAdminCheck][i]){
                FlagaAdmin[userAdminCheck]++;
               
              }
    }
  }
  int i=0;
  for(;i<userNumber-1;i++){
    if(Flaga[i]==0)break;
  }
  int j=0;
  for(;j<userAdminNumber-1;j++){
    if(Flaga[j]==0)break;
  }

            //Pod tymi ifami można podpiąc np ruch cewką zamka aby się otworzyły. 
              if(Flaga[i]==0){
                  Serial.println("\n\nWszystko Ok prosze wejsc\n");
                    blinkAcess();
                 }
               else if(FlagaAdmin[j]==0){
                Serial.println("\n\nWitamy Szanowego admina\n");
                blinkAdmin();
               }
               else if(Flaga[i]!=0||FlagaAdmin!=0){
                Serial.println("\n\nOdmowa dostepu\n");
                blinkDenay();
               }      
}
void blinkDenay(){
  for(int q=0;q<5;q++){
    digitalWrite(RED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(RED, LOW);    // turn the LED off by making the voltage LOW
    delay(50);   
  }                
}
void blinkAcess(){
  for(int q=0;q<5;q++){
    digitalWrite(GREEN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(GREEN, LOW);    // turn the LED off by making the voltage LOW
    delay(50); 
  }
}
void blinkAdmin(){
  for(int q=0;q<5;q++){
    digitalWrite(BLUE, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(BLUE, LOW);    // turn the LED off by making the voltage LOW
    delay(50); 
  }
}

