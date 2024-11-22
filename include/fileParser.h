#ifndef _FILE_PARSER
#define _FILE_PARSER
#include <singlyLinkedList.hxx>
#include <process.h>


class FileParser {
  private:
    string filename;
    SinglyLinkedList<Process>* processes;

  public:
    FileParser();
    FileParser(const char* inputFile);
    ~FileParser();

    bool parseFile();
    singlyLinkedList* getProcesses();

};

#endif
