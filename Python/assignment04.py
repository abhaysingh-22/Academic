class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BST:
    def __init__(self):
        self.root = None

    # a) INSERT (handle duplicates)
    def insert(self, root, data):
        if root is None:
            return Node(data)
        if data < root.data:
            root.left = self.insert(root.left, data)
        elif data > root.data:
            root.right = self.insert(root.right, data)
        else:
            print(f"Duplicate entry {data} ignored.")
        return root

    # b) DELETE
    def delete(self, root, key):
        if root is None:
            return root
        if key < root.data:
            root.left = self.delete(root.left, key)
        elif key > root.data:
            root.right = self.delete(root.right, key)
        else:
            # Node with one or no child
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left
            # Node with two children: find inorder successor
            temp = self.min_value_node(root.right)
            root.data = temp.data
            root.right = self.delete(root.right, temp.data)
        return root

    def min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current

    # c) SEARCH
    def search(self, root, key):
        if root is None or root.data == key:
            return root
        if key < root.data:
            return self.search(root.left, key)
        return self.search(root.right, key)

    # d) DISPLAY TREE (Traversals)
    def inorder(self, root):
        if root:
            self.inorder(root.left)
            print(root.data, end=' ')
            self.inorder(root.right)

    def preorder(self, root):
        if root:
            print(root.data, end=' ')
            self.preorder(root.left)
            self.preorder(root.right)

    def postorder(self, root):
        if root:
            self.postorder(root.left)
            self.postorder(root.right)
            print(root.data, end=' ')

    # e) DEPTH OF TREE
    def depth(self, root):
        if root is None:
            return 0
        return 1 + max(self.depth(root.left), self.depth(root.right))

    # f) MIRROR IMAGE
    def mirror(self, root):
        if root:
            root.left, root.right = root.right, root.left
            self.mirror(root.left)
            self.mirror(root.right)

    # g) CREATE COPY
    def copy_tree(self, root):
        if root is None:
            return None
        new_node = Node(root.data)
        new_node.left = self.copy_tree(root.left)
        new_node.right = self.copy_tree(root.right)
        return new_node

    # h) DISPLAY PARENT AND CHILD NODES
    def display_parents(self, root):
        if root:
            if root.left:
                print(f"Parent {root.data} -> Left Child {root.left.data}")
            if root.right:
                print(f"Parent {root.data} -> Right Child {root.right.data}")
            self.display_parents(root.left)
            self.display_parents(root.right)

    # i) DISPLAY LEAF NODES
    def display_leaves(self, root):
        if root:
            if root.left is None and root.right is None:
                print(root.data, end=' ')
            self.display_leaves(root.left)
            self.display_leaves(root.right)

    # j) DISPLAY LEVEL WISE
    def level_order(self, root):
        if root is None:
            return
        queue = [root]
        while queue:
            node = queue.pop(0)
            print(node.data, end=' ')
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)


# ---- MAIN PROGRAM ----
bst = BST()

while True:
    print("\n--- BINARY SEARCH TREE OPERATIONS ---")
    print("1. Insert")
    print("2. Delete")
    print("3. Search")
    print("4. Display Traversals")
    print("5. Depth of Tree")
    print("6. Mirror Image")
    print("7. Copy Tree")
    print("8. Display Parent and Child Nodes")
    print("9. Display Leaf Nodes")
    print("10. Display Level-wise")
    print("0. Exit")

    choice = int(input("Enter your choice: "))

    if choice == 1:
        val = int(input("Enter value to insert: "))
        bst.root = bst.insert(bst.root, val)

    elif choice == 2:
        val = int(input("Enter value to delete: "))
        bst.root = bst.delete(bst.root, val)

    elif choice == 3:
        val = int(input("Enter value to search: "))
        res = bst.search(bst.root, val)
        print("Found!" if res else "Not found!")

    elif choice == 4:
        print("\nInorder:", end=' ')
        bst.inorder(bst.root)
        print("\nPreorder:", end=' ')
        bst.preorder(bst.root)
        print("\nPostorder:", end=' ')
        bst.postorder(bst.root)
        print()

    elif choice == 5:
        print("Depth of Tree:", bst.depth(bst.root))

    elif choice == 6:
        bst.mirror(bst.root)
        print("Mirror image created.")

    elif choice == 7:
        copied = bst.copy_tree(bst.root)
        print("Copy of tree (inorder):", end=' ')
        bst.inorder(copied)
        print()

    elif choice == 8:
        print("Parent and Child Nodes:")
        bst.display_parents(bst.root)

    elif choice == 9:
        print("Leaf Nodes:", end=' ')
        bst.display_leaves(bst.root)
        print()

    elif choice == 10:
        print("Level-wise Display:", end=' ')
        bst.level_order(bst.root)
        print()

    elif choice == 0:
        print("Exiting...")
        break

    else:
        print("Invalid choice! Try again.")
