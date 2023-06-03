#include<iostream>

using namespace std;

class point {
	int x, y;
public:
	point(){}
	void print()const { cout << x << y << endl; }
};

int main() {
	point p;
	p.print();




	return 0;
}