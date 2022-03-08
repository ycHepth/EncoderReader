//
// Created by ycAzure on 2022/3/8.
//

#ifndef ENCODERREADER_ENCODERREADER_H
#define ENCODERREADER_ENCODERREADER_H

#include <cstdint>
#include <bitset>
#include <cmath>

class EncoderReader{
public:
    EncoderReader();
    EncoderReader(float Ratio);
    ~EncoderReader() {};

    std::bitset<32> getMultiData();
    std::bitset<17> getSingleData();

    void read(int64_t cnt);

    float getTotalRound();
    float getAngular();

    float getOutputRound();
    float getOutputAngular();


private:
    std::bitset<32> binaryCnt;
    std::bitset<17> singleBinary;
    std::bitset<32> multiBinary;
    float motorRound;
    float motorAngular;

    float outputRound;
    float outputAngular;

    float GearRatio;

    std::bitset<32> BaseBinary; // reference for incremental value

};

#endif //ENCODERREADER_ENCODERREADER_H
