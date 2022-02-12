#include <iostream>

template<class T, size_t S = 0>
class BindList
{
public:
	using ValueType = T;
	BindList() {
		Cell* temp = nullCell;
		for (size_t i = 0; i < S; i++)
		{
			Cell* newCell = new Cell(temp, nullCell);
			temp->Next = newCell;
			temp = newCell;
		}
		size = S;
		endCell = temp;
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

	Cell* getCell(int index) {
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
		// change null cell
		size++;
	}

	void removeCell(int index) {
		Cell * cellToDelete = getCell(index);
		cellToDelete->Previous->Next = cellToDelete->Next;
		cellToDelete->Next->Previous = cellToDelete->Previous;
		size--;
		delete cellToDelete;
	}

	ValueType GetValue(int index) {
		if (index > size) {
			return NULL;
		}
		Cell* temp = getCell(index);
		return temp->value;
	}
};

int main()
{
	BindList<int> testList;
	testList.pushCell(65);
	testList.pushCell(888);
	testList.pushCell(235);

	testList.removeCell(1);

	BindList<int>::Cell *t = testList.getCell(1);

	std::cout << testList[1];;

}