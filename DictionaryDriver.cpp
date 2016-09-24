/*
*	File : DictionaryEntryEntry.h
*	Author :  Nicholas Robless
*	Date : 4/22/2016
*	Purpose : Header file of DictionaryDriver. Used to create and modify a BST full of DictionaryEntry items according to user input.
*/

#include "DictionaryDriver.h"

// Global Functions
std::istream& operator>>(std::istream& is, DictionaryEntry& de)
{
    std::string word;
    std::string defn;

    is >> word;
    getline(is, defn);

    de.setWord(word);
    de.setDefn(defn);

    return is;
}

std::ostream& operator<<(std::ostream& os, const DictionaryEntry& de)
{
    os << de.getWord() << ": " << de.getDefn() << '\n';
    return os;
}

void visit(std::string& aKey)
{
    std::cout << aKey << '\n';
}

void visit(DictionaryEntry& anItem)
{
    std::cout << anItem << '\n';
}

// Constructor / Destructor
DictionaryDriver::DictionaryDriver() : treeCopied(false)
{
}

DictionaryDriver::~DictionaryDriver()
{
}

/////////////////////////////////////////////////
//     Helper methods Section
/////////////////////////////////////////////////
std::string DictionaryDriver::convertWord(std::string word)
{
	//Convert word to camelcase.
    word[0] = std::toupper(word[0]);
    for(std::size_t i = 1 ; i < word.length(); i++)
    {
        word[i] = std::tolower(word[i]);
    }
    return word;
}

void DictionaryDriver::printMenu()
{
	std::cout << "What would you like to do?" << '\n';
	std::cout << "Options: search, copy, add, remove, save, test, quit" << '\n';
	std::cout << "Your choice: ";
}

void DictionaryDriver::save(std::string order, std::string tree, ofstream& outFile)
{
    if (tree == "original")
    {
        bst.save(outFile, order);
    }
    else if (tree == "copy")
    {
        if (!treeCopied)
        {
            copyBst = new BinarySearchTree<DictionaryEntry, std::string>(bst);
            std::cout << "Original tree copied." << '\n';
            treeCopied = true;
        }
        copyBst->save(outFile, order);
    }
    else
    {
        std::cout << "Invalid input, please try again." << '\n';
    }

    std::cout << "Saved dictionary to file." << '\n';
}

/////////////////////////////////////////////////
//      Tests Functions Section
/////////////////////////////////////////////////
void DictionaryDriver::testAdd(BinarySearchTree<DictionaryEntry, std::string> dictionary)
{
    BinarySearchTree<DictionaryEntry, std::string>* copy = new BinarySearchTree<DictionaryEntry, std::string>(dictionary);

    std::string newWord;
    std::string newDefn;

    std::cout << "Enter the word you would like to add: ";
    std::cin >> newWord;
    cin.ignore();

    std::cout << "Enter its definition: ";
    std::getline(cin, newDefn);

    DictionaryEntry newEntry(newWord, newDefn);

    if (copy->add(newEntry))
    {
        std::cout << convertWord(newWord) << " added to dictionary." << '\n';
    }

    copy->inorderTraverse(visit);

    delete copy;
}

void DictionaryDriver::testRemove(BinarySearchTree<DictionaryEntry, std::string> dictionary)
{
    BinarySearchTree<DictionaryEntry, std::string>* copy = new BinarySearchTree<DictionaryEntry, std::string>(dictionary);

    std::string wordToDelete;
    std::cout << "Enter the word you would like to remove: ";
    std::cin >> wordToDelete;

    try
    {
        copy->removeEntry(convertWord(wordToDelete));
        std::cout << convertWord(wordToDelete) << " removed from dictionary." << '\n';
        copy->inorderTraverse(visit);
    }
    catch (NotFoundException e)
    {
        std::cerr << e.what();
    }

    delete copy;
}

void DictionaryDriver::testWriteToFile(BinarySearchTree<DictionaryEntry, std::string> dictionary)
{
    std::string outputFilename;
    std::cout << "Enter the output file name: " ;
    std::cin >> outputFilename;

    ofstream outFile;
    outFile.open(outputFilename);

    dictionary.save(outFile, "inorder");
    std::cout << "Saved dictionary to file." << '\n';

    outFile.close();
}

/////////////////////////////////////////////////
//      Run engine Section
/////////////////////////////////////////////////
void DictionaryDriver::createTree(std::string filename)
{
    ifstream file;
    file.open(filename);

    std::string line;

    while (std::getline(file,line))
    {
        if(line == "")
        {
            continue;
        }

        std::string word = line.substr(0,  line.find(' '));
        std::string defn = line.substr(line.find(' ') + 1);

        if(word == "")
        {
            continue;
        }

        word = convertWord(word);
        DictionaryEntry entry(word,defn);
        bst.add(entry);
    }

    file.close();
}

void DictionaryDriver::run()
{
    std::string command;
    printMenu();
	std::cin >> command;

	while(command != "quit")
    {
        if(command == "search")
        {
            std::string word;
            std::cout << "Enter the word to search for: ";
            std::cin >> word;
            word = convertWord(word);

            // search for the word
            try
            {
                if (bst.contains(word))
                {
                    std::cout << bst.getEntry(word);
                }
                else
                {
                    std::cout << "Word not found." << '\n';
                }
            }
            catch (NotFoundException e)
            {
                std::cerr << e.what();
            }
        }
        else if(command == "copy")
        {
            copyBst = new BinarySearchTree<DictionaryEntry, std::string>(bst);
            std::cout << "Original tree copied." << '\n';
            treeCopied = true;
        }
        else if(command == "add")
        {
            if (!treeCopied)
            {
                copyBst = new BinarySearchTree<DictionaryEntry, std::string>(bst);
                std::cout << "Original tree copied." << '\n';
                treeCopied = true;
            }

            std::string newWord;
            std::string newDefn;

            std::cout << "Enter the word you would like to add: ";
            std::cin >> newWord;
            cin.ignore();

            newWord = convertWord(newWord);

            std::cout << "Enter its definition: ";
            std::getline(cin, newDefn);

            DictionaryEntry newEntry(newWord, newDefn);

            if (copyBst->add(newEntry))
            {
                std::cout << convertWord(newWord) << " added to dictionary." << '\n';
            }
        }
        else if(command == "remove")
        {
            if (!treeCopied)
            {
                copyBst = new BinarySearchTree<DictionaryEntry, std::string>(bst);
                std::cout << "Original tree copied." << '\n';
                treeCopied = true;
            }

            std::string wordToDelete;
            std::cout << "Enter the word you would like to remove: ";
            std::cin >> wordToDelete;

            try
            {
                copyBst->removeEntry(convertWord(wordToDelete));
                std::cout << convertWord(wordToDelete) << " removed from dictionary." << '\n';
            }
            catch (NotFoundException e)
            {
                std::cerr << e.what();
            }
        }
        else if(command == "save")
        {
            std::string outputFilename;
            std::cout << "Enter the output file name: ";
            std::cin >> outputFilename;

            ofstream outFile;
            outFile.open(outputFilename);

            std::string whichTree;
            std::cout << "Which tree would you like to save?" << '\n';
            std::cout << "Options: original, copy" << '\n';
            std::cout << "Your choice: ";
            std::cin >> whichTree;

            std::string whichOrder;
            std::cout << "Which traversal order would you like to use?" << '\n';
            std::cout << "Options: inorder, preorder, postorder" << '\n';
            std::cout << "Your choice: ";
            std::cin >> whichOrder;

            save(whichOrder, whichTree, outFile);

            outFile.close();
        }
        else if(command == "test")
        {
            std::string testChoice;
            std::cout << "What test would you like to run?" << '\n';
            std::cout << "Options: add, remove, write" << '\n';
            std::cout << "Your choice: ";
            std::cin >> testChoice;

            if(testChoice == "add")
            {
                testAdd(bst);
            }
            else if(testChoice == "remove")
            {
                testRemove(bst);
            }
            else if(testChoice == "write")
            {
                testWriteToFile(bst);
            }
            else
            {
                std::cout << "Invalid input, please try again." << '\n';
            }
        }
        else
        {
            std::cout << "Invalid command, please try again." << '\n';
        }

        printMenu();
        std::cin >> command;
	}

    std::cout << "Exiting..." << '\n';
}
