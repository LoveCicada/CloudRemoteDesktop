
#pragma once

#include <iostream>
#include <string>
using std::string;

class ClientData
{
public:
    ClientData();
    ~ClientData();

    void Init();

public:
    int16_t width;
    int16_t height;
    int16_t port;
    string  ip;
};