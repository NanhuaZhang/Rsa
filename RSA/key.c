//
// Created by eric on 17-4-5.
//
#include "main.h"

#define ACCURACY 5
#define SINGLE_MAX 10000

/**
 * Computes a^b mod c
 */
int modpow(long long a, long long b, int c) {
    int res = 1;
    while(b > 0) {
        /* Need long multiplication else this will overflow... */
        if(b & 1) {
            res = (res * a) % c;
        }
        b = b >> 1;
        a = (a * a) % c; /* Same deal here */
    }
    return res;
}
/**
 * Computes the Jacobi symbol, (a, n)
 */
int jacobi(int a, int n) {
    int twos, temp;
    int mult = 1;
    while(a > 1 && a != n) {
        a = a % n;
        if(a <= 1 || a == n) break;
        twos = 0;
        while(a % 2 == 0 && ++twos) a /= 2; /* Factor out multiples of 2 */
        if(twos > 0 && twos % 2 == 1) mult *= (n % 8 == 1 || n % 8 == 7) * 2 - 1;
        if(a <= 1 || a == n) break;
        if(n % 4 != 1 && a % 4 != 1) mult *= -1; /* Coefficient for flipping */
        temp = a;
        a = n;
        n = temp;
    }
    if(a == 0) return 0;
    else if(a == 1) return mult;
    else return 0; /* a == n => gcd(a, n) != 1 */
}

/**
 * Check whether a is a Euler witness for n
 */
int solovayPrime(int a, int n) {
    int x = jacobi(a, n);
    if(x == -1) x = n - 1;
    return x != 0 && modpow(a, (n - 1)/2, n) == x;
}

/**
 * Test if n is probably prime, using accuracy of k (k solovay tests)
 */
int probablePrime(int n, int k) {
    if(n == 2) return 1;
    else if(n % 2 == 0 || n == 1) return 0;
    while(k-- > 0) {
        if(!solovayPrime(rand() % (n - 2) + 2, n)) return 0;
    }
    return 1;
}
/**
 * Find a random (probable) prime between 3 and n - 1, this distribution is
 * nowhere near uniform, see prime gaps
 */
int randPrime(int n) {
    int prime = rand() % n;
    n += n % 2; /* n needs to be even so modulo wrapping preserves oddness */
    prime += 1 - prime % 2;
    while(1) {
        if(probablePrime(prime, ACCURACY)) return prime;
        prime = (prime + 2) % n;
    }
}

/**
 * Compute gcd(a, b)
 */
int gcd(int a, int b) {
    int temp;
    while(b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * Find a random exponent x between 3 and n - 1 such that gcd(x, phi) = 1,
 * this distribution is similarly nowhere near uniform
 */
int randExponent(int phi, int n) {
    int e = rand() % n;
    while(1) {
        if(gcd(e, phi) == 1) return e;
        e = (e + 1) % n;
        if(e <= 2) e = 3;
    }
}
/**
 * Compute n^-1 mod m by extended euclidian method
 */
int inverse(int n, int modulus) {
    int a = n, b = modulus;
    int x = 0, y = 1, x0 = 1, y0 = 0, q, temp;
    while(b != 0) {
        q = a / b;
        temp = a % b;
        a = b;
        b = temp;
        temp = x; x = x0 - q * x; x0 = temp;
        temp = y; y = y0 - q * y; y0 = temp;
    }
    if(x0 < 0) x0 += modulus;
    return x0;
}
//return *key key[0]:n,key[1]:e,key[2]:d
int * key(){
    int p,q,n,phi,e, d;
    int *key=(int *) malloc(sizeof(int)*3);
    p = randPrime(SINGLE_MAX);
    q = randPrime(SINGLE_MAX);
    printf("%d ",p);
    printf("%d\n",q);
    n=p*q;
    phi=(p-1)*(q-1);
    e=randExponent(phi,n);
    d=inverse(e,phi);
    key[0]=n;
    key[1]=e;
    key[2]=d;
    return key;
}
//ktype:1 private_key,0 public_key
int *get_key(int ktype){
    int *keys=(int*)malloc(2*sizeof(int));
    int *k =key();
    if(ktype) {
        keys[0] = k[0];
        keys[1] = k[2];
    } else{
        keys[0]=k[0];
        keys[1]=k[1];
    }
    return keys;
}

