/*
*	File : DictionaryEntry.h
*	Author :  Nicholas Robless
*	Date : 4/22/2016
*	Purpose : Header file of DictionaryEntry. Used to create and modify DictionaryEntry items.
*/

#include "DictionaryEntry.h"

DictionaryEntry::DictionaryEntry() : word(""),defn("")
{
}

DictionaryEntry::DictionaryEntry(std::string w, std::string d) : word(w),defn(d)
{
}

bool DictionaryEntry::operator<(std::string key) const
{
    return word < key;
}

bool DictionaryEntry::operator==(std::string key) const
{
    return word == key;
}

bool DictionaryEntry::operator>(std::string key) const
{
    return word > key;
}

bool DictionaryEntry::operator<(DictionaryEntry de) const
{
    return word < de.getWord();
}

bool DictionaryEntry::operator==(DictionaryEntry de) const
{
    return word == de.getWord();
}

bool DictionaryEntry::operator>(DictionaryEntry de) const
{
    return word > de.getWord();
}

std::string DictionaryEntry::getWord() const
{
    return word;
}

std::string DictionaryEntry::getDefn() const
{
    return defn;
}

void DictionaryEntry::setWord(std::string w)
{
    word = w;
}

void DictionaryEntry::setDefn(std::string d)
{
    defn = d;
}
