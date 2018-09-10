import random

# Python program to demonstrate delete operation
# in binary search tree
 
# A Binary Tree Node
class Node:
 
	# Constructor to create a new node
	def __init__(self, key):
		self.key = key 
		self.left = None
		self.right = None

	def __str__(self):
		res = "Val: " + str(self.key)
		if self.haveLeftChild():
			res = res + ". Left: " + str(self.left.key)
		if self.haveRightChild():
			res = res + ". Right: " + str(self.right.key)
			
		return res

	def haveLeftChild(self):
		if self.left is None:
			return False
		return True

	def haveRightChild(self):
		if self.right is None:
			return False
		return True


def findAt(parent, value):
	# Base Cases: parent node is null or key is present at parent node
	if parent == None:
		return None

	if parent.key == value:
		return parent
		
	if parent.key > value:
		# Key is smaller than root's key
		return findAt(parent.left, value)
	elif parent.key < value:
		# Key is greater than root's key
		return findAt(parent.right, value)
		
 
# A utility function to do inorder traversal of BST
def inorder(root):
	if root is not None:
		inorder(root.left)
		print(root),
		inorder(root.right)
 
 
# A utility function to insert a new node with given key in BST
def insert( node, key):
 
	# If the tree is empty, return a new node
	if node is None:
		return Node(key)
 
	# Otherwise recur down the tree
	if key < node.key:
		node.left = insert(node.left, key)
	else:
		node.right = insert(node.right, key)
 
	# return the (unchanged) node pointer
	return node
 
# Given a non-empty binary search tree, return the node
# with minum key value found in that tree. Note that the
# entire tree does not need to be searched 
def minValueNode( node):
	current = node
 
	# loop down to find the leftmost leaf
	while(current.left is not None):
		current = current.left 
 
	return current 
 
# Given a binary search tree and a key, this function
# delete the key and returns the new root
def deleteNode(root, key):
 
	# Base Case
	if root is None:
		return root 
 
	# If the key to be deleted is similiar than the root's
	# key then it lies in  left subtree
	if key < root.key:
		root.left = deleteNode(root.left, key)
 
	# If the kye to be delete is greater than the root's key
	# then it lies in right subtree
	elif(key > root.key):
		root.right = deleteNode(root.right, key)
 
	# If key is same as root's key, then this is the node
	# to be deleted
	else:
		 
		# Node with only one child or no child
		if root.left is None :
			temp = root.right 
			root = None
			return temp 
			 
		elif root.right is None :
			temp = root.left 
			root = None
			return temp
 
		# Node with two children: Get the inorder successor
		# (smallest in the right subtree)
		temp = minValueNode(root.right)
 
		# Copy the inorder successor's content to this node
		root.key = temp.key
 
		# Delete the inorder successor
		root.right = deleteNode(root.right , temp.key)
 
 
	return root 
 
# Driver program to test above functions
""" Let us create following BST
			  5
		   /     \
		  3       7
		 /  \    /  \
	   2    4   6    8 """
 
root = None

random_array = random.sample(range(2, 9), 7)
for item in random_array:
	root = insert(root, item)

print("Inorder traversal of the given tree")
inorder(root)
 
node = findAt(root, 3)
print(" - Find 3: " + str(node))
 
# This code is contributed by Nikhil Kumar Singh(nickzuck_007)

# TODO: delete node, why not stable when create 