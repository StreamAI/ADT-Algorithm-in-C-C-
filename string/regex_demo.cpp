#include<iostream>
#include<string>
#include<regex>

using namespace std;

static void regex_search_demo(void)
{
    string data1("XML tag: <tag-name>the value</tag-name>.");		// Ҫ����ƥ�������1
    regex reg1("<(.*)>(.*)</(\\1)>");			// ����������ʽ1������ת���ַ�\\1 ʵ������'\1'����ʾ����һ����ͬ
    bool found = regex_match(data1, reg1);		// ����ƥ�������ַ�����
    cout << "regex_match result:    " << (found ? "found" : "not found") << endl;

    regex reg2(".*<(.*)>(.*)</(\\1)>.*");		// ����������ʽ2
    found = regex_match(data1, reg2);			// ����ƥ�������ַ�����
    cout << "regex_match result:    " << (found ? "found" : "not found") << endl;

    found = regex_search(data1, reg1);			// ������Ҳ����ַ�����
    cout << "regex_search result:   " << (found ? "found" : "not found") << endl;
    cout << endl;

    smatch mres;		// ����ƥ��ķ��ؽ������ƥ����Ϊstring object ��ʹ��smatch ���ͣ�wstring ��Ӧwsmatch��
    					//��ƥ����ΪC-string ��ʹ��cmatch ���ͣ�wchar_t ��Ӧwcmatch��
    found = regex_search(data1, mres, reg1);	// ����ģʽƥ�������������
    if(found == true) {
        cout << "mres.size():           " << mres.size() << endl;			// ƥ�����ĸ���������ͼ��ʾdata1 ����4 ��ƥ�����mres[0] ~ mres[3]
        cout << "mres.str():            " << mres.str() << endl;			// ��ӡ����ƥ�������ַ����У���ʹ��str(n) ��ö�Ӧ���ֵ�ƥ���ַ����У�n ��Ӧ��ͼ��0 ~ 3
        cout << "mres.length():         " << mres.length() << endl;			// ��ӡ����ƥ�������ַ�������ʹ��length(n) ��ö�Ӧ���ֵ��ַ�������n ��Ӧ��ͼ��0 ~ 3
        cout << "mres.position():       " << mres.position() << endl;		// ��ӡ����ƥ��������ʼλ�ã���ʹ��position(n) ��ö�Ӧ���ֵ�ƥ���ַ�λ�ã�n ��Ӧ��ͼ��0 ~ 3
        cout << "mres.prefix().str():   " << mres.prefix().str() << endl;	// ��ʾ��һ��ƥ��ϸ���ַ�ǰ���������ַ�
        cout << "mres.suffix().str():   " << mres.suffix().str() << endl;	// ��ʾ���һ��ƥ��ϸ���ַ��󷽵������ַ�
        cout << endl;
    }

    string data2 =  "<person>\n"
                    "<first>Nico</first>\n"
                    "<last>Joson</last>\n"
                    "</person>\n";				// Ҫ����ƥ�������2
    auto pos = data2.cbegin();					// ����Ҫ�������ݵ���ʼλ��
    while (regex_search(pos, data2.cend(), mres, reg1)) {
        cout << "match result:      	" << mres.str() << endl;	// ��ӡƥ����
        cout << "tag-name:          	" << mres.str(1) << endl;	// ��ӡƥ�����ĵ�һ�飬Ҳ����ͼ�е�m[1]
        cout << "the value:         	" << mres.str(2) << endl;	// ��ӡƥ�����ĵڶ��飬Ҳ����ͼ�е�m[2]
        pos = mres.suffix().first;		// ���������ݵ���ʼλ������Ϊ��ƥ��������һ���ַ�
    }
}

static void regex_replace_demo(void)
{
    string data1 =  "<person>\n"
                    "<first>Nico</first>\n"
                    "<last>Joson</last>\n"
                    "</person>\n";				// Ҫ����ƥ�������1
    cout << "The original data:" << endl << data1 << endl;
    regex reg1("<(.*)>(.*)</(\\1)>");			// ����������ʽ1������ת���ַ�\\1 ʵ������'\1'����ʾ����һ����ͬ
    string repl1 = R"(<$1 value = "$2"/>)";		// Ҫ��ƥ�����滻�ɵ��ַ�����ʽ��R ��ʾraw string ��ʡ��ת���ַ�
    											// $1 ��$2 ��ʾƥ����ӱ��ʽ��ͬ��ͼ�е�m[1] ��m[2]��Ҳ��tag-name ��the value��
    string res1 = regex_replace(data1, reg1, repl1);	// ��ƥ�����滻Ϊrepl1 ����ʽ
    cout << "After replacement data:" << endl << res1 << endl;
}

static void regex_token_separator_demo(void)
{
    string data1 = "Hello world, friend\t of mine!\n";      // Ҫ�ָ���ַ���1
    regex sep("[ \t\n]*[,;.:! ][ \t\n]*");              // ʹ��������ʽ����ָ���,;.:!space��ǰ������������space\t\n
    // ���ָ�������Ϊƥ�����token_iterator ��ȡƥ��������֮������ݣ��൱��ʵ��������з���token separator �Ĺ���
    sregex_token_iterator pos1(data1.cbegin(), data1.cend(), sep, -1);  // ���һ������ -1 ��ʾ��ÿ��ƥ��������֮��������и���Ȥ
                                                                // 0 ��ʾ������ƥ�����и���Ȥ�൱��m[0]��n ��ʾ�Ե�n ��ƥ�������и���Ȥ�൱��m[n]
    sregex_token_iterator end;
    for (; pos1 != end; ++pos1)
        cout << "token:     " << *pos1 << endl;         // �����token separator �зֳ���ÿ��token
    cout << endl;

    string data2 =  "<person>\n"
                    "<first>Nico</first>\n"
                    "<last>Joson</last>\n"
                    "</person>\n";				// Ҫ����ƥ�������2
    regex reg1("<(.*)>(.*)</(\\1)>");			// ����������ʽ1
    sregex_token_iterator pos2(data2.cbegin(), data2.cend(), reg1, {0, 2}); // ���һ������{0,2}��ʾ������ƥ�����к͵�2��ƥ�������и���Ȥ��Ҳ��m[0]��m[2]
    for (; pos2 != end; ++pos2)
        cout << "match:     " << pos2->str() << endl;      // �������Ȥ��ƥ����
    cout << endl;
}

int main(int argc, char* argv[])
{ 
    regex_search_demo();
    cout << endl;
    regex_replace_demo();
    cout << endl;
    regex_token_separator_demo();
    cout << endl;
    
    return 0;
}