#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// SD Card Setup
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=725.0000228881836,314.00000953674316
AudioPlaySdWav           playSdWav2;     //xy=740.0000228881836,430.0000114440918
AudioMixer4              mixer4;         //xy=939.0001907348633,450.0000114440918
AudioMixer4              mixer3;         //xy=956.0001907348633,332.00000762939453
AudioEffectFlange        flange2;        //xy=1153,419
AudioEffectFlange        flange1;        //xy=1154,322
AudioMixer4              mixer1;         //xy=1366,385
AudioEffectFreeverb      freeverb1;      //xy=1507,426
AudioMixer4              mixer2;         //xy=1658,383
AudioEffectDelay         delay1;         //xy=1716,575
AudioOutputI2S           i2s1;           //xy=1971,381
AudioConnection          patchCord1(playSdWav1, 0, mixer3, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer3, 1);
AudioConnection          patchCord3(playSdWav2, 0, mixer4, 0);
AudioConnection          patchCord4(playSdWav2, 1, mixer4, 1);
AudioConnection          patchCord5(mixer4, flange2);
AudioConnection          patchCord6(mixer3, flange1);
AudioConnection          patchCord7(flange2, 0, mixer1, 3);
AudioConnection          patchCord8(flange1, 0, mixer1, 1);
AudioConnection          patchCord9(mixer1, freeverb1);
AudioConnection          patchCord10(mixer1, 0, mixer2, 0);
AudioConnection          patchCord11(freeverb1, 0, mixer2, 1);
AudioConnection          patchCord12(mixer2, delay1);
AudioConnection          patchCord13(delay1, 0, mixer2, 3);
AudioConnection          patchCord14(delay1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1515,633
// GUItool: end automatically generated code


// number of "voices" in the chorus which INCLUDES the original voice
int n_chorus = 2;

//Define Initial Flange Characteristics
#define FLANGE_DELAY_LENGTH (2*AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short f_l_delayline[FLANGE_DELAY_LENGTH];
short f_r_delayline[FLANGE_DELAY_LENGTH];

int s_idx = 2*FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = 3;

//USB Host Setup
#include "USBHost_t36.h"
USBHost myusb;
USBHub hub1(myusb);
USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);
USBHIDParser hid3(myusb);
USBHIDParser hid4(myusb);
#define COUNT_JOYSTICKS 4
JoystickController joysticks[COUNT_JOYSTICKS](myusb);
int user_axis[64];
uint32_t buttons_prev = 0;

USBDriver *drivers[] = {&hub1, &joysticks[0], &joysticks[1], &joysticks[2], &joysticks[3], &hid1, &hid2, &hid3, &hid4};
#define CNT_DEVICES (sizeof(drivers)/sizeof(drivers[0]))
const char * driver_names[CNT_DEVICES] = {"Hub1", "joystick[0D]", "joystick[1D]", "joystick[2D]", "joystick[3D]",  "HID1", "HID2", "HID3", "HID4"};
bool driver_active[CNT_DEVICES] = {false, false, false, false};

// Lets also look at HID Input devices
USBHIDInput *hiddrivers[] = {&joysticks[0], &joysticks[1], &joysticks[2], &joysticks[3]};
#define CNT_HIDDEVICES (sizeof(hiddrivers)/sizeof(hiddrivers[0]))
const char * hid_driver_names[CNT_DEVICES] = {"joystick[0H]", "joystick[1H]", "joystick[2H]", "joystick[3H]"};
bool hid_driver_active[CNT_DEVICES] = {false};
bool show_changed_only = false;

uint8_t joystick_left_trigger_value[COUNT_JOYSTICKS] = {0};
uint8_t joystick_right_trigger_value[COUNT_JOYSTICKS] = {0};
uint64_t joystick_full_notify_mask = (uint64_t) - 1;


//Joystick Input
float x_input = 0; //joystick x position
float y_input = 0; //joystick y position
float z_input = 0; //joystick yaw position(twisting bit)
float slider_input =0; //slider posiyion
float button_input = 0; //button input

//Throttle Input
float t_x_input = 0; //Throttle joystick x position
float t_y_input = 0; // Throttle joystick y position
float throttle_input = 0; //Throttle position
float pattle_input = 0; //Paddle position
float wheel_input = 0; //Wheel position
float throttle_button = 0; //Throttle Button


void setup() {
  // Setup SD Card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // Setup Music stuff
  AudioMemory(250);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  mixer1.gain(1,0.5);
  mixer1.gain(3,0.5);
  mixer2.gain(0, 0.45);
  mixer2.gain(1, 0.05);
  mixer2.gain(3,0.5);
  mixer3.gain(0,0.5);
  mixer3.gain(1,0.5);
  mixer4.gain(0,0.5);
  mixer4.gain(1,0.5);  
  delay1.delay(0, 400);
  delay(700);

  //Begin Flange Effect
  flange1.begin(f_l_delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  flange2.begin(f_l_delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  flange1.voices(0,0,0);
  flange2.voices(0,0,0);

  //Set freeverb
  freeverb1.roomsize(0.7);
  freeverb1.damping(0.3);
  
  //Start USB Host
  myusb.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  //Get input from usb host
  myusb.Task();
  PrintDeviceListChanges();

  //Get Throttle Input
  float t_x_input = joysticks[1].getAxis(0); //Throttle joystick x position
  float t_y_input = joysticks[1].getAxis(1); // Throttle joystick y position
  float throttle_input = joysticks[1].getAxis(2); //Throttle position
  float pattle_input = joysticks[1].getAxis(5); //Paddle position
  float wheel_input = joysticks[1].getAxis(7); //Wheel position
  float throttle_button = joysticks[1].getButtons(); //Throttle button

  //Normalize Throttle Inputs
  float t_x_val = t_x_input/1023; //Throttle joystick x position
  float t_y_val = t_y_input/1023; // Throttle joystick y position
  float throttle_val = throttle_input/65535; //Throttle position
  float pattle_val = pattle_input/1023; //Paddle position
  float wheel_val = wheel_input/1023; //Wheel position

  //Get Joystick Input
  float x_input = joysticks[0].getAxis(0); //Joystick x position
  float y_input = joysticks[0].getAxis(1); // Joystick y position
  float z_input = joysticks[0].getAxis(5); // Yaw Position
  float slider_input = joysticks[0].getAxis(6); //Slider position
  float button_input = joysticks[0].getButtons(); //Button position

  //Normalize Joystick Inputs
  float x_val = x_input/16383; //Throttle joystick x position
  float y_val = y_input/16383; // Throttle joystick y position
  float z_val = z_input/255; //Throttle position
  float slider_val = slider_input/255; //Paddle position

  
  //Continuously loop Samples
  if (playSdWav1.isPlaying() == false) {
    //Serial.println("Start playing 1");
    playSdWav1.play("RYTHM1.WAV");
    delay(10); // wait for library to parse WAV info
  }
  if (playSdWav2.isPlaying() == false) {
    //Serial.println("Start playing 2");
    playSdWav2.play("SOFT2.WAV");
    delay(10); // wait for library to parse WAV info
  }
  //Change freeverb mixing
  float dry = throttle_val/2;
  float wet = 0.5 - dry;
  float echo = slider_val/2;
  mixer2.gain(0, dry);
  mixer2.gain(1, wet);
  mixer2.gain(3, echo);

  //Change Sample mixing
  float gain1 = z_val;
  float gain2 = 1 - gain1;
  mixer1.gain(1,gain1);
  mixer1.gain(3,gain2);

  
  //Change freeverb settings
  float room = x_val;
  float damp = y_val;
  freeverb1.roomsize(room);
  freeverb1.damping(damp);

  //Change Flange Settings
  int s_idx = t_x_val*FLANGE_DELAY_LENGTH;
  int s_depth = wheel_val*FLANGE_DELAY_LENGTH;
  double s_freq = 3*t_y_val;

  //If button is pressed activate flange
  if(button_input == 1) {
    flange1.voices(s_idx,s_depth,s_freq);
    flange2.voices(s_idx,s_depth,s_freq);
  }

  //If button isn;t pressed deactivate flange
  if(button_input == 0) {
    flange1.voices(0,0,0);
    flange2.voices(0,0,0);
  }
}

//=============================================================================
// Show when devices are added or removed
//=============================================================================
void PrintDeviceListChanges() {
  for (uint8_t i = 0; i < CNT_DEVICES; i++) {
    if (*drivers[i] != driver_active[i]) {
      if (driver_active[i]) {
        Serial.printf("*** Device %s - disconnected ***\n", driver_names[i]);
        driver_active[i] = false;
      } else {
        Serial.printf("*** Device %s %x:%x - connected ***\n", driver_names[i], drivers[i]->idVendor(), drivers[i]->idProduct());
        driver_active[i] = true;

        const uint8_t *psz = drivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = drivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = drivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }

  for (uint8_t i = 0; i < CNT_HIDDEVICES; i++) {
    if (*hiddrivers[i] != hid_driver_active[i]) {
      if (hid_driver_active[i]) {
        Serial.printf("*** HID Device %s - disconnected ***\n", hid_driver_names[i]);
        hid_driver_active[i] = false;
      } else {
        Serial.printf("*** HID Device %s %x:%x - connected ***\n", hid_driver_names[i], hiddrivers[i]->idVendor(), hiddrivers[i]->idProduct());
        hid_driver_active[i] = true;

        const uint8_t *psz = hiddrivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = hiddrivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = hiddrivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }
}
