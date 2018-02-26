 // LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;



/*declareatio of functions in the program */
int get_password();
  int time,counter=0;
void clear(char []);
void caculator();
char  recieve();

char keypadPort at PORTD;
char kPad[16]={'7','8','9','/','4','5','6','*','1','2','3','-','c','0','=','+'};/* keu pad chars as a matrix to make operation more efficint */

char password[6]={'\0','\0','\0','\0','\0'};
char pass[6] = {"11111"};   /* we can make password any combination of key pad chars  not just numbers with any length  */
//char pass[]="123";
int get_password()
{

   int temp=0 ;   /*store number of attempts of wrong password */
   int i ,length;       /*index  and length of password array */

   while(temp<3){
       length=strlen(pass);
       loop:
         Lcd_Cmd(_LCD_CLEAR);
         Lcd_Out(1, 1, "Enter Password :");

         for(i=0;i<length;i++)
         {
               while (password[i] == 0)
               {
                password[i] = Keypad_Key_Click();
               }
               password[i]=kPad[(password[i]-1)];  //   password[i]-1 is an index to get the correct number from kwyPad array
               // i.e if password[i]=1 , then kPad[password[i]-1]='7' and so on
              Lcd_Chr(2, i+1, password[i] );
          }

        if(strcmp(password,pass) == 0) {
             return 1;
          }
        else
        {
           temp++; /* a wrong password */
           Lcd_Cmd(_LCD_CLEAR);
           Lcd_Out(1,1, "wrong password ");
           Lcd_Out(2,1, "Try again");
           delay_ms(500);
           clear(password);
         }
  }
    /* if the user enter wrong passord 3 times
    * turn oiff the system and ask him to reset it and try agian */
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1,1,"Wrong pass 3 times ");
    Lcd_Out(2,1,"reset the system");
    delay_ms(300);
    Lcd_Cmd(_LCD_TURN_OFF);
     //go into infinte loop until user reset the system
     while(1){
        ;
     }
}
/*a general clear method to clear an array */
void clear(char s[]){
  int i,length=strlen(s);
  for(i=0; i<length ;i++)
        s[i]='\0';
}
 //for initialize the intertupt timer
 void initialize_tmI(void){
 TMR0IE_bit=1; // Enable timer 0 interrupt
 GIE_bit=1; //Enable Global Interrupt
 T0CS_bit=0; // Select f/4 clock for the TMR0
 PSA_bit=0; // Prescaler is assigned to the Timer0 module
 PS0_bit=0; // Set pre-scaler to 8
 PS1_bit=1; // PS2,PS1,PS0 = 010
 PS2_bit=0; //
 TMR0=6; //counter starting value
}

char kp;  /* kep pad entered key */
char ch, op;
int x = 0, y = 0,result=0,  var = 0;
char res[7];


    //timer method from zero to 10
void lcd_counter(){
                while(1){

 if(counter==100){ // check if the counter reaches 125
 counter=0; // start counter from the beginning
 time=time++; // increase time one second
 //when time reach 10 sec stop the motor and lcd counter
   if(time==11){
   portc.f0=0;
   break;
 }
 IntToStrWithZeros(time,kPad); // convert the number of seconds to string
 Lcd_Out(2,1,kPad); // display the number of seconds
 }
}
       }


void main() {
   trisc.f0=0;
   portc.f0=0;

     Lcd_Init();
     Keypad_Init();
     LCD_Cmd(_LCD_CURSOR_OFF);
     get_password();
     Lcd_Cmd(_LCD_CLEAR);
     portc.f0=1;
     Lcd_Out(1,1 , "Welcome ^_^ ");
     initialize_tmI();
     lcd_counter();

                                 }


     void interrupt() { // Interrupt handler
 if (INTCON.TMR0IF==1) { // check for timer 0 interrupt flag
 counter++; // increment 1 every interrupt
 INTCON.TMR0IF=0; // reset the TMR0IF flag
 TMR0=6; // store 6 in the TMR0 register
 }   }

