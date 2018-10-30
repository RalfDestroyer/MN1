#pragma once
using namespace std;
#include <string>
#include <list>
class Tree
{
protected:
	class DecisionTreeNode;

	class ValidAnswer
	{
	public:
		string ans;
		DecisionTreeNode* son;
		ValidAnswer(string a, DecisionTreeNode* b) { ans = a; son = b; }
		~ValidAnswer() { delete son; };
	};

	class DecisionTreeNode
	{
	public:
		string value;
		bool isLeaf;
		DecisionTreeNode* father;
		list<ValidAnswer*> answersList;
		DecisionTreeNode(string val, DecisionTreeNode * father1 = NULL) { value = val; isLeaf = true; father = father1; }
		~DecisionTreeNode() {
			while ((this->answersList.size()) != 0)
				this->answersList.erase(this->answersList.begin()); 
		}
	};

	DecisionTreeNode *root;


private:
	DecisionTreeNode* searchQuestion(DecisionTreeNode *ptrNode, string val)
	{

		if (ptrNode->value == val)
			return ptrNode;

		DecisionTreeNode * ptrReturn = NULL;
		if (ptrNode->isLeaf == false)
		{
			list<ValidAnswer*>::iterator it = ptrNode->answersList.begin();
			for (; it != ptrNode->answersList.end(); it++)
			{
				if (searchQuestion((*it)->son, val) != NULL)
					ptrReturn = searchQuestion((*it)->son, val);
			}
		}
		return ptrReturn;
	}
	void deleteAllSubTree(DecisionTreeNode *);
	void printAll(DecisionTreeNode *);
	void postOrder(DecisionTreeNode *);
	void processPrivate(DecisionTreeNode *);
public:
	Tree() { root = NULL; }
	~Tree() {
		if (root != NULL)
			deleteAllSubTree(root);
	}
	void addRoot(string);
	bool addSon(string, string, string);
	void deleteSubTree(string);
	void printAllTree() { printAll(root); };
	void searchAndPrint(string);
	void process() { processPrivate(root); }
};

