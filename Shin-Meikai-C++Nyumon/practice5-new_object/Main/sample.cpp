/**
 * @file sample.cpp
 *
 * @author bigface / created on 2021/07/05
 */
#include <stdio.h>
#include <iostream>

using namespace std;

int main( int argc, char *argv[] )
{
    int* x = new int(5);
    cout << *x ;
    delete x;
}