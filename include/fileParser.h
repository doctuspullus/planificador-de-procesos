#pragma once
#include <singlyLinkedList.hxx>
#include <process.h>


class FileParser {
  private:
    string filename;
    SinglyLinkedList<Process>* processes;

  public:
    FileParser();
    FileParser(const string inputFile);
    ~FileParser();

    bool parseFile(const string filename);
    SinglyLinkedList<Process>* getProcesses();

};