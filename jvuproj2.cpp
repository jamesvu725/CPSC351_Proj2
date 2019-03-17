#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
using namespace std;

mutex mtx;

void alpha(ofstream& outputFile) {
  outputFile << "Thread A (ID " << this_thread::get_id() << ") created" << endl;
  mtx.lock();
  for (size_t i = 0; i < 10; ++i) {
    for (char j = 'A'; j <= 'Z'; ++j) {
      outputFile << j << " ";
    }
    outputFile << std::endl;
  }
  mtx.unlock();
  outputFile << "Thread A (ID " << this_thread::get_id() << ") terminated" << endl;
}

void number(ofstream& outputFile) {
  outputFile << "Thread B (ID " << this_thread::get_id() << ") created" << endl;
  mtx.lock();
  for (size_t i = 0; i < 10; ++i) {
    for (size_t j = 1; j <= 26; ++j) {
      outputFile << j << " ";
    }
    outputFile << std::endl;
  }
  mtx.unlock();
  outputFile << "Thread B (ID " << this_thread::get_id() << ") terminated" << endl;
}

int main(int argc, char* argv[]) {
  ofstream file("jvu.log");
  if (file.is_open()) {
    file << "James Vu's Project 2 started" << endl;

    thread A(alpha, ref(file));
    thread B(number, ref(file));

    A.join();
    B.join();

    file << "James Vu's Project 2 ended" << endl;
    file.close();
  } else { cout << "Could not open file" << endl; }

  return 0;
}
