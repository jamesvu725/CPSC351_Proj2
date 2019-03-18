#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>

std::mutex mtx;

void alpha(std::ofstream& outputFile) {
  mtx.lock();
  outputFile << "Thread A (ID " << std::this_thread::get_id() << ") created" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  mtx.unlock();

  mtx.lock();
  for (size_t i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    for (char j = 'A'; j <= 'Z'; ++j) {
      outputFile << j << " ";
    }
    outputFile << std::endl;
  }
  mtx.unlock();

  mtx.lock();
  outputFile << "Thread A (ID " << std::this_thread::get_id() << ") terminated" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  mtx.unlock();
}

void number(std::ofstream& outputFile) {
  mtx.lock();
  outputFile << "Thread B (ID " << std::this_thread::get_id() << ") created" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  mtx.unlock();

  mtx.lock();
  for (size_t i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    for (size_t j = 1; j <= 26; ++j) {
      outputFile << j << " ";
    }
    outputFile << std::endl;
  }
  mtx.unlock();

  mtx.lock();
  outputFile << "Thread B (ID " << std::this_thread::get_id() << ") terminated" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  mtx.unlock();
}

int main(int argc, char* argv[]) {
  std::ofstream file("jvu.log");
  
  if (file.is_open()) {
    file << "James Vu's Project 2 started" << std::endl;

    std::thread A(alpha, ref(file));
    std::thread B(number, ref(file));

    A.join();
    B.join();

    file << "James Vu's Project 2 ended" << std::endl;
    file.close();
  } else { std::cout << "Could not open file" << std::endl; }

  return 0;
}
