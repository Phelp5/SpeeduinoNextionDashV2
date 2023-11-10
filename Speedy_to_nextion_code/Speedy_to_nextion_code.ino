     

 
#define PACKETLENGTH 75                      
#define NO2C_Serial3 Serial3                                                                                     
#define NEXTION_Serial2 Serial2                                                                                  

 int  cltbar, tpsbar,rpmbar,fuelbar;                                                                           
 unsigned int    freeRAM, TPS, advance, tpsDOT,ethanolPct, flexCorrection,flexIgnCorrection, afrTarget,rpmDOT,
 idleLoad, testOutputs, baro, O2_2, O2,  VE, corrections, AEamount,RPM, PW1,battery10,batCorrection,
 wueCorrection, iatCorrection, egoCorrection,canin0, canin1, canin2, canin3, canin4,
 canin5, canin6, canin7, canin8,canin9, canin10, canin11, canin12, canin13, canin14,
 canin15, getNextError ;
  
  byte     engine, spark, boostTarget, boostDuty, loopsPerSecond, coolant, IAT, MAP,dwell, secl,tpsADC ;
  boolean  Running, Crank, Launch_hard, Launch_soft, Limit_hard, Limit_soft, Boostcut_spark, warmup ,Error, Ase, Sync;
  boolean  status1; 
  
int rpm1 = 0;                                                 // this is to enable 2x rpm outputs, one for gauge, one for number display                                                                         

int PWR_LED = 13;
const int ProcessNO2C = 100;

int  databox;                                                            
byte  fullStatus[PACKETLENGTH];                                         
                                                                       

void setup() {

  
 Serial.begin(115200);                                         // all Baud rates need to be set to 115200
 NEXTION_Serial2.begin(115200);                               
 NO2C_Serial3.begin(115200);                                 // Mega2560 Serial3 to Speedy serial3 data output.  tx3 to rx3 & rx3 to tx3 

 Serial.print(F("Speeduino 2022.07-ser"));                 // Version of Speeduino I'm currently using
}
           

void loop() {
NO2C_ECU_SERIAL3();                                                  // run NO2C_ECU_SERIAL() Loop
    }

void NO2C_ECU_SERIAL3(){                                                  // loop begins
    
  if (NO2C_Serial3.available() >= 0) {                                  //Serial Check, if found, write A to get data list. {}
    pinMode(PWR_LED, OUTPUT);                                          
    digitalWrite(PWR_LED, 1);                                              
   
 NO2C_Serial3.write("A");                                           // Sending "A" for the 'simple data set' if using "n" or "r" modifications may be needed
 databox = (NO2C_Serial3.read());                                  
 for (int databox = 0; databox <PACKETLENGTH; databox++)          
 fullStatus[databox] = NO2C_Serial3.read();                      
 delay(ProcessNO2C);                                            
                       
// the list below only support "A" command.

       
  secl         = fullStatus[0];                                                             //increment seconds
  status1      = fullStatus[1];                                                            // bitfield status1
  engine       = fullStatus[2];                                                           // engine bitfield status
  dwell        = fullStatus[3];                                                          // igntion dwell
  MAP          = ((fullStatus[5] << 8) | (fullStatus[4]));                                   // engine MAP kPa (2bytes) so we group fullStatus 4&5 together
  IAT            = fullStatus[6];                                                         // Intake Temp
  coolant        = fullStatus[7];                                                        // coolant Temp
  batCorrection  = fullStatus[8];                                                       // batt corr
  battery10      = fullStatus[9];                                                      // batt voltage
  O2             = fullStatus[10];                                                    // O2 afr
  egoCorrection   = fullStatus[11];                                                     // ego corr
  iatCorrection   = fullStatus[12];                                                    // iat corr
  wueCorrection  = fullStatus[13];                                                    // warmup enrich corr
  RPM          = ((fullStatus[15] << 8) | (fullStatus[14]));                           // rpm (2 bytes)       "                           "
  AEamount      = fullStatus[16];                                                   // AE
  corrections   = fullStatus[17];                                                  // correction
  VE          = fullStatus[18];                                                      // VE
  afrTarget   = fullStatus[19];                                                     // afr Target
  PW1         = ((fullStatus[21] << 8) | (fullStatus[20]));                          // pulse width1
  tpsDOT           = fullStatus[22];                                              // tpsDOT
  advance          = fullStatus[23];                                             // timing adv
  TPS              = fullStatus[24];                                            // throttle
 loopsPerSecond    = ((fullStatus[26] << 8) | (fullStatus[25]));                    // loops Per Second  (2 bytes)
 freeRAM           = ((fullStatus[28] << 8) | (fullStatus[27]));                   // free ram    (2bytes)
 boostTarget       = fullStatus[29];                                            // boost target
 boostDuty         = fullStatus[30];                                           // boost duty
 spark             = fullStatus[31];                                          // spark bitfield
 rpmDOT            = ((fullStatus[33] << 8) | (fullStatus[32]));             // rpm dot
 ethanolPct        = fullStatus[34];                                           // ethanol content%
 flexCorrection    = fullStatus[35];                                          // flex fuel corr
 flexIgnCorrection = fullStatus[36];                                         // flex ign corr
 idleLoad        = fullStatus[37];                                          // idle load
 testOutputs      = fullStatus[38];                                        // test outputs
 O2_2            = fullStatus[39];                                           // O2_2  afr2
 baro            = fullStatus[40];                                          // baro
 canin0          = ((fullStatus[42] << 8) | (fullStatus [41]));            // auxin 0
 canin1          = ((fullStatus[44] << 8) | (fullStatus [43]));           // auxin  1
 canin2          = ((fullStatus[46] << 8) | (fullStatus [45]));          //  auxin  2
 canin3          = ((fullStatus[48] << 8) | (fullStatus [47]));         //   "   "   3
 canin4          = ((fullStatus[50] << 8) | (fullStatus [49])); 
 canin5          = ((fullStatus[52] << 8) | (fullStatus [51])); 
 canin6          = ((fullStatus[54] << 8) | (fullStatus [53])); 
 canin7          = ((fullStatus[56] << 8) | (fullStatus [55])); 
 canin8          = ((fullStatus[58] << 8) | (fullStatus [57])); 
 canin9          = ((fullStatus[60] << 8) | (fullStatus [59])); 
 canin10          = ((fullStatus[62] << 8) | (fullStatus [61])); 
 canin11          = ((fullStatus[64] << 8) | (fullStatus [63]));
 canin12          = ((fullStatus[66] << 8) | (fullStatus [65])); 
 canin13          = ((fullStatus[68] << 8) | (fullStatus [67])); 
 canin14          = ((fullStatus[70] << 8) | (fullStatus [69])); 
 canin15          = ((fullStatus[72] << 8) | (fullStatus [71]));          // auxin 15
 tpsADC           = fullStatus[73];                                      // tpsADC voltage
 getNextError     = fullStatus[74];                                     //  get error
                                 
                                       //STATUS BITS
//---------------------------(engine) is a bitfield status- it contains muplitple bits each for a different engine running status------------------------------
                       Running        = bitRead(engine, 0);   // bit status when engine is Running
                       Crank          = bitRead(engine, 1);
                       Ase            = bitRead(engine, 2);
                       warmup         = bitRead(engine, 3);
//---------------------------(spark) is a bitfield status- it contains muplitple bits each for differnt spark status------------------------------ 
                       Launch_hard    = bitRead(spark, 0);
                       Launch_soft    = bitRead(spark, 1);
                       Limit_hard     = bitRead(spark, 2);
                       Limit_soft     = bitRead(spark, 3);
                       Boostcut_spark = bitRead(spark, 4);
                       Error          = bitRead(spark, 5);
                       Sync           = bitRead(spark, 7);

 
                                                  
 // Nextion Obj info below,  
    
  NEXTION_Serial2.print("kpa.txt=");                                            
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(MAP);                                                  //map kpa readout
  NEXTION_Serial2.write(0x22);                                                 // if the nextion gauge you created is a (.txt=) you need to write (0x22) after to the serial port
  NEXTION_Serial2.write(0xff);                                                 // write (0xff) x3 times for each val or txt
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  NEXTION_Serial2.print("clt.val=");                                          //   for bar gauge
  cltbar = map(coolant - 40 , -40, 220, 0, 100);                             //  offset -40 Celcius readout with map for 0 - 100% bar gauge
  NEXTION_Serial2.print(cltbar);
   NEXTION_Serial2.write(0xff);                    
  NEXTION_Serial2.write(0xff);                                             // as above send (0xff)everytime 3x
  NEXTION_Serial2.write(0xff);
 
  NEXTION_Serial2.print("afr.txt=");
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(O2 / 10.0);                                       //(afr/10.0) needed to give decimal
  NEXTION_Serial2.write(0x22);                    
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  NEXTION_Serial2.print("batt.txt=");
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(battery10 / 10.0);                              // as above 
  NEXTION_Serial2.write(0x22);  
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  NEXTION_Serial2.print("tps.val=");                        // .val=  (number gauge)  gauge name: tps
  tpsbar = map(TPS, 0, 100, 0, 100);
  NEXTION_Serial2.print(tpsbar);                           //bar gauge
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  NEXTION_Serial2.print("VE.txt=");                    
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(VE);
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  NEXTION_Serial2.print("tps1.txt=");                    
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(TPS);
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  
  NEXTION_Serial2.print("ign.txt=");                    
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(advance);
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  
  NEXTION_Serial2.print("iat.txt=");
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(IAT - 40);                    // offset -40 for C reading
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

  
  NEXTION_Serial2.print("pw1.txt=");              
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.print(PW1);
  NEXTION_Serial2.write(0x22);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);

   
 rpm1=map(RPM, 0, 7500, 226, 497);                                        //in order to have both rpm gauge and numbers as nextion can only use one, once.
  
  NEXTION_Serial2.print("tach.val=");              // tach - number value
  NEXTION_Serial2.print(rpm1);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  
  NEXTION_Serial2.print("rpm.val=");             // gauge name : rpm
  rpmbar = map(RPM, 0, 8000, 0, 100);           // just a normal bar gauge mapped for 0 - 8000rpm
  NEXTION_Serial2.print(rpmbar);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  
                            //Basic Bits for warnings etc.
  
if (Launch_soft){  
  NEXTION_Serial2.print("vis LaunchS,1");                   // create a image name: LaunchS   display as picture gauge for Lanuch_soft limit
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis LaunchS,0");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
//--------------------------------------HARD LAUNCH-------------------------------------------------

if (Launch_hard){
  NEXTION_Serial2.print("vis LaunchH,1");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis LaunchH,0");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
 //-----------------------------------------SOFT REV LIMIT--------------------------------------------------------
 if (Limit_soft){
  NEXTION_Serial2.print("vis RevS,1");
 NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis RevS,0");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }  
  //-------------------------------------HARD REV LIMIT--------------------------------------------------
if (Limit_hard){
  NEXTION_Serial2.print("vis RevH,1");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis RevH,0");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
//-----------------------------------BOOSTCUT-------------------------------------------
if (Boostcut_spark){
  NEXTION_Serial2.print("vis BoostCut,1");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis BoostCut,0");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  //------------------------------------ASE--------------------------------------------------
if (Ase){
  NEXTION_Serial2.print("vis Ase,1");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis Ase,0");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
//-------------------------------------WARMUP--------------------------------------------------------------
if (warmup){
   NEXTION_Serial2.print("vis Warmup,1");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis Warmup,0");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
//--------------------------------ERROR---------------------------------------
if (Error){
  NEXTION_Serial2.print("vis Error,1");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis Error,0");
   NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
//-------------------------------------SYNC-------------------------------------------------  
  if (Sync){
  NEXTION_Serial2.print("vis Sync,1");                                      // all status gauge are same as launchS picture gauge
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis Sync,0");                           
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
//----------------------------------------------------Running--------------------
if (Running){
  NEXTION_Serial2.print("vis Running,1");                 // create an picture named: Running to display as a engine runnning status an seen on tunerstudio
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis Running,0"); 
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  //-----------------------------------------------------CRANKING-------------------------
  if (Crank){         //Crank
  NEXTION_Serial2.print("vis Cranking,1");
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  }
  else
  { 
  NEXTION_Serial2.print("vis Cranking,0");                
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);
  NEXTION_Serial2.write(0xff);


  }
  }
  delay(50);           
   while (NO2C_Serial3.available()>PACKETLENGTH)        // clear serial buffer for new data
   {
    NO2C_Serial3.read();                      
    }
}
