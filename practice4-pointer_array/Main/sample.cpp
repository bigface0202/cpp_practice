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
    int a[5] = {1, 2, 3, 4, 5};
    int* p = a;
    cout << "a[1]: " << 3[a] << '\n';
    cout << "p[1]: " << *p << '\n';

    p[3] = 10;

    cout << "a[3]: " << a[3] << '\n';
    cout << "p[3]: " << p[3] << '\n';
 
}