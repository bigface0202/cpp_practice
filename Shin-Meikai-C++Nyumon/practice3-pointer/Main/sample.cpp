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
    int n = 130;

    cout << "n:" << n  << '\n';
    cout << "&n:" << &n << '\n';

    int* ptr = &n;
    cout << "ptr:" << ptr << '\n';
    cout << "*ptr:" << *ptr << '\n';

    *ptr = 500;

    cout << "n:" << n  << '\n';
    cout << "&n:" << &n << '\n';

    cout << "ptr:" << ptr << '\n';
    cout << "*ptr:" << *ptr << '\n';

}