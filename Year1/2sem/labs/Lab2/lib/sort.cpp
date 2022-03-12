#include "sort.h"

using namespace std;

vector<String *> LecSort(const vector<vector<char>> &NotEmpty, const vector<vector<String *>> &len_strings)
{
  deque<String *> Queue;

  String *tmp;

  vector<queue<String *>> Cherpaki(LEN, queue<String *>());
  for (int i = STR_LEN - 1; i > -1; --i)
  {
    cout << i << endl;
    for (auto v = len_strings[i].begin(); v != len_strings[i].end(); v++)
    {
      Queue.push_front(*v);
    }

    while (!Queue.empty())
    {
      tmp = Queue.front();

      Queue.pop_front();

      Cherpaki[tolower((*tmp)[i])].push(tmp); // The rison of using tolower is that F < a
    }
    // cout << i << endl;

    for (auto v = NotEmpty[i].begin(); v != NotEmpty[i].end(); v++)
    {
      // out << "inp" << endl;

      while (!Cherpaki[(*v)].empty())
      {
        // cout << (int) *v << endl;
        Queue.push_back(Cherpaki[(unsigned char)(*v)].front());

        Cherpaki[(unsigned char)(*v)].pop();
      }
    }
  }

  vector<String *> out;
  while (!Queue.empty())
  {

    out.push_back(Queue.front());
    Queue.pop_front();
  }
  return out;
}

char **_LecSort(const vector<vector<char>> &NotEmpty, const vector<vector<String *>> &len_strings)
{
  deque<String *> Queue;

  String *tmp;

  vector<queue<String *>> Cherpaki(LEN, queue<String *>());
  for (int i = STR_LEN - 1; i > -1; --i)
  {
    cout << i << endl;
    for (auto v = len_strings[i].begin(); v != len_strings[i].end(); v++)
    {
      Queue.push_front(*v);
    }

    while (!Queue.empty())
    {
      tmp = Queue.front();

      Queue.pop_front();

      Cherpaki[tolower((*tmp)[i])].push(tmp); // The rison of using tolower is that F < a
    }
    // cout << i << endl;

    for (auto v = NotEmpty[i].begin(); v != NotEmpty[i].end(); v++)
    {
      // out << "inp" << endl;

      while (!Cherpaki[(*v)].empty())
      {
        // cout << (int) *v << endl;
        Queue.push_back(Cherpaki[(unsigned char)(*v)].front());

        Cherpaki[(unsigned char)(*v)].pop();
      }
    }
  }

  char **out = new char *[Queue.size()];
  while (!Queue.empty())
  {
    *out = Queue.front()->mas;
    Queue.pop_front();
    out++;
  }

  return out;
}

char **sort_strings(char **mas, int n)
{
  bool Map[STR_LEN][LEN];
  for (int i = 0; i < STR_LEN; ++i)
    memset(Map[i], false, LEN);

  vector<vector<String *>> Strings = ToLenStrings(mas, n);
  vector<vector<char>> NonEmpty = ToNotEmpty(Strings);

  return _LecSort(NonEmpty, Strings);
}

void _write_out(char **mas, int n)
{
}

void OutSort(char *filename, size_t memeory = 256)
{
  FILE *MainFile, *FirstOutFile, *SecondFileOut;
  MainFile = fopen(filename, "r");
  typedef char *strng;

  // char str1[STR_LEN], str2[STR_LEN];
  int allowed_mas = memeory / STR_LEN; // if we can read more than 2 strings at once, function will work faster

  char **strings = new strng[allowed_mas];
  char *strl, *prev;
  bool tofirst = true, end = false;
  int i = 0;

  for (i = 0; i < allowed_mas; ++i)
  {
    strl = fgets(strl, STR_LEN - 1, MainFile);
    if (strl)
    {
      strings[i] = strl;
      prev = strl;
    }
    else
      end = false;
  }

  if (!end)
  {
  }
}

void OutSort(char *name)
{
  int a1, a2, k, i, j, kol, tmp;

  FILE *f, *f1, *f2;
  kol = 0;

  if ((f = fopen(name, "r")) == NULL)
    printf("ERROR");
  else
  {
    while (!feof(f))
    {
      fscanf(f, "%d", &a1);
      kol++;
    }
    fclose(f);
  }
  k = 1;
  while (k < kol)
  {
    f = fopen(name, "r");
    
    f1 = fopen("smsort_1", "w");
    f2 = fopen("smsort_2", "w");
    
    if (!feof(f))
      fscanf(f, "%d", &a1);
    
    while (!feof(f))
    {
      for (i = 0; i < k && !feof(f); i++)
      {
        fprintf(f1, "%d ", a1);
        fscanf(f, "%d", &a1);
      }
      for (j = 0; j < k && !feof(f); j++)
      {
        fprintf(f2, "%d ", a1);
        fscanf(f, "%d", &a1);
      }
    }
    fclose(f2);
    fclose(f1);
    fclose(f);

    f = fopen(name, "w");
    f1 = fopen("smsort_1", "r");
    f2 = fopen("smsort_2", "r");
    if (!feof(f1))
      fscanf(f1, "%d", &a1);
    if (!feof(f2))
      fscanf(f2, "%d", &a2);

    while (!feof(f1) && !feof(f2))
    {
      i = 0;
      j = 0;
      while (i < k && j < k && !feof(f1) && !feof(f2))
      {
        if (a1 < a2)
        {
          fprintf(f, "%d ", a1);
          fscanf(f1, "%d", &a1);
          i++;
        }
        else
        {
          fprintf(f, "%d ", a2);
          fscanf(f2, "%d", &a2);
          j++;
        }
      }
      while (i < k && !feof(f1))
      {
        fprintf(f, "%d ", a1);
        fscanf(f1, "%d", &a1);
        i++;
      }
      while (j < k && !feof(f2))
      {
        fprintf(f, "%d ", a2);
        fscanf(f2, "%d", &a2);
        j++;
      }
    }
    while (!feof(f1))
    {
      fprintf(f, "%d ", a1);
      fscanf(f1, "%d", &a1);
    }
    while (!feof(f2))
    {
      fprintf(f, "%d ", a2);
      fscanf(f2, "%d", &a2);
    }
    fclose(f2);
    fclose(f1);
    fclose(f);
    k *= 2;
  }
  remove("smsort_1");
  remove("smsort_2");
}