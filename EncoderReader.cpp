//
// Created by ycAzure on 2022/3/8.
//

#include "EncoderReader.h"

EncoderReader::EncoderReader() {
    this->GearRatio = 1;
    this->singleBinary.reset();
    this->multiBinary.reset();
}

EncoderReader::EncoderReader(float Ratio) {
    this->GearRatio = Ratio;
    this->singleBinary.reset();
    this->multiBinary.reset();
}

std::bitset<17> EncoderReader::getSingleData() {
    return singleBinary;
}

std::bitset<32> EncoderReader::getMultiData() {
    return multiBinary;
}

void EncoderReader::read(int64_t cnt) {
    std::bitset<17> bsLow(cnt);
    std::bitset<32> bsFull(cnt);
    binaryCnt = bsFull;
    multiBinary = (binaryCnt >> 17);
    singleBinary = bsLow;
}

float EncoderReader::getTotalRound() {

    std::bitset<17> refBinary;
    refBinary.set(); // set all bits to '1'

    auto singleCnt = (float)singleBinary.to_ulong();
    auto refCnt = (float)refBinary.to_ulong();
    auto multiCnt = (float)multiBinary.to_ulong();

    motorRound = multiCnt + 1.0 * singleCnt / refCnt;

    return motorRound;
}

float EncoderReader::getAngular() {
    motorAngular = motorRound * 2 * M_PI;
    return motorAngular;
}

float EncoderReader::getOutputRound() {
    getTotalRound();
    outputRound = motorRound/GearRatio;
    return outputRound;
}

float EncoderReader::getOutputAngular() {
    getAngular();
    outputAngular = motorAngular/GearRatio;
    return outputAngular;
}