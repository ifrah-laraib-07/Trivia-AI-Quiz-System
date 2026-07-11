#ifndef CHAPTERMANAGER_H
#define CHAPTERMANAGER_H

#include <string>

using namespace std;

class ChapterManager {
public:
    void createChapter();
    void deleteChapter();
    void listChapters() const;
    void readChapter(const string& chapterName) const;
};

#endif
