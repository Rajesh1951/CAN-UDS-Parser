#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "parser.h"
#include "response_gen.h"
using namespace std;

int main()
{
  ifstream file("input.txt");
  if (file.is_open())
  {
    string line;
    while (getline(file, line))
    {
      parseFrame(line);      
    }
    
  }
  else
  {
    cout << "invalid input ";
  }
  return 0;
}
/*
----------------------------------------
Parsed CAN Frame:
> CAN ID        : 0x18DAF110 (Extended)
> DLC           : 3 bytes
> Data Bytes    : 22 F1 90
> UDS Service   : ReadDataByIdentifier (0x22)
> Requested DID : 0xF190 → Vehicle VIN
> Simulated Response: 62 F1 90 WBAXX1234567890
----------------------------------------

*/