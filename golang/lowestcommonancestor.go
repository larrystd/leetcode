package main

import "fmt"

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func Construct(vals []int) *TreeNode {
	root := &TreeNode{Val: vals[0]}
	queue := make([]*TreeNode, 0)
	queue = append(queue, root)
	ids := 1
	for ids < len(vals) {
		node := queue[0]
		queue = queue[1:]

		node.Left = &TreeNode{Val: vals[ids]}
		queue = append(queue, node.Left)
		if ids+1 >= len(vals) {
			break
		}
		node.Right = &TreeNode{Val: vals[ids+1]}
		queue = append(queue, node.Right)
		ids += 2
	}
	return root
}

func PrintTree(root *TreeNode) []int {
	queue := make([]*TreeNode, 0)
	queue = append(queue, root)
	result := []int{}
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		result = append(result, node.Val)
		if node.Left != nil {
			queue = append(queue, node.Left)
		}
		if node.Right != nil {
			queue = append(queue, node.Right)
		}
	}
	return result
}

func GetTargetNode(root *TreeNode, val int) *TreeNode {
	if root == nil {
		return nil
	}
	if root.Val == val {
		return root
	}
	left := GetTargetNode(root.Left, val)
	right := GetTargetNode(root.Right, val)
	if left != nil {
		return left
	}
	if right != nil {
		return right
	}
	return nil
}

func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}
	if root == p || root == q {
		return root
	}
	left := lowestCommonAncestor(root.Left, p, q)
	right := lowestCommonAncestor(root.Right, p, q)
	if left != nil && right != nil {
		return root
	}
	if left != nil {
		return left
	}
	if right != nil {
		return right
	}
	return nil
}

func main() {
	vals := []int{3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4}
	var root *TreeNode
	root = Construct(vals)
	result := PrintTree(root)
	fmt.Println(result)

	p := GetTargetNode(root, 5)
	q := GetTargetNode(root, 1)
	fmt.Println(lowestCommonAncestor(root, p, q).Val)
}
