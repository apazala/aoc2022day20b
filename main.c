#include <stdio.h>
#include <inttypes.h>

#define INPUT_FILENAME "input.txt"
#define DECKEY 811589153

typedef struct node
{
    int64_t value;
    struct node *left;
    struct node *right;   
} node;

node originalArr[5005];
node* workingArr[5005];
int lenArr;

void printList(node *start)
{
    node *curr = start;
    printf("%11" PRId64 " ", curr->value);
    for (curr = curr->right; curr != start; curr = curr->right)
    {
        printf("%11" PRId64 " ", curr->value);
    }
    printf("\n");
}

void swapThisAndRight(node *oldLeft)
{
    node* oldRight = oldLeft->right;

    oldLeft->right = oldRight->right;
    oldLeft->right->left = oldLeft;
    oldRight->right = oldLeft;
    oldRight->left = oldLeft->left;
    oldRight->left->right = oldRight;
    oldLeft->left = oldRight;
}



int main()
{
    FILE *pf = fopen(INPUT_FILENAME, "r");
    if (!pf)
    {
        fprintf(stderr, "Can't open input file: %s.\n", INPUT_FILENAME);
        return 1;
    }

    int value;
    fscanf(pf, "%d", &value); //First 
    originalArr[lenArr].value = value;
    originalArr[lenArr].value*=DECKEY;
    lenArr++;
    while (fscanf(pf, "%d", &value) == 1)
    {
        originalArr[lenArr].value = value;
        originalArr[lenArr].value*=DECKEY;
        originalArr[lenArr].left = &originalArr[lenArr-1];
        originalArr[lenArr-1].right = &originalArr[lenArr];
        lenArr++;
    }
    fclose(pf);

    originalArr[lenArr-1].right = &originalArr[0];
    originalArr[0].left = &originalArr[lenArr-1];

    for(int ktimes = 0; ktimes < 10; ktimes++)
    {
        for(node *curr = originalArr, *endArr = originalArr + lenArr; curr != endArr; curr++)
        {
            int defactoMove = (int)(curr->value%(lenArr-1));
            if(defactoMove < 0){
                for(int i = defactoMove; i < 0; i++)
                    swapThisAndRight(curr->left);
            }else{
                for(int i = 0; i < defactoMove; i++)
                    swapThisAndRight(curr);
            }
        }

        //printList(&originalArr[0]);
    }


    node *pnode = &originalArr[0];
    while (pnode->value != 0)
    {
        pnode = pnode->right;
    }
    
    for(int i = 0; i < lenArr; i++){
        workingArr[i] = pnode;
        //printf("%4d ", pnode->value);
        pnode = pnode->right;
    }

    int position = 0;
    int64_t sum = 0;
    for(int i = 0; i < 3; i++)
    {
        position = (position+1000)%lenArr;
        sum+=workingArr[position]->value;
    }

    printf("%" PRId64 "\n", sum);
}
