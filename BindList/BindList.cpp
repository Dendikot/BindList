#include <iostream>
template<class T>
class BindList
{
public:
	using ValueType = T;
	BindList() {
		nullCell->Next = endCell;
		nullCell->Previous = endCell;
		size = 0;
	}

	// fix this
	BindList(int range) {
		Cell* temp = nullCell;
		for (size_t i = 0; i < range; i++)
		{
			Cell* newCell = new Cell(temp, nullCell);
			temp->Next = newCell;
			temp = newCell;
		}
		size = range;
		endCell = temp;
		nullCell->Next = getCell(0);
		nullCell->Previous = endCell;
	}

	// fix this
	BindList(int range, ValueType value) {
		Cell* temp = nullCell;
		for (size_t i = 0; i < range; i++)
		{
			Cell* newCell = new Cell(value,temp, nullCell);
			temp->Next = newCell;
			temp = newCell;
		}
		size = range;
		endCell = temp;
		nullCell->Next = getCell(0);
		nullCell->Previous = endCell;
	}

	// fix this
	BindList(const BindList& other) {
		if (other.size < 0) { return; }
		for (int i = 0; i < other.size; i++)
		{
			pushCell(other.getCell(i)->value);
			//ValueType m = other[i];
			//pushCell(other[i]);
		}
		endCell = getCell(other.size-1);
		nullCell->Next = getCell(0);
		nullCell->Previous = endCell;

	}

	struct Cell
	{
		Cell* Previous, * Next;
		ValueType value;
		Cell(Cell* Previous, Cell* Next) {
			this->Previous = Previous;
			this->Next = Next;
		}
		Cell(ValueType cellValue, Cell* Previous, Cell* Next) {
			value = cellValue;
			this->Previous = Previous;
			this->Next = Next;
		}
		Cell() {

		}
		// copy constructor for cell
		Cell(const Cell& other) {
			value = other.value;
			this->Previous = other.Previous;
			this->Next = other.Next;
		}
	};

	~BindList() {
		int finSize = size;
		for (size_t i = 0; i < finSize; i++)
		{
			removeCell(0);
		}
		delete nullCell;
	}
private:

	Cell* nullCell = new Cell();
	Cell* endCell = nullCell;

	int size;
public:

	ValueType operator[](int index) {
		if (index <= size)
		{
			ValueType value = GetValue(index);
			return value;
		}
		else
		{
			return NULL;
		}
	}

	Cell* getCell(int index) const {
		Cell* temp = nullCell->Next;
		for (size_t i = 0; i < index; i++)
		{
			temp = temp->Next;
		}
		return temp;
	}
	
	void pushCell(const ValueType& item) {
		Cell* newCell = new Cell (item, endCell, nullCell);
		endCell->Next = newCell;
		endCell = newCell;
		endCell->Next = nullCell;
		size++;
	}

	void pushCellFront(const ValueType& item) {
		Cell* newCell = new Cell(item, nullCell, nullCell->Next);
		nullCell->Next = newCell;
		size++;
	}

	void removeCell(int index) {
		Cell * cellToDelete = getCell(index);
		cellToDelete->Previous->Next = cellToDelete->Next;
		cellToDelete->Next->Previous = cellToDelete->Previous;
		size--;
		delete cellToDelete;
	}

	void reverse() {
		//we need to switch last with first
		// we can simply create a new array and start filling it correctly
		if (size < 2){return;}
		Cell tempNull;
		Cell* temp = &tempNull;

		for (int i = size-1; i >= 0; i--)
		{
			Cell* currentCell = getCell(i);
			temp->Next = currentCell;
			currentCell->Previous = temp;
			temp = currentCell;
		}

		*nullCell = tempNull;
	}

	ValueType GetValue(int index) {
		if (index > size) {
			return NULL;
		}
		return getCell(index)->value;
	}
	
	// swap bind lists with each other, simply reassign nullpointers and endpointers
	// change size
	// replace size with parameter

	void swap(const BindList& swapList)
	{
		BindList t = swapList;
	}

	/*bool testMethod(ValueType a, ValueType b, function<ValueType(ValueType, ValueType)> func) {
		return func(a, b);
	}*/
};

bool CompareMethod(int a, int b) {
	if (a > b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{

	BindList<int> testList;
	testList.pushCell(65);
	testList.pushCell(888);
	testList.pushCell(235);
	
	BindList<int> testList2 = testList;
	//std::cout << testList[1];;

	testList.removeCell(1);

	BindList<int>::Cell *t = testList.getCell(1);

	//std::cout << testList2[1];;

	BindList<int> testList3(2,2);
	testList3.pushCellFront(66);

	BindList<int> testList4(4,65);

	testList3.swap(testList4);

	//testList3.testMethod(2,4, &CompareMethod);

	//for (size_t i = 0; i < 3; i++)
	//{
	//	std::cout << testList3[i] << "\n";
	//}

	//testList3.reverse();

	//for (size_t i = 0; i < 3; i++)
	//{
	//	std::cout << testList3[i] << "\n";
	//}
}