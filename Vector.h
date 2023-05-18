typedef int Rank; //������������Rank����˼�����Ԫ�ص����൱�������Ԫ�ص�λ�� 
#define DEFAULT_CAPACITY 3 //Ĭ�ϳ�ʼ����Ϊ3 Ĭ��3ά���� 
#include <cstdlib> //����ȡ�����rand()���� 
#include "Fib.h" // ���� 쳲��������� �� 
using namespace std; 
template <typename T> class Vector //����ģ���� 
{
	protected:
		Rank _size; int _capacity; T* _elem; //��ģ������������������ 
		void copyFrom (T const* A, Rank lo, Rank hi); //������������A[lo,hi) ��ǰ�պ󿪣� �� 
		void expand(); //���ڿռ䲻��ʱ���� �� 
		void shrink(); //װ�����ӹ�Сʱѹ�� ��
		Rank max(Rank lo, Rank hi); //��������ѡȡ���Ԫ��
	public:
		//�������㷨�ŵ���public�﷽��ָ��ʹ���ĸ����򷽷� 
		bool bubble (Rank lo, Rank hi); //ɨ�轻�� ��
		void bubbleSort (Rank lo, Rank hi); //���������㷨  ��
		void merge (Rank lo,Rank mi,Rank hi); //�鲢�㷨  ��
		void mergeSort (Rank lo, Rank hi); //�鲢�����㷨 ��
		void selectionSort (Rank lo,Rank hi); //ѡ�������㷨 
		Rank partition (Rank lo, Rank hi); //��㹹���㷨 
		void quickSort (Rank lo, Rank hi); //���������㷨 
		void heapSort (Rank lo, Rank hi); //������ 
		void insertSort (Rank lo, Rank hi); //��������
		Vector (int c = DEFAULT_CAPACITY, int s = DEFAULT_CAPACITY, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv 
		{_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);} //��̬����洢�ռ�s<=c 
		Vector (T const* A, Rank n){copyFrom (A, 0, n);} //�������帴�� 
		Vector (T const* A, Rank lo, Rank hi) {copyFrom (A, lo, hi); }//�������� �� 
		Vector (Vector<T> const& V) {copyFrom (V._elem, 0, V._size);} //���帴�Ƹ����� 
		Vector (Vector<T> const& V, Rank lo, Rank hi) {copyFrom (V._elem, lo, hi);} //���Ƹ��������� 
		~Vector(){delete [] _elem;} //�ͷ��ڲ��ռ� 
		Rank size() const {return _size;} //��ѯ��ģ��С 
		void resize(Rank newSize) {_size = newSize;} //���¹�ģ��С 
		bool empty() const {return !_size;} //�ж��Ƿ�Ϊ�գ���_size��Ϊ�� 
		int disordered() const; //�ж������Ƿ������� �� 
		Rank find (T const& e) const {return find (e, 0, _size);} //��������������� 
		Rank find (T const& e, Rank lo, Rank hi) const; //��������������� �� 
        template <typename U>
        Vector<T> findInRange(U m1, U m2);
		Rank search (T const& e) const {return (0 >= _size) ? -1 : search (e, 0, _size); } //���������������
		Rank search (T const& e, Rank lo, Rank hi) const; //���������������
		T& operator[] (Rank r) const; //�����±������"[]"����������������Ԫ�� 
		Vector<T> & operator= (Vector<T> const&); //���ظ�ֵ������"="������ֱ�ӿ�¡����
		T remove (Rank r); //ɾ����Ϊr��Ԫ�� �� 
		int remove (Rank lo, Rank hi); //����ɾ����������[lo, hi)֮���Ԫ�� �� 
		Rank insert (Rank r, T const& e); //��r������Ԫ�� �� 
		Rank insert (T const& e) {return insert (_size, e);} //��ָ��λ����Ĭ����ĩλ����Ԫ��
		void sort (Rank lo, Rank hi); //������[lo, hi)���� 
		void sort() {sort(0, _size);} //���������� 
		void unsort (Rank lo, Rank hi); //������[lo, hi)���� �� 
		void unsort() {unsort (0, _size);} //���������� �� 
		void reverse (Rank lo, Rank hi); //������[lo, hi)����
		void reverse() {reverse(0, _size);} 
		int deduplicate(); //����ȥ�� �� 
		int uniquify(); //����ȥ�� �� 
		void traverse (void (*) (T&)); //ʹ�ú���ָ�������ʵ��ֻ����ֲ��޸�  �� 
		template <typename VST> void traverse (VST&); //ʹ�ú��������������ȫ�����޸� �� 
    	void copyfrom(T const* A, Rank lo, Rank hi) {this->copyFrom(A, lo, hi);} // ���û����copyFrom����
    	void expanding(){this->expand();}
};

template <typename T> void Vector<T>::copyFrom (T const* A, Rank lo, Rank hi){ //��������A��[lo, hi)���� 
	_elem = new T[_capacity = 2*(hi - lo)]; //����һ���¿ռ� 
	_size = 0; //������Aճ����������ģ����
	while (lo < hi)
		_elem[_size++] = A[lo++]; //��A[lo, hi)�е�Ԫ�� �� һ �� ���Ƶ�_elem[0, hi-lo) 
} 

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V){ //���ظ�ֵ�����"=" 
	if (_elem)
		delete [] _elem; //����ԭ���������ͷ�ԭ������
	copyFrom (V._elem, 0, V.size()); //���帴������V
	return *this; //���ص�ǰ����������Ա���ʽ��ֵ 
} 

template <typename T> T& Vector<T>::operator[] (Rank r)const{ //�����±������"[]"
	return _elem[r];
}

template <typename T> void Vector<T>::expand (){ //�����ռ䲻��ʱ���� ���㹻ʱֱ�ӷ��� 
	if(_size<_capacity)  //�ж��Ƿ���Ҫ���� 
		return;
	if(_capacity<DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //����ԭ�������� 
	}
	delete [] oldElem; //�ͷ�ԭ�ռ� 
} 

template <typename T> void Vector<T>::shrink(){ //װ�����ӹ�Сʱѹ��������ռ�ռ�
	if(_capacity<DEFAULT_CAPACITY << 1)
		return;
	if(_size << 2 > _capacity)
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for(int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i]; //����ԭ�������� 
	}
	delete [] oldElem; //�ͷ�ԭ�ռ� 
}

template <typename T> void permute (Vector<T>& V){ //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ�� 
	for(int i = V.size(); i>0; i--)
		swap (V[i-1], V[rand() % i]); 
}

template <typename T> void Vector<T>::unsort (Rank lo, Rank hi){ //�ȸ��������������[lo, hi)
	T* V = _elem + lo; //��������_elem[lo,hi)������һ����V[0, hi-lo) 
	for(Rank i = hi-lo; i > 0; i--) //�Ժ���ǰ
		swap (V[i-1], V[rand() % i]); //��V[i-1]��V[0,i)��ĳһԪ��������� 
}

//�е� 
template <typename T> static bool lt (T* a, T* b) {return lt (*a, *b);} //
template <typename T> static bool lt (T& a, T& b) {return a < b;} //
template <typename T> static bool gt (T* a, T* b) {return gt (*a, *b);} //
template <typename T> static bool gt (T& a, T& b) {return a > b;} //
template <typename T> static bool eq (T* a, T* b) {return eq(*a, *b);} //
template <typename T> static bool eq (T& a, T& b) {return a == b;} //a�Ƿ���b��� 

template <typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{ //����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo-1 
	while ((lo < hi--)&&(e != _elem[hi]));//�Ӻ���ǰ˳����� 
	return hi; //��hi < lo������ζ�Ų���ʧ�ܣ����򷵻�ֵhi��Ϊ����Ԫ�ص��� 
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::findInRange(U m1, U m2) {
    Vector<T> result(0, 0, T());
    Rank lo = 0, hi = _size - 1;
    while (lo < hi) {
        Rank mid = (lo + hi) / 2;
        if (_elem[mid] < m1) lo = mid + 1;
        else hi = mid;
    }
    Rank start = lo;
    hi = _size - 1;
    while (lo < hi) {
        Rank mid = (lo + hi) / 2;
        if (_elem[mid] < m2) lo = mid + 1;
        else hi = mid;
    }
    Rank end = lo;
    for (Rank i = start; i < end; i++) {
        result.insert(_elem[i]);
    }
    return result;
}

template <typename T> Rank Vector<T>::insert(Rank r, T const& e){ //��e��Ϊ��Ϊr��Ԫ�ز��� 
	expand(); //���б�Ҫ�Ļ��������������� 
	for (int i = _size; i>r; i--) _elem[i] = _elem[i-1]; //����󵽲���λ�ã����Ԫ�����κ���һ����Ԫ 
	_elem[r] = e; _size++; //������Ԫ�ز��������� 
	return r; //������ 
}

template <typename T> int Vector<T>::remove(Rank lo, Rank hi){ //ɾ������[lo, hi) 
	if(lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0) 
	while (hi < _size) _elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ 
	_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)���� 
	shrink(); //ɾ�������б�Ҫ������ 
	return hi-lo; //���ر�ɾ��Ԫ�ص���Ŀ 
}

template <typename T> T Vector<T>::remove(Rank r){ //ɾ����������Ϊr��Ԫ�أ�0 <= r < size 
	T e = _elem[r]; //���ݱ�ɾ��Ԫ�� 
	remove (r, r+1); //��������ɾ���㷨����Ч�ڶ�����[r, r+1)��ɾ�� 
	return e; //���ر�ɾ��Ԫ�� 
}

template <typename T> int Vector<T>::deduplicate(){ //ɾ�������������ظ���Ԫ�أ���Ч�棩 
	int oldSize = _size; //��¼ԭ��ģ
	Rank i = 1; //��_elem[1]��ʼ 
	while (i < _size) //��ͷ��iλ����һ�����Ԫ�� 
		(find (_elem[i], 0, i) < 0)? i++ : remove(i);  //����ǰ׺��Ѱ����֮��ͬ�ߣ�����һ���� 
	return oldSize - _size; //���ع�ģ�仯������ɾ����Ԫ������ 
}

template <typename T> void Vector<T>::traverse(void (*visit) (T&)){  //��������ָ����� 
	for (int i=0; i < _size; i++)
		visit(_elem[i]); //�������� 
}

template <typename T> template <typename VST> void Vector<T>::traverse (VST& visit) { //��������������� //T��VST�ֱ���Ԫ�����ͺͲ�����(operator)   
	for (int i=0; i < _size; i++)
		visit (_elem[i]); //�������� 
}

template <typename T> struct Increase{ //��������Ϊһ��������ĵ������� 
	virtual void operator() (T& e) {e++;}; //����T��ֱ�ӵ����������"++"�ѱ����� 
};

template <typename T> void increase (Vector<T> & V) //ͳһ���������и�Ԫ�� 
{ V.traverse( increase<T>() ); } //��Increase<T>()Ϊ�����������б��� 

template <typename T> int Vector<T>::disordered() const{ //������������������Ԫ�ضԵĸ��� 
	int n=0; //���岢��ʼ�������� 
	for ( int i=1; i<_size; i++ ) //��һ���ҹ�_size-1������Ԫ�� 
		if ( _elem[i-1]>_elem[i] ) n++; //��Ϊ��������� 
	return n; //���ҽ���n=0ʱ����Ϊ���� 
} 
 

template <typename T> int Vector<T>::uniquify() { // ��������������ظ�Ԫ���޳��㷨
	Rank i = 0, j = 0; //��ʼ�����Ի�������Ԫ�ص���
	while (++j < _size) //)��һɨ�� 
		if ( _elem[i] != _elem[j]) //����鵽���ص�Ԫ��ʱ����ǰ�ƣ��ظ���Ԫ����Ȼ��Ȼ�ľ͵�����ȥ�� 
			_elem[++i] = _elem[j];
	_size = ++i; shrink(); //ɨ�����Ժ�һ������������Ԫ��ͨͨȥ�� 
	return j-i; //����ֵ��ӳ��������ģ�ı仯��������ɾ��Ԫ�ص����� 
} 

/*
#include <unordered_set>
template <typename T> 
int Vector<T>::uniquify() {  ��ϣ��Ψһ��������Ӧ���ں�����ΪԪ�ص����� 
    unordered_set<T> s;
    Rank i = 0, j = 0;
    while (j < _size) {
        if (s.find(_elem[j]) == s.end()) { // ���Ԫ��δ���ֹ���������ϣ��
            s.insert(_elem[j]);
            _elem[i++] = _elem[j++];
        } else { // ���Ԫ���Ѿ����ֹ�����ֱ������
            ++j;
        }
    }
    _size = i;
    shrink();
    return j - i;
}
#include <functional> // ���� hash �������ڵ�ͷ�ļ�

template<typename T>
struct ComplexHash {
    std::size_t operator()(const Complex<T>& c) const {
        std::hash<T> hash_fn;
        return hash_fn(c.real()) ^ hash_fn(c.imag());
    }
};
#include <unordered_set> // ���� unordered_set �����ڵ�ͷ�ļ�
int main() {
    Vector< Complex<int> > vec;
    // �� vec �����Ԫ��
    std::unordered_set< Complex<int>, ComplexHash<int> > seen;
    int i = 0;
    while (i < vec.size()) {
        if (seen.count(vec[i]) == 0) {
            seen.insert(vec[i]);
            i++;
        } else {
            vec.remove(i);
        }
    }
    // ��������
}
*/


/*
template <typename T>
int Vector<T>::uniquify() {
    if (_size < 2) return 0;
    int i = 0, j = 0;
    sort(0, _size); // ����
    while (_elem, _elem + _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}
*/

template <typename T> Rank Vector<T>::search (T const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ? binSearch (_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); //���ʹ�ö��ֲ��ҷ���쳲��������ҷ� 
} 
/*template <typename T> //���ض���ȵĲ��� 
std::vector<Rank> Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    std::vector<Rank> result;
    Rank r = (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
    if (r >= 0) {
        result.insert(r);
        Rank i = r;
        while (--i >= lo && _elem[i] == e) {
            result.insert(i);
        }
        i = r;
        while (++i < hi && _elem[i] == e) {
            result.insert(i);
        }
    }
    return result;
}*/
template <typename T> static Rank binSearch (T* A, T const& e, Rank lo, Rank hi){ //���ֲ��ҷ� �汾C
	while ( lo < hi ){ //�Ľ���ÿ������ֻ����һ�αȽ��жϣ�ֻ��������֧�� �� �� �ɹ����Һ����������Ƿ��ж��һ����� 
		Rank mi = ( lo + hi ) >> 1; //�Դ��е㿪ʼ 
		(e<A[mi]) ? hi = mi : lo = mi + 1; //���бȽϺ��������ǰ�뻹�Ǻ��� 
	} 
	return --lo; //ѭ������ʱ��loΪ����eԪ�ص���С�ȣ���lo - 1Ϊ������e��Ԫ�ص������ 
} //�Ľ����޷���������ȵ�ȱ�㣬����ʧ��ʱҲ�ܷ���ʧ�ܵ�λ�� 

template <typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
    MyFib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.getFib()) 
			fib.getPrevFib();
        Rank mi = lo + fib.getFib() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else {
			return mi;
        }
    }
    return -1;
}

/*
template <typename T> static Rank binSearch (T* A, T const& e, Rank lo, Rank hi){ //���ֲ��ҷ� �汾A 
	while (lo < hi){ //ÿ������ ���� Ҫ�����αȽ��жϣ�����������֧ 
		Rank mi = (lo + hi) >> 1; //���е�Ϊ��ʼ�� 
		if (e<A[mi]) //����ǰ��� 
			hi = mi;
		else if (A[mi] < e) //���Һ��� 
			lo = mi + 1;
		else //�ҵ��󷵻�λ�ã���ǰ��ֹ 
			return mi;
	}
	return -1; //����ʧ�� 
} //ȱ�㣺�ٴ�����Ԫ���ظ�����ʱ���ܱ�֤�����������Ǹ��� �ڲ���ʧ��ʱû��ָʾ������ʧ��
*/


/*
template <typename T> static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
    MyFib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.getFib())
            fib.getPrevFib();
        Rank mi = lo + fib.getFib() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
} //ȱ��ͬ���ַ� A 
*/


/*template <typename T> �������ȵĲ��ҷ����ϰ� 
static Rank* fibSearch(T* A, T const& e, Rank lo, Rank hi) { //fib���ҷ� 
    Rank* result = new Rank[hi - lo]; //�����ҽ�������һ����̬���������� 
    int count = 0;
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else {
            result[count++] = mi; //�����Ԫ�ص��ȴ������� 
            lo = mi + 1; // ˳�������һ���ظ�Ԫ��
        }
    }
    if(count == 0){ //����ʧ�� 
    	delete[] result; //�ͷ������ڴ� 
    	return nullptr; //����һ�������� 
	} 
	else{ //���ҳɹ� 
		Rank* finalresult = new Rank[count + 1]; //�½�һ����̬������������������������� 
        for (int i = 0; i < count; i++)
            finalresult[i] = result[i]; // ��������Ԫ��
        finalresult[count] = -1; // ĩβ����ڱ�Ԫ�أ��������
        delete[] result; // �ͷ������ڴ�
        return finalresult;
	} 
}*/


/*
template <typename T> static Rank binSearch (T* A, T const& e, Rank lo, Rank hi) { //���ֲ��ҷ� �汾B
	while (i < hi - lo){ //�Ľ���ÿ������ֻ����һ�αȽ��жϣ�ֻ��������֧�� �� �� �ɹ����Һ����������Ƿ��ж��һ����� 
		Rank mi = ( lo + hi ) >> 1; //�Դ��е㿪ʼ 
		(e<A[mi])?hi = mi:lo = mi; //���бȽϺ��������ǰ�뻹�Ǻ��� 
	} //���������ڽ���һ��Ԫ��A[lo] 
	return (e == A[lo])?lo:-1; //�ɹ��ҵ��󷵻ض�Ӧ���ȣ�һ��û�ҵ��ͷ���-1 
} //ȱ��û�� 
*/

/*template <typename T> static Rank* binSearch(T* A, T const& e, Rank lo, Rank hi) { // ���ֲ��ҷ� �汾C �����޵�plus���ð� �ϰ� 
    Rank* result = new Rank[hi - lo];
    int count = 0;
    while (lo < hi) { // �Ľ���ÿ������ֻ����һ�αȽ��жϣ�ֻ��������֧�����ҳɹ����Һ����������Ƿ��ж��һ�����
        Rank mi = (lo + hi) >> 1; // �Դ��е㿪ʼ
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else { // ���ҳɹ�ʱ�����Ԫ�ص���ѹ������result
            result[count++] = mi;
            for (Rank i = mi - 1; i >= lo && A[i] == e; i--) result[count++] = i;
            for (Rank i = mi + 1; i < hi && A[i] == e; i++) result[count++] = i;
            break;
        }
    }
    if (count == 0) { //����ʧ�� 
    	delete[] result; //�ͷ������ڴ� 
    	return nullptr; //����һ�������� 
    }
    else { //���ҳɹ� 
        Rank* finalResult = new Rank[count + 1]; //�½�һ����̬������������������������� 
        for (int i = 0; i < count; i++)
            finalResult[i] = result[i]; //��������Ԫ�� 
        finalResult[count] = -1; //ĩβ����ڱ�Ԫ�أ�������� 
        delete[] result; //�ͷ������ڴ� 
        return finalResult; // ѭ������ʱ��loΪ����eԪ�ص���С�ȣ���lo - 1Ϊ������e��Ԫ�ص������
    }
} //�Ľ����޷�����ظ�Ԫ�ص��ȵ�ȱ�� */


	//switch (rand() % 2){ //�ȿ������ѡȡ�����㷨 //���źͶ��Ż�û�� 
		//case 1: bubbleSort (lo, hi); break; //�������� 
		//case 2: selectionSort (lo, hi); break; //ѡ�����򣨴����� 
		//case 3: mergeSort (lo, hi); break; //�鲢���� 
		//case 4: heapSort (lo, hi); break; //������ 
		//default: quickSort (lo, hi); break; //�������� 
	//}
// template <typename T> void Vector<T>::sort (Rank lo, Rank hi){ //��������[lo, hi)���� 
// 	(rand() % 2) ? bubbleSort (lo, hi) : mergeSort(lo, hi);
// } 

template <typename T> void Vector<T>::bubbleSort (Rank lo, Rank hi){
	while (!bubble (lo, hi--)); //ÿ����һ��ɨ�裬ֱ����ȫ�ź��� 
} 
template <typename T> bool Vector<T>::bubble (Rank lo, Rank hi){ //����ÿһ�˵�ɨ�� 
	bool sorted = true; //�������־ 
	while (++lo < hi) //�������ң���һ����������Ԫ���Ƿ���Ҫ���� 
		if ((_elem[lo - 1] > _elem[lo])){ //���������־��Ϊ��δ���� 
			sorted = false;
			swap ( _elem[lo-1], _elem[lo]); //������һ������Ԫ��ʹ�þֲ����� 
		}
	return sorted; //���������־����Ϊtrue�����꣬��Ϊfalse������һ�� 
}

template <typename T> //�����鲢����
void Vector<T>::mergeSort (Rank lo, Rank hi){
	if (hi - lo < 2) return; //����Ԫ��������Ȼ������ʼ�鲢���� 
	int mi = (lo + hi)/2; //���е㿪ʼ 
	mergeSort (lo, mi); mergeSort (mi, hi); //���е����߷ֱ����� 
	merge (lo, mi, hi); //�鲢 
}
template <typename T> void Vector<T>::merge (Rank lo, Rank mi, Rank hi){ //����������[lo, mi)��[mi, hi)�Ĺ鲢
	T* A = _elem + lo; //��ϲ��������Ϊ����A[0, hi-lo) = _elem[lo, mi)����ģΪhi-lo 
	int lb = mi - lo; T* B = new T[lb]; //ǰ������B[0, lb) = _elem[lo, mi) 
	for (Rank i = 0; i < lb; B[i] = A[i++]); //����ǰ������ 
	int lc = hi - mi; T* C = _elem + mi; //��������C[0, lc) = _elem[mi, hi) 
    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc); i++) { //B[j]��C[k]�еĽ�С�߽ӵ�A��β�� 
        if ((j < lb) && ((k >= lc) || (B[j] <= C[k]))) {
            A[i] = B[j++];
        } else {
            A[i] = C[k++];
        }
    }
	delete [] B; //�ͷ���ʱ�ռ�B 
}  //�鲢��õ���������������[lo, hi) 
/*
template<typename T> //�Ը��������ػ��鲢������������Ԫ�ص�ģ�������򣬵����˱��� B[j].modulus()������ 
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo; // ����������ʼ��ַ
    int lb = mi - lo; T* B = new T[lb]; // BΪ������丱��
    for (Rank i = 0; i < lb; i++) B[i] = A[i]; // �����������
    T* C = _elem + mi; // �Ұ��������ʼ��ַ
    int lc = hi - mi; T* D = new T[lc]; // DΪ�Ұ����丱��
    for (Rank i = 0; i < lc; i++) D[i] = C[i]; // �����Ұ�����
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
        if ((j < lb) && (!(k < lc) || (B[j].modulus() < D[k].modulus()))) A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (D[k].modulus() <= B[j].modulus()))) A[i++] = D[k++];
    }
    delete [] B; delete [] D; // �ͷ���ʱ�ռ�
}
*/
//�����������У�mergeSort()����ʹ���˷����㷨��˼�룬�������������Ϊ�������������䣬�ݹ�ض������������������Ȼ���ٽ��Ѿ�������������������кϲ���һ���������С�
//merge()�����������ںϲ��������������еĺ�����������������������ֱ��Ƶ���ʱ����B��D�У����ù鲢�����˼��ϲ�B��D�е�Ԫ�أ���󽫺ϲ����Ԫ�ظ��ƻ�ԭ�����С�

template <typename T> void Vector<T>::reverse(Rank lo, Rank hi) { //�������������� 
    while (lo < hi) {
        swap(_elem[lo++], _elem[--hi]);
    }
}

template <typename T>
void Vector<T>::quickSort (Rank lo, Rank hi ) {
	if (hi - lo < 2) return; //��Ԫ��������Ȼ���򣬷���...
	Rank mi = partition(lo, hi - 1); //��[lo, hi)�ڹ������
	quickSort(lo, mi); //��ǰ׺�ݹ�����
	quickSort(mi + 1, hi); //�Ժ�׺�ݹ�����
}

// template <typename T>
// Rank Vector<T>::partition ( Rank lo, Rank hi ) { //�汾A
// 	swap ( _elem[lo], _elem[lo + rand() % (hi - lo + 1)] ); //��ѡһ��Ԫ������Ԫ�ؽ���
// 	T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㣬��ʱ����Ԫ��������ʱ������ΨһԪ�أ���Ч�ڽ���Ԫ�ش��������޳�
// 	while ( lo < hi ) {
// 		while ( ( lo < hi ) && ( pivot <= _elem[hi] ) ) hi--; //�ڲ�С��pivot��ǰ���£�������չ�Ҷ�������
// 			hi--;
// 		_elem[lo] = _elem[hi]; //С��pivot�߹������������
// 		while ( ( lo < hi ) && ( _elem[lo] <= pivot ) )
// 			lo++;
// 		_elem[lo] = _elem[hi]; //����pivot�߹����Ҳ�������
// 	} //���ˣ�assert: lo == hi
// 	_elem[lo] = pivot; //�����ݵ�����¼����ǰ����������֮��
// 	return lo; //����������
// }

template <typename T>
Rank Vector<T>:: partition ( Rank lo, Rank hi ) { //�汾B
	swap ( _elem[lo], _elem[lo + rand() % (hi - lo + 1)] ); //��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㣬��ʱ����Ԫ��������ʱ������ΨһԪ�أ���Ч�ڽ���Ԫ�ش��������޳�
	while ( lo < hi ) { //�����������˽�������м�ɨ��
		while ( lo < hi )
			if( pivot < _elem[hi] ) //�ڴ���pivot��ǰ����
				hi--; //������չ�Ҷ�������
			else //ֱ������������pivot��
				{_elem[lo++] = _elem[hi]; break;} //������չ�Ҷ�������
		while ( lo < hi )
			if ( _elem[lo] < pivot ) //��С��pivot��ǰ����
				lo++; //������չ���������
			else //ֱ��������С��pivot��
				{_elem[hi--] = _elem[lo]; break;} //������չ���������
	} //���ˣ�lo == hi
	_elem[lo] = pivot; //�����ݵ�����¼����ǰ����������֮��
	return lo; //����������
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
	while (lo < hi) {
		Rank min = lo;
		for (Rank i = lo + 1; i < hi; i++) {
			if (_elem[i] < _elem[min]) {
				min = i;
			}
		}
		swap(_elem[lo++], _elem[min]);
	}
}

template <typename T>
void Vector<T>::insertSort(Rank lo, Rank hi) {
	for (Rank i = lo + 1; i < hi; i++) {
		T e = _elem[i];
		Rank j = i;
		while (j > lo && _elem[j - 1] > e) {
			_elem[j] = _elem[j - 1];
			j--;
		}
		_elem[j] = e;
	}
}