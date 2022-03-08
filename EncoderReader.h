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
    EncoderReader(int64_t base);
    EncoderReader(int64_t base,float Ratio);
    ~EncoderReader() {};

    std::bitset<17> getMultiData(); // [1 bit] sign + [16 bits] data
    std::bitset<18> getSingleData();  // [1 bit] sign + [17 bits] data
    std::bitset<32> getBaseData();

    void read(int64_t cnt); // absolute data

    void update(int64_t cnt); // increment data

    float getTotalRound();
    float getAngular();

    float getOutputRound();
    float getOutputAngular();


    float getIncRound();


private:
    float GearRatio;

    int64_t BaseCnt;

    std::bitset<32> binaryCnt;
    std::bitset<17> singleBinary;
    std::bitset<32> multiBinary;
    float _motorRound;
    float _motorAngular;

    float _outputRound;
    float _outputAngular;

    bool sign = true; // default is positive
};

#endif //ENCODERREADER_ENCODERREADER_H
