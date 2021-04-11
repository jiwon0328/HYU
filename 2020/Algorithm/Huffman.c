//2019000982_leejiwon_11802

#include<stdio.h>
#include<stdlib.h>

typedef struct node node;
struct node
{
   char *v;
   int cnt;
   node* next;
   node* left;
   node* right;
};

void push(int n);
int pop(void);
void addToSLL(node* cur);
node* findSmallest(void);
node* buildHuffmanTree(void);
//void showAll(void);
void showCode(void);
void inorderTraversal(node* cur);

node*head = 0;

int stack[100];
int top = -1;

int main(void)
{
    int n, s;
    scanf("%d", &n);
    
    char *ch = (char*) malloc(sizeof(char) * 4);
    int chNum;
    
    for(int i = 0; i < n; i++) {
        scanf("%s %d", ch, &chNum);
        
        node*newOne = (node*)malloc(sizeof(node));
        newOne->v = ch;
        newOne->cnt = chNum;
        newOne->left = newOne->right = newOne->next = 0;

        addToSLL(newOne);
    }
    
    scanf("%d", &s);
    printf("%d", s*3);
    
    node* tree = buildHuffmanTree();

    inorderTraversal(tree);

   return 0;
}

void push(int n) {
   top += 1;
   stack[top] = n;
}

int pop(void) {
   int result = stack[top];
   top -= 1;
   return result;
}

void addToSLL(node* cur) {
   if (head == 0) {
      head = cur;
      return;
   }

   node*temp = head;
   while (temp->next != 0) {
      temp = temp->next;
   }
   temp->next = cur;
}

node*findSmallest() {
   
   int short_num = 10000;
   node*short_node = head;

   if (head == 0) {
      return 0;
   }
   
   node*temp = head;
   while (temp != 0) {
      if (temp->cnt < short_num) {
         short_node = temp;
         short_num = temp->cnt;
      }
      temp = temp->next;
   }
   
   if (short_node == head) {
      head = head->next;
   }
   else {
      node*prev = head;
      while (prev->next != short_node)
      {
         prev = prev->next;
      }
      prev->next = short_node->next;
   }

   short_node->next = 0;
   return short_node;
}

node* buildHuffmanTree(void) {
   while (1) {
      node* first = findSmallest();   // 빈도수 제일 낮은 것을 뽑는다.
      node* second = findSmallest();

      if (second == 0) {
         return first;
      }

      node*newOne = (node*)malloc(sizeof(node));
      newOne->next = 0;
      newOne->left = first;
      newOne->right = second;
      newOne->cnt = first->cnt + second->cnt;

      addToSLL(newOne);   // 트리 전체를 구성원으로 넣는다.
   }
   
}

//void showAll() {
//   node*temp = head;
//   while (temp != 0) {
//      printf("%s : %d\n", temp->v, temp->cnt);
//      temp = temp->next;
//   }
//}

void showCode() {
   for (int i = top-1; i >= 0; i--) {
      printf("%d", stack[i]);
   }
   printf("\n");
}

void inorderTraversal(node* cur) {
   if (cur == 0) {
      pop();
      return;
   }
   push(0);
   inorderTraversal(cur->left);
   if (cur->left == 0 && cur->right == 0) {
      printf("%s : ",cur->v);
      showCode();
   }
   push(1);
   inorderTraversal(cur->right);
   pop();
}
