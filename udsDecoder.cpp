#include <bits/stdc++.h>
#include "udsDecoder.h"
using namespace std;
string service, req_did;
unordered_map<string, string> services = {
    {"22", "Read DID"},
    {"2E", "Write DID"},
    {"2F", "Input Output DID"},
    {"31", "RIDs"}};
unordered_map<uint8_t, string> didMap = {
    {0xF190, "Vehicle VIN"},
    {0xF187, "Software Version"},
    {0xF18C, "ECU Serial Number"},
    {0xF18A, "Hardware Number"},
    {0xF189, "Vehicle Manufacturer"},
    {0xF197, "Vehicle Type"}};
void decodeService(string input)
{
  if (services.find(input) != services.end())
  {
    service = services[input];
  }
  else
  {
    service = "invalid request";
  }
}
void lookupDID(string did)
{
  uint16_t did_hex = static_cast<uint16_t>(stoi(did, nullptr, 16));
  if (didMap.find(did_hex) != didMap.end())
  {
    req_did = didMap[did_hex];
  }
  else
  {
    req_did = "invalid request";
  }
}

string decodeCANResponse(string response){
  if(response[0]=='6' && response[1]=='E'){
    return "Write succesfull";
  }
  string decoded="";
  for (int i = 6; i < response.size(); i+=2)
  {
    string ascii="";
    ascii=response[i];
    ascii+=response[i+1];
    decoded+=(char)(stoi(ascii,nullptr,16));
  }
  return decoded;
}

/*PENDING 
check single/ multi
rest features
*/