/* Copyright 2020 Albert Niyonsenga. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This code pans between two samples based on the throttle position of a Thrustmaster T16000m Throttle stick
==============================================================================*/
// Audio Setup 
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav1;     //xy=118.00000762939453,170.80000686645508
AudioPlaySdWav           playWav2;     //xy=124.00000381469727,246.80000686645508
AudioMixer4              mixer2;         //xy=333.00000762939453,244.00000762939453
AudioMixer4              mixer1;         //xy=339.00000762939453,127.00000381469727
AudioEffectFreeverb      freeverb2;      //xy=522.0000152587891,228.00000762939453
AudioEffectFreeverb      freeverb1;      //xy=531,180
AudioMixer4              mixer3;         //xy=712.0001411437988,148.0000228881836
AudioMixer4              mixer4;         //xy=714.0000190734863,239.0000457763672
AudioOutputI2S           i2s1;           //xy=936.7999877929688,201.8000144958496
AudioConnection          patchCord1(playWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playWav2, 1, mixer2, 1);
AudioConnection          patchCord5(mixer2, freeverb2);
AudioConnection          patchCord6(mixer2, 0, mixer4, 0);
AudioConnection          patchCord7(mixer1, freeverb1);
AudioConnection          patchCord8(mixer1, 0, mixer3, 0);
AudioConnection          patchCord9(freeverb2, 0, mixer4, 1);
AudioConnection          patchCord10(freeverb1, 0, mixer3, 1);
AudioConnection          patchCord11(mixer3, 0, i2s1, 0);
AudioConnection          patchCord12(mixer4, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=840.0000152587891,358.0000925064087
// GUItool: end automatically generated code

//Include Main Functions
#include <TensorFlowLite.h>
#include "model_data.h"
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"


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

// SD Card Setup
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

// Create an area of memory to use for input, output, and intermediate arrays.
// Finding the minimum value for your model may require some trial and error.
constexpr int kTensorArenaSize = 2 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

float x_input = 0; //use this for the input from our controller
float y_input = 0;
float slider_input =0;

void setup() {
 // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
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

  //Set up Mixers
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  // Audio Sample mixing
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  // Freeverb mixing
  mixer3.gain(0,0.1);
  mixer3.gain(1,0.9);
  mixer4.gain(0,0.1);
  mixer4.gain(1,0.9);
  
  
  delay(700);

  //Start USB Host
  myusb.begin();
}

void loop() {
  //Get input from usb host
  myusb.Task();
  PrintDeviceListChanges();

  //Inputs
  x_input = joysticks[0].getAxis(0); //Joystick X position
  y_input = joysticks[0].getAxis(1); //Joystick Y position
  slider_input = joysticks[0].getAxis(6); //slider position
  
  float x_val = x_input/16383; // convert so that it is between 0 and 1
  float y_val = y_input/16383;
  float slider_val = slider_input/255;
  
  //Continuously loop Samples
  if (playWav1.isPlaying() == false) {
    //Serial.println("Start playing 1");
    playWav1.play("RYTHM1.WAV");
    delay(10); // wait for library to parse WAV info
  }
  if (playWav2.isPlaying() == false) {
    //Serial.println("Start playing 2");
    playWav2.play("SOFT2.WAV");
    delay(10); // wait for library to parse WAV info
  }
  
  // Place our calculated x value in the model's input tensor
  input->data.f[0] = x_val;
  input->data.f[1] = y_val;
  input->data.f[2] = slider_val;

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter->Report("Invoke failed on x_val: %f\n",
                           static_cast<double>(x_val));
    return;
  }

  // Get outputs
  
  float y1 = output->data.f[0]; //sample mix
  float y2 = output->data.f[1]; //freeverb1 mix
  float y3 = output->data.f[2]; //freeverb2 mix
  float y4 = output->data.f[3]; //roomsize1
  float y5 = output->data.f[4]; //roomsize2
  float y6 = output->data.f[5]; //damp1
  float y7 = output->data.f[6]; //damp2
  float y8 = output->data.f[7]; //volume

  // change gain(normalize to 1)
  float s2 = -y1 + 1;
  float sum = y1 + s2;
  float gain1 = y1/sum;
  float gain2 = 1 - gain1; 

  //change freeverb1 mix
  float s3 = -y2 + 1;
  float sum2 = y2 + s3;
  float gain3 = y2/sum2;
  float gain4 = 1 - gain3;
  
  //change freeverb2 mix
  float s4 = -y3 + 1;
  float sum3 = y3 + s4;
  float gain5 = y3/sum3;
  float gain6 = 1 - gain5;
  
  // change freeverb parameters
  float room1 = y4;
  float room2 = y5;
  float damp1 = y6;
  float damp2 = y7;

  //change volume
  float vol = 0.3*y8;
  
  // Change the mixing between the samples being played
  mixer1.gain(0, gain2);
  mixer1.gain(1, gain1);
  mixer2.gain(0, gain2);
  mixer2.gain(1, gain1);

  //Change freeverb1 mixing
  mixer3.gain(0, gain4);
  mixer3.gain(1, gain3);

  //Change freeverb2 mixing
  mixer4.gain(0, gain6);
  mixer4.gain(1, gain5);

  // change freeverb
  freeverb1.roomsize(room1);
  freeverb1.damping(damp1);
  freeverb2.roomsize(room2);
  freeverb2.damping(damp2);

  //change volume
  sgtl5000_1.volume(vol);

//  //Print new outputs
//  Serial.print("Out1 = ");
//  Serial.print(y1);
//  Serial.print("Out2 = ");
//  Serial.print(y2);
//  Serial.print("Out3 = ");
//  Serial.print(y3);
//  Serial.print("Out4 = ");
//  Serial.print(y4);
//  Serial.print("Out5 = ");
//  Serial.print(y5);
//  Serial.print("Out6 = ");
//  Serial.print(y6);
//  Serial.print("Out7 = ");
//  Serial.print(y7);
//  Serial.print("Out8 = ");
//  Serial.println(y8);
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
