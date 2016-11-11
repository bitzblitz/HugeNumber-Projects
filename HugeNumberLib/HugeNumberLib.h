#pragma once

#ifdef HUGENUMBERLIBRARY_EXPORTS  
#define HUGENUMBERLIBRARY_API __declspec(dllexport)   
#else  
#define HUGENUMBERLIBRARY_API __declspec(dllimport)   
#endif  

#include <vector>
#include <string>

using namespace std;

class HUGENUMBERLIBRARY_API HugeNumber:public vector<bool>
	{
	private:
		typedef vector<bool>::_Vectype::_Myt::value_type _MyWord;
		typedef vector<bool>::_Vectype::iterator _MyWordIterator;
		static bool AddBit(_MyWord& Word, _MyWord Bit);
		static bool SubtractBit(_MyWord& Word, _MyWord Bit);
		void AddWord(_MyWordIterator Dest, _MyWord W);
		void SubtractWord(_MyWordIterator Dest, _MyWord W);
	public:
		HugeNumber(long long Value=0);
		HugeNumber(_XSTD initializer_list<bool> _Ilist):vector<bool>(_Ilist)
			{
			}
		HugeNumber(_XSTD initializer_list<int> _Ilist)
			{
			for(int b:_Ilist)
				push_back(b!=0);
			}

		template<class T>
		HugeNumber(const basic_string<T> BitString)
			{
			FromString(BitString);
			}

		template<class C>
		HugeNumber(const C* Chars)
			{
			FromChars(Chars);
			}

		HugeNumber(const HugeNumber& Other):vector<bool>(Other)
			{
			}

		HugeNumber(const HugeNumber&& Other):vector<bool>(Other)
			{
			}

		~HugeNumber();
		void FromInt(long long Value);
		// Turn HugeNumber into a normal integer.
		long long ToInt()	const throw(domain_error);

		operator long long() const throw(domain_error)
			{
			return ToInt();
			}

		// stringify the HugeNumber: convert to text representation, low bit first.
		template<class T>
		operator std::basic_string<T>() const
			{
			std::basic_string<T> res;
			for(bool b:*this)
				res.push_back(b?static_cast<T>('1'):static_cast<T>('0'));
			return res;
			}

		template<class T>
		HugeNumber& FromString(basic_string<T> BitString)
			{
			clear();
			for(auto ch:BitString)
				{
				switch(ch)
					{
					case '1':
						push_back(true);
						break;
					case '0':
						push_back(false);
						break;
					}
				}
			return *this;
			}

		template<class C>
		HugeNumber& FromChars(C const* Chars)
			{
			clear();
			while(*Chars != static_cast<C>('\0'))
				{
				switch(*Chars++)
					{
					case '1':
						push_back(true);
						break;
					case '0':
						push_back(false);
						break;
					}
				}
			return *this;
			}

		// remove trailing 0's
		const HugeNumber& Trim();

		// return a negated copy of this
		HugeNumber Negate() const;

		int CompareTo(const HugeNumber& Other) const;

		friend HugeNumber HUGENUMBERLIBRARY_API operator +(const HugeNumber& Left, const HugeNumber& Right);

		friend HugeNumber HUGENUMBERLIBRARY_API operator -(const HugeNumber& Left, const HugeNumber& Right);

		HugeNumber operator -() const
			{
			return Negate();
			}

		friend bool HUGENUMBERLIBRARY_API operator <(const HugeNumber& Left, const HugeNumber& Right)
			{
			return Left.CompareTo(Right)<0;
			}

		friend bool HUGENUMBERLIBRARY_API operator <=(const HugeNumber& Left, const HugeNumber& Right)
			{
			return Left.CompareTo(Right)<=0;
			}

		friend bool HUGENUMBERLIBRARY_API operator ==(const HugeNumber& Left, const HugeNumber& Right)
			{
			return Left.CompareTo(Right)==0;
			}

		friend bool HUGENUMBERLIBRARY_API operator !=(const HugeNumber& Left, const HugeNumber& Right)
			{
			return Left.CompareTo(Right)!=0;
			}

		friend bool HUGENUMBERLIBRARY_API operator >=(const HugeNumber& Left, const HugeNumber& Right)
			{
			return Left.CompareTo(Right)>=0;
			}

		friend bool HUGENUMBERLIBRARY_API operator >(const HugeNumber& Left, const HugeNumber& Right)
			{
			return Left.CompareTo(Right)>0;
			}

		HugeNumber& operator =(long long Value)
			{
			FromInt(Value);
			return *this;
			}

		HugeNumber& operator=(const HugeNumber& Right)
			{
			vector<bool>::operator=(Right);
			return *this;
			}
	};

inline bool HugeNumber::AddBit(_MyWord& Word, _MyWord Bit)
	{
	if((Word&Bit)==0)
		{
		Word|=Bit;
		return false;
		}
	_MyWord sBit=Bit<<1;
	Word^=Bit|sBit;
	return (Word&sBit)!=0;
	}

inline bool HugeNumber::SubtractBit(_MyWord& Word, _MyWord Bit)
	{
	if((Word&Bit)!=0)
		{
		Word&=~Bit;
		return false;
		}
	_MyWord sBit=Bit<<1;
	Word^=Bit|sBit;
	return (Word&sBit)==0;
	}
