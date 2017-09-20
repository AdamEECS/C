//
//  main.c
//  C programming
//
//  Created by san on 2017/9/20.
//  Copyright © 2017年 suzumiya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//
//创建两个单链表A、B,要求A、B 的元素按升序排列,输出单链表A、B,
//然后将A、B中相同的元素放在单链表C中，C也按升序排列，输出单链表C。


// interface

struct JMNode;
typedef struct JMNode JMList;
typedef int type;

struct JMNode {
    type element;
    JMList *next;
};



JMList *
JMListCreate(int *element, int numberOfElements) {
    assert(numberOfElements >= 0);
    
    JMList *list = malloc(sizeof(JMList));
    list->next = NULL;
    
    for(int i = numberOfElements - 1; i >= 0; i--) {
        JMList *n = malloc(sizeof(JMList));
        n->element = element[i];
        n->next = list->next;
        
        list->next = n;
    }
    
    return list;
}

void
JMListLog(JMList *list) {
    JMList *l = list->next;
    while(l != NULL) {
        printf("%d  ", l->element);
        l = l->next;
    }
    printf("\n");
}

void
JMListSort(JMList *list) {
    JMList *cusor = list->next;
    
    while(cusor != NULL) {
        JMList *l = cusor;
        JMList *min = l;
        
        while(l != NULL) {
            if(min->element > l->element) {
                min = l;
            }
            l = l->next;
        }
        type tmp = min->element;
        min->element = cusor->element;
        cusor->element = tmp;
        
        cusor = cusor->next;
    }
}

//JMList *
//JMListFindTail(JMList *list) {
//    JMList *l = list->next;
//    while(list != NULL) {
//        l = l->next;
//    }
//    return l;
//}
//
//void
//JMListAppendList(JMList *list, JMList *anotherList) {
//    JMList l = JMListFindTail(list);
//    l->next = anotherList->next;
//    free(anotherList);
//}

void
JMListInsert(JMList *list, type element) {
    JMList *n = malloc(sizeof(JMList));
    n->element = element;
    n->next = list->next;
    list->next = n;
}

JMList *
DisgustingAlgorithm(JMList *a, JMList *b) {
    JMList *c = JMListCreate(0, 0);
    
    a = a->next;
    b = b->next;
    while(a != NULL && b != NULL) {
        if(a->element < b->element) {
            a = a->next;
        } else if(a->element > b->element) {
            b = b->next;
        } else {
            JMListInsert(c, a->element);
            a = a->next;
            b = b->next;
        }
    }
    return c;
}

JMList *
DisgustingAlgorithm2(JMList *a, JMList *b) {
    JMList *c = JMListCreate(0, 0);
    
    a = a->next;
    b = b->next;
    while(a != NULL && b != NULL) {
        if(a->element < b->element) {
            JMListInsert(c, a->element);
            a = a->next;
        } else if(a->element > b->element) {
            JMListInsert(c, b->element);
            b = b->next;
        } else {
            JMListInsert(c, a->element);
            a = a->next;
            b = b->next;
        }
    }
    return c;
}

int main(int argc, const char * argv[]) {
    type data_a[] = {1, 2, 9, 4, 5, 11, 3};
    type data_b[] = {3, 5, 6, 7, 11, 8};
    
    JMList *A = JMListCreate(data_a, 7);
    JMList *B = JMListCreate(data_b, 6);
    
    // 要求A、B 的元素按升序排列
    JMListSort(A);
    JMListSort(B);
    
    // 输出单链表A、B
    JMListLog(A);
    JMListLog(B);
    
    // 然后将A、B中相同的元素放在单链表C中
    JMList *C = DisgustingAlgorithm(A, B);
    //    JMList *C = JMListAppendList(A, B);
    //    JMSet *s = JMSetCreateWithList(C);
    //    C = JMListFromSet(s);
    
    // C也按升序排列
    JMListSort(C);
    
    printf("求 A 和 B 的交：\n");
    // 输出单链表C
    JMListLog(C);
    
    // 然后将A、B并集的元素放在单链表D中
    JMList *D = DisgustingAlgorithm2(A, B);
    
    // D也按升序排列
    JMListSort(D);
    
    printf("求 A 和 B 的并：\n");
    // 输出单链表D
    JMListLog(D);

    return 0;
}
