#include <bits/stdc++.h>
#include "response_gen.h"
#include "parser.h"
#include "udsDecoder.h"
using namespace std;
unordered_map<uint16_t, string> fakeResponse = {{0xF190, "WVZZZ1KZAW000123"},
                                                {0xF187, "Volkswagen"},
                                                {0xF18C, "SW_VER_01.05.07"},
                                                {0xF18A, "HW_VER_02.01.00"}};
string getResponse(vector<uint8_t> data)
{
  uint8_t didService = data[0];
  uint16_t didID = (static_cast<int>(data[1]) << 8) | data[2];
  return (fakeResponse.find(didID) == fakeResponse.end()) ? "invalid DID ID" : fakeResponse[didID];
}
void generateResponse(string data)
{
  for (int i = 0; i < data.size(); i+=2)
  {
    cout<<data[i]<<data[i+1]<<' ';
  }
}
void printResponse()
{
  cout << "----------------------------------------" << '\n';
  cout << "Parsed CAN Frame:" << '\n';
  cout << "> CAN ID        : " << canframeS.can_id << (can_frame.isExtended ? " Extended" : " Standard") << '\n';
  cout << "> DLC           : " << canframeS.dlc << " bytes" << '\n';
  cout << "> Data Bytes    : " << canframeS.service_id << ' ' << canframeS.data_identifier << '\n';
  cout << "> UDS Service   : " << service << " 0x" << hex << uppercase << static_cast<int>(can_frame.data[0]) << dec << '\n';
  cout << "> Requested DID : " << canframeS.data_identifier << " -> " << req_did << '\n';
  cout << "----------------------------------------" << '\n';
}
void printCANResponse()
{
  cout << "----------------------------------------" << '\n';
  cout << "Parsed CAN Response:" << '\n';
  cout << "> Frame type    : " << (isMultiFrame ? "Single" : "Multi") << '\n';
  cout << "> Payload Bytes : ";
  generateResponse(canResponse.response);
  cout << '\n';
  cout << "> Decoded ASCII : " << decodeCANResponse(canResponse.response) << '\n';
  cout << "----------------------------------------" << '\n';
}
