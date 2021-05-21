#pragma once

#include "Stack.h"

template <class T>
class TMultiStack
{
protected:
    int length;
    T* data;
    int stackCount;
    TStack<T>* stacks;
    T** oldData;
    void Repack(int ind);
public:
    TMultiStack(int size = 1, int stackCount = 1);
    TMultiStack(const TMultiStack<T>& ms);
    ~TMultiStack();
    TMultiStack<T>& operator=(const TMultiStack<T>& ms);
    void Push(T n, int ind);
    void Pop(int ind);
    T Get(int ind);
    string GetMultiStack();
    bool IsEmpty(int ind);
    bool IsFull(int ind);
    int Length();
    void Resize(int size = 1, int stackCount = 1);
    template <class T1>
    friend ostream& operator<<(ostream& ostr, const TMultiStack<T1>& MS);
    template <class T1>
    friend istream& operator>>(istream& istr, TMultiStack<T1>& MS);
    template <class T1>
    friend ofstream& operator<<(ofstream& ofstr, const TMultiStack<T1>& MS);
    int GetMinElemStack(); // Доп. Задание 3
    void WriteToFile(string filename); // Доп. Задание 2
};

template<class T>
inline TMultiStack<T>::TMultiStack(int size, int stackCount)
{
    if (size < 0 || stackCount < 0)
        throw -1;
    this->length = size;
    this->stackCount = stackCount;
    data = new T[size];
    for (int i = 0; i < size; i++)
        data[i] = 0;
    int count = size / stackCount;
    int* sizes = new int[stackCount];
    for (int i = 0; i < (stackCount - 1); i++)
        sizes[i] = count;
    sizes[stackCount - 1] = size - count * (stackCount - 1);
    oldData = new T * [stackCount];
    stacks = new TStack<T>[stackCount];
    int k = 0;
    for (int i = 0; i < stackCount; i++)
    {
        stacks[i].SetData(&data[k], sizes[i], -1);
        oldData[i] = &data[k];
        k += sizes[i];
    }
}

template<class T>
inline TMultiStack<T>::TMultiStack(const TMultiStack<T>& ms)
{
    this->length = ms.length;
    this->stackCount = ms.stackCount;
    this->data = new T[length];
    for (int i = 0; i < length; i++)
        this->data[i] = ms.data[i];
    this->oldData = new T * [stackCount];
    this->stacks = new TStack<T>[stackCount];
    for (int i = 0; i < stackCount; i++)
    {
        this->oldData[i] = ms.oldData[i];
        this->stacks[i] = ms.stacks[i];
    }
}

template<class T>
inline TMultiStack<T>::~TMultiStack()
{
    length = 0;
    stackCount = 0;
    if (data != 0)
    {
        delete[] data;
        delete[] stacks;
    }
    data = 0;
}

template<class T>
inline void TMultiStack<T>::Repack(int ind)
{
    int freeSize = 0;
    for (int i = 0; i < stackCount; i++)
        freeSize += stacks[i].Length() - stacks[i].Count();

    if (freeSize == 0)
        throw - 1;

    int count = freeSize / stackCount;
    int* sizes = new int[stackCount];
    for (int i = 0; i < stackCount; i++)
        sizes[i] = count + stacks[i].Count();
    sizes[ind] += freeSize % stackCount;

    T** newData = new T * [stackCount];

    int k = 0;
    for (int i = 0; i < stackCount; i++)
    {
        newData[i] = &data[k];
        k += sizes[i];
    }
    int i = 0;
    while (i < stackCount)
        if (newData[i] == oldData[i])
        {
            stacks[i].SetData(newData[i], sizes[i], stacks[i].Count() - 1);
            i++;
        }
        else if (newData[i] < oldData[i])
        {
            for (int j = 0; j < stacks[i].Count(); j++)
                newData[i][j] = oldData[i][j];
            stacks[i].SetData(newData[i], sizes[i], stacks[i].Count() - 1);
            i++;
        }
        else
        {
            int k = i;
            for (; k < stackCount; k++)
                if (!(newData[k] > oldData[k]))
                    break;
            k--;
            for (int s = k; s >= i; s--)
            {
                for (int j = sizes[s] - 1; j >= 0; j--)
                    newData[s][j] = oldData[s][j];
                stacks[s].SetData(newData[s], sizes[s], stacks[s].Count() - 1);
            }
            i = k + 1;
        }

    T** buf = oldData;
    oldData = newData;
    delete[] buf;
    delete[] sizes;
}

template<class T>
inline TMultiStack<T>& TMultiStack<T>::operator=(const TMultiStack<T>& ms)
{
    if (this == &ms)
        return *this;
    if (this->length != ms.length || this->stackCount != ms.stackCount)
    {
        this->length = ms.length;
        this->stackCount = ms.stackCount;
        delete[] this->data;
        delete[] this->stacks;
        this->data = new T[length];
        this->oldData = new T * [stackCount];
        this->stacks = new TStack<T>[stackCount];
    }
    for (int i = 0; i < length; i++)
        this->data[i] = ms.data[i];
    for (int i = 0; i < stackCount; i++)
    {
        this->oldData[i] = ms.oldData[i];
        this->stacks[i] = ms.stacks[i];
    }
    return *this;
}

template<class T>
inline void TMultiStack<T>::Push(T n, int ind)
{
    if (ind < 0 || ind >= stackCount)
        throw -1;
    if (stacks[ind].IsFull())
        Repack(ind);
    stacks[ind].Push(n);
}

template<class T>
inline void TMultiStack<T>::Pop(int ind)
{
    if (ind < 0 || ind >= stackCount)
        throw exception();
    stacks[ind].Pop();
}

template<class T>
inline T TMultiStack<T>::Get(int ind)
{
    if (ind < 0 || ind >= stackCount)
        throw exception();
    return stacks[ind].Get();
}

template<class T>
inline string TMultiStack<T>::GetMultiStack()
{
    string res = "";
    for (int i = 0; i < length; i++)
        res += data[i] + '0';
    return res;
}

template<class T>
inline bool TMultiStack<T>::IsEmpty(int ind)
{
    if (ind < 0 || ind >= stackCount)
        throw exception();
    return stacks[ind].IsEmpty();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int ind)
{
    if (ind < 0 || ind >= stackCount)
        throw exception();
    return stacks[ind].IsFull();
}

template<class T>
inline int TMultiStack<T>::Length()
{
    return length;
}

template<class T>
inline void TMultiStack<T>::Resize(int size, int stackCount)
{
    *this = TMultiStack(size, stackCount);
}

template <class T1>
ostream& operator<<(ostream& ostr, const TMultiStack<T1>& MS)
{
    for (int i = 0; i < MS.stackCount; i++)
        ostr << MS.stacks[i] << endl;
    return ostr;
}

template <class T1>
istream& operator>>(istream& istr, TMultiStack<T1>& MS)
{
    int stCount = 0;
    istr >> stCount;
    int size = 0;
    istr >> size;
    MS.Resize(size, stCount);
    for (int i = 0; i < stCount; i++)
        istr >> MS.stacks[i] << endl;
    return istr;
}

template<class T1>
inline ofstream& operator<<(ofstream& ofstr, const TMultiStack<T1>& MS)
{
    for (int i = 0; i < MS.stackCount; i++)
        ofstr << MS.stacks[i];
    return ofstr;
}

template<class T>
inline int TMultiStack<T>::GetMinElemStack() //Доп. Задание 3
{
    int minstack = 0;
    for (int i = 1; i < stackCount; i++)
        if (stacks[i].Count() < stacks[minstack].Count())
            minstack = i;
    return minstack;
}

template<class T>
inline void TMultiStack<T>::WriteToFile(string name) // Доп. задание 2
{
    ofstream fout(name.c_str());
    fout << *this;
    fout.close();
}

