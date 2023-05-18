#include <iostream>
#include "../Vector.h"
#include <ctime>//���ڻ�ȡ��������Ӻ�clock()���� 
#include <chrono>
using namespace std::chrono; 
int main()
{
	srand(time(NULL));//��ȡ��ǰʱ���Ӧ����������ӣ�ȷ��ÿ���������������һ��
	int n;
	cin>>n;
	Vector<int> Vec(n, n, (0, 0));
	for(int i=0; i<n; i++)
	{ 
		Vec[i] = ( rand()%1000, rand()%1000 );
	}
	Vec.unsort();
	Vec.quickSort(0, Vec.size());

	cout<<"˳�������"<<endl;
	auto start = high_resolution_clock::now();  // ʹ�ø߾���ʱ��
	Vec.bubbleSort(0, Vec.size());
	auto end = high_resolution_clock::now();  // ʹ�ø߾���ʱ��
	auto elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ð������ʱ��: " << elapsed_time.count() << " ��" << endl;
		
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;

	start = high_resolution_clock::now();
	Vec.quickSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "��������ʱ��: " << elapsed_time.count() << " ��" << endl;

	start = high_resolution_clock::now();
	Vec.selectionSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ѡ������ʱ��: " << elapsed_time.count() << " ��" << endl;

	start = high_resolution_clock::now();
	Vec.insertSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "��������ʱ��: " << elapsed_time.count() << " ��" << endl;

	cout<<"���������"<<endl;
	Vec.unsort(); 
	start = high_resolution_clock::now(); 
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ð������ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.quickSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "��������ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.selectionSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ѡ������ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.unsort();
	start = high_resolution_clock::now();
	Vec.insertSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "��������ʱ��: " << elapsed_time.count() << " ��" << endl;
	
	cout <<"���������"<<endl;
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.bubbleSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;
	
	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.mergeSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "�鲢����ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.quickSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "��������ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.selectionSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "ѡ������ʱ��: " << elapsed_time.count() << " ��" << endl;

	Vec.reverse();
	start = high_resolution_clock::now();
	Vec.insertSort(0, Vec.size());
	end = high_resolution_clock::now();
	elapsed_time = duration_cast<duration<double>>(end - start);
	cout << "��������ʱ��: " << elapsed_time.count() << " ��" << endl;
	
	return 0;
}