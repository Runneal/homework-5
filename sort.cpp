#include <iostream>
#include "Vector.h"
#include <ctime>//用于获取随机数种子和clock()函数 
#include <chrono>
using namespace std::chrono; 
int main()
{
	srand(time(NULL));//获取当前时间对应的随机数种子，确保每次生成随机数都不一样
	int n;
	cin>>n;
	Vector<int> Vec(n, n, (0, 0));
	for(int i=0; i<n; i++)
	{ 
		Vec[i] = ( rand()%1000, rand()%1000 );
	}
	Vec.unsort();
	Vec.quickSort(0, Vec.size());

	cout<<"顺序情况下"<<endl;
	auto start = high_resolution_clock::now();  // 使用高精度时钟
	Vec.bubbleSort(0, Vec.size());
	auto end = high_resolution_clock::now();  // 使用高精度时钟
	auto elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "冒泡运行时间: " << elapsed_time.count() << " 秒" << endl;
		
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;

	start = high_resolution_clock::now();
	Vec.quickSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "快速运行时间: " << elapsed_time.count() << " 秒" << endl;

	start = high_resolution_clock::now();
	Vec.selectionSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "选择运行时间: " << elapsed_time.count() << " 秒" << endl;

	start = high_resolution_clock::now();
	Vec.insertSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "插入运行时间: " << elapsed_time.count() << " 秒" << endl;

	cout<<"乱序情况下"<<endl;
	Vec.unsort(); 
	start = high_resolution_clock::now(); 
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "冒泡运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.quickSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "快速运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.selectionSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "选择运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.insertSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "插入运行时间: " << elapsed_time.count() << " 秒" << endl;
	
	cout <<"逆序情况下"<<endl;
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;
	
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "归并运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.quickSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "快速运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.selectionSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "选择运行时间: " << elapsed_time.count() << " 秒" << endl;

	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.insertSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "插入运行时间: " << elapsed_time.count() << " 秒" << endl;
	
	return 0;
}
