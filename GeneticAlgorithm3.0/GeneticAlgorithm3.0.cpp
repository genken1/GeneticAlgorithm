#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

const int GENERATION=100;
void Mutation(double ChildArray[2][GENERATION]);
void Crossover(double ChildArray[2][GENERATION], double GenerationArray[3][GENERATION], int ParrentIndex[2][GENERATION]);
int Selection(double forSumStepSelection[GENERATION], double SumValues);
double SumOfFunctionValues(double GenerationArray[3][GENERATION], double SumValues);

double Function(double x, double y)//Функция для которой ищем экстремумы.
{
	//return y * pow(x, (1 / 2)) - 2 * pow(y,2) - x + 14 * y;//ForSortUse "<". =28
	//return 3 * x * x + x * y + 2 * y * y - x - 4 * y;//ForSortUse ">". =-2
	//return x*x*x + 8 * y*y*y - 6 * x * y + 5;//ForSortUse ">". =4
	//return exp(x + y) * (pow(x, 2) - 2 * pow(y, 2));//ForSortUse ">". =8/e^2 ----------
	return 4 + pow(pow((pow(x,2)+pow(y,2)),2),(1/3));////ForSortUse ">". =4
}

void ChoiceParents(double GenerationArray[3][GENERATION])//Создание родителей(единоразовое использование).
{
	/*srand(time(NULL));
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < GENERATION; j++)
		{
			GenerationArray[i][j] = rand() % GENERATION;
		}
	}*/
	for (int i = 0; i < GENERATION; i++) {
		GenerationArray[0][i]=((double)((double)rand() / (RAND_MAX + 1.0) > 0.5 ? rand() : -1 * rand()) / RAND_MAX + rand() % 5);
		GenerationArray[1][i] = ((double)((double)rand() / (RAND_MAX + 1.0) > 0.5 ? rand() : -1 * rand()) / RAND_MAX + rand() % 5);
	}
}

void Sort(double GenerationArray[3][GENERATION])//Сортируем массив поколений.
{
	for (int j = 0; j < GENERATION; j++)
	{
		GenerationArray[2][j] = Function(GenerationArray[0][j], GenerationArray[1][j]);
	}


	for (int i = 0; i < GENERATION; i++)
	{
		for (int j = 0; j < GENERATION; j++)
		{
			if (GenerationArray[2][j] < GenerationArray[2][i])//Максимум-"<". Минимум-">".
			{
				double tmp = GenerationArray[0][i];
				GenerationArray[0][i] = GenerationArray[0][j];
				GenerationArray[0][j] = tmp;

				double tmp1 = GenerationArray[1][i];
				GenerationArray[1][i] = GenerationArray[1][j];
				GenerationArray[1][j] = tmp1;

				double tmp2 = GenerationArray[2][i];
				GenerationArray[2][i] = GenerationArray[2][j];
				GenerationArray[2][j] = tmp2;
			}
		}
	}
}

//Шаги с суммой, Сумма значений функции, Массив детей, Массив поколения.
void CreateChildren(double forSumStepSelection[GENERATION], double SumValues, double ChildArray[2][GENERATION], double GenerationArray[3][GENERATION])
{
	int ParrentIndex[2][GENERATION];
	SumValues = SumOfFunctionValues(GenerationArray, SumValues);

	for (unsigned i = 0; i < GENERATION; i++) {
		ParrentIndex[0][i]=(Selection(forSumStepSelection, SumValues));
		ParrentIndex[1][i]=(Selection(forSumStepSelection, SumValues));
		if (ParrentIndex[0][i] == ParrentIndex[1][i]) {
			if ((rand() / (RAND_MAX + 1.0) < 0.5)) {
				if ((rand() / (RAND_MAX + 1.0) < 0.5)) {
					ParrentIndex[0][i] = Selection(forSumStepSelection, SumValues);
				}
				else {
					ParrentIndex[1][i] = Selection(forSumStepSelection, SumValues);
				}
			}
		}
	}

	Crossover(ChildArray, GenerationArray, ParrentIndex);

	for(int i=0; i<2; i++)
	{
		for (int j=0; j<GENERATION; j++)
		{
			GenerationArray[i][j] = ChildArray[i][j];
		}
	}
}

double SumOfFunctionValues(double GenerationArray[3][GENERATION], double SumValues)
{
	SumValues = 0;
	for (int i = 0; i<GENERATION; i++)
	{
		SumValues = GenerationArray[0][i];
	}
	return SumValues;
}

void SumInSteps(double GenerationArray[3][GENERATION], double forSumStepSelection[GENERATION])//
{
	int inter = 0;
	for (int i = 0; i < GENERATION; i++) {
		inter += GenerationArray[2][i];
		forSumStepSelection[i] = inter;
	}
}

int Selection(double forSumStepSelection[GENERATION], double SumValues)//Метод рулетки.
{
	double randomFitnessToChooseParent = (float)(rand()) / RAND_MAX * (SumValues / 3);
	int firstIndex = 0;
	int lastIndex = GENERATION - 1;
	int middle = (int)((firstIndex + lastIndex) / 2);
	int parentIndex = INT_MIN;

	do {
		(randomFitnessToChooseParent > forSumStepSelection[middle]) ? firstIndex = middle : lastIndex = middle;
		middle = (int)((firstIndex + lastIndex) / 2);
		if (abs(firstIndex - lastIndex) == 1) {
			parentIndex = lastIndex;
		}
	} while ((parentIndex < 0) && (firstIndex <= lastIndex));
	return parentIndex;
}

//Куда преобразовываем, что преобразовываем, с помощью чего преобразовываем.
void Crossover(double ChildArray[2][GENERATION], double GenerationArray[3][GENERATION], int ParrentIndex[2][GENERATION])
{
	for (unsigned i = 0; i < GENERATION; i++) {
		if ((rand() / (RAND_MAX + 1.0)) > 0.6) {
			ChildArray[0][i] = GenerationArray[0][ParrentIndex[0][i]];
			ChildArray[1][i] = GenerationArray[1][ParrentIndex[1][i]];
		}
		else {
			if ((rand() / (RAND_MAX + 1.0)) < 0.6) {
				ChildArray[0][i] = GenerationArray[0][ParrentIndex[0][i]];
				ChildArray[1][i] = GenerationArray[1][ParrentIndex[1][i]];
			}
			else {
				ChildArray[0][i] = GenerationArray[0][ParrentIndex[0][i]];
				ChildArray[1][i] = GenerationArray[1][ParrentIndex[1][i]];
			}
		}
	}
	Mutation(ChildArray);
}

void Mutation(double ChildArray[2][GENERATION]) {
	for (unsigned i = 0; i < GENERATION; i++) {
		if ((rand() / (RAND_MAX + 1.0)) < 0.6) {
			if ((rand() / (RAND_MAX + 1.0)) < 0.5) {
				ChildArray[0][i] += 0.5;//0.1//0.5//0.2
				ChildArray[1][i] += 0.5;//0.1//0.5//0.2
			}
			else {
				ChildArray[0][i] -= 0.5;//0.7//0.5//0.6
				ChildArray[1][i] -= 0.5;//0.7//0.5//0.6
			}
		}
	}
}

void printGeneration(double GenerationArray[3][GENERATION])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < GENERATION; j++)
		{
			cout<<GenerationArray[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	
	//Массив многомерный для всего поколения.
	double GenerationArray[3][GENERATION];
	ChoiceParents(GenerationArray);

	//Массив дополнительный-для подсчета суммы функций с шагом один и дальнейшем применением в реализации селекции(методом рклетки).
	double forSumStepSelection[GENERATION];

	//Переменная-хранит сумму всех значений функции(Инициализируем нулем!).
	double SumValues=0;

	//Создание детей с использованием селекции, кросинговера и мутаций генов.
	double ChildArray[2][GENERATION];
	
	for (int i = 0; i < 2000; i++)
	{
		//Сортируем массив по возрастанию/убыванию.
		Sort(GenerationArray);
		//Счетчик суммы с единичным шагом для селекции(рулетки).
		SumInSteps(GenerationArray, forSumStepSelection);
		//Создаем потомков.
		CreateChildren(forSumStepSelection, SumValues, ChildArray, GenerationArray);
	}
	printGeneration(GenerationArray);
	//Округляем результат до целого.
	double result = GenerationArray[2][0];
	if (result>0) 
	{
		result = trunc(result);
	}
	else
	{
		result = floor(result);
	}

	cout << "Extreme Function(x,y)=" << result;
	return 0;
	system("pause");
}