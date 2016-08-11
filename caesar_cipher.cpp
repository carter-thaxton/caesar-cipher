#include <iostream>
#include <sstream>
#include <ctype.h>

using namespace std;

void decode(istream &in, ostream &out, int shift);
char decodeChar(char c, int shift);
int analyzeShift(istream &in);

// https://en.wikipedia.org/wiki/Letter_frequency
double englishLetterFrequencies[26] = {
  0.08167, 0.01492, 0.02782, 0.04253,
  0.12702, 0.02228, 0.02015, 0.06094,
  0.06966, 0.00153, 0.00772, 0.04025,
  0.02406, 0.06749, 0.07507, 0.01929,
  0.00095, 0.05987, 0.06327, 0.09056,
  0.02758, 0.00978, 0.02361, 0.00150,
  0.01974, 0.00074
};


int main(int argc, char *argv[]) {
  stringstream buf;
  buf << cin.rdbuf();

  int shift;
  if (argc > 2 && strcmp(argv[1], "-s") == 0) {
    shift = atoi(argv[2]);
  } else {
    shift = -analyzeShift(buf);
    buf.clear();
    buf.seekg(0);
  }

  decode(buf, cout, shift);

  return 0;
}


int analyzeShift(istream &in) {
  int letterCounts[26] = {0};
  int totalLetters = 0;

  char c;
  while (in.get(c)) {
    if (isalpha(c)) {
      int letter = tolower(c) - 'a';
      letterCounts[letter]++;
      totalLetters++;
    }
  }

  double letterFrequencies[26];
  for (int i=0; i < 26; i++) {
    letterFrequencies[i] = (double) letterCounts[i] / totalLetters;
  }

  double minError;
  int bestShift;
  for (int s=0; s < 26; s++) {
    double error = 0.0;
    for (int i=0; i < 26; i++) {
      int j = (i + s) % 26;
      double diff = letterFrequencies[j] - englishLetterFrequencies[i];
      error += diff * diff;
    }
    if (s == 0 || error < minError) {
      minError = error;
      bestShift = s;
    }
  }

  return bestShift;
}

void decode(istream &in, ostream &out, int shift) {
  char c;
  while (in.get(c)) {
    out << decodeChar(c, shift);
  }
}

char decodeChar(char c, int shift) {
  if (isalpha(c)) {
    char base = islower(c) ? 'a' : 'A';
    int letter = c - base;
    int newLetter = (letter + shift) % 26;
    if (newLetter < 0) newLetter += 26;
    return base + newLetter;
  }
  return c;
}
