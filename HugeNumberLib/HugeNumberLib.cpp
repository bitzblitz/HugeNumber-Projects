#include "stdafx.h"
#include "HugeNumberLib.h"

using namespace std;

void HugeNumber::AddWord(_MyWordIterator Dest, _MyWord W)
	{
	if(Dest==_Myvec.end())
		{
		push_back(false);	// need more bits
		Dest=_Myvec.end();
		--Dest;
		}
	_MyWord mask=1;
	while(mask!=0&&mask<W)
		{
		if((W&mask)!=0)
			{
			register _MyWord m=mask;
			while(AddBit(*Dest, m))
				m<<=2;  // carry required.
			if(m==0)
				AddWord(Dest+1, 1);	// carry went off the end.
			}
		mask<<=1;
		}
	}

void HugeNumber::SubtractWord(_MyWordIterator Dest, _MyWord W)
	{
	if(Dest==_Myvec.end())
		{
		push_back(false);	// need more bits
		Dest=_Myvec.end();
		--Dest;
		}
	_MyWord mask=1;
	while(mask!=0&&mask<W)
		{
		if((W&mask)!=0)
			{
			register _MyWord m=mask;
			while(m && SubtractBit(*Dest, m))
				m<<=2;  // borrow required.
			if(m==0)
				SubtractWord(Dest+1, 1);	// borrow went off the end.
			}
		mask<<=1;
		}
	}

HugeNumber::HugeNumber(long long Value)
	{
	FromInt(Value);
	}

HugeNumber::~HugeNumber()
	{
	}

void HugeNumber::FromInt(long long Value)
	{
	clear();
	while(Value!=0)
		{
		auto q_r=div(Value, (long long)-2);
		Value=q_r.quot;	// do divide and modulo at the same time for efficiency.
		if(q_r.rem<0)
			++Value;
		push_back(q_r.rem!=0);
		}

	}


// Turn HugeNumber into a normal integer.
long long HugeNumber::ToInt()	const
	{
	if(size()>65&&back()) // long long.MaxValue takes 65 bits.
		throw domain_error("Value too large for long long type");
	long long result=0;
	long long bit_value=1;
	for(unsigned int b=0;b<size();++b)
		{
		result+=operator[](b)?bit_value:0;
		bit_value*=-2;
		}
	return result;
	}

const HugeNumber& HugeNumber::Trim()
	{
	while(size()>0&&!back())
		pop_back();
	return *this;
	}

HugeNumber HugeNumber::Negate() const
	{
	HugeNumber result(*this);
	_MyWord carry=0;
	for(auto& w:result._Myvec)
		{
		register _MyWord mask=1;
		register _MyWord original=w;
		if(carry)
			{
			w^=carry;
			mask<<=1;
			}
		while(mask!=0)
			{
			if(w&mask)
				{
				mask<<=1;
				w^=mask;
				}
			mask<<=1;
			}
		carry=(original&w&(1<<(_VBITS-1)))?1:0;
		}
	if(carry!=0||back()&&result.back())
		result.push_back(1);	// extend our list if the negate carried
	else
		result.Trim();	// may no longer need high order bit
	return result;
	}

#pragma region Friends
int HugeNumber::CompareTo(const HugeNumber& Other) const
	{
	// find the highest order bits in each
	int my_high_bit=size()-1;
	while(my_high_bit>0&&!operator[](my_high_bit))
		--my_high_bit;
	int other_high_bit=Other.size()-1;
	while(other_high_bit>0&&!Other[other_high_bit])
		--other_high_bit;
	// testing unequal length numbers requires only high order bit:
	if(my_high_bit>other_high_bit)
		return (my_high_bit&1)==0?1:-1;
	else if(my_high_bit<other_high_bit)
		return (other_high_bit&1)==0?-1:1;
	// look for unequal bits starting from high end in equal length numbers:
	int word=_Myvec.size()-1;
	while(word>=0&&_Myvec[word]==Other._Myvec[word])
		--word;	// skip over matching words
	if(word<0)
		return 0;	// all bits matched
	register int bit=_VBITS-1;
	register _MyWord mask=1<<bit;
	register _MyWord myBits=_Myvec[word]&~(Other._Myvec[word]);	// my different bits.
	register _MyWord otherBits=~(_Myvec[word])&(Other._Myvec[word]);	// other different bits
	if(myBits>otherBits)
		{	// I have the highest bit
		while((myBits&mask)==0&&bit>0)
			{
			--bit;
			mask>>=1;
			}
		return (bit&1)==0?1:-1;
		}
	else
		{	// Other has the highest bit
		while((otherBits&mask)==0&&bit>0)
			{
			--bit;
			mask>>=1;
			}
		return (bit&1)==0?-1:1;
		}
	return 0;	// all bits matched.
	}

HugeNumber & HugeNumber::operator+=(const HugeNumber& Right)
	{
	resize(max(size(), Right.size())+2);	// pad out the result to the maximum size.
	for(unsigned int b=0;b<Right.size();++b)
		{
		if(Right[b])
			{
			int bit=b;
			while(AddBit(bit))
				bit+=2;
			}
		}
	Trim();
	return *this;
	}

HugeNumber operator +(const HugeNumber& Left, const HugeNumber& Right)
	{
	HugeNumber result(Left);
	return result+=Right;
	}

//HugeNumber operator +(const HugeNumber& Left, const HugeNumber& Right)
//	{
//	HugeNumber result(Left);
//	result.resize(max(Right.size(), Left.size())+2);	// pad out the result to the maximum size.
//	auto rIter=Right._Myvec.begin();
//	for(auto w=result._Myvec.begin();w<result._Myvec.end();++w)
//		{
//		result.AddWord(w, *rIter++);
//		if(rIter==Right._Myvec.end())
//			break;
//		}
//	return result.Trim();
//	}

HugeNumber HUGENUMBERLIBRARY_API operator-(const HugeNumber & Left, const HugeNumber & Right)
	{
	HugeNumber result(Left);
	if(result.size()<Right.size())
		result.resize(Right.size()+2);	// pad out the result to the maximum size.
	auto rIter=Right._Myvec.begin();
	for(auto w=result._Myvec.begin();w<result._Myvec.end();++w)
		{
		result.SubtractWord(w, *rIter++);
		if(rIter==Right._Myvec.end())
			break;
		}
	result._Mysize+=2;
	return result.Trim();
	}

#pragma endregion

