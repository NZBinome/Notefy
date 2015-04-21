//
// Endian.h - MrsWatson
// Created by Nik Reiman on 10 Dec 14.
// Copyright (c) 2014 Teragon Audio. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef MrsWatson_Endian_h
#define MrsWatson_Endian_h

#include "base/Types.h"

/**
 * Flip bytes for a short value. This does not take into account the host's
 * endian-ness.
 * @param value Short integer
 * @return Flipped version of short integer
 */
unsigned short flipShortEndian(const unsigned short value);

/**
 * Flip bytes for an integer value. This does not take into account the host's
 * endian-ness.
 * @param value Integer
 * @return Flipped version of integer
 */
unsigned int flipIntEndian(const unsigned int value);

/**
 * Convert a big endian short integer to the platform's native endian-ness.
 * @param value Short integer
 * @return Flipped version of short integer. If the host is big endian, the same
 * value will be returned.
 */
unsigned short convertBigEndianShortToPlatform(const unsigned short value);

/**
 * Convert a big endian integer to the platform's native endian-ness.
 * @param value Integer
 * @return Flipped version of integer. If the host is big endian, the same value
 * will be returned.
 */
unsigned int convertBigEndianIntToPlatform(const unsigned int value);

/**
 * Convert a little endian short integer to the platform's native endian-ness.
 * @param value Short integer
 * @return Flipped version of short integer. If the host is little endian, the
 * same value will be returned.
 */
unsigned int convertLittleEndianIntToPlatform(const unsigned int value);

/**
 * Convert a big endian floating-point value to the platform's native endian-ness.
 * @param value Floating-point number
 * @return Flipped version of float. If the host is big endian, the same value
 * will be returned.
 */
float convertBigEndianFloatToPlatform(const float value);

/**
 * Convert raw bytes to an unsigned short value, taking into account the host's
 * endian-ness.
 * @param value A buffer which holds at least two bytes
 * @return Unsigned short integer
 */
unsigned short convertByteArrayToUnsignedShort(const byte *value);

/**
 * Convert raw bytes to an unsigned int value, taking into account the host's
 * endian-ness.
 * @param value A buffer which holds at least four bytes
 * @return Unsigned short integer
 */
unsigned int convertByteArrayToUnsignedInt(const byte *value);

#endif
