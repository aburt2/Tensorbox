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
==============================================================================*/

// Automatically created from a TensorFlow Lite flatbuffer using the command:
// xxd -i model.tflite > model_data.cc

#include "model_data.h"

// We need to keep the data array aligned on some architectures.
#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define DATA_ALIGN_ATTRIBUTE __attribute__((aligned(4)))
#else
#define DATA_ALIGN_ATTRIBUTE
#endif

const unsigned char model_tflite[] DATA_ALIGN_ATTRIBUTE = {
  0x1c, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x00, 0x00, 0x12, 0x00,
  0x1c, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00,
  0x00, 0x00, 0x18, 0x00, 0x12, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xac, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x44, 0x03, 0x00, 0x00, 0xa4, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0xb4, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x88, 0x09, 0x00, 0x00,
  0x84, 0x09, 0x00, 0x00, 0xb4, 0x08, 0x00, 0x00, 0x24, 0x08, 0x00, 0x00,
  0xa4, 0x07, 0x00, 0x00, 0xdc, 0x06, 0x00, 0x00, 0xf8, 0x04, 0x00, 0x00,
  0x64, 0x03, 0x00, 0x00, 0x68, 0x09, 0x00, 0x00, 0x64, 0x09, 0x00, 0x00,
  0x60, 0x09, 0x00, 0x00, 0x5c, 0x09, 0x00, 0x00, 0x58, 0x09, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x0c, 0x00, 0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
  0x6d, 0x69, 0x6e, 0x5f, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x5f,
  0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00, 0xb6, 0xf7, 0xff, 0xff,
  0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x31, 0x2e, 0x31, 0x34,
  0x2e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x4d, 0x4c, 0x49, 0x52, 0x20, 0x43, 0x6f, 0x6e,
  0x76, 0x65, 0x72, 0x74, 0x65, 0x64, 0x2e, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00,
  0x48, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x88, 0x08, 0x00, 0x00, 0x24, 0x08, 0x00, 0x00,
  0x94, 0x07, 0x00, 0x00, 0x0c, 0x07, 0x00, 0x00, 0x9c, 0x06, 0x00, 0x00,
  0xd0, 0x05, 0x00, 0x00, 0xec, 0x03, 0x00, 0x00, 0x58, 0x02, 0x00, 0x00,
  0xb8, 0x01, 0x00, 0x00, 0x38, 0x01, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
  0x68, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0xe8, 0x01, 0x00, 0x00, 0x64, 0x01, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,
  0x78, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x46, 0xfe, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xbc, 0xf7, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1a, 0xf8, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x49, 0x64, 0x65, 0x6e,
  0x74, 0x69, 0x74, 0x79, 0x00, 0x00, 0x00, 0x00, 0x08, 0xf8, 0xff, 0xff,
  0x26, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x6e, 0xf8, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
  0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65,
  0x5f, 0x31, 0x2f, 0x53, 0x69, 0x67, 0x6d, 0x6f, 0x69, 0x64, 0x00, 0x00,
  0x6c, 0xf8, 0xff, 0xff, 0x0e, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x08,
  0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x84, 0xf8, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0xe2, 0xf8, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x1a, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69,
  0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x31, 0x2f, 0x42,
  0x69, 0x61, 0x73, 0x41, 0x64, 0x64, 0x00, 0x00, 0x2c, 0xf9, 0xff, 0xff,
  0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x6e, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x0e, 0x01, 0x00, 0x00, 0x00, 0x5e, 0xf9, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
  0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65,
  0x2f, 0x53, 0x69, 0x67, 0x6d, 0x6f, 0x69, 0x64, 0x00, 0x00, 0x00, 0x00,
  0xa8, 0xf9, 0xff, 0xff, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x10, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x84, 0xf9, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x09, 0x01, 0x00, 0x00, 0x00, 0xfa, 0xf9, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
  0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65,
  0x2f, 0x42, 0x69, 0x61, 0x73, 0x41, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00,
  0xf8, 0xf9, 0xff, 0xff, 0xca, 0xfa, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
  0x40, 0x01, 0x00, 0x00, 0x43, 0x52, 0x34, 0x3c, 0xe3, 0x1c, 0xeb, 0xbe,
  0x18, 0x28, 0x0f, 0xbf, 0xd4, 0x7d, 0x76, 0x3f, 0x54, 0x41, 0x67, 0xbe,
  0x15, 0xdd, 0x91, 0x3e, 0xbd, 0x36, 0xb9, 0x3d, 0x43, 0xd2, 0x55, 0x3e,
  0x20, 0x84, 0x4b, 0x3f, 0x52, 0xec, 0x5d, 0xbe, 0x40, 0x62, 0xf0, 0x3d,
  0x2b, 0x72, 0x90, 0x3e, 0x64, 0x3d, 0xba, 0xbe, 0x30, 0xd2, 0x20, 0x3e,
  0xa0, 0xf4, 0x70, 0xbf, 0x3d, 0x07, 0xcc, 0x3e, 0x6d, 0x1d, 0xc4, 0x3c,
  0x9b, 0x99, 0xc2, 0x3e, 0x52, 0xfc, 0x2b, 0x3e, 0x11, 0x35, 0x46, 0x3f,
  0xf6, 0x9f, 0x3f, 0x3f, 0x02, 0x1e, 0x0b, 0x3f, 0x3a, 0xbc, 0x5d, 0xbe,
  0x21, 0x9c, 0x28, 0x3e, 0xa4, 0xd4, 0xe1, 0xbe, 0xef, 0x94, 0x2b, 0x3e,
  0x7c, 0x67, 0xd5, 0xbe, 0x4f, 0x8e, 0x05, 0xbf, 0xa0, 0x66, 0x6b, 0x3f,
  0xda, 0xdb, 0xf3, 0xbd, 0xe2, 0x63, 0x9f, 0xbd, 0x5a, 0x75, 0xa4, 0xbe,
  0x9b, 0xf8, 0xe5, 0x3e, 0x29, 0xec, 0xb4, 0x3e, 0xc7, 0xed, 0x57, 0xbf,
  0xf2, 0x05, 0x18, 0x3f, 0x76, 0xc8, 0x53, 0x3c, 0x72, 0xd0, 0xf1, 0x3e,
  0x22, 0x99, 0x1c, 0x3f, 0x2e, 0xfb, 0x3b, 0xbe, 0x05, 0x25, 0x0d, 0xbe,
  0x73, 0x43, 0x68, 0x3e, 0x57, 0xe1, 0x97, 0x3c, 0xfb, 0x6a, 0x5f, 0x3f,
  0x98, 0x96, 0x56, 0xbf, 0x72, 0x89, 0x09, 0xbf, 0x8a, 0x86, 0x0f, 0x3f,
  0xbe, 0x13, 0x1c, 0xbe, 0xd5, 0x1e, 0x5e, 0x3f, 0xf0, 0x97, 0xad, 0x3e,
  0xb3, 0x56, 0xc5, 0x3e, 0xbd, 0xce, 0x5e, 0x3d, 0x2e, 0x3e, 0x2b, 0xbe,
  0xbe, 0xd0, 0x17, 0x3f, 0x05, 0x8a, 0xf6, 0xbe, 0xd5, 0x5c, 0xcb, 0xbe,
  0xc2, 0x11, 0x0c, 0x3e, 0x4f, 0x36, 0x2d, 0x3f, 0x24, 0x8d, 0x30, 0x3f,
  0xf6, 0x91, 0x6f, 0xbe, 0x35, 0x25, 0x3e, 0xbd, 0x93, 0x96, 0xb2, 0x3e,
  0x6f, 0x95, 0x32, 0x3e, 0x27, 0xa9, 0x8a, 0x3e, 0xf1, 0x2b, 0xc6, 0xbe,
  0x23, 0x0a, 0x0e, 0x3f, 0x34, 0x6f, 0xb1, 0x3e, 0xfd, 0x06, 0x34, 0x3f,
  0xad, 0xc6, 0x24, 0x3f, 0xcd, 0xbc, 0x0d, 0xbf, 0x69, 0x2f, 0x2a, 0x3f,
  0x2e, 0xb4, 0x4c, 0x3f, 0xf4, 0x09, 0x24, 0xbf, 0x4c, 0xc8, 0x1b, 0xbe,
  0xb1, 0xba, 0x69, 0xbf, 0x4e, 0xc9, 0xe0, 0x3e, 0xc6, 0x7e, 0xa6, 0xbe,
  0xbb, 0xb8, 0x80, 0x3d, 0x72, 0xc0, 0x80, 0xbc, 0x77, 0xb4, 0x1a, 0x3f,
  0x8a, 0xfb, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
  0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64,
  0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75,
  0x6c, 0x00, 0x00, 0x00, 0x88, 0xfb, 0xff, 0xff, 0x5a, 0xfc, 0xff, 0xff,
  0x04, 0x00, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x4b, 0x13, 0x44, 0x3f,
  0xf3, 0x8d, 0xc9, 0x3e, 0x91, 0xd1, 0x32, 0x3e, 0xbb, 0x77, 0x51, 0x3f,
  0x10, 0xbd, 0xe9, 0x3d, 0xf6, 0xef, 0xb7, 0xbe, 0xa5, 0xcd, 0xd1, 0xbe,
  0x8d, 0x8a, 0x7a, 0xbf, 0x00, 0xf1, 0x39, 0xbe, 0xa7, 0x2b, 0xff, 0x3d,
  0x68, 0x47, 0xb9, 0x3e, 0x0d, 0x6b, 0x27, 0xbd, 0x5b, 0x72, 0xb9, 0xbd,
  0xaf, 0x01, 0x23, 0x3f, 0x35, 0x57, 0xb1, 0xbe, 0xf1, 0xc4, 0x8c, 0x3d,
  0x67, 0x66, 0xec, 0xbe, 0x23, 0xf7, 0x92, 0xbf, 0x0c, 0x45, 0x20, 0xbf,
  0x2d, 0x0b, 0xbe, 0x3e, 0xa9, 0x14, 0x29, 0xbf, 0x64, 0x13, 0x42, 0x3e,
  0x82, 0x28, 0x0a, 0xbf, 0x88, 0x86, 0xa2, 0xbf, 0xe2, 0xbc, 0x6f, 0x3e,
  0x4c, 0x52, 0xc1, 0xbe, 0xa2, 0x67, 0x6e, 0x3f, 0x93, 0x5b, 0x68, 0x3f,
  0x9d, 0x99, 0x6d, 0xbc, 0xb9, 0x2b, 0xe9, 0x3d, 0xbd, 0xb4, 0x1e, 0xbf,
  0xbd, 0xb4, 0x42, 0x3f, 0x24, 0xe0, 0x48, 0xbf, 0x5e, 0xde, 0x6d, 0x3e,
  0xbc, 0x82, 0x0f, 0x3f, 0x92, 0x03, 0xb4, 0xbe, 0x54, 0xe1, 0x8c, 0xbf,
  0x41, 0xd8, 0xb1, 0x3e, 0xea, 0x13, 0xd4, 0x3e, 0xdf, 0xae, 0xf0, 0x3e,
  0xcd, 0xda, 0x4e, 0xbf, 0xe3, 0xf1, 0xbb, 0xbe, 0x31, 0xfb, 0x0d, 0x3f,
  0xba, 0xeb, 0x9e, 0x3e, 0x10, 0xda, 0x36, 0xbd, 0xef, 0x84, 0xf8, 0x3d,
  0x81, 0xa6, 0xb3, 0x3f, 0x27, 0xac, 0xd7, 0x3e, 0x81, 0x96, 0x03, 0x3f,
  0xb0, 0x34, 0x73, 0xbf, 0x29, 0xb7, 0x87, 0x3f, 0x52, 0xb2, 0x54, 0x3e,
  0x84, 0x59, 0x9d, 0xbe, 0x0e, 0xcd, 0xe9, 0xbe, 0x3e, 0xcf, 0x20, 0xbf,
  0x4c, 0x85, 0x94, 0x3e, 0x62, 0x3b, 0x7f, 0xbf, 0xcb, 0x8d, 0xca, 0xbd,
  0x24, 0x8f, 0x20, 0xbf, 0xe6, 0x8a, 0x16, 0x3f, 0x2f, 0xbc, 0x27, 0xbf,
  0xde, 0xf4, 0xa1, 0xbd, 0x08, 0xc2, 0xad, 0xbe, 0x68, 0x82, 0x0c, 0xbf,
  0x1d, 0xbc, 0xfd, 0x3e, 0x03, 0xbc, 0x93, 0xbe, 0x15, 0x9b, 0xe0, 0xbe,
  0x20, 0xd6, 0x25, 0x3f, 0x88, 0x23, 0xa8, 0x3e, 0xf6, 0x66, 0x1b, 0xbd,
  0x4e, 0x14, 0x5a, 0xbe, 0x6d, 0x99, 0x13, 0x3f, 0xc8, 0x04, 0x90, 0xbf,
  0x80, 0xff, 0x39, 0xbf, 0xcd, 0xaf, 0xb8, 0xbe, 0x36, 0x02, 0xf6, 0x3c,
  0xf3, 0x19, 0x93, 0xbf, 0xab, 0xc3, 0xbb, 0x3e, 0xfa, 0x1e, 0xa6, 0x3e,
  0x61, 0xe6, 0x96, 0x3e, 0x9b, 0x2c, 0x96, 0x3d, 0xd4, 0x3f, 0x35, 0x3e,
  0xa7, 0x09, 0x3d, 0xbf, 0x7b, 0x10, 0x88, 0x3b, 0x04, 0xff, 0x0f, 0x3f,
  0xc4, 0x0b, 0x75, 0xbe, 0x09, 0x9b, 0xdd, 0xbf, 0x36, 0xff, 0x98, 0xbe,
  0xe2, 0x45, 0xfb, 0x3d, 0x79, 0x87, 0x42, 0x3f, 0x80, 0x64, 0x7e, 0x3f,
  0x55, 0x12, 0xbb, 0xbe, 0x5c, 0x20, 0x44, 0x3f, 0x97, 0x84, 0x85, 0x3e,
  0x99, 0x90, 0x65, 0xbe, 0x2b, 0x7b, 0xcd, 0x3e, 0x54, 0xad, 0xcd, 0xbe,
  0xcd, 0x66, 0xf8, 0xbe, 0xb8, 0xb5, 0xcb, 0xbe, 0xc5, 0xe8, 0x0e, 0xbe,
  0x6a, 0xfd, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
  0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64,
  0x65, 0x6e, 0x73, 0x65, 0x5f, 0x31, 0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75,
  0x6c, 0x00, 0x00, 0x00, 0x68, 0xfd, 0xff, 0xff, 0x3a, 0xfe, 0xff, 0xff,
  0x04, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xea, 0xa8, 0xc8, 0x3d,
  0xdb, 0x60, 0x24, 0xbf, 0x38, 0xb3, 0xe4, 0x3f, 0xd1, 0xd5, 0x5b, 0x3f,
  0x84, 0x34, 0x90, 0x3f, 0xa4, 0x24, 0x7f, 0x3d, 0xc3, 0xc8, 0xd8, 0xbf,
  0x89, 0x11, 0xb0, 0xbd, 0xf7, 0xc8, 0x6b, 0x3e, 0xa0, 0x71, 0xc7, 0xbf,
  0x51, 0xd0, 0x9c, 0x3f, 0x67, 0x4b, 0x82, 0x3f, 0x6d, 0x8b, 0xc1, 0x3d,
  0x36, 0x51, 0xde, 0x3f, 0xe4, 0x3b, 0x4d, 0xbf, 0x8d, 0x72, 0xb6, 0xbe,
  0x4a, 0x97, 0x82, 0xbf, 0x1b, 0xd3, 0x16, 0x3f, 0x45, 0x23, 0x8f, 0xbf,
  0x9e, 0x73, 0x87, 0xbf, 0xf0, 0xcf, 0xfa, 0xbe, 0x00, 0x86, 0x1b, 0x3f,
  0x81, 0x7d, 0x8d, 0xbc, 0xc5, 0x02, 0xbd, 0xbf, 0xd0, 0x78, 0x06, 0xbc,
  0x2e, 0xc8, 0x80, 0x3f, 0xdf, 0x03, 0xa0, 0xbf, 0x93, 0xed, 0x92, 0x3f,
  0xe9, 0xa6, 0x3e, 0x3f, 0xba, 0x05, 0x25, 0x3f, 0x32, 0xfe, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x2c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
  0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65,
  0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75, 0x6c, 0x00, 0x2c, 0xfe, 0xff, 0xff,
  0xfe, 0xfe, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
  0xc7, 0xc0, 0x07, 0x3e, 0xb0, 0x25, 0x9f, 0x3d, 0x3d, 0x6b, 0xe5, 0x3c,
  0x23, 0xbf, 0x3b, 0x3e, 0xa3, 0x6f, 0x7a, 0x3d, 0x32, 0xad, 0x34, 0x3d,
  0x14, 0xf2, 0x48, 0xbe, 0x60, 0x31, 0x3e, 0x3e, 0x9e, 0xfe, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x3c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x29, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69,
  0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x2f, 0x42,
  0x69, 0x61, 0x73, 0x41, 0x64, 0x64, 0x2f, 0x52, 0x65, 0x61, 0x64, 0x56,
  0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x4f, 0x70, 0x00, 0x00, 0x00,
  0xa8, 0xfe, 0xff, 0xff, 0x7a, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
  0x28, 0x00, 0x00, 0x00, 0xd8, 0x68, 0xb5, 0xbd, 0x2f, 0x5a, 0x82, 0x3d,
  0xd5, 0x5e, 0x99, 0x3c, 0x3e, 0x03, 0xaa, 0xbe, 0xa4, 0x0f, 0xfd, 0x3d,
  0xb8, 0x07, 0xf3, 0x3c, 0x8a, 0x2b, 0xc5, 0xbd, 0x47, 0xb4, 0x20, 0x3d,
  0xd6, 0x3a, 0x05, 0xbe, 0x6f, 0xdc, 0x83, 0x3d, 0x22, 0xff, 0xff, 0xff,
  0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x3c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x29, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69,
  0x61, 0x6c, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x31, 0x2f, 0x42,
  0x69, 0x61, 0x73, 0x41, 0x64, 0x64, 0x2f, 0x52, 0x65, 0x61, 0x64, 0x56,
  0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x4f, 0x70, 0x00, 0x00, 0x00,
  0x78, 0xff, 0xff, 0xff, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
  0x9d, 0x52, 0xb5, 0xbe, 0x4a, 0x50, 0x07, 0xbf, 0x93, 0xdc, 0xc7, 0x3e,
  0x35, 0x63, 0xd3, 0xbe, 0xe9, 0xbd, 0xb6, 0xbe, 0x0f, 0x49, 0x20, 0x3e,
  0x1e, 0x73, 0x56, 0x3f, 0x5f, 0x43, 0xd2, 0x3d, 0xda, 0xb2, 0x91, 0xbd,
  0x62, 0x5c, 0x3d, 0xbf, 0xae, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00,
  0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x2f, 0x64,
  0x65, 0x6e, 0x73, 0x65, 0x2f, 0x42, 0x69, 0x61, 0x73, 0x41, 0x64, 0x64,
  0x2f, 0x52, 0x65, 0x61, 0x64, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c,
  0x65, 0x4f, 0x70, 0x00, 0x04, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x0c, 0x00, 0x10, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x0b, 0x00, 0x00, 0x00, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x69, 0x6e,
  0x70, 0x75, 0x74, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00
};

const int model_tflite_len = 2524;
