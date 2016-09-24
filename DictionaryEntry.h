/*
*	File : DictionaryEntry.h
*	Author :  Nicholas Robless
*	Date : 4/22/2016
*	Purpose : Header file of DictionaryEntry. Used to create and modify DictionaryEntry items.
*/

#ifndef DICTIONARYENTRY_H
#define DICTIONARYENTRY_H

#include <string>

class DictionaryEntry
{
    private:
        std::string word;
        std::string defn;
    public:
        DictionaryEntry();
        DictionaryEntry(std::string w, std::string d);

        bool operator<(std::string key) const;
        bool operator==(std::string key) const;
        bool operator>(std::string key) const;
        bool operator<(DictionaryEntry de) const;
        bool operator==(DictionaryEntry de) const;
        bool operator>(DictionaryEntry de) const;

        std::string getWord() const;
        std::string getDefn() const;
        void setWord(std::string w);
        void setDefn(std::string d);
};

#endif
