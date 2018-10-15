//
// Created by gyorgy on 12/10/18.
//

#include "../include/Configuration.h"

std::string Configuration::WindowTitle = "Gameboy Emulator";
unsigned int Configuration::PixelScaleFactor = 2;
RGBA Configuration::Colours[4] = {(255), (171), (87), (3)};

Configuration::Configuration() {}

Configuration::~Configuration() {}
