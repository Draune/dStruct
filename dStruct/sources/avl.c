#include "../headers/avl.h"

#define FIXED 1
#define NOT_FIXED 0
void fix(dAVL* avl,dNode* node);
void sort(dAVL* avl,dNode* node);
void rotate_right(dAVL* avl,dNode* top);
void rotate_left(dAVL* avl,dNode* top);
void set_high(dNode* node);
int get_diff_high(dNode* node);
int get_high(dNode* node);

dNode* find_replacement(dNode* node);
dNode* replace(dAVL* avl,dNode* node,dNode* replacement); // the output for sort

dAVL d_create_avl(int (*sort_test)(void*,void*)){
    dAVL avl;
    avl.start = NULL;
    avl.sort_test = sort_test;
    return avl;
}

void d_insert_avl(dAVL* avl,void* content){
    dNode* new = d_create_node(content);
    fix(avl,new);
    sort(avl,new);
}

dNode* d_find_node_avl(dAVL* avl,void* content){
    if(avl->start == NULL)
        return NULL;
    dNode* return_ = NULL;
    dNode* current = avl->start;
    while(current != NULL){
        if(avl->sort_test((void*)current->content,(void*)content)){
            return_ = current;
            current = current->right;
        }
        else
            current = current->left;
    }
    return return_;
}

void* d_find_avl(dAVL* avl,void* content){
    dNode* return_ = d_find_node_avl(avl,content);
    if(return_ == NULL)
        return NULL;
    return (void*)return_->content;
}

void* d_remove_node_avl(dAVL* avl,dNode* node){
    if(node == NULL)
        return NULL;
    
    sort(avl,replace(avl,node,find_replacement(node)));
    return d_destroy_node(node);
}

void* d_remove_avl(dAVL* avl,void* content){
    return (void*)d_remove_node_avl(avl,d_find_node_avl(avl,content));
}

void d_clear_avl(dAVL* avl,void (*free_content)(void*)){
    if(avl->start != NULL){
        dNode* more_on_right = avl->start;
        while(more_on_right->right != NULL)
            more_on_right = more_on_right->right;
        void* more_on_right_content = d_remove_node_avl(avl,more_on_right);
        while (avl->start != NULL){
            void* to_delete = d_remove_avl(avl,more_on_right_content);
            if(to_delete != NULL)
                free_content(to_delete);
        }
    }
}

void fix(dAVL* avl,dNode* node){
    if(avl->start == NULL)
        avl->start = node;
    else{
        dNode* current = avl->start;
        int fixed = NOT_FIXED;
        while(fixed != FIXED){
            if(avl->sort_test((void*)node->content,(void*)current->content)){
                if(current->left == NULL){
                    node->prev = current;
                    current->left = node;
                    fixed = FIXED;
                }
                else
                    current = current->left;
            }
            else{
                if(current->right == NULL){
                    node->prev = current;
                    current->right = node;
                    fixed = FIXED;
                }
                else
                    current = current->right;
            }
        }
    }
}

void sort(dAVL* avl,dNode* node){
    while(node != NULL){
        switch (get_diff_high(node)){
        case -2:// higher on left
            if(get_diff_high(node->left) == 1){// so higher on left then on right
                node = node->left;
                rotate_left(avl,node);
                set_high(node);
                node = node->prev->prev;
                rotate_right(avl,node);
            }
            else
                rotate_right(avl,node);
            break;
        case 2:// higher on right
            if(get_diff_high(node->right) == -1){// so higher on right then on left
                node = node->right;
                rotate_right(avl,node);
                set_high(node);
                node = node->prev->prev;
                rotate_left(avl,node);
            }
            else
                rotate_left(avl,node);
            break;
        case -1:
        case 0: // normal cases
        case 1:
            break;
        default:
            break;
        }
        set_high(node);
        node = node->prev;
    }
}

void rotate_right(dAVL* avl,dNode* top){
    dNode* left = top->left;

    if(top->prev != NULL){
        if(top->prev->left == top)
            top->prev->left = left;
        else
            top->prev->right = left;
    }
    else
        avl->start = left;
    left->prev = top->prev;

    if(left->right != NULL)
        left->right->prev = top;
    top->left = left->right;

    top->prev = left;
    left->right = top;
}

void rotate_left(dAVL* avl,dNode* top){
    dNode* right = top->right;

    if(top->prev != NULL){
        if(top->prev->left == top)
            top->prev->left = right;
        else
            top->prev->right = right;
    }
    else
        avl->start = right;
    right->prev = top->prev;

    if(right->left != NULL)
        right->left->prev = top;
    top->right = right->left;

    top->prev = right;
    right->left = top;
}

void set_high(dNode* node){
    node->count = (get_high(node->right) > get_high(node->left))? get_high(node->right):get_high(node->left);
    (node->count)++;
}

int get_diff_high(dNode* node){
    return get_high(node->right) - get_high(node->left);
}

int get_high(dNode* node){
    if(node == NULL)
        return 0;
    else
        return node->count;
}

dNode* find_replacement(dNode* node){
    if(node->right == NULL && node->left == NULL)
        return NULL;
    dNode* return_;
    if(node->right == NULL){
        return_ = node->left;
        if(return_->left != NULL)
            return_->left->prev = node;
        node->left = return_->left;

        if(return_->right != NULL)
            return_->right->prev = node;
        node->right = return_->right;
    }
    else if(node->left == NULL){
        return_ = node->right;
        if(return_->left != NULL)
            return_->left->prev = node;
        node->left = return_->left;

        if(return_->right != NULL)
            return_->right->prev = node;
        node->right = return_->right;
    }
    else{
        return_ = node->left;
        while(return_->right != NULL)
            return_ = return_->right;
        
        if(return_->prev->right == return_)
            return_->prev->right = return_->left;
        else
            return_->prev->left = return_->left;
        if(return_->left != NULL)
            return_->left->prev = return_->prev;
    }
    return return_;
}

dNode* replace(dAVL* avl,dNode* node,dNode* replacement){
    dNode* return_;
    if(node->prev != NULL){
        if(node->prev->left == node)
            node->prev->left = replacement;
        else 
            node->prev->right = replacement;
    }
    else
        avl->start = replacement;

    if(replacement == NULL)
        return_ = node->prev;
    else{
        return_ = replacement->prev;
        
        replacement->prev = node->prev;

        if(node->left != NULL)
            node->left->prev = replacement;
        replacement->left = node->left;

        if(node->right != NULL)
            node->right->prev = replacement;
        replacement->right = node->right;
    }
    return return_;
}