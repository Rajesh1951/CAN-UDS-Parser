#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
using namespace std;
struct CANFrame
{
  uint32_t id;
  bool isExtended;
  uint8_t dlc;
  vector<uint8_t> data;
};
struct CANFrameString
{
  string can_id, dlc, service_id, data_identifier;
};
struct CANResponse
{
  string can_id,response;
  int size;
};
void parseFrame(string input);
bool isExtendedFrame(uint32_t canID);
extern CANFrameString canframeS;
extern CANFrame can_frame;
extern CANResponse canResponse;
extern bool isMultiFrame;

#endif