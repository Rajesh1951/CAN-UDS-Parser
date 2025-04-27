#ifndef UDSDECODER_H
#define UDSDECODER_H
#include<bits/stdc++.h>
using namespace std;
extern string service,req_did;
void decodeService(string input);
void lookupDID(string did);
string decodeCANResponse(string response);
#endif