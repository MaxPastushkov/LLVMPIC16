//===--- PIC16.cpp - PIC16 ToolChain Implementations ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PIC16.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Options/Options.h"
#include "llvm/Option/ArgList.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang;
using namespace llvm::opt;

PIC16ToolChain::PIC16ToolChain(const Driver &D, const llvm::Triple &Triple,
                               const ArgList &Args)
    : ToolChain(D, Triple, Args) {
  // ProgramPaths are found via 'PATH' environment variable.
}

bool PIC16ToolChain::isPICDefault() const { return true; }

bool PIC16ToolChain::isPIEDefault(const llvm::opt::ArgList &Args) const { return false; }

bool PIC16ToolChain::isPICDefaultForced() const { return true; }

bool PIC16ToolChain::SupportsProfiling() const { return false; }

bool PIC16ToolChain::hasBlocksRuntime() const { return false; }
