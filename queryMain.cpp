#include "QueryResult.h"
#include "TextQuery.h"
int main()
{
    void runQuery(ifstream & file);


    ifstream file("file.txt");
    runQuery(file);
    return 0;

}


ostream& print(ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " times" << endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line" << num + 1 << ") " << *(qr.file->begin() + num) << endl;
    }
    return os;
}

void runQuery(ifstream& file)
{
    TextQuery tq(file);
    while (true)
    {
        cout << "enter word to look for,or q to quit" << endl;
        string s;
        if (!(cin >> s) || s == "q")
        {
            break;
        }
        print(cout, tq.query(s)) << endl;
    }

}