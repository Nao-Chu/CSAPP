#include <iostream>

using namespace std;
void T2_60(unsigned x, int i, unsigned char b)
{
	x = 0x12345678;
	i = 3;
	b = 0xAB;

	unsigned char*y = (unsigned char*)&x;
	y[i] = b;
	cout << hex << x<< endl;
}

void T2_61(int x)
{
	x = 0xFFFFFFFF;
	int bit = (sizeof(int) << 3) - 1;
	int c0 = ~(x|0x0);
	int c1 = (x|0x0);
	int c2 = (x>>bit) &0x1;
	int c3 = x & 0x1;
	cout << !c0 << "," << !c1 << "," << !c2 << "," << c3 << endl;
}

void T2_62(int x)
{
	x = 0x80000000;
	int bit = (sizeof(int) << 3);
	int y = x >> bit &0x1;
	cout << hex << y << endl;
}

void T2_63()
{
	int bit = (sizeof(int) << 3);
	unsigned x = 0xF1234567;
	unsigned xsra = (int)x >> 4;

	cout << hex << xsra << "\t";
	int tmp = (0x1 << 4) - 1;
	tmp <<= 32-4;
	xsra &= ~tmp;
	cout << hex << xsra << endl;

	int x1 = 0x81234567;
	int xsrl = (unsigned)x1 >> 4;
	cout << hex << xsrl << " \t";
	int tmp1 = (0x1 << 4 + 1) - 1;
	tmp1 <<= 32-(4 + 1);
	int m = 2*((xsrl&tmp1) != 0x0) - 1;
	xsrl |= (tmp1<<m);
	cout << hex << xsrl << endl;
}

void T2_64(unsigned x)
{
	x = 0x1;
	int mask = 0x55555555;
	cout << hex << (x&mask) << endl;
}

void T2_65()
{
	unsigned x = 0x9;
	x ^= (x>>1);
	x ^= (x>>2);
	x ^= (x>>4);
	x ^= (x>>8);
	x ^= (x>>16);
	cout << (x&0x1) << endl;
}

void T2_66()
{
	unsigned x = 0XFF;
	x |= (x>>1);
	x |= (x>>2);
	x |= (x>>4);
	x |= (x>>8);
	x |= (x>>16);
	x = x^(x>>1);
	cout << hex << x << endl;

}

void T2_68()
{
	int n = 17;

	unsigned y = 0x1 << n+1;
	cout << hex << y - 1 << endl;
}

void T2_69()
{
	int n = 4;
	unsigned x = 0x12345678;
	unsigned y = x >> 32-n;
	x <<= n;
	x |= y;
	cout << hex << x << endl;
}

void T2_70()
{
	int x = -7;
	int n = 4;
	x >>= (n-1);
	cout << hex << !x << "," << !(~x) << endl;
}

void T2_73()
{
	int x = 0x1 << 30;
	int y = 0x1 << 30;
	int c = x + y;
	int ans = x+y;
	x>>=31;
	y>>=31;
	c>>=31;
	int pos_ovf = ~x&~y&c;
	int neg_ovf = x&y&~c;
	int novf    = ~(pos_ovf|neg_ovf);

	pos_ovf &= INT8_MAX;
	novf &= ans;
	neg_ovf &= INT8_MIN;
	cout << hex << pos_ovf << ",";
        cout << novf << ",";
	cout << neg_ovf	<< endl;
}

void T2_74()
{
	int x = 0x1;
	int y = 0xf;
	int z = x-y;
	x>=31;
	y>=31;
	z>=31;
	int p = (x != y) && (y == t);

	cout << !novf < endl;
}

void T2_77()
{
	int x = 10;
	int y0 = 17;
	x<<4 + x;
	int y1 = -17;
	x - x<<4 - x<<1;
	int y2 = 60;
	x<< 8 - x<<2;
	int y3 = -12;
	x<<2 - x<<4;
	
}

void T2_78()
{
	int x = 0x11;
	int k = 3;
	int y = x >> k;
	y += (x>>31) && (x&( (1<<k)-1));
	return y;
}

void T2_79()
{
	int x = 0x0100;
	int y = x >> 2;
	y += (x>>31) && (x&7);
	y = y << 1 + y;
}


int main()
{
	T2_60(0x1,3,0xa);
	T2_61(0x1);
	T2_62(0x1);
	T2_63();
	T2_64(0x1);
	T2_65();
	T2_66();
	T2_68();
	T2_69();
	T2_70();
	T2_73();
}
