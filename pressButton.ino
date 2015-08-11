/*
  This code does key press decoding using a matrix scanning method.
  
  This code can detect two simultaneous keypresses.
  
  For a character to be decoded, a key press on the thumb and another on the fingers has to be pressed.
  
  The key press is to be sent via BlueTooth to an Android phone to be read when typing sms.
  
  
  modified January 12, 2015
  by Denis Tran
 */
 
 //#define DEBUG 1

 int button1=0;
 int button2=0;
 int button3=0;
 int button4=0;
 int button5=0;
 int button6=0;
 int button7=0;
 int button8=0;
 int button9=0;
 
 // to read other finger presses
 int prev_finger = 0;
 int prev_button = 0;
 
 // to read thumb button presses
 int prev_thumb = 0;
 int prev_thumb_button = 0;
 
 // combined keypress
 int prev_encoded = 0;
 int encoded = 0;
 
 // the current character map is just like the iphone keyboard, with the 3 keyboards corresponding to the 3 levels on the thumb
 char charMap[100];

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, INPUT);
  pinMode(28, INPUT);
  pinMode(29, INPUT);
  pinMode(30, INPUT);  
  pinMode(31, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  for (int i = 0;i<100;i++)
  {
    charMap[i] = 0;
  }
  
//  thumb top row
  charMap[72]='q';
  charMap[73]='w';
  charMap[74]='e';
  charMap[81]='r';
  charMap[82]='t';
  charMap[83]='y';
  charMap[90]='u';
  charMap[91]='i';
  charMap[92]='o';
  charMap[97]='p';
  charMap[97]=8;// bksp
  
  charMap[69]='a';
  charMap[70]='s';
  charMap[71]='d';
  charMap[78]='f';
  charMap[79]='g';
  charMap[80]='h';
  charMap[87]='j';
  charMap[88]='k';
  charMap[89]='l';
  charMap[95]=8; // backspace
  charMap[96]=8; // backspace
  
  charMap[66]=' ';  // space
  charMap[67]='z';
  charMap[68]='x';
  charMap[75]='c';
  charMap[76]='v';
  charMap[77]='b';
  charMap[84]='n';
  charMap[85]='m';
  charMap[86]='!';
  charMap[93]='?';
  charMap[94]=8;

// thumb middle row  
  charMap[39]='1';
  charMap[40]='2';
  charMap[41]='3';
  charMap[48]='4';
  charMap[49]='5';
  charMap[50]='6';
  charMap[57]='7';
  charMap[58]='8';
  charMap[59]='9';
  charMap[64]='0';
  charMap[65]=8;  // bksp
  
  charMap[36]='-';
  charMap[37]=47; // /
  charMap[38]=':';
  charMap[45]=';';
  charMap[46]='(';
  charMap[47]=')';
  charMap[54]='$';
  charMap[55]='&';
  charMap[56]='@';
  charMap[62]=34; // "
  charMap[63]=8; // bksp

  charMap[33]=' ';
  charMap[34]='.';
  charMap[35]=',';
  charMap[42]='?';
  charMap[43]='!';
  charMap[44]=' ';
  charMap[51]=' ';
  charMap[52]=' ';
  charMap[53]=' ';
  charMap[60]=8;
  charMap[61]=8;

// thumb bottom row
  charMap[6]='[';
  charMap[7]=']';
  charMap[8]='{';
  charMap[15]='}';
  charMap[16]='#';
  charMap[17]='%';
  charMap[24]='^';
  charMap[25]='*';
  charMap[26]='+';
  charMap[31]='=';
  charMap[32]=8;// bksp
  
  charMap[3]='_';
  charMap[4]='92';
  charMap[5]='|';
  charMap[12]='~';
  charMap[13]='<';
  charMap[14]='>';
  charMap[21]='E';//euro
  charMap[22]='P';//pound
  charMap[23]='Y';// yen
  charMap[29]=8; // backspace
  charMap[30]=8; // backspace

  charMap[0]=' ';  // space
  charMap[1]='.';
  charMap[2]=',';
  charMap[9]='?';
  charMap[10]='!';
  charMap[11]=' ';
  charMap[18]=' ';
  charMap[19]=' ';
  charMap[20]=' ';
  charMap[27]=8;//backspace  
  charMap[28]=8;//backspace    
  Serial.begin(9600);
}

void printButton(int finger)// for all except the thumb
{
  button1=digitalRead(27);
  button2=digitalRead(28);
  button3=digitalRead(29);
  button4=digitalRead(30);
  button5=digitalRead(31);
  button6=digitalRead(32);
  button7=digitalRead(33);
  button8=digitalRead(34);
  button9=digitalRead(35);
  
  if ((prev_finger == finger)&&(button1||button2||button3||button4||button5||button6||button7||button8||button9) == 0)
  {// nothing was pressed
    //Serial.println("nothing pressed");
    prev_finger = 0;
    prev_button = 0;
  }
  else if (button1)
  {
    if (prev_finger != finger || prev_button !=1)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 1");
      
      #endif
      prev_finger = finger;
      prev_button = 1;
    }
  }
  else if (button2)
  {
    if (prev_finger != finger || prev_button !=2)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 2");
      
      #endif
      prev_finger = finger;
      prev_button = 2;
    }
  }
  else if (button3)
  {
    if (prev_finger != finger  || prev_button !=3)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 3");
      #endif
      
      prev_finger = finger;
      prev_button = 3;
    }
  }
  else if (button4)
  {
    if (prev_finger != finger || prev_button !=4)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 4");
      #endif
      prev_finger = finger;
      prev_button = 4;
    }
  }
  else if (button5)
  {
    if (prev_finger != finger || prev_button !=5)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 5");
      
      #endif
      
      prev_finger = finger;
      prev_button = 5;
    }
  }
  else if (button6)
  {
    if (prev_finger != finger || prev_button !=6)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 6");
      
      #endif
      prev_finger = finger;
      prev_button = 6;
    }
  }
  else if (button7)
  {
    if (prev_finger != finger || prev_button !=7)
    {
      #ifdef DEBUG
      
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 7");
      #endif
      
      prev_finger = finger;
      prev_button = 7;
    }
  }
  else if (button8)
  {
    if (prev_finger != finger || prev_button !=8)
    {
      #ifdef DEBUG
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 8");
      #endif
      prev_finger = finger;
      prev_button = 8;
    }
  }
  else if (button9)
  {
    if (prev_finger != finger || prev_button !=9)
    {
      #ifdef DEBUG
        Serial.print("finger ");
        Serial.print(finger);
        Serial.println("button 9");
      #endif
      prev_finger = finger;
      prev_button = 9;
    }
  }
}

void printThumbButton()// for thumb
{
  button1=digitalRead(27);
  button2=digitalRead(28);
  button3=digitalRead(29);
  button4=digitalRead(30);
  button5=digitalRead(31);
  button6=digitalRead(32);
  
  if ((button1||button2||button3||button4||button5||button6) == 0)
  {// nothing was pressed
    //Serial.println("nothing pressed");
     prev_thumb_button = 0;
  }
  else if (button1)
  {
    //Serial.println("ooo");
    if (prev_thumb_button !=1)
    {
      #ifdef DEBUG
        Serial.print("thumb ");
        Serial.println("button 1");
      #endif
      prev_thumb_button = 1;
    }
  }
  else if (button2)
  {
    if (prev_thumb_button !=2)
    {
      #ifdef DEBUG
        Serial.print("thumb ");
        Serial.println("button 2");
      #endif
      prev_thumb_button = 2;
    }
  }
  else if (button3)
  {
    if (prev_thumb_button !=3)
    {
      #ifdef DEBUG        
        Serial.print("thumb ");
        Serial.println("button 3");
      #endif
      prev_thumb_button = 3;
    }
  }
  else if (button4)
  {
    if (prev_thumb_button !=4)
    {
      #ifdef DEBUG        
        Serial.print("thumb ");
        Serial.println("button 4");
      #endif
      prev_thumb_button = 4;
    }
  }
  else if (button5)
  {
    if (prev_thumb_button !=5)
    {
      #ifdef DEBUG
        Serial.print("thumb ");
        Serial.println("button 5");
      #endif
      prev_thumb_button = 5;
    }
  }
  else if (button6)
  {
    if (prev_thumb_button !=6)
    {
      #ifdef DEBUG        
        Serial.print("thumb ");
        Serial.println("button 6");
      #endif
      prev_thumb_button = 6;
    }
  }  
}

void sendCharBT()
{
  if (prev_button != 0 && prev_thumb_button != 0)
  {
    // encode finger presses
    encoded = floor((prev_thumb_button-1)/2)*33 + (prev_finger-2)*9 + (prev_button-1);
 
    if (encoded != prev_encoded)
    {   
      // need to be replaced by an actual character from a table look-up
      #ifdef DEBUG      
        Serial.print("thumb ");
        Serial.print(prev_thumb_button);
        Serial.print(" finger ");
        Serial.print(prev_finger);
        Serial.print(" button ");
        Serial.print(prev_button);
        Serial.print("        ");
      #endif
      prev_encoded = encoded;
      Serial.println(charMap[encoded]);
    }
  }
  else
  {
    prev_encoded = 0;
  }
}

// the loop function runs over and over again forever
void loop() {

  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);

  // for each finger, check if any buttons are pressed
  // thumb
  pinMode(22,OUTPUT);
  digitalWrite(22, HIGH);   // turn the thumb on (HIGH is the voltage level)
  //check if any buttons are pressed
  printThumbButton();
  digitalWrite(22, LOW);
  pinMode(22,INPUT);
  
  pinMode(23,OUTPUT);
  digitalWrite(23, HIGH);   // turn the thumb on (HIGH is the voltage level)
  //check if any buttons are pressed
  printButton(2);
  digitalWrite(23, LOW);
  pinMode(23,INPUT);
    
  pinMode(24,OUTPUT);
  digitalWrite(24, HIGH);   // turn the thumb on (HIGH is the voltage level)
  //check if any buttons are pressed
  printButton(3);
  digitalWrite(24, LOW);
  pinMode(24,INPUT);
  
  pinMode(25,OUTPUT); 
  digitalWrite(25, HIGH);   // turn the thumb on (HIGH is the voltage level)
  //check if any buttons are pressed
  printButton(4);
  digitalWrite(25, LOW);
  pinMode(25,INPUT); 
  
  pinMode(26,OUTPUT); 
  digitalWrite(26, HIGH);   // turn the thumb on (HIGH is the voltage level)
  //check if any buttons are pressed
  printButton(5);
  digitalWrite(26, LOW);
  pinMode(25,INPUT); 
  
  sendCharBT();
  
  delay(10);
//  delay(1000);              // wait for a second
}
