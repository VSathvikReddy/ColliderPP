#include <iostream>
#include <SFML/System.hpp>
using namespace std;

void func() {
  for (int i = 0; i < 10; i++) {
    cout << "Thread 1" << endl;
  }
}

int main() {
  sf::Thread thread1(&func), thread2(&func);
  thread1.launch();
  thread2.launch();

  for(int i = 0; i < 10; i++) {
    cout << "Main thread" << endl;
  }

  return 0;
}
  
		      
