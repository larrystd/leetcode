package main

import "fmt"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func InsertNode(root *TreeNode, val int) *TreeNode {
	if root == nil {
		return &TreeNode{Val: val}
	}

	if val < root.Val {
		root.Left = InsertNode(root.Left, val)
	} else if val > root.Val {
		root.Right = InsertNode(root.Right, val)
	}
	return root
}

func InOrderTraversal(root *TreeNode) []int {
	var result []int

	var inOrder func(*TreeNode)

	inOrder = func(node *TreeNode) {
		if node == nil {
			return
		}

		inOrder(node.Left)
		result = append(result, node.Val)
		inOrder(node.Right)
	}

	inOrder(root)
	return result
}

func main() {
	values := []int{5, 3, 7, 2, 4, 6, 8}
	var root *TreeNode
	for _, val := range values {
		root = InsertNode(root, val)
	}

	result := InOrderTraversal(root)
	fmt.Println(result)
}
