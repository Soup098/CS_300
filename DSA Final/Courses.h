#pragma once
#include <string>
#include <vector>


struct Course {
	string Id;
	string Name;
	vector<string> prereqs;


};

struct TreeNode {
	Course course;
	TreeNode* left;
	TreeNode* right;

	//default constructor
	TreeNode() {
		left = nullptr;
		right = nullptr;

	}
};	