#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	int ht;//height of node
};
struct node* root = NULL;

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    // return the new node after rotation
    return right_child;
}

struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    // return the new node after rotation
    return left_child;
}

int balance_factor(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	return lh - rh;
}


int height (struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	if (lh > rh)
		return lh;
	return rh;
}


struct node* create_node(int data){
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	
	return new_node;
}

struct node* insert (struct node* root, int data){
	if(root == NULL){
		struct node* new_node = create_node(data);
		root = new_node;
	}
	else if ( data > root->data){
		root->right = insert(root->right, data);
		
		//if unbalanced, rotate!
		if (balance_factor(root) == -2){
			if (data > root->right->data){//case RR
				root = rotate_left(root);
			}
			else{ //case RL
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}			
		}		
	}
	else{
		root->left = insert(root->left, data);
		
		if (balance_factor(root) == 2){
			//CASE LL
			if (data < root->left->data){ 
				root = rotate_right(root);
			}
			//CASE LR
			else{
				root->left = rotate_left(root->left);
				root = rotate_right(root);

			}
		}
	}
	//get height of node
	root->ht = height(root);
	return root;
}


// inorder traversal of the tree
void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
// preorder traversal of the tree
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
 
// postorder traversal of the tree
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

struct node* find_min(struct node* root) {
    struct node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* delete_node(struct node* root, int data) {
    if (root == NULL) {
        return root; 
    }

    // Cari simpul yang akan dihapus
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } 
	else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } 
	else {
        if (root->left == NULL || root->right == NULL) {
            struct node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } 
			else { 
                *root = *temp; 
            }
            free(temp);
        } 
		else {
            struct node* temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }
    
    root->ht = height(root);
    int balance = balance_factor(root);

    // Jika tidak balance, maka rotate
    if (balance > 1) {
        if (balance_factor(root->left) >= 0) {
            // Kasus LL
            root = rotate_right(root);
        } 
		else {
            // Kasus LR
            root->left = rotate_left(root->left);
            root = rotate_right(root);
        }
    } 
	else if (balance < -1) {
        if (balance_factor(root->right) <= 0) {
            // Kasus RR
            root = rotate_left(root);
        } 
		else {
            // Kasus RL
            root->right = rotate_right(root->right);
            root = rotate_left(root);
        }
    }

    return root;
}

struct node* search(struct node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    // Jika nilai yang dicari lebih kecil dari nilai root, cari di subpohon kiri
    if (data < root->data) {
        return search(root->left, data);
    }

    // Jika nilai yang dicari lebih besar dari nilai root, cari di subpohon kanan
    return search(root->right, data);
}





int main() {
    // Menambahkan simpul ke pohon
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 17);
    root = insert(root, 8);
    root = insert(root, 6);

    printf("Before Deletion:\n");
    inorder(root);
    printf("\n");

  
//    root = delete_node(root, 10);
//    root = delete_node(root, 15);
//    root = delete_node(root, 20);
//    root = delete_node(root, 9);
//    root = delete_node(root, 5);
//    root = delete_node(root, 16);
    root = delete_node(root, 17);
//    root = delete_node(root, 8);
//    root = delete_node(root, 6);
    

    printf("After Deletion:\n");
    inorder(root);
    printf("\n");
    
    int key = 15;
    struct node* result = search(root, key);
    if (result != NULL) {
        printf("%d found in AVL.\n", key);
    } else {
        printf("%d can't be found in AVL.\n", key);
    }

    return 0;
}
