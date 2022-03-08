//
// Created by ycAzure on 2022/3/8.
//

#include <iostream>
#include "EncoderReader.h"

EncoderReader::EncoderReader(int64_t base) {
    this->GearRatio = 1;
    this->singleBinary.reset();
    this->multiBinary.reset();
    this->BaseCnt = base;
}

EncoderReader::EncoderReader(int64_t base, float Ratio) {
    this->GearRatio = Ratio;
    this->singleBinary.reset();
    this->multiBinary.reset();
    this->BaseCnt = base;
}

std::bitset<18> EncoderReader::getSingleData() {
    std::bitset<18> singleData;
    if (sign)
        singleData.reset();
    else
        singleData.set();

    for (int i = 0; i < 17; i++) {
        singleData[i] = singleBinary[i];
    }
    return singleData;
}

std::bitset<17> EncoderReader::getMultiData() {
    std::bitset<17> MultiData;
    if (sign)
        MultiData.reset();
    else
        MultiData.set();

    for (int i = 0; i < 16; i++) {
        MultiData[i] = multiBinary[i];
    }
    return MultiData;
}


void EncoderReader::read(int64_t cnt) { // == update(cnt,0) [DO NOT USE THIS METHOD]
    std::bitset<32> bsFull(cnt);

    if (cnt < 0) {
        sign = false; // only affect high-16 bits
        std::bitset<32> bsTemp(1.0 + bsFull.flip().to_ulong());
        bsFull = bsTemp;
    }

    std::bitset<17> bsLow(cnt);

    binaryCnt = bsFull;
    multiBinary = (binaryCnt >> 17);
    singleBinary = bsLow;

}

float EncoderReader::getTotalRound() {

    std::bitset<17> refBinary;
    refBinary.set(); // set all bits to '1'
    auto refCnt = (float) refBinary.to_ulong();


    auto singleCnt = (float) singleBinary.to_ulong();
    auto multiCnt = (float) multiBinary.to_ulong();

    if (sign)
        _motorRound = multiCnt + 1.0 * singleCnt / refCnt;
    else
        _motorRound = (-1) * multiCnt - 1.0 * (1 - singleCnt / refCnt);

    return _motorRound;
}

float EncoderReader::getAngular() {
    _motorAngular = _motorRound * 2 * M_PI;
    return _motorAngular;
}

float EncoderReader::getOutputRound() {
    getTotalRound();
    _outputRound = _motorRound / GearRatio;
    return _outputRound;
}

float EncoderReader::getOutputAngular() {
    getAngular();
    _outputAngular = _motorAngular / GearRatio;
    return _outputAngular;
}


void EncoderReader::update(int64_t cnt) {
    read(cnt - BaseCnt);
}
