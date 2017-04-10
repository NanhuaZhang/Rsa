//
// Created by eric on 17-4-5.
//

#ifndef UNTITLED_MAIN_H
#define UNTITLED_MAIN_H

#include <stdio.h>
#include <stdlib.h>
int modpow(long long a, long long b, int c);
/*
 * return *key
 * key[0]:n,key[1]:e,key[2]:d
 */
int * key();
/*
 * encode function
 * private key:(e,n)
 * bytes:according to the parameter n.
 */
int* encodeMessage(int len, int bytes, char* message, int e, int n);
/*
 * decode function
 * public key:(d,n)
 * cryptogram:the array which encode function has returned.
 */
int* decodeMessage(int len, int bytes, int* cryptogram, int d, int n);
#endif //UNTITLED_MAIN_H
