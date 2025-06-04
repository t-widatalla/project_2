#include <iostream>
#include <cstdlib>
using namespace std;

enum enLevel { easy = 1, medium = 2, hard = 3, mixLevel = 4 };
enum enOperation { add = 1, sub = 2, mul = 3, divOp = 4, mix = 5 };

struct stQuizGen {
	int firstNum = 1;
	int secNum = 1;
	enOperation op;
	char operationType;
	int playerAnswer;
	int rightAnswer;
	string result;
};
struct stGameInfo
{
	short howManyQuestions;

	enLevel leve;
	string levelName;
	enOperation operationType;
	string operation;

	short numberOfRightAnswers;
	short numberOfWrongAnswers;
};

int randomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

enOperation randomOperation(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return (enOperation)randNum;
}

int howManyQuestions()
{
	int questions;
	cout << "enter how many question do you want to answer\n";
	cin >> questions;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "invalid number, enter a valid number\n";
		cin >> questions;
	}

	return questions;
}

char operationSymbol(enOperation choice)
{
	char arrOperation[4] = { '+', '-', '*', '/' };
	return arrOperation[choice - 1];
}
void printQuestion(stQuizGen quiz)
{
	cout << quiz.firstNum << "\n";
	cout << quiz.secNum << " " << quiz.operationType << endl;
	cout << "__________\n";
}

int enterAnswer(stQuizGen quiz)
{
	cout << "\n";
	cin >> quiz.playerAnswer;
	return quiz.playerAnswer;
}



int operation(enOperation operation, stQuizGen quiz)
{
	switch (operation)
	{
	case enOperation::add:
		return quiz.firstNum + quiz.secNum;
		break;

	case enOperation::sub:
		return quiz.firstNum - quiz.secNum;
		break;

	case enOperation::mul:
		return quiz.firstNum * quiz.secNum;
		break;

	case enOperation::divOp:
		return quiz.firstNum / quiz.secNum;
		break;
	}
}

int getRightAnswer(enOperation operation1 ,stQuizGen quiz)
{
	quiz.rightAnswer = operation(operation1, quiz);
	return quiz.rightAnswer;
}

string compareAnswers(stQuizGen quiz)
{
	if (quiz.playerAnswer == quiz.rightAnswer)
	{
		system("color 2F");
		return "right answer :-)";
	}

	else
	{
		system("color 4F");
		cout << "\a";
		return"wrong answer :-(";
	}
}

string levelName(enLevel level)
{
	string arrLevel[4] = { "easy", "medium", "hard", "mix" };
	return arrLevel[level - 1];
}

string operationName(enOperation operationName)
{
	string arrOperation[5] = { "add","sub","multiplication","division","mix" };
	return arrOperation[operationName - 1];
}

stGameInfo fillGameInfo(short howManyQuestions, enLevel leven, enOperation type, short rightAnswers, short wrongAnswers)
{
	stGameInfo info;
	info.howManyQuestions = howManyQuestions;
	info.leve = leven;
	info.levelName = levelName(leven);
	info.operationType = type;
	info.operation = operationName(type);
	info.numberOfRightAnswers = rightAnswers;
	info.numberOfWrongAnswers = wrongAnswers;

	return info;
}

enLevel enterLevel()
{
	int level;
	do
	{
		cout << "enter your question level [1] easy, [2] medium, [3] hard, [4] mix\n";
		cin >> level;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "enter a valid number\n";
			cin >> level;
		}

	} while (level < 1 || level >4);

	return (enLevel)level;
}

enOperation enterOperation()
{
	int operation;
	do
	{
		cout << "enter operation type [1] add, [2] sub, [3] mul, [4] div, [5] mix\n";
		cin >> operation;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "invalid choice, please enter a valid choice\n";
			cin >> operation;
		}

	} while (operation < 1 || operation > 5);

	return (enOperation)operation;
}

int difficulty(enLevel level)
{
	switch (level)
	{
	case enLevel::easy:
		return randomNumber(1, 10);
		break;

	case enLevel::medium:
		return randomNumber(11, 99);
		break;

	case enLevel::hard:
		return randomNumber(100, 1000);
		break;

	case enLevel::mixLevel:
		return randomNumber(1, 1000);
		break;
	}

}

enOperation chooseOperation(enOperation type)
{
	switch(type)
	{
	case enOperation::add:
		return (enOperation)1;
		break;

	case enOperation::sub:
		return enOperation(2);
		break;

	case enOperation::mul:
		return (enOperation)3;
		break;

	case enOperation::divOp:
		return (enOperation)4;
		break;

	case enOperation::mix:
		return (enOperation)randomNumber(1, 4);
		break;
	}

}
stGameInfo playGame(enOperation operation, enLevel level, int howManyQuestions)
{
	stQuizGen quiz;

	int rightAnswers = 0, wrongAnswers = 0;
	for (int question = 1; question <= howManyQuestions; question++)
	{
		cout << "\n";
		cout << "Question [" << question << "/" << howManyQuestions << "]\n";
		quiz.firstNum = difficulty(level);
		quiz.secNum = difficulty(level);
		quiz.op = chooseOperation(operation);
		quiz.operationType = operationSymbol(quiz.op);

		printQuestion(quiz);
		quiz.playerAnswer = enterAnswer(quiz);
		quiz.rightAnswer = getRightAnswer(quiz.op, quiz);
		quiz.result = compareAnswers(quiz);
		cout << quiz.result << "\n";
		
		if (quiz.result == "right answer :-)") rightAnswers++;
		else
		{
			cout << "right answer is : " << quiz.rightAnswer << "\n";
			wrongAnswers++;
		}

	}

	return fillGameInfo(howManyQuestions, level, operation, rightAnswers, wrongAnswers);
}



void FinalResultScreen(stGameInfo game)
{
	string result = "";
	if (game.numberOfRightAnswers > game.numberOfWrongAnswers) result = "PASS :-)";
	else result = "FAIL :-(";
	cout << "\n_______________________________\n\n";
	cout << " final result is :" << result << endl;
	cout << "_______________________________\n";
}


void printGameResults(stGameInfo game)
{
	cout << "\n";
	cout << "questions : " << game.howManyQuestions << endl;
	cout << "question level : " << game.levelName << endl;
	cout << "Operation : " << game.operation << endl;
	cout << "number of right ansewrs : " << game.numberOfRightAnswers << endl;
	cout << "number of wrong answers : " << game.numberOfWrongAnswers << endl;
	cout << "\n_______________________________\n";
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame()
{
	char playAgain = 'Y';

	do
	{
		resetScreen();
		stGameInfo game = playGame(enterOperation(),enterLevel(),howManyQuestions());
		FinalResultScreen(game);
		printGameResults(game);


		cout << " \ndo you want to play again? Y or N\n";
		cin >> playAgain;

	} while (playAgain == 'y' || playAgain == 'Y');



}

int main()
{
	srand((unsigned)time(NULL));

	startGame();


	return 0;
}