#ifndef PREP_H
#define PREP_H

#include <QString>

struct Prep
{
    friend bool operator==(const Prep& a, const Prep& b) {
        return a.id == b.id;
    }

    int id;
    int subjectId;
    QString name;
    QString picPath;
};

namespace std
{
  template<>
    struct hash<Prep>
    {
      size_t
      operator()(const Prep& obj) const
      {
        return hash<int>()(obj.id);
      }
    };
}

#endif // PREP_H
