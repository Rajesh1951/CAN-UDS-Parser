#include "parser.h"
#include "udsDecoder.h"
#include "response_gen.h"
using namespace std;

CANFrameString canframeS;
CANFrame can_frame;
CANResponse canResponse;
bool isMultiFrame;
void storeData(vector<string> data);
void parseResponse(vector<string> input);
bool isExtendedFrame(uint32_t canId)
{
  return canId > 0x7FF;
}
vector<string> splitFrame(string input)
{
  vector<string> splits;
  string temp = "";
  int i = 0;
  while (i < input.size())
  {
    if (input[i] == ' ')
    {
      splits.push_back(temp);
      temp = "";
    }
    else
    {
      temp += input[i];
    }
    i++;
  }
  splits.push_back(temp);
  return splits;
}
void parseFrame(string input)
{
  vector<string> splits = splitFrame(input);
  string canId = splits[0];
  if ((canId[6] == 'F') && (canId[7] == '1'))
  { // response  F1 is tester
    parseResponse(splits);
  }
  else
  {
    storeData(splits);
  }
}
void parseMultiFrameResponse(vector<string> input)
{
  if (input[1] == "10")
  {
    /*first frame*/
    canResponse.can_id = input[0];
    canResponse.size = stoi(input[2], nullptr, 16);
    canResponse.response = "";
    for (int i = 3; i < input.size(); i++)
    {
      canResponse.response += input[i];
    }
  }
  else
  {
    for (int i = 2; i < input.size(); i++)
    {
      canResponse.response += input[i];
    }
  }
  if ((canResponse.response.size() / 2) == canResponse.size - 1)
  {
    printCANResponse();
  }
}
void parseResponse(vector<string> input)
{
  int firstDataByte = stoi(input[1], nullptr, 16);
  if ((firstDataByte & 0xF0) == 0x00)
  {
    isMultiFrame = true;
    canResponse.response = "";
    /* parse single frame response*/
    for (int i = 2; i < input.size(); i++)
    {
      canResponse.response += input[i];
    }
    printCANResponse();
  }
  else
  {
    isMultiFrame = false;
    parseMultiFrameResponse(input);
  }
}
void storeData(vector<string> data)
{
  canframeS.can_id = data[0];
  canframeS.dlc = data[1];
  canframeS.service_id = data[2];
  canframeS.data_identifier = data[3] + data[4];
  decodeService(canframeS.service_id);
  lookupDID(canframeS.data_identifier);
  can_frame = CANFrame{stoul(data[0], nullptr, 16),
                       isExtendedFrame(static_cast<uint32_t>(stoul(data[0], nullptr, 16))),
                       static_cast<uint8_t>(stoi(data[1], nullptr, 16)),
                       {static_cast<uint8_t>(stoi(data[2], nullptr, 16)), static_cast<uint8_t>(stoi(data[3], nullptr, 16)), static_cast<uint8_t>(stoi(data[4], nullptr, 16))}};
  printResponse();
}
