/**
 * @file sample.cpp
 *
 * @author bigface / created on 2021/07/05
 */
#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

int main( int argc, char *argv[] )
{
    char s[5] = "Soft";
    strcat(s, "Bank");
    cout << s;
}