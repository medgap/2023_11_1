#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;    
}TreeNode;

typedef struct StackNode{
    TreeNode* data;
    struct StackNode* next;
}StackNode;

StackNode* initStack() {
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

void createTree(TreeNode** tree,char* data,int* index){
    char ch = data[*index];
    (*index)++;
    if(ch == '#'){
        *tree = NULL;
    }
    else{
        *tree = (TreeNode*)malloc(sizeof(TreeNode));
        (*tree)->data = ch;
        createTree(&((*tree)->lchild),data,index);
        createTree(&((*tree)->rchild),data,index);
    }
}

int isEmpty(StackNode* s){
    if(s->next == NULL)
        return 1;
    return 0;
}

//出栈
StackNode* pop(StackNode* s){
    if(isEmpty(s)){
        return NULL;
    }
    else{
        StackNode* node = s->next;
        s->next = node->next;
        return node;
    }
}

//进栈
void push(StackNode* s,TreeNode* data){
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = data;
    node->next = s->next;
    s->next = node;
}

void preOrder(TreeNode* T){
    TreeNode* node = T;
    StackNode* s = initStack();
    while(!isEmpty(s) || node){
        if(node){
            printf("%c ",node->data);
            push(s,node);
            node = node->lchild;
        }
        else{
            node = pop(s)->data;
            node = node->rchild;
        }
    }
}

void inOrder(TreeNode* T){
    TreeNode* node = T;
    StackNode* s = initStack();
    while(!isEmpty(s) || node){
        if(node){
            push(s,node);
            node = node->lchild;
        }
        else{
            node = pop(s)->data;
            printf("%c ",node->data);
            node = node->rchild;
        }
    }
}

int main(int argc,char* argv[]){
    TreeNode* t;
    int index = 0;
    createTree(&t,"ABD##E##CF##G##",&index);
    preOrder(t);
    printf("\n");
    inOrder(t);
    printf("\n");
    return 0;
}