/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
// This is for music production
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include <TensorFlowLite.h>

#include "main_functions.h"

#include "constants.h"
#include "output_handler.h"
#include "sine_model_data.h"
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "chords.h" // this is to get the chord data

// Guitar music stuff

AudioSynthKarplusStrong  string1;
AudioSynthKarplusStrong  string2;
AudioSynthKarplusStrong  string3;
AudioSynthKarplusStrong  string4;
AudioSynthKarplusStrong  string5;
AudioSynthKarplusStrong  string6;
AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(string1, 0, mixer1, 0);
AudioConnection          patchCord2(string2, 0, mixer1, 1);
AudioConnection          patchCord3(string3, 0, mixer1, 2);
AudioConnection          patchCord4(string4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, mixer2, 0);
AudioConnection          patchCord6(string5, 0, mixer2, 1);
AudioConnection          patchCord7(string6, 0, mixer2, 2);
AudioConnection          patchCord8(mixer2, 0, i2s1, 0);
AudioConnection          patchCord9(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

const int finger_delay = 5;
const int hand_delay = 220;


int chordnum=0;
int num = 0;
bool up = true;
float velocity = 1.0;

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

// The name of this function is important for Arduino compatibility.
void setup() {
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_sine_model_data);
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

  // Keep track of how many inferences we have performed.
  inference_count = 0;

  // Setup music stuff
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  mixer1.gain(0, 0.15);
  mixer1.gain(1, 0.15);
  mixer1.gain(2, 0.15);
  mixer1.gain(3, 0.15);
  mixer2.gain(1, 0.15);
  mixer2.gain(2, 0.15);
  delay(700);
}

void strum_up(const float *chord, float velocity);
void strum_dn(const float *chord, float velocity);

// The name of this function is important for Arduino compatibility.
void loop() {
  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle);
  float x_val = position * kXrange;

  // Place our calculated x value in the model's input tensor
  input->data.f[0] = x_val;

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter->Report("Invoke failed on x_val: %f\n",
                           static_cast<double>(x_val));
    return;
  }

  // Read the predicted y value from the model's output tensor
  float y_val = output->data.f[0];

  // Output the results. A custom HandleOutput function can be implemented
  // for each supported hardware target.
  HandleOutput(error_reporter, x_val, y_val);

  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle) inference_count = 0;

    // play music
  const float *chord;

  // compute new volume
  velocity = 0.25*y_val+0.5;
  Serial.println(velocity);
  
  // each 5 loops time through the loop, play a different chord
  if (chordnum == 0) {
    chord = Cmajor;
    Serial.println("C major");
  } else if (chordnum == 1) {
    chord = Gmajor;
    Serial.println("G major");
  } else if (chordnum == 2) {
    chord = Aminor;
    Serial.println("A minor");
  } else {
    chord = Eminor;
    Serial.println("E minor");
  }
//  strum_up(chord, 1.0);
//  delay(hand_delay);
  // each time we loop through we play a different note
  if (num == 0){
    strum_up(chord, velocity);
    delay(hand_delay);
  } else if (num == 1){
    strum_up(chord, velocity);
  } else if (num == 2){
    strum_dn(chord, velocity);
    delay(hand_delay);
  } else if (num == 3){
    strum_dn(chord, velocity);
  } else if (num == 4){
    strum_up(chord, velocity);
  } else if (num == 5){
    strum_dn(chord, velocity);
  } else if (num == 6) {
    strum_up(chord, velocity);
    delay(hand_delay);
  } else if (num == 7) {
    strum_up(chord, velocity);
  } else if (num == 8) {
    strum_dn(chord, velocity);
    delay(hand_delay);
  } else if (num == 9) {
    strum_dn(chord, velocity);
  } else if (num == 10) {
    strum_up(chord, velocity);
  } else if (num == 11) {
    strum_dn(chord, velocity);
    chordnum++;
  }

  // Go up or down by 1
  num++;
  if (num > 11) {
    num = 0;
  }

  // Change Direction
  if (chordnum >= 5) {
    chordnum = 0;
  }
  // Add delay
  delay(hand_delay);
  
  Serial.print("Max CPU Usage = ");
  Serial.print(AudioProcessorUsageMax(), 1);
  Serial.println("%");
}

void strum_up(const float *chord, float velocity)
{
  if (chord[0] > 20.0) string1.noteOn(chord[0], velocity);
  delay(finger_delay);
  if (chord[1] > 20.0) string2.noteOn(chord[1], velocity);
  delay(finger_delay);
  if (chord[2] > 20.0) string3.noteOn(chord[2], velocity);
  delay(finger_delay);
  if (chord[3] > 20.0) string4.noteOn(chord[3], velocity);
  delay(finger_delay);
  if (chord[4] > 20.0) string5.noteOn(chord[4], velocity);
  delay(finger_delay);
  if (chord[5] > 20.0) string6.noteOn(chord[5], velocity);
  delay(finger_delay);
}

void strum_dn(const float *chord, float velocity)
{
  if (chord[5] > 20.0) string1.noteOn(chord[5], velocity);
  delay(finger_delay);
  if (chord[4] > 20.0) string2.noteOn(chord[4], velocity);
  delay(finger_delay);
  if (chord[3] > 20.0) string3.noteOn(chord[3], velocity);
  delay(finger_delay);
  if (chord[2] > 20.0) string4.noteOn(chord[2], velocity);
  delay(finger_delay);
  if (chord[1] > 20.0) string5.noteOn(chord[1], velocity);
  delay(finger_delay);
  if (chord[0] > 20.0) string6.noteOn(chord[0], velocity);
  delay(finger_delay);
}
