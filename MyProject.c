
void run();
void fire();
void close();
void open();
void innerPanelButtons(short int floor);
void upDownButtons(short int but);
void light_currentFloor();
void decide_nextfloor();
void go_next();
void waitsecond();

short int up=1;
short int alarmed=0;
short int floorButtons[6]={0,0,0,0,0,0};
short int innerButtons[4]={0,0,0,0};
short int curfloor=0;
short int nextfloor=0;


void fire(){

}

void close(){

}

void waitsecond(){
     Delay_ms(1000);
}

void innerPanelButtons(short int floor){
     switch (floor){
      case 0: innerButtons[0]=1; break;
      case 1: innerButtons[1]=1; break;
      case 2: innerButtons[2]=1; break;
      case 3: innerButtons[3]=1; break;
      default : break;
     }
}
void upDownButtons(short int but){
     switch (but){
      case 0: floorButtons[0]=1; break;
      case 1: floorButtons[1]=1; break;
      case 2: floorButtons[2]=1; break;
      case 3: floorButtons[3]=1; break;
      case 4: floorButtons[4]=1; break;
      case 5: floorButtons[5]=1; break;
      default : break;
     }
}
void interrupt(){
     PORTB.RB2=~PORTB.RB2;
     if(PORTB.RB7==1){
     fire();
     }
     if(PORTA.RA0==1){
     PORTB.RB1=1;
     innerPanelButtons(0);
     }
     if(PORTA.RA1==1){
     innerPanelButtons(1);
     }
     if(PORTA.RA2==1){
     innerPanelButtons(2);
     }
     if(PORTA.RA3==1){
     innerPanelButtons(3);
     }
     if(PORTC.RC0==1){
     upDownButtons(0);
     }
     if(PORTC.RC1==1){
     upDownButtons(1);
     }
     if(PORTC.RC2==1){
     upDownButtons(2);
     }
     if(PORTC.RC3==1){
     upDownButtons(3);
     }
     if(PORTC.RC4==1){
     upDownButtons(4);
     }
     if(PORTC.RC5==1){
     upDownButtons(5);
     }
     if(PORTB.RB6==1){
     close();
     }
     if(PORTB.RB5==1){
     open();
     }
     INTCON.INTE=1;
     INTCON.INTF=0;
}

void initialize(){
     //interuppt enabled
     INTCON.GIE=1;
     INTCON.INTE=1;
     //Port B :- RB0 : interrupt pin, RB1-4: 0-3 floor led in inner panel
     //RB5-7 : open, close, fire switch in inner panel
     TRISB = 0;
     TRISB.RB0=TRISB.RB5=TRISB.RB6=TRISB.RB7=1;
     PORTB=0;
     //PORTB.RB1=PORTB.RB2=PORTB.RB3=PORTB.RB4=0;
     //PortA RB0-3 : floor buttons from  0-3 in inner pannel
     TRISA = 0xff;
     //PortD 0-3 goes to yellow(door open) LEDs 4-7 goes to RED (lift came) LEDs
     TRISD = 0;
     PORTD = 0;
     //PortC 0-2 goes to down buttons of floor 1-3, 3-5 goes up buttons of floor 0-2
     TRISC = 1;
     PORTC = 0;
}
void main() {
     initialize();
     PORTB.RB4=1;

     while(1){
     run();
     }
     
}

void run(){
 light_currentFloor();
 decide_nextfloor();
 go_next();
 PORTD.RD0=1;
 PORTD.RD4=1;
 waitsecond();
 PORTD.RD0=0;
 waitsecond();
 PORTD.RD1=1;
 PORTD.RD4=0;
 PORTD.RD5=1;
 waitsecond();
 PORTD.RD1=0;
 waitsecond();
 PORTD.RD2=1;
 PORTD.RD5=0;
 PORTD.RD6=1;
 waitsecond();
 PORTD.RD2=0;
 waitsecond();
  PORTD.RD3=1;
 PORTD.RD6=0;
 PORTD.RD7=1;
 waitsecond();
 PORTD.RD3=0;
 waitsecond();
 
 
}

void go_next(){
     if(curfloor==nextfloor){
           innerButtons[curfloor]=0;
           open();
     }else if(curfloor<nextfloor){
           up=1;
           delay_ms(4000);
           curfloor++;
     }else{
           up=0;
           delay_ms(4000);
           curfloor--;
     }

}
void light_currentFloor(){
     innerButtons[curfloor]=0;
     
     PORTD.RD4=PORTD.RD5=PORTD.RD6=PORTD.RD7=0;
     switch(curfloor){
          case 0: PORTD.RD4=1; break;
          case 1: PORTD.RD5=1; break;
          case 2: PORTD.RD6=1; break;
          case 3: PORTD.RD7=1; break;
          default: break;
     }
}

void decide_nextfloor(){
     short int i;
     if(up==1){
               for(i=curfloor;i<4;i++){
                if(innerButtons[i]==1){
                 nextfloor=i;
                 return;
                }
               }
               
               for(i=0;i<curfloor;i++){
                 if(innerButtons[i]==1){
                 nextfloor=i;
                 return;
                 }
               }
     }else if(up==0){
               for(i=curfloor;i>=0;i--){
                if(innerButtons[i]==1){
                 nextfloor=i;
                 return;
                }
               }

               for(i=4;i>curfloor;i--){
                 if(innerButtons[i]==1){
                 nextfloor=i;
                 return;
                 }
               }
     }else{
               for(i=0;i<6;i--){
                if(floorButtons[i]==1){
                 nextfloor=i;
                 return;
                }
               }
     }
}
void open(){
     switch(curfloor){
      case 0: PORTD.RD0=1; break;
      case 1: PORTD.RD1=1; break;
      case 2: PORTD.RD2=1; break;
      case 3: PORTD.RD3=1; break;
      default: break;
     }
     delay_ms(5000);
     PORTD.RD0=PORTD.RD1=PORTD.RD2=PORTD.RD3=0;
}