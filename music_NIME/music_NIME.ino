#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable4;     //xy=149,145.8000087738037
AudioSynthWavetable      wavetable5;     //xy=150,202.80004692077637
AudioSynthWavetable      wavetable3;     //xy=151,104.80000686645508
AudioSynthWavetable      wavetable1;     //xy=154,20.400009155273438
AudioSynthWavetable      wavetable6;     //xy=154,246.80004692077637
AudioSynthWavetable      wavetable2;     //xy=155,61.80000686645508
AudioSynthWavetable      wavetable8;     //xy=158,325.8000478744507
AudioSynthKarplusStrong  string1;        //xy=158.00000381469727,384.0000114440918
AudioSynthWavetable      wavetable7;     //xy=159.00000381469727,287.8000478744507
AudioSynthKarplusStrong  string2;        //xy=160,426
AudioSynthWavetable      wavetable13; //xy=168,566
AudioSynthWavetable      wavetable15; //xy=169,648.9999618530273
AudioSynthWavetable      wavetable14; //xy=170,606.9999618530273
AudioSynthWavetable      wavetable16; //xy=170.00000381469727,685.999963760376
AudioMixer4              mixer2; //xy=352.00000953674316,245.00009536743164
AudioMixer4              mixer3;         //xy=365.0000114440918,389.0000534057617
AudioMixer4              mixer4; //xy=371.00004959106445,584.0000171661377
AudioMixer4              mixer1;         //xy=388.00000762939453,59.00002670288086
AudioMixer4              mixer5;         //xy=700.0000076293945,213.00000381469727
AudioOutputI2S           i2s1;           //xy=901.0000267028809,195.00000476837158
AudioConnection          patchCord1(wavetable4, 0, mixer1, 3);
AudioConnection          patchCord2(wavetable5, 0, mixer2, 0);
AudioConnection          patchCord3(wavetable3, 0, mixer1, 2);
AudioConnection          patchCord4(wavetable1, 0, mixer1, 0);
AudioConnection          patchCord5(wavetable6, 0, mixer2, 1);
AudioConnection          patchCord6(wavetable2, 0, mixer1, 1);
AudioConnection          patchCord7(wavetable8, 0, mixer2, 3);
AudioConnection          patchCord8(string1, 0, mixer3, 0);
AudioConnection          patchCord9(wavetable7, 0, mixer2, 2);
AudioConnection          patchCord10(string2, 0, mixer3, 1);
AudioConnection          patchCord11(wavetable13, 0, mixer4, 0);
AudioConnection          patchCord12(wavetable15, 0, mixer4, 2);
AudioConnection          patchCord13(wavetable14, 0, mixer4, 1);
AudioConnection          patchCord14(wavetable16, 0, mixer4, 3);
AudioConnection          patchCord15(mixer2, 0, mixer5, 1);
AudioConnection          patchCord16(mixer3, 0, mixer5, 2);
AudioConnection          patchCord17(mixer4, 0, mixer5, 3);
AudioConnection          patchCord18(mixer1, 0, mixer5, 0);
AudioConnection          patchCord19(mixer5, 0, i2s1, 0);
AudioConnection          patchCord20(mixer5, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=815.0000152587891,401.0000114440918
// GUItool: end automatically generated code



//Include wavetables
#include "Flute_samples.h"
#include "Trumpet_samples.h"
#include "drum_samples.h"

//set audio delays
const int hand_delay = 300;
//Set Wavetable frequencies
float base_freq = 261;
float base_freq2 = 261;
float string_freq = 100;
float drum_freq = 100;
float string_vol = 0.5;
const float f1 = 0.5;
const float f2 = 1.5;
const float f3 = 4/3;
const float f4 = 2;
const float f5 = 3;
const float f6 = 4;

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
//float slider_input =0; //slider posiyion
float joy_button = 0; //button input

//Throttle Input
//float t_x_input = 0; //Throttle joystick x position
//float t_y_input = 0; // Throttle joystick y position
float throttle_input = 0; //Throttle position
float pattle_input = 0; //Paddle position
//float wheel_input = 0; //Wheel position
float throttle_button = 0; //Throttle Button

//Set speed values
float prev_throttle = 0;
float prev_paddle = 0;
float prev_x = 0;
float prev_y = 0;
float prev_z = 0;
float throttle_speed = 0;
float paddle_speed = 0;
float joy_speed = 0;
float total_speed = 0;
float x_speed = 0;
float y_speed = 0;
float z_speed = 0;

//Setup Machine learning
#include <TensorFlowLite.h>
#include "model_data.h"
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

// Create an area of memory to use for input, output, and intermediate arrays.
// Finding the minimum value for your model may require some trial and error.
constexpr int kTensorArenaSize = 2 * 6024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {
  //Audio Setup
  AudioMemory(250);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  //Wavetable Group 1
  mixer1.gain(0,0.25); 
  mixer1.gain(1,0.25); 
  mixer1.gain(2,0.25); 
  mixer1.gain(3,0.25); 
  //Wavetable Group 2
  mixer2.gain(0,0.25); 
  mixer2.gain(1,0.25); 
  mixer2.gain(2,0.25); 
  mixer2.gain(3,0.25); 
  //Wavetable Group 3
  mixer3.gain(0,0.5);
  mixer3.gain(1,0.5);
  //Wavetable Group 4
  mixer4.gain(0,0.25);
  mixer4.gain(1,0.25);
  mixer4.gain(2,0.25);
  mixer4.gain(3,0.25);
  //Final Mixer
  mixer5.gain(0,0.25); //trumpets
  mixer5.gain(1,0.25); //trombone
  mixer5.gain(2,0.25); //guitar
  mixer5.gain(3,0.25); //drums

  //Set wavetable instruments
  wavetable1.setInstrument(Trumpet);
  wavetable2.setInstrument(Trumpet);
  wavetable3.setInstrument(Trumpet);
  wavetable4.setInstrument(Trumpet);
  wavetable5.setInstrument(Flute);
  wavetable6.setInstrument(Flute);
  wavetable7.setInstrument(Flute);
  wavetable8.setInstrument(Flute);
  wavetable13.setInstrument(drum);
  wavetable14.setInstrument(drum);
  wavetable15.setInstrument(drum);
  wavetable16.setInstrument(drum);


  //Set wavetable amplitudes
  wavetable1.amplitude(0.1);
  wavetable2.amplitude(0.1);
  wavetable3.amplitude(0.1);
  wavetable4.amplitude(0.1);
  wavetable5.amplitude(0.1);
  wavetable6.amplitude(0.1);
  wavetable7.amplitude(0.1);
  wavetable8.amplitude(0.1);
  wavetable13.amplitude(1);
  wavetable14.amplitude(1);
  wavetable15.amplitude(1);
  wavetable16.amplitude(1);

  //Initialize all the wavetables
  wavetable1.playFrequency(base_freq);
  wavetable2.playFrequency(f1*base_freq);
  wavetable3.playFrequency(f2*base_freq);
  wavetable4.playFrequency(f3*base_freq);
  wavetable5.playFrequency(base_freq2);
  wavetable6.playFrequency(f4*base_freq2);
  wavetable7.playFrequency(f5*base_freq2);
  wavetable8.playFrequency(f6*base_freq2);
  wavetable13.playFrequency(drum_freq);
  wavetable14.playFrequency(drum_freq);
  wavetable15.playFrequency(drum_freq);
  wavetable16.playFrequency(drum_freq);

  delay(700);

  //Start USB Host
  myusb.begin();

  // Machine Learning Setup
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report(
        "Model provided is schema version %d not equal "
        "to supported version %d.",
        model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::ops::micro::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);
}

void loop() {
  //loop wavetables
  if (wavetable1.isPlaying() == false) {
    wavetable1.playFrequency(base_freq);
    wavetable2.playFrequency(f1*base_freq);
    wavetable3.playFrequency(f2*base_freq);
    wavetable4.playFrequency(f3*base_freq);
  }
  if (wavetable5.isPlaying() == false) {
    wavetable5.playFrequency(base_freq2);
    wavetable6.playFrequency(f4*base_freq2);
    wavetable7.playFrequency(f5*base_freq2);
    wavetable8.playFrequency(f6*base_freq2);
  }
  //Get input from usb host
  myusb.Task();
  PrintDeviceListChanges();

  //Get Throttle Input
//  t_x_input = joysticks[0].getAxis(0); //Throttle joystick x position
//  t_y_input = joysticks[0].getAxis(1); // Throttle joystick y position
  throttle_input = joysticks[1].getAxis(2); //Throttle position
  pattle_input = joysticks[1].getAxis(5); //Paddle position
//  wheel_input = joysticks[0].getAxis(7); //Wheel position
  throttle_button = joysticks[1].getButtons(); //Throttle button

  //Normalize Throttle Inputs
//  float t_x_val = t_x_input/1023; //Throttle joystick x position
//  float t_y_val = t_y_input/1023; // Throttle joystick y position
  float throttle_val = throttle_input/65535; //Throttle position
  float pattle_val = pattle_input/1023; //Paddle position
//  float wheel_val = wheel_input/1023; //Wheel position

  //Get Joystick Input
  x_input = joysticks[0].getAxis(0); //Joystick x position
  y_input = joysticks[0].getAxis(1); // Joystick y position
  z_input = joysticks[0].getAxis(5); // Yaw Position
//  slider_input = joysticks[1].getAxis(6); //Slider position
  joy_button = joysticks[0].getButtons(); //Button position

  //Normalize Joystick Inputs
  float x_val = x_input/16383; //Throttle joystick x position
  float y_val = y_input/16383; // Throttle joystick y position
  float z_val = z_input/255; //Throttle position
  //  float slider_val = slider_input/255; //Paddle position

  // Get Speed Values
  throttle_speed = throttle_val - prev_throttle;
  x_speed = x_val - prev_x;
  y_speed = y_val - prev_y;
  paddle_speed = pattle_val - prev_paddle;
  z_speed = z_val - prev_z;

  // Take the absolute value(abs function doesnt seem to work)
  if (throttle_speed < 0) {
    throttle_speed = -1* throttle_speed;
  }
  if (paddle_speed < 0) {
    paddle_speed = -1 * paddle_speed;
  }
  if (x_speed < 0) {
    x_speed = -1 * x_speed;
  }
  if (y_speed < 0) {
    y_speed = -1 * y_speed;
  }
  if (z_speed < 0) {
    z_speed = -1 * z_speed;
  }

  // Normalize speed
  if (throttle_speed > 1) {
    throttle_speed = 1;
  }
  if (paddle_speed > 1) {
    paddle_speed = 1;
  }
  if (x_speed > 1) {
    x_speed = 1;
  }
  if (y_speed > 1) {
    y_speed = 1;
  }
  if (z_speed > 1) {
    z_speed = 1;
  }
  // Find total speed
  joy_speed = max(x_speed,y_speed);
  total_speed = max(joy_speed,throttle_speed);

  
  // update previous values
  prev_throttle = throttle_val;
  prev_paddle = pattle_val;
  prev_x = x_val;
  prev_y = y_val;
  prev_z = z_val;

  // Place inputs in the model's input tensor
  input->data.f[0] = x_val; //joystick movement
  input->data.f[1] = y_val;
  input->data.f[2] = z_val;
  input->data.f[3] = throttle_val; //throttle stick inputs
  input->data.f[4] = z_speed;
  input->data.f[5] = paddle_speed;
  input->data.f[6] = total_speed;

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
//
  // Get outputs 
  float y1 = output->data.f[0]; //sine base frequency 1
  float y2 = output->data.f[1]; //sine base frequency 2
//  float y3 = output->data.f[2]; //string freq
  float y4 = output->data.f[3]; //drum hit
  float y5 = output->data.f[4]; //String Volume
  float y6 = output->data.f[5]; //sine amplitude

//  float y1 = 100;
//  float y2 = 100;
  float y3 = 100;  
//  float y4 = 1;
//  float y5 = 0.5;
//  float y6 = 0.5;
  //wavetable volume
  float vol_1 = throttle_speed;
  float vol_2 = joy_speed;

  // Make sure volume is never above 1 or below 0
  if (vol_1 > 1) {
    vol_1 = 1;
  }
  if (vol_1 < 0) {
    vol_1 = 0;
  }
  if (vol_2 > 1) {
    vol_2 = 1;
  }
  if (vol_2 < 0) {
    vol_2 = 0;
  }
  
  //wavetable frequencies
  base_freq = y1;
  base_freq2 = y2;
  string_vol = z_speed;
  string_freq = y3;
  //Change String Synths 
  if (string_vol>1) {
    string_vol = 1; //cap y6 to 1
  }
  if (string_vol<0) {
    string_vol = 0;
  }
  //Update frequencies
  //Update trumpet
  wavetable1.setFrequency(base_freq);
  wavetable2.setFrequency(f1*base_freq);
  wavetable3.setFrequency(f2*base_freq);
  wavetable4.setFrequency(f3*base_freq);
    
  //Update Flute  
  wavetable5.setFrequency(base_freq2);
  wavetable6.setFrequency(f4*base_freq2);
  wavetable7.setFrequency(f5*base_freq2);
  wavetable8.setFrequency(f6*base_freq2);

  //Update String frequencies
  string1.noteOn(string_freq,string_vol);
  string2.noteOn(1.5*string_freq,string_vol);
  
  
  //Update wavetable volume(if I'm not holding a button)
  if (throttle_button == 0) {
    wavetable1.amplitude(vol_1);
    wavetable2.amplitude(vol_1);
    wavetable3.amplitude(vol_1);
    wavetable4.amplitude(vol_1);
  }
  if (joy_button == 0) {
    wavetable5.amplitude(vol_2);
    wavetable6.amplitude(vol_2);
    wavetable7.amplitude(vol_2);
    wavetable8.amplitude(vol_2);
  }
  //Drum hit
  if (paddle_speed>0.1) {
    wavetable13.playFrequency(drum_freq);
    wavetable14.playFrequency(drum_freq);
    wavetable15.playFrequency(drum_freq);
    wavetable16.playFrequency(drum_freq);
  }
  delay(hand_delay);
  joysticks[0].joystickDataClear();
  joysticks[1].joystickDataClear();
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
