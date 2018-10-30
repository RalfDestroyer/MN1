#include <iostream>
#include <list>
#include"Tree.h"
using namespace std;
class DecisionTreeNode;

void Tree::addRoot(string startQuestion)
{
	root = new DecisionTreeNode(startQuestion);
	return;
}

bool Tree::addSon(string question, string newAns, string nextQuestion)
{
	DecisionTreeNode * find = searchQuestion(root, question);
	DecisionTreeNode * ptrNextQuestion = new DecisionTreeNode(nextQuestion,find);
	if (find != NULL)
	{
		find->answersList.push_back(new ValidAnswer(newAns, ptrNextQuestion));
		find->isLeaf = false;
		return true;
	}
	return false;

}

void Tree::deleteSubTree(string question)
{
	DecisionTreeNode * find = searchQuestion(root, question);
	if (find != NULL)
		deleteAllSubTree(find);
	return;
}

void Tree::searchAndPrint(string question)
{
	DecisionTreeNode * find = searchQuestion(root, question);
	postOrder(find);
	return;
}

void Tree::deleteAllSubTree(DecisionTreeNode *node)
{
	list <ValidAnswer*>::iterator it = node->answersList.begin();
	for (; it != node->answersList.end(); it++)
	{
		deleteAllSubTree((*it)->son);
	}
	if (node->isLeaf == true) 
	{
		node->father->isLeaf = true;
		delete node;
	}
}

void Tree::printAll(DecisionTreeNode *node)
{
	cout << node->value << endl;
	if (node->isLeaf == false) 
	{
		list <ValidAnswer*>::iterator it = node->answersList.begin();
		for (; it != node->answersList.end(); it++)
		{
			cout << ": " << (*it)->ans << endl;
			cout << "   ";
			printAll((*it)->son);
		}
	}
	return;
}

void Tree::postOrder(DecisionTreeNode *node)
{
	if (node->father == NULL)
		cout << node->value << "=>";
	else
	{
		postOrder(node->father);
		cout << node->value;
		if (node->isLeaf == false)
			cout << "=>";
	}
	return;
}

void Tree::processPrivate(DecisionTreeNode *node)
{
	string userInput;
	cout << node->value << endl;
	if (node->isLeaf)
		return;
	cin >> userInput;
	list<ValidAnswer*>::iterator it = node->answersList.begin();
	for (; it != node->answersList.end(); it++)
	{
		if ((*it)->ans == userInput)
		{
			processPrivate((*it)->son);
		}
	}

}
