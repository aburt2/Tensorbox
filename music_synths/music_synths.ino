#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "trombone_samples.h"
#include "tuba_samples.h"

// GUItool: begin automatically generated code
AudioSynthKarplusStrong  string1;        //xy=129,69.00000762939453
AudioSynthKarplusStrong  string2;        //xy=129,112.00000190734863
AudioSynthSimpleDrum     drum1;          //xy=130.00001525878906,30.000001907348633
AudioSynthWavetable      wavetable4;     //xy=147,340.79999351501465
AudioSynthWavetable      wavetable3;     //xy=149,299.799991607666
AudioSynthWavetable      wavetable1;     //xy=152,215.39999389648438
AudioSynthWavetable      wavetable2;     //xy=153,256.799991607666
AudioSynthWavetable      wavetable5;     //xy=187,435.79999446868896
AudioSynthWavetable      wavetable6;     //xy=191,479.79999446868896
AudioSynthWavetable      wavetable8;     //xy=195,558.7999954223633
AudioSynthWavetable      wavetable7;     //xy=196.00000381469727,520.7999954223633
AudioMixer4              mixer2;         //xy=367,101
AudioMixer4              mixer1;         //xy=386.00000762939453,254.0000114440918
AudioMixer4              mixer4; //xy=389.00000762939453,478.0000047683716
AudioMixer4              mixer3;         //xy=700.0000076293945,213.00000381469727
AudioOutputI2S           i2s1;           //xy=900.0000114440918,185.00000381469727
AudioConnection          patchCord1(string1, 0, mixer2, 1);
AudioConnection          patchCord2(string2, 0, mixer2, 2);
AudioConnection          patchCord3(drum1, 0, mixer2, 0);
AudioConnection          patchCord4(wavetable4, 0, mixer1, 3);
AudioConnection          patchCord5(wavetable3, 0, mixer1, 2);
AudioConnection          patchCord6(wavetable1, 0, mixer1, 0);
AudioConnection          patchCord7(wavetable2, 0, mixer1, 1);
AudioConnection          patchCord8(wavetable5, 0, mixer4, 0);
AudioConnection          patchCord9(wavetable6, 0, mixer4, 1);
AudioConnection          patchCord10(wavetable8, 0, mixer4, 3);
AudioConnection          patchCord11(wavetable7, 0, mixer4, 2);
AudioConnection          patchCord12(mixer2, 0, mixer3, 0);
AudioConnection          patchCord13(mixer1, 0, mixer3, 1);
AudioConnection          patchCord14(mixer4, 0, mixer3, 2);
AudioConnection          patchCord15(mixer3, 0, i2s1, 0);
AudioConnection          patchCord16(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=815.0000152587891,401.0000114440918
// GUItool: end automatically generated code


//set audio delays
const int finger_delay = 5;
const int hand_delay = 300;
//Set Wavetable frequencies
float base_freq = 261;
float base_freq2 = 261;
const float f1 = 1.015;
const float f2 = 0.503;
const float f3 = 1.496;
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
//float button_input = 0; //button input

//Throttle Input
//float t_x_input = 0; //Throttle joystick x position
//float t_y_input = 0; // Throttle joystick y position
float throttle_input = 0; //Throttle position
float pattle_input = 0; //Paddle position
//float wheel_input = 0; //Wheel position
//float throttle_button = 0; //Throttle Button

//Set speed values
float prev_throttle = 0;
float prev_paddle = 0;
float prev_z = 0;
float throttle_speed = 0;
float paddle_speed = 0;
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
constexpr int kTensorArenaSize = 2 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {
  //Audio Setup
  AudioMemory(250);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  //Sine Group 1
  mixer1.gain(0,0.25); //sine1 gain
  mixer1.gain(1,0.25); //sine2 gain
  mixer1.gain(2,0.25); //sine3 gain
  mixer1.gain(3,0.25); //sine4 gain
  //Sine Group 2
  mixer4.gain(0,0.25); //sine5 gain
  mixer4.gain(1,0.25); //sine6 gain
  mixer4.gain(2,0.25); //sine7 gain
  mixer4.gain(3,0.25); //sine8 gain
  //Drum and Strings
  mixer2.gain(0,0.25); //drum1 gain
  mixer2.gain(1,0.25); //string1 gain
  mixer2.gain(2,0.25); //string2 gain
  //Final Mixer
  mixer3.gain(0,0.33); //drum/guitar gain
  mixer3.gain(1,0.33); //sine group 1 gains
  mixer3.gain(2,0.33); //sine group 2 gains

  //Set wavetable settings
  wavetable1.setInstrument(tuba);
  wavetable2.setInstrument(tuba);
  wavetable3.setInstrument(tuba);
  wavetable4.setInstrument(tuba);
  wavetable5.setInstrument(trombone);
  wavetable6.setInstrument(trombone);
  wavetable7.setInstrument(trombone);
  wavetable8.setInstrument(trombone);
  wavetable1.amplitude(0.1);
  wavetable2.amplitude(0.1);
  wavetable3.amplitude(0.1);
  wavetable4.amplitude(0.1);
  wavetable5.amplitude(0.1);
  wavetable6.amplitude(0.1);
  wavetable7.amplitude(0.1);
  wavetable8.amplitude(0.1);

  //Initialize all the wavetables
  wavetable1.playFrequency(base_freq);
  wavetable2.playFrequency(f1*base_freq);
  wavetable3.playFrequency(f2*base_freq);
  wavetable4.playFrequency(f3*base_freq);
  wavetable5.playFrequency(base_freq2);
  wavetable6.playFrequency(f4*base_freq2);
  wavetable7.playFrequency(f5*base_freq2);
  wavetable8.playFrequency(f6*base_freq2);

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
//  throttle_button = joysticks[0].getButtons(); //Throttle button

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
//  button_input = joysticks[1].getButtons(); //Button position

  //Normalize Joystick Inputs
  float x_val = x_input/16383; //Throttle joystick x position
  float y_val = y_input/16383; // Throttle joystick y position
  float z_val = z_input/255; //Throttle position
//  float slider_val = slider_input/255; //Paddle position

  //Get Speed Values
  throttle_speed = 65535*abs(throttle_val - prev_throttle);
  paddle_speed = 2*abs(pattle_val - prev_paddle);
  z_speed = 2*abs(z_val - prev_z);

  //Normalize speed
  if (throttle_speed > 1) {
    throttle_speed = 1;
  }
  
  //update previous values
  prev_throttle = throttle_val;
  prev_paddle = pattle_val;
  prev_z = z_val;

  // Place inputs in the model's input tensor
  input->data.f[0] = x_val; //joystick movement
  input->data.f[1] = y_val;
  input->data.f[2] = z_speed;
//  input->data.f[0] = 0; //joystick movement
//  input->data.f[1] = 0;
//  input->data.f[2] = 0;
  input->data.f[3] = throttle_val; //throttle stick inputs
  input->data.f[4] = throttle_speed;
  input->data.f[5] = paddle_speed;

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();

  // Get outputs 
  float y1 = output->data.f[0]; //sine amplitude
  float y2 = output->data.f[1]; //sine base frequency 1
  float y3 = output->data.f[2]; //sine base frequency 2
  float y4 = output->data.f[3]; //drum hit
  float y5 = output->data.f[4]; //string freq
  float y6 = output->data.f[5]; //string volume

  
  //wavetable volume
  float vol = 1; //offset the volume so that it is never silent
  if (vol > 1) {
    vol = 1;
  }
  if (vol < 0) {
    vol = 0;
  }
  
  //wavetable frequencies
  base_freq = (308*y2) + 44; // scale frequency to be between 44 to349 hertz(roughly tuba range)
  base_freq2 = (490*y2) + 33; // scale frequency to be between 33 to 523 hertz(roughly base trombone range)
  
  //Update frequencies
  wavetable1.setFrequency(base_freq);
  wavetable2.setFrequency(f1*base_freq);
  wavetable3.setFrequency(f2*base_freq);
  wavetable4.setFrequency(f3*base_freq);  
  wavetable5.setFrequency(base_freq2);
  wavetable6.setFrequency(f4*base_freq2);
  wavetable7.setFrequency(f5*base_freq2);
  wavetable8.setFrequency(f6*base_freq2);

  //Update volume
  wavetable1.amplitude(vol);
  wavetable2.amplitude(vol);
  wavetable3.amplitude(vol);
  wavetable4.amplitude(vol);
  wavetable5.amplitude(vol);
  wavetable6.amplitude(vol);
  wavetable7.amplitude(vol);
  wavetable8.amplitude(vol);


  //Drum hit
  if (y4>0.5) {
    drum1.noteOn(); //hit drumn if above certain speed
  }

  //Change String Synths
  if (y6>1) {
    y6 = 1; //cap y6 to 1
  }
  if (y6<0) {
    y6 = 0;
  }
  string1.noteOn(y5,y6);
  string2.noteOn(1.5*y5,y6);
  delay(hand_delay);
  joysticks[0].joystickDataClear();
  joysticks[1].joystickDataClear();
  Serial.printf("\n*********************\n");
  Serial.printf("Throttle Speed: %f\n",throttle_speed);
  Serial.printf("Volume: %f\n",vol);
  Serial.printf("Paddle Speed: %f\n",paddle_speed);
  Serial.printf("Drum hit: %f\n",y4);
  Serial.printf("Z Speed: %f\n",z_speed);
  Serial.printf("String Volume: %f\n",y6);
  Serial.printf("*********************\n");
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
