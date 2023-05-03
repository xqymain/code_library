LL qpower(LL x, LL n, LL m)
{
    LL res = 1;
    while (n > 0){
        if  (n & 1)
            res = (res * x) % m;
        x = (x * x) % m;
        n >>= 1;
    }
    return res;
}
///
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b){
    return a / gcd(a, b) * b;
}
///
unsigned xor_n(unsigned n){
	unsigned t = n & 3;
	if (t & 1) return t / 2u ^ 1;
	return t / 2u ^ n;
}
