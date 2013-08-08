

// btree.h
// Rosen
// 2013-8-8

#ifndef BTREE_H_
#define BTREE_H_


//#define 

class CNodeData
{
public:
		CNodeData(){}
		~CNodeData(){}
private:
	char *m_data;
};

class CBtreeNode
{
public:
	static const int MAX_NODE = 4;	
	CBtreeNode(){}
	~CBtreeNode(){}
private:
	CBtreeNode *parent;
	CBtreeNode *ptr[MAX_NODE+1];
	NodeData	key[MAX_NODE+1];


};

class CResult
{
public:
	CResult(){}
	~CResult(){}
priveate:
	CBtreeNode *pt;
	int	index;		// 1..m index of key
	int retVal;		// return value for search function

};

#endif
