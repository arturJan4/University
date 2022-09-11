#include <algorithm> 
#include <iostream> 
#include <string> 
 
bool checka(int i, const std::string& s)
{
    if(i >= 3)
    {
        if((s[i] == 'a') && (s[i-1] == 'a') && (s[i-2] == 'a') && (s[i-3] == 'a'))
            return false;
    }
    return true;
}

bool checkb(int i, const std::string& s)
{
    if(i >= 2)
    {
        if((s[i] == 'b') && (s[i-1] == 'b') && (s[i-2] == 'b'))
            return false;
    }
    return true;
}

bool checkc(int i, const std::string& s)
{
    if(i >= 1)
    {
        if((s[i] == 'c') && (s[i-1] == 'c'))
            return false;
    }
    return true;
}
// A && C
bool good_a_c(const std::string& s) {
  bool checkeda = false;
  bool checkedc = false; 
  for (int i = 0; i < 9; ++i) { 
    if(!checkeda && !checka(i,s))
        checkeda = true;
    if(!checkedc && !checkc(i,s))
        checkedc = true;
  } 
  if(checkeda && checkedc)
    return true;

  return false; 
} 

// A && B
bool good_a_b(const std::string& s) {
  bool checkeda = false;
  bool checkedb = false; 
  for (int i = 0; i < 9; ++i) { 
    if(!checkeda && !checka(i,s))
        checkeda = true;
    if(!checkedb && !checkb(i,s))
        checkedb = true;
  } 
  if(checkeda && checkedb)
    return true;

  return false; 
} 

// B && C
bool good_b_c(const std::string& s) {
  bool checkedb = false;
  bool checkedc = false; 
  for (int i = 0; i < 9; ++i) { 
    if(!checkedb && !checkb(i,s))
        checkedb = true;
    if(!checkedc && !checkc(i,s))
        checkedc = true;
  } 
  if(checkedb && checkedc)
    return true;

  return false; 
} 

// A && B && C
bool gooda_b_c(const std::string& s) {
  bool checkeda = false;
  bool checkedb = false;
  bool checkedc = false; 
  for (int i = 0; i < 9; ++i) { 
    if(!checkeda && !checka(i,s))
        checkeda = true;
    if(!checkedb && !checkb(i,s))
        checkedb = true;
    if(!checkedc && !checkc(i,s))
        checkedc = true;
  } 
  if(checkeda && checkedb && checkedc)
    return true;

  return false; 
} 

int counterfirst = 0;
// A v B v C
bool good(const std::string& s) { 
  for (int i = 0; i < 9; ++i) { 
    if(!checka(i,s) || !checkb(i,s) || !checkc(i,s))
        return false;
    }
  return true; 
} 
 
int main() { 
  std::string s = "aaaabbbcc"; 
  int total = 0;
  int cnt = 0; 
  do { 
    if (good(s)) ++cnt; 
    total++;
  } while (std::next_permutation(s.begin(), s.end())); 
  std::cout << total << " " << cnt << " " <<  total - cnt << std::endl; 
 
  return 0; 
} 