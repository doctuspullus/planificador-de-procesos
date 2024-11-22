#ifndef _FILE_PARSER
#define _FILE_PARSER
#include <singlyLinkedList.hxx>
#include <process.h>


class FileParser {
  private:
    string filename;
    singlyLinkedList* processes;

    Process* parseProcess(FILE file);
    bool parseInstructions(FILE* file, Process* process);

  public:
    FileParser();
    FileParser(const char* inputFile);
    ~FileParser();

    bool parseFile();
    singlyLinkedList* getProcesses();

};

#endif
