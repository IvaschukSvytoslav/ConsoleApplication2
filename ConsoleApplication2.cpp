using System;
using System.Collections;
using System.Collections.Generic;

public class Journal : IComparable<Journal>
{
    public string Name{ get; set; }
    public decimal Price{ get; set; }
    public int PageCount{ get; set; }
    public int SalesRating{ get; set; } // ������� ������� �� ������ 10 ����

        public Journal(string name, decimal price, int pageCount, int salesRating)
    {
        Name = name;
        Price = price;
        PageCount = pageCount;
        SalesRating = salesRating;
    }

    // ��������� ���������� IComparable ��� ��������� �� �����
    public int CompareTo(Journal other)
    {
        if (other == null) return 1;
        return Price.CompareTo(other.Price);
    }

    public override string ToString()
    {
        return $"{Name}: ֳ�� = {Price} ���, ������� = {PageCount}, ������� ������� = {SalesRating}/10";
    }
}

// ��������� ���������� IComparer ��� ��������� �� ������� ������� � ��������� �������
public class JournalComparer : IComparer<Journal>
{
    private readonly ComparisonType comparisonType;

    public enum ComparisonType
    {
        PageCount,
        SalesRating
    }

    public JournalComparer(ComparisonType type)
    {
        comparisonType = type;
    }

    public int Compare(Journal x, Journal y)
    {
        if (x == null || y == null) throw new ArgumentException("����������� �������� ��� ���������");

        return comparisonType switch
        {
            ComparisonType.PageCount = > x.PageCount.CompareTo(y.PageCount),
                ComparisonType.SalesRating = > x.SalesRating.CompareTo(y.SalesRating),
                _ = > throw new ArgumentOutOfRangeException()
        };
    }
}

// ��������� ���������� IEnumerable ��� �������� �������
public class JournalCollection : IEnumerable<Journal>
{
    private List<Journal> journals = new List<Journal>();

    public void Add(Journal journal)
    {
        journals.Add(journal);
    }

    public IEnumerator<Journal> GetEnumerator()
    {
        return journals.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public void SortBySalesRating()
    {
        journals.Sort(new JournalComparer(JournalComparer.ComparisonType.SalesRating));
    }
}

class Program
{
    static void Main()
    {
        // ��������� �������� �������
        JournalCollection journalCollection = new JournalCollection();
        journalCollection.Add(new Journal("����� � �����", 50m, 100, 8));
        journalCollection.Add(new Journal("Forbes", 75m, 90, 9));
        journalCollection.Add(new Journal("National Geographic", 65m, 120, 10));
        journalCollection.Add(new Journal("������ �����", 55m, 110, 7));

        // ���������� ������� �� ��������� �������
        journalCollection.SortBySalesRating();

        // ���� �� �������
        Console.WriteLine("�������, ����������� �� ��������� �������:");
        foreach(var journal in journalCollection)
        {
            Console.WriteLine(journal);
        }
    }
}
