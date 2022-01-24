#include "TextQuery.h"

#include "QueryResult.h"

TextQuery::TextQuery(ifstream& is) :m_file(new vector<string>)
{
    string text;
    while (getline(is, text))                    //���ı��ж�ȡһ��
    {
        m_file->push_back(text);                  //ÿ����Ϊһ��Ԫ�ش���vector
        int n = m_file->size() - 1;               //�кţ��±�
        istringstream line(text);
        string word;
        while (line >> word)                      //��ÿ���ж�ȡ��������
        {
            auto& lines = m_wm[word];             //map���±������������ؼ��ֲ����ڣ��򴴽�һ����Ԫ�ء�                                            
                                                //��valueΪ��ָ��
                                                //lines�����ã��ı���Ҳ��ı�����ָ��
            if (!lines)
            {
                lines.reset(new set<line_no>);  //��һ������wordΪ��ָ�룬�������ָ���µ�set
            }
            lines->insert(n);                   //���кŲ���set������ظ���ִ���κβ���
        }
    }
}


TextQuery::~TextQuery()
{
}


QueryResult TextQuery::query(const string& sought)const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = m_wm.find(sought);
    if (loc == m_wm.end())
    {
        return QueryResult(sought, nodata, m_file);           //���û�ҵ������ؿ�set
    }
    else
    {
        return QueryResult(sought, loc->second, m_file);      //����ָ��set��ָ��
    }
}
