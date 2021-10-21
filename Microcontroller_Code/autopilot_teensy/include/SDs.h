#ifndef SD_H
#define SD_H
#include <Arduino.h>
#include <SD.h>
#include <pb_encode.h>
#include <autopilot.pb.h>
#include <base64.h>

class wrapSD{

    private:
    // Protobuf
    PlaneBuf &plane_buf;
    // File
    File myFile;
    

    void writeFormattedFloat(float val, uint8_t leading, uint8_t decimals);
    void wrapSD::writeVec(float *vec, int size);

    public:
    wrapSD(PlaneBuf &plane_buf);
    bool setup();
    void writeData();
    void open();
    void close();





};

#endif