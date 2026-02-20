//===---- PIC16TargetInfo.h - PIC16 Target Implementation -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_PIC16_TARGETINFO_PIC16TARGETINFO_H
#define LLVM_LIB_TARGET_PIC16_TARGETINFO_PIC16TARGETINFO_H

namespace llvm {

class Target;

Target &getThePIC16Target();

} // namespace llvm

#endif // LLVM_LIB_TARGET_PIC16_TARGETINFO_PIC16TARGETINFO_H
