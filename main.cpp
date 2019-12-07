#include "String.h"

int main()
{
	{
		cout << "************** Testing constructors **************" << endl;

		String<char> str1;
		cout << "s1: " << str1 << endl;
		String<char> s2("char string");
		cout << "s2: " << s2 << endl;
		String<char> s3(s2);
		cout << "s3: " << s3 << endl;

		String<wchar_t> sw1;
		cout << "sw1: " << sw1 << endl;
		String<wchar_t> sw2(L"wchar string");
		cout << "sw2: " << sw2 << endl;
		String<wchar_t> sw3(sw2);
		cout << "sw3: " << sw3 << endl;
	}
	{
		String<char> s1("chainmaw");
		String<char> s2(s1);
		cout << "s1: " << s1 << ", s2: " << s2 << endl;
		s2[5] = 's';
		cout << "s1: " << s1 << ", s2: " << s2 << endl;

		String<wchar_t> sw1(L"chainmaw");
		String<wchar_t> sw2(sw1);
		cout << "sw1: " << sw1 << ", sw2: " << sw2 << endl;
		sw2[5] = 's';
		cout << "sw1: " << sw1 << ", sw2: " << sw2 << endl;
	}
	{
		cout << "************** Testing operator= **************" << endl;

		String<char> s1("Char operator =");
		String<char> s2 = s1;
		cout << "s2: " << s2 << endl;
		s2 = "New char string";
		cout << "s2: " << s2 << endl;

		String<wchar_t> sw1(L"WChar test operator =");
		String<wchar_t> sw2 = sw1;
		cout << "sw2: " << sw2 << endl;
		sw2 = L"New wchar string";
		cout << "sw2: " << sw2 << endl;
	}
	cout << endl;
	{
		cout << "************** Testing length, empty **************" << endl;

		String<char> s;
		cout << " s: " << s << endl;
		cout << " s length: " << s.length() << endl;
		cout << " s empty: " << s.empty() << endl;

		String<wchar_t> sw(L"hello");
		cout << " ws: " << sw << endl;
		cout << " ws length: " << sw.length() << endl;
		cout << " ws empty: " << boolalpha << sw.empty() << endl;
	}
	cout << endl;
	{
		cout << "************** Testing operators + **************" << endl << endl;
		cout << "Char strings:" << endl;
		cout << String<char>("hello ") + String<char>("world") << endl;
		cout << String<char>("something ") + String<char>("gone") << endl << endl;

		cout << "WChar strings:" << endl;
		cout << String<wchar_t>(L"this is ") + String<wchar_t>(L"wchar_t string") << endl;
		cout << String<wchar_t>(L"check this out.") + String<wchar_t>(L"It works") << endl;
	}
	cout << endl;
	{
		cout << "************** Testing bool operators **************" << endl << endl;
		cout << "Char strings:" << endl;
		cout << "aabc == aabc: " << boolalpha << (String<char>("aabc") == String<char>("aabc")) << endl;
		cout << "abc == aabc: " << boolalpha << (String<char>("abc") == String<char>("aabc")) << endl;
		cout << "aabc != aabc: " << boolalpha << (String<char>("aabc") != String<char>("aabc")) << endl;
		cout << "aabc != abc: " << boolalpha << (String<char>("aabc") != String<char>("abc")) << endl;
		cout << "abc < aabc: " << boolalpha << (String<char>("abc") < String<char>("aabc")) << endl;
		cout << "aabc < abc: " << boolalpha << (String<char>("aabc") < String<char>("abc")) << endl;
		cout << "abc > aabc: " << boolalpha << (String<char>("abc") > String<char>("aabc")) << endl;
		cout << "aabc > abc: " << boolalpha << (String<char>("aabc") > String<char>("abc")) << endl;
		cout << "abc <= aabc: " << boolalpha << (String<char>("abc") <= String<char>("aabc")) << endl;
		cout << "abc <= abc: " << boolalpha << (String<char>("abc") <= String<char>("abc")) << endl;
		cout << "aabc <= abc: " << boolalpha << (String<char>("aabc") <= String<char>("abc")) << endl;
		cout << "aabc >= abc: " << boolalpha << (String<char>("aabc") >= String<char>("abc")) << endl;
		cout << "abc >= abc: " << boolalpha << (String<char>("abc") >= String<char>("abc")) << endl;
		cout << "abc >= aabc: " << boolalpha << (String<char>("abc") >= String<char>("aabc")) << endl;
		cout << endl;

		cout << "Wchar_t strings:" << endl;
		cout << "aabc == aabc: " << boolalpha << (String<wchar_t>(L"aabc") == String<wchar_t>(L"aabc")) << endl;
		cout << "abc == aabc: " << boolalpha << (String<wchar_t>(L"abc") == String<wchar_t>(L"aabc")) << endl;
		cout << "aabc != aabc: " << boolalpha << (String<wchar_t>(L"aabc") != String<wchar_t>(L"aabc")) << endl;
		cout << "aabc != abc: " << boolalpha << (String<wchar_t>(L"aabc") != String<wchar_t>(L"abc")) << endl;
		cout << "abc < aabc: " << boolalpha << (String<wchar_t>(L"abc") < String<wchar_t>(L"aabc")) << endl;
		cout << "aabc < abc: " << boolalpha << (String<wchar_t>(L"aabc") < String<wchar_t>(L"abc")) << endl;
		cout << "abc > aabc: " << boolalpha << (String<wchar_t>(L"abc") > String<wchar_t>(L"aabc")) << endl;
		cout << "aabc > abc: " << boolalpha << (String<wchar_t>(L"aabc") > String<wchar_t>(L"abc")) << endl;
		cout << "abc <= aabc: " << boolalpha << (String<wchar_t>(L"abc") <= String<wchar_t>(L"aabc")) << endl;
		cout << "abc <= abc: " << boolalpha << (String<wchar_t>(L"abc") <= String<wchar_t>(L"abc")) << endl;
		cout << "aabc <= abc: " << boolalpha << (String<wchar_t>(L"aabc") <= String<wchar_t>(L"abc")) << endl;
		cout << "aabc >= abc: " << boolalpha << (String<wchar_t>(L"aabc") >= String<wchar_t>(L"abc")) << endl;
		cout << "abc >= abc: " << boolalpha << (String<char>("abc") >= String<char>("abc")) << endl;
		cout << "abc >= aabc: " << boolalpha << (String<char>("abc") >= String<char>("aabc")) << endl;
		cout << endl;
	}
	return 0;
}